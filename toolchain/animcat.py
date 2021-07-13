'''
Concatenate animations from bin files according to anim.txt.
Output:
- a bin file containing all the animations
- a .c file containing an animation header table of z64_animation_entry_link_t
- a .out.ld file containing the end address
'''
import sys, os, glob

baseaddr = None
with open('anim.out.ld', 'r') as ldfile:
    for l in ldfile:
        l = l.strip()
        if not l: continue
        if l[-1] != ';': continue
        l = l[:-1]
        toks = l.split(' ')
        if len(toks) != 3: continue
        if toks[1] != '=': continue
        if toks[0] != 'anim_START': continue
        baseaddr = int(toks[2], 0)
        break
if not baseaddr:
    print('Could not find anim_START in anim.out.ld')

class AnimInfo():
    def __init__(self, filepath, frames, addr):
        self.filepath, self.frames, self.addr = filepath, frames, addr
        print(hex(addr) + ': ' + str(self.frames) + ' frames: ' + self.filepath)

animinfo = []
curaddr = baseaddr
binfiles = glob.glob('*.bin')
with open('anim.txt', 'r') as txtfile:
    for l in txtfile:
        l = l.strip()
        if not l: continue
        if l[0] == '#': continue
        matchfiles = list(filter(lambda x: l in x, binfiles))
        if len(matchfiles) == 0:
            raise RuntimeError('Could not find animation matching ' + l)
        if len(matchfiles) > 1:
            raise RuntimeError('Multiple animations match ' + l 
                + ', maybe you did not delete the old one when changing animation length')
        binfile = matchfiles[0]
        frames = binfile[binfile.rindex('_')+1:-4]
        if not frames.isnumeric():
            raise RuntimeError('Error with anim frame count ' + frames)
        frames = int(frames)
        size = os.path.getsize(binfile)
        assert size % 0x86 == 0
        animinfo.append(AnimInfo(binfile, frames, curaddr))
        curaddr += size

if len(animinfo) == 0:
    raise RuntimeError('No animations found')

with open('anim.bin', 'wb') as binout:
    for a in animinfo:
        with open(a.filepath, 'rb') as f:
            binout.write(f.read())
    if (curaddr & 0xF) != 0:
        oldcuraddr = curaddr
        curaddr = (curaddr + 15) & 0xFFFFFFF0
        binout.write(bytes([0] * (curaddr - oldcuraddr)))
    
with open('anim.c', 'w') as cout:
    cout.write('LinkAnimationHeader linkAnimPatchTable[' 
        + str(len(animinfo)) + '] = {\n')
    for a in animinfo:
        cout.write('    {{' + str(a.frames) + '}, ' + hex(a.addr) + '},\n')
    cout.write('};\n')

with open('anim.out.ld', 'w') as ldout:
    ldout.write('anim_START = ' + hex(baseaddr) + ';\n')
    ldout.write('anim_END = ' + hex(curaddr) + ';\n')

print('animcat done')
