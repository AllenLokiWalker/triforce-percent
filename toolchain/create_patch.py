import sys

def patchfull(i, o):
    ind = i.read()
    inptr = 0
    outd = b''
    while inptr < len(ind):
        bthistime = min(255, len(ind)-inptr)
        outd += bytes([0, bthistime]) + ind[inptr:inptr+bthistime]
        inptr += bthistime
    outd += bytes([0, 0])
    o.write(outd)

if __name__ == '__main__':
    if sys.argv[1].endswith('full'):
        assert(sys.argv[3].endswith('.pat'))
        with open(sys.argv[2], 'rb') as i, open(sys.argv[3], 'wb') as o:
            patchfull(i, o)
    else:
        print('Differential patching not yet supported!')
        sys.exit(1)
 
