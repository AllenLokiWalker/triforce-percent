'''
Patch specific instructions in a file which originally loaded values from memory
to instead load a constant value to the register.
Use: python3 patchinstr.py target.zovl patch.txt
patch text file format:
80XXXXXX [base address of start of file, this is subtracted from all addresses]
[must be as first line, value may be 0 to not change addresses below]
80YYYYYY t6 0x1 [replace the instruction at Y with `addiu $t6, $zero, 1`]
80ZZZZZZ v0 -12345 [replace the instruction at Z with `addiu $v0, $zero, -12345`]
'''
import sys

def patchinstr(data, patchfile):
    data = bytearray(data)
    baseaddr = None
    regs = ['zero', 'at', 'v0', 'v1', 'a0', 'a1', 'a2', 'a3',
        't0', 't1', 't2', 't3', 't4', 't5', 't6', 't7',
        's0', 's1', 's2', 's3', 's4', 's5', 's6', 's7',
        't8', 't9', 'k0', 'k1', 'gp', 'sp', 's8', 'ra']
    for l in patchfile:
        l = l.strip()
        if not l or l.startswith('#') or l.startswith('//'):
            continue
        toks = l.split(' ')
        if baseaddr is None:
            assert len(toks) == 1
            baseaddr = int(toks[0], 16)
            assert baseaddr >= 0 and baseaddr <= 0xFFFFFFFF
            print('baseaddr: ' + hex(baseaddr))
            continue
        assert len(toks) == 3
        addr = int(toks[0], 16) - baseaddr
        assert addr >= 0 and addr < len(data) and (addr & 3) == 0
        reg = toks[1].lower()
        regnum = regs.index(reg)
        if regnum == 0 or regnum >= 26:
            raise RuntimeError('There are no known situations in which it is correct to be patching a load to register ' + reg)
        value = int(toks[2], 0)
        assert value >= -0x8000 and value < 0x8000
        data[addr+0] = 0x24
        data[addr+1] = regnum
        data[addr+2:addr+4] = value.to_bytes(2, 'big', signed=True)
        print(hex(addr) + ": " + data[addr:addr+4].hex())
    return data

if __name__ == '__main__':
    assert len(sys.argv) == 3
    assert sys.argv[2].endswith('.txt')
    with open(sys.argv[1], 'rb') as datafile, open(sys.argv[2], 'r') as patchfile:
        data = datafile.read()
        data = patchinstr(data, patchfile)
    with open(sys.argv[1], 'wb') as datafile:
        datafile.write(data)
