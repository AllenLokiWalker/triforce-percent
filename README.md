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

### TRIFORCE% OOT ACE SHOWCASE

Director \
SAURAEN

RTA Speedrunner \
SAVESTATE

### ASSET UNIT

Actor Design & Program \
SAURAEN

Scene Design \
CDI-FAILS \
\/ZEL\/ \
SAURAEN

Music \
SAURAEN

Animation \
SAURAEN

Textures \
\/ZEL\/ \
SAURAEN

Scenario \
SAURAEN /
REBECCAETRIPP

Screen Text Writer \
KIM-SUKLEY

Translator \
???

Voice Actor \
???

### PROGRAM UNIT

Host Frontend \
SAURAEN

TAStm32 Firmware \
OWNASAURUS \
SAURAEN

SRM / ACE Setup \
MRCHEEZE

Bootstrapper Chain \
SAURAEN

Hyperspeed Loader \
TERUSTHEBIRD \
SAURAEN

System Patches \
SAURAEN \
\/ZEL\/

Game / Actor Patches \
SAURAEN

### TOOL UNIT

Build Toolchain \
SAURAEN

z64ovl \
Z64ME \
SKAWO \
CROOKEDPOE \
\/ZEL\/

fast64 \
KURETHEDEAD \
SAURAEN \
\/ZEL\/

seq64 \
SAURAEN

OoT Decomp \
A BUNCH OF CLEVER FOLKS

### SUPPORT UNIT

Technical Support \
MZXRULES \
Z64ME \
JACK WALKER

GDQ / TASbot Liaison \
DWANGOAC

YouTube Partner Channels \
SWANKYBOX

Special Thanks \
ARIANA ALMANDOZ

### PRESENTED AT

Awesome Games Done Quick 2022

### 

Assets, Scenario, and Performance \
Copyright (C) 2019-2022 \
The Triforce% Team

The Legend of ZELDA: Ocarina of Time \
Copyright (C) 1998 \
Nintendo
