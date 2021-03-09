'''
Small assembler to patch specific instructions in a file.
Supported instructions:
    addiu
    lui
    lb
    lh
    lw
    lbu
    lhu
    sb
    sh
    sw
Use: python3 patchinstr.py target.zovl patch.txt
patch text file format:
80XXXXXX [base address of start of file, this is subtracted from all addresses]
[must be as first line, value may be 0 to not change addresses below]
80YYYYYY lui t6 0x1 [commas, dollar signs optional]
80ZZZZZZ addiu $v0, $t1, -12345
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
    regs = ['zero', 'at', 'v0', 'v1', 'a0', 'a1', 'a2', 'a3',
        't0', 't1', 't2', 't3', 't4', 't5', 't6', 't7',
        's0', 's1', 's2', 's3', 's4', 's5', 's6', 's7',
        't8', 't9', 'k0', 'k1', 'gp', 'sp', 's8', 'ra']
    meminstr = {'lb': 0x80, 'lh': 0x84, 'lw': 0x8C, 'lbu': 0x90, 'lhu': 0x94, 
        'sb': 0xA0, 'sh': 0xA4, 'sw': 0xAC}
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
        if regnum >= 26 or (regnum == 0 and dest):
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
        assert len(toks) in [4, 5]
        addr = int(toks[0], 16) - baseaddr
        assert addr >= 0 and addr < len(data) and (addr & 3) == 0
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
        assert value >= -0x8000 and value < 0x8000
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
