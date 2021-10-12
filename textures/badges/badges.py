import json
from PIL import Image # pip install pillow
import struct

with open('badges.json', 'r') as f:
    badges_data = json.loads(f.read())
    
palette_files = set()

for badge in badges_data:
    palette_files.add(badge['plt'])

palette_files = list(palette_files)

for badge in badges_data:
    badge['plt'] = palette_files.index(badge['plt'])

palettes = []
for p in palette_files:
    print('Palette ' + p)
    with Image.open(p) as im:
        assert im.size == (16, 1)
        assert len(im.getbands()) == 4
        ib = im.tobytes()
        assert len(ib) == 64
        for i in range(1, 16):
            assert ib[4*i+3] == 255
        #print('Palette ' + str(len(palettes)) + ': ' + b.hex())
        palettes.append(ib)

outsz = 24

for badge in badges_data:
    print('Badge ' + badge['path'])
    with Image.open(badge['path']) as im:
        assert im.size[0] in [71, 72] and im.size[1] in [72, 73]
        bands = len(im.getbands())
        if bands == 1:
            im = im.convert()
            bands = len(im.getbands())
        assert bands in [3, 4]
        im = im.resize((outsz, outsz), resample=Image.NEAREST)
        ib = im.tobytes()
        plt = palettes[badge['plt']]
        plt_has_alpha = plt[3] == 0
        d = []
        for i in range(len(ib)//bands):
            if bands == 4:
                r, g, b, a = struct.unpack("BBBB", ib[bands*i:bands*(i+1)])
            else:
                r, g, b = struct.unpack("BBB", ib[bands*i:bands*(i+1)])
                a = 255
            if a < 128:
                if not plt_has_alpha:
                    raise RuntimeError('Need alpha but palette does not have it')
                d.append(0)
            else:
                bestscore = 100000000
                bestq = -1
                for q in range(0,16):
                    if plt_has_alpha and q == 0:
                        continue
                    pr, pg, pb = struct.unpack("BBB", plt[4*q:4*q+3])
                    score = (r - pr) ** 2 + (g - pg) ** 2 + (b - pb) ** 2
                    if score < bestscore:
                        bestq = q
                        bestscore = score
                assert bestq >= 1 and bestq <= 15
                d.append(bestq)
        assert len(d) == outsz * outsz
        badge['data'] = d

with open('badges.inc', 'w') as f:
    f.write('__attribute__((aligned(16))) static const u64 badge_textures[] = {\n')
    for badge in badges_data:
        f.write('    // ' + badge['path'] + '\n')
        d = badge['data']
        i = 0
        while i < len(d):
            f.write('    ')
            for _ in range(4):
                f.write('0x')
                for _ in range(16):
                    f.write(format(d[i], 'x'))
                    i += 1
                f.write(', ')
            f.write('\n')
    f.write('};\n\n__attribute__((aligned(16))) static const u16 badge_palettes[] = {\n')
    for p in palettes:
        f.write('    ')
        for i in range(16):
            if i == 0:
                val = 0
            else:
                val = ((p[4*i+0] >> 3) << 11) | ((p[4*i+1] >> 3) << 6) | ((p[4*i+2] >> 3) << 1) | 1
            f.write('0x' + format(val, '04x') + ', ')
        f.write('\n')
    f.write('};\n\nstatic const Gfx badge_tile_setup_dls[] = {\n')
    bi = 0
    while bi < len(badges_data):
        f.write('    gsDPLoadSync(),\n')
        f.write('    gsDPLoadBlock(7, 0, 0, ((BADGE_SIZE*BADGE_SIZE+3)>>2)-1, CALC_DXT_4b(BADGE_SIZE)),\n')
        f.write('    gsDPPipeSync(),\n')
        for t in range(7):
            if bi >= len(badges_data): break
            p = badges_data[bi]['plt']
            f.write('    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, ((((BADGE_SIZE)>>1)+7)>>3), 0,\n')
            f.write('        ' + str(t) + ', ' + str(p) + ', 0, 0, 0, 0, 0, 0),\n')
            bi += 1
        f.write('    gsSPEndDisplayList(),\n')
    f.write('};\n\n')
