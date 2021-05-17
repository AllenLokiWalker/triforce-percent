# triforce-dev

Reconstructing "lost beta elements" and "legitimately" obtaining the Triforce in Ocarina of Time via ACE / Total Control in a hybrid RTA/TAS run.


# Setup

- Make sure you got the Git submodules (ZAP2).
- If you don't already have it, install the N64 toolchain from https://github.com/glankk/n64.
- Clone, build, and copy novl to your toolchain folder (e.g. /opt/n64/bin/novl). If the autogen build system for novl gives you garbage, try this makefile from z64me (you still need the prereq packages):
```
default:
	gcc -o novl -s -Os -DNDEBUG -flto src/*.c `pkg-config --cflags --libs libelf glib-2.0`

clean:
	rm -f novl
```
- Get https://github.com/z64me/z64ovl_archived, and make sure this is the z64ovl version used below.
- Copy local.mk.example to local.mk and edit the paths defined there to point to the relevant tools on your computer, e.g. zzrtl(.exe), etc. (This should go without saying, but do not copy these tools to the toolchain folder!)
- Make a `build-shortcut` folder and paste the OoT 1.0U compressed ROM into it, with the name `oot_1.0U_comp.z64`.
- Make a `build-romhack` and paste the OoT 1.0U uncompressed ROM into it, with the name `oot_1.0U_uncomp.z64`.
- `make`


# Credits

- Sauraen: concept, director, bootstrapper MIPS ASM programmer, DMA patcher C programmer, TAStm32 firmware mods, TAStm32 Z64TC mode Python frontend, actor design/programming, music arranging
- Kargaroc: fast_loader and debugger C programmer
- /zel/: map design: Triforce Room; rhstatics programmer
- CDi-Fails: map design: Unicorn Fountain, Chamber of Sages
- Savestate: live speedrun skills

## Tools

- z64ovl: z64me, Skawo, CrookedPoe, Zel, ???
- zzrtl: z64me
- OoT decomp: a bunch of clever folks
- SEQ64: Sauraen

## Technical Support

- Zel
- z64me
- CrookedPoe
- mzxrules
- Jack Walker
- Ownasaurus

## Lore / Project Support

- dwangoAC
- SwankyBox
- RebeccaETripp
