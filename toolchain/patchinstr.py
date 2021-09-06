'''
Small assembler to patch specific instructions in a file.
Supported instructions:
    addiu
    lui
    lb, lh, lw, lbu, lhu, sb, sh, sw
    j, jal
    beq, bne
    nop
Use: python3 patchinstr.py target.zovl patch.txt [ldfile1.ld ldfile2.ld ...]
patch text file format:

80XXXXXX [base address of start of file, this is subtracted from all addresses]
[must be as first line, value may be 0 to not change addresses below]
!00VVVVVV [optional: offset of start of reloc table. Value at this offset is
    a u32 giving the number of relocs. The reloc table itself starts at the
    next word.]

80YYYYYY lui t6 0x1 [commas, dollar signs optional]
80ZZZZZZ addiu $v0, $t1, %hi(symbol) [symbol is taken from one of the input ld files]
80WWWWWW lb $v1, %lo(symbol)(s3) [hi and lo supported with signed immediate]
!80UUUUUU sw t2, 0x2222(t3) [! means null the reloc entry for this instruction]

'''
import sys

symbols = {}

def loadsymbols(ldfile):
    global symbols
    for l in ldfile:
        l = l.strip()
        if not l: continue
        if l[-1] != ';': continue
        l = l[:-1]
        toks = l.split(' ')
        if len(toks) != 3: continue
        if toks[1] != '=': continue
        if toks[0] in symbols:
            raise RuntimeError('Multiple definition of ' + toks[0])
        sym = toks[0]
        addr = int(toks[2], 0)
        print('Loaded symbol ' + sym + ' = ' + hex(addr))
        symbols[sym] = addr

