# Triforce%

Triforce% is a hybrid RTA/TAS "speedrun" of Ocarina of Time which uses Arbitrary
Code Execution (ACE) to install a set of data loaders in system memory, enabling
arbitrary assets (scenes, objects, music, etc.) in the game ROM to be seamlessly
live-patched from the host PC. By modifying the game programming and assets,
beta content cut from the final version of OoT is restored and brought to life
on screen. A new plot is constructed based on this beta content and on urban
legends from the late '90s, culminating in Link obtaining the Triforce.

But, in front of thousands of live viewers, once we have the power of the
Goddesses--and the power to make the game whatever we can imagine--what will we
use this power for?


# Setup

- Install Linux (Debian / Ubuntu / other Debian derivative), either directly or through WSL/WSL2 if you're on Windows.
- Make sure you got the Git submodules (ZAP2/ZAPD, novl, z64hdr). You will need libpng (`libpng-dev`, `libelf-dev`, and `libglib2.0-dev` for these to compile.
- If you don't already have it, install the N64 toolchain from https://github.com/glankk/n64.
- Get a copy of zzrtl which is stable enough to work on Linux with the default (i.e. non-Jared Johnson) scripts, e.g. 0.01r4. Put this somewhere outside the Git repo (i.e. not in the `toolchain` folder).
- Copy local.mk.example to local.mk and edit the paths defined there to point to the relevant tools on your computer, i.e. zzrtl and python 3.
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
SAURAEN \
RANKAISIJA \
Z64ME \
\/ZEL\/

Scene Design \
CHANCELLOR DYNAMITE-INFERNO \
\/ZEL\/ \
SAURAEN

Music \
SAURAEN \
REBECCAETRIPP

Animation \
SAURAEN \
AEROARTWORK

Cinema Scenes \
SAURAEN

Textures \
KIM-SUKLEY \
\/ZEL\/ \
CHANCELLOR DYNAMITE-INFERNO \
SAURAEN

Scenario \
SAURAEN \
REBECCAETRIPP

Screen Text \
KIM-SUKLEY \
SAURAEN

Translator \
YUKLOJ

Voice Actor \
ZERO

Motion Capture Actor \
TBD

Motion Capture Technician \
TBD

### PROGRAM UNIT

Host Frontend \
SAURAEN

TAStm32 Firmware \
OWNASAURUS \
SAURAEN

SRM / ACE Setup \
MRCHEEZE \
SAVESTATE

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

Build Toolchain \
SAURAEN

### SUPPORT UNIT

Technical Support \
\/ZEL\/ \
Z64ME \
MZXRULES \
THARO \
JACK WALKER

Video Editing \
MUSKET012 \
GRAVATOS \
SAVESTATE \
SAURAEN

YouTube Partner Channels \
SWANKYBOX \
TBD

Special Thanks \
KAZE EMANUAR \
XDANIEL \
ARIANA ALMANDOZ

Producer \
DWANGOAC

### PRESENTED AT

Awesome Games Done Quick 2022

### 

Assets, Toolchain, and Performance \
Copyright (C) 2019-2022 \
The Triforce% Team

The Legend of ZELDA: Ocarina of Time \
Copyright (C) 1998 \
Nintendo
