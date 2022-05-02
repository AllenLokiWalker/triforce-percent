import json
from PIL import Image # pip install pillow
import struct
import ci4tool

with open('badges.json', 'r') as f:
    badges_data = json.loads(f.read())
    
palette_files = set()

for badge in badges_data:
    palette_files.add(badge['plt'])

palette_files = sorted(list(palette_files))

for badge in badges_data:
    badge['plt'] = palette_files.index(badge['plt'])

palettes = []
for p in palette_files:
    print('Palette ' + p)
    palettes.append(ci4tool.load_palette_from_png(p, True))

outsz = 32

for badge in badges_data:
    print('Badge ' + badge['path'])
    with Image.open(badge['path']) as im:
        assert (im.size[0] in [71, 72] and im.size[1] in [72, 73]) or im.size == (outsz, outsz) or im.size == (112, 112)
        if len(im.getbands()) == 1:
            im = im.convert()
        if im.size[0] != outsz or im.size[1] != outsz:
            im = im.resize((outsz, outsz), resample=Image.NEAREST)
        badge['data'] = ci4tool.apply_palette_to_im(im, palettes[badge['plt']], badge['dither'])

with open('badges.inc', 'w') as f:
    f.write('__attribute__((aligned(16))) static const u64 badge_textures[] = {\n')
    for badge in badges_data:
        f.write(ci4tool.indexes_to_c(badge['data'], None, badge['path']))
    f.write('};\n\n__attribute__((aligned(16))) static const u16 badge_palettes[] = {\n')
    for p in palettes:
        f.write(ci4tool.palette_to_c(p))
    f.write('};\n\nstatic const Gfx badge_tile_setup_dls[] = {\n')
    bi = 0
    while bi < len(badges_data):
        f.write('    gsDPLoadSync(),\n')
        f.write('    gsDPLoadBlock(7, 0, 0, ((ICON_SIZE*ICON_SIZE*ICONS_PER_GROUP+3)>>2)-1,\n')
        f.write('        G_DXT(G_IM_SIZ_4b, ICON_SIZE)),\n')
        f.write('    gsDPPipeSync(),\n')
        for t in range(4):
            if bi >= len(badges_data): break
            p = badges_data[bi]['plt']
            f.write('    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, ((((ICON_SIZE)>>1)+7)>>3),\n')
            f.write('        ' + str(t) + '*(ICON_SIZE*ICON_SIZE)/16, ' + str(t) + ', ' + str(p) + ', 0, 0, 0, 0, 5, 0),\n')
            #f.write('    gsDPSetTileSize(' + str(t) + ', 0, 0, (ICON_SIZE-1)<<G_TEXTURE_IMAGE_FRAC,\n')
            #f.write('        (ICON_SIZE-1)<<G_TEXTURE_IMAGE_FRAC),\n')
            bi += 1
        f.write('    gsSPEndDisplayList(),\n')
    f.write('};\n\n')