def patchinstr(data, patchfile):
    global symbols
    data = bytearray(data)
    baseaddr = None
    relocaddr = None
    numreloc = 0
    regs = ['zero', 'at', 'v0', 'v1', 'a0', 'a1', 'a2', 'a3',
        't0', 't1', 't2', 't3', 't4', 't5', 't6', 't7',
        's0', 's1', 's2', 's3', 's4', 's5', 's6', 's7',
        't8', 't9', 'k0', 'k1', 'gp', 'sp', 's8', 'ra']
    meminstr = {'lb': 0x80, 'lh': 0x84, 'lw': 0x8C, 'lbu': 0x90, 'lhu': 0x94, 
        'sb': 0xA0, 'sh': 0xA4, 'sw': 0xAC}
    jumpinstr = {'beq': 0x10, 'bne': 0x14}
    def getreg(tok, dest=True):
        tok = tok.lower()
        if tok[0] == '$':
            tok = tok[1:]
        if tok[-1] == ',':
            tok = tok[:-1]
        try:
            regnum = regs.index(tok)
        except ValueError:
            raise RuntimeError('Unknown register ' + tok)
        if regnum in [26, 27, 28, 30] or (regnum == 0 and dest):
            raise RuntimeError('You should not be using register ' + tok)
        return regnum
    for l in patchfile:
        l = l.strip()
        if not l or l.startswith('#') or l.startswith('//'):
            continue
        toks = [t for t in l.split(' ') if t]
        if baseaddr is None:
            assert len(toks) == 1
            baseaddr = int(toks[0], 16)
            assert baseaddr >= 0 and baseaddr <= 0xFFFFFFFF
            print('baseaddr: ' + hex(baseaddr))
            continue
        doreloc = False
        if toks[0][0] == '!':
            toks[0] = toks[0][1:]
            if relocaddr is None:
                assert len(toks) == 1
                relocaddr = int(toks[0], 16)
                assert relocaddr >= 0 and relocaddr < len(data) and (relocaddr & 3) == 0
                numreloc = int.from_bytes(data[relocaddr:relocaddr+4], 'big')
                assert numreloc >= 0 and numreloc < 0x2000 # Link is 0xD09
                assert relocaddr + (numreloc * 4) <= len(data)
                relocaddr += 4
                print('reloc table: ' + hex(relocaddr) + ', ' + str(numreloc) + ' relocs')
                continue
            doreloc = True
        assert len(toks) >= 2
        addr = int(toks[0], 16) - baseaddr
        assert addr >= 0 and addr < len(data) and (addr & 3) == 0
        if doreloc:
            for r in range(numreloc):
                rta = relocaddr + r*4
                offset = int.from_bytes(data[rta+1:rta+4], 'big')
                if offset == addr:
                    data[rta:rta+4] = bytes([0]*4)
                    print('Nulled reloc for ' + hex(addr) + ' at ' + hex(rta))
                    break
            else:
                raise RuntimeError('Could not find reloc for ' + hex(addr))
        if toks[1] == 'nop':
            assert len(toks) == 2
            data[addr:addr+4] = bytes([0]*4)
        elif toks[1] in ['j', 'jal']:
            assert len(toks) == 3
            sym = toks[2]
            if sym not in symbols:
                raise RuntimeError('Symbol ' + sym + ' not defined in any input linker files')
            symaddr = symbols[sym]
            instr = 0x08000000 if toks[1] == 'j' else 0x0C000000
            instr |= (symaddr >> 2) & 0x03FFFFFF
            data[addr:addr+4] = instr.to_bytes(4, 'big')
        elif toks[1] in jumpinstr:
            assert len(toks) == 5
            rs = getreg(toks[2], False)
            rt = getreg(toks[3], False)
            branchaddr = int(toks[4], 16) - baseaddr
            assert branchaddr >= 0 and branchaddr < len(data) and (branchaddr & 3) == 0
            branchoff = (branchaddr - (addr + 4)) >> 2
            if branchoff < 0:
                branchoff += 0x10000
            assert branchoff >= 0 and branchoff <= 0xFFFF
            instr = (jumpinstr[toks[1]] << 24) | (rs << 21) | (rt << 16) | branchoff
            data[addr:addr+4] = instr.to_bytes(4, 'big')
        else:
            # Immediate/offset instructions
            relreg = None
            if toks[-1][-1] == ')' and toks[-1][-4] == '(' and toks[-1][-3:-1] in regs:
                relreg = getreg(toks[-1][-3:-1])
                toks[-1] = toks[-1][:-4]
            if toks[-1][0] == '%' and toks[-1][1:3] in ['hi', 'lo'] and toks[-1][3] == '(' and toks[-1][-1] == ')':
                ishi = toks[-1][1:3] == 'hi'
                sym = toks[-1][4:-1]
                if sym not in symbols:
                    raise RuntimeError('Symbol ' + sym + ' not defined in any input linker files')
                symaddr = symbols[sym]
                if symaddr & 0x00008000:
                    hival = (symaddr >> 16) + 1
                    loval = (symaddr & 0xFFFF) - 0x10000
                else:
                    hival = symaddr >> 16
                    loval = symaddr & 0xFFFF
                if hival & 0x8000:
                    hival -= 0x10000
                value = hival if ishi else loval
            else:
                value = int(toks[-1], 0)
                if value >= 0x8000:
                    value -= 0x10000
            if value < -0x8000 or value >= 0x8000:
                raise RuntimeError('Immediate/offset value ' + hex(value) + ' out of range in ' + l)
            data[addr+2:addr+4] = value.to_bytes(2, 'big', signed=True)
            if toks[1] == 'lui':
                assert len(toks) == 4
                reg = getreg(toks[2])
                topval = 0x3C00 | reg
            elif toks[1] == 'addiu':
                assert len(toks) == 5
                rt = getreg(toks[2])
                rs = getreg(toks[3], False)
                topval = 0x2400 | (rs << 5) | rt
            elif toks[1] in meminstr:
                assert len(toks) == 4
                assert relreg is not None
                rt = getreg(toks[2])
                topval = (meminstr[toks[1]] << 8) | (relreg << 5) | rt
            else:
                raise RuntimeError('Unknown instruction ' + toks[1])
            data[addr:addr+2] = topval.to_bytes(2, 'big')
        print(hex(addr) + ": " + data[addr:addr+4].hex())
    return data

if __name__ == '__main__':
    assert len(sys.argv) >= 3
    assert sys.argv[2].endswith('.txt')
    for ldf in sys.argv[3:]:
        with open(ldf, 'r') as ldfile:
            loadsymbols(ldfile)
    with open(sys.argv[1], 'rb') as datafile, open(sys.argv[2], 'r') as patchfile:
        data = datafile.read()
        data = patchinstr(data, patchfile)
    with open(sys.argv[1], 'wb') as datafile:
        datafile.write(data)
