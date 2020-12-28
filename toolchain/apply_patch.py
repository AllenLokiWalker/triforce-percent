import sys

# Not actually needed for the toolchain currently--used to check that 
# the patch creation was correct.

def applypatch(orig, pat, o):
    origd = orig.read()
    patd = pat.read()
    outd = b''
    origptr = 0
    patptr = 0
    while True:
        assert patptr <= len(patd) - 2
        skipcount = patd[patptr]
        writecount = patd[patptr+1]
        patptr += 2
        if skipcount == 0 and writecount == 0:
            break
        assert origptr + skipcount <= len(origd)
        for i in range(skipcount):
            outd += bytes([origd[origptr+i]])
        origptr += skipcount
        assert origptr + writecount <= len(origd)
        assert patptr + writecount + 2 <= len(patd)
        for i in range(writecount):
            outd += bytes([patd[patptr+i]])
        origptr += writecount
        patptr += writecount
    assert patptr == len(patd)
    while origptr < len(origd):
        outd += bytes([origd[origptr]])
        origptr += 1
    assert len(origd) == len(outd)
    o.write(outd)

if __name__ == '__main__':
    assert len(sys.argv) == 4
    assert sys.argv[2].endswith('.pat')
    with open(sys.argv[1], 'rb') as orig, open(sys.argv[2], 'rb') as pat, open(sys.argv[3], 'wb') as o:
        applypatch(orig, pat, o)
