# triforce-dev

Reconstructing "lost beta elements" and "legitimately" obtaining the Triforce in Ocarina of Time via ACE / Total Control in a hybrid RTA/TAS run.


# Setup

- Make sure you got the Git submodules (ZAP2).
- Copy local.mk.example to local.mk and edit the paths defined there to point to the relevant tools on your computer, e.g. zzrtl(.exe), etc. (This should go without saying, but do not copy these tools to the toolchain folder!)
- Make `build-romhack` and `build-shortcut` folders and paste the OoT 1.0U uncompressed ROM into each of them, with the name `oot_1.0U_uncomp.z64`.
- `make`


# Credits

- Sauraen: concept, director, bootstrapper MIPS ASM programmer, DMA patcher C programmer, TAStm32 firmware mods, TAStm32 Z64TC mode Python frontend, actor design/programming, music arranging
- Kargaroc: fast_loader and debugger C programmer
- /zel/: map design: Triforce Room, Unicorn Fountain
- Savestate: live speedrun skills

## Tools

- z64ovl: z64me, Skawo, CrookedPoe, ???
- zzrtl: z64me
- OoT decomp: OoT decomp team
- SEQ64: Sauraen

## Technical Support

- /zel/
- z64me
- CrookedPoe
- mzxrules
- Jack Walker
- Ownasaurus

## Lore / Project Support

- dwangoAC
- SwankyBox
- RebeccaETripp
