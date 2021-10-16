Blender Files:
--------------

*-raw.blend:

These files are the raw DAEs, imported but otherwise unmodified. They
have armatures and some unnecessary meshes and transformations. These
files may be useful if the artist wants to reference the old armatures
or something (although I am not sure if those even work.)

*.blend:

Cleaned-up files with unnecessary (imo) things removed. Transformations
are applied so that the models are oriented correctly. This is probably
where the artist should start working on low-poly versions.


The rest of this readme contains notes about how the Blender files were
made.



Final game files used:
----------------------

The title IDs differ by one character. The one with "0" is the original disc files.
The one with "E" is the online update files.

00050000101C9400 = disc files        0005000E101C9400 = update files

Some files must be extracted from TitleBG.pack. This can be done using SARCExtract:

    https://github.com/aboood40091/SARCExtract

The disc and update versions of TitleBG.pack are different, but the files we are
interested in are identical in each.

pack file used (either):

a2517db2e32d4b5a0c8c1aed3f72cbd2  ./00050000101C9400/content/Pack/TitleBG.pack (disc)
726fa857afd859ceaf403cb272b8e328  ./0005000E101C9400/content/Pack/TitleBG.pack (update)


sbfres files used:

Link:

512be2cf96741c742c2d99cfa4c56247  ./00050000101C9400/content/Pack/TitleBG/Model/Link.sbfres
23ac00c1bba0227c85e716a9679dd309  ./00050000101C9400/content/Model/Link.Tex1.sbfres


Armor_Default: (Hair)

97a15c603e44d422f3383e705fb40b1e  ./00050000101C9400/content/Pack/TitleBG/Model/Armor_Default.sbfres
3160ee3c4cceb21f08562b71c7ad9fea  ./00050000101C9400/content/Model/Armor_Default.Tex1.sbfres


Armor_001 (Hylian Trousers)

0839c3ccefe7b49b7be4e798ed07d1d5  ./0005000E101C9400/content/Model/Armor_001.sbfres
3940dfc1cd3bdb71e1f6e59b3959740c  ./00050000101C9400/content/Model/Armor_001.Tex1.sbfres


Armor_116 (Blue Tunic)

91e968c1782a19a685eec5fae2ac1055  ./0005000E101C9400/content/Model/Armor_116.sbfres
08a989a3fcef1a7bc5bc37d3d41005af  ./00050000101C9400/content/Model/Armor_116.Tex1.sbfres


Npc_Zelda_Miko (Zelda)

b84437fc382fec2a802f7d6399ab0d7a  ./0005000E101C9400/content/Model/Npc_Zelda_Miko.sbfres
1470c817b5b08095f4c0f97f68307db1  ./00050000101C9400/content/Model/Npc_Zelda_Miko.Tex1.sbfres



How to convert to Collada DAE with Switch Toolbox:
--------------------------------------------------

0. If running in VirtualBox, you MUST enable GPU acceleration of the VM.
   If you do not do this, Switch Toolbox will exit with no error when
   you open any file.

1. Install Switch Toolbox dependencies. Some things you may need:

 * DirectX runtimes
    https://www.microsoft.com/en-us/download/details.aspx?id=35

 * Dotnet runtimes
    Link in Switch Toolbox docs is broken. They require 4.6 or newer.
    Seems included with Windows 10, or I already downloaded it.
    
 * MSVC C++ runtimes
    https://docs.microsoft.com/en-US/cpp/windows/latest-supported-vc-redist?view=msvc-160

   If you reach some step in this guide where things just refuse to work,
   chances are you are missing one or more of the above. The documentation
   isn't very clear about which versions you need though.

2. Install Switch Toolbox

    https://github.com/KillzXGaming/Switch-Toolbox

     * You must "unblock" the Switch Toolbox zip file, by right clicking
       and selecting properties. Then tick the "unblock" box.

       NOTE: This is different from unblocking the executable, which you
       also have to do, but Windows will ask you to do that when you try
       to run it. Failing to unblock the ZIP will cause files to be
       silently ignored during decompression, which causes Switch Toolbox
       to malfunction much later.
     
     * Extract Switch Toolbox somewhere.

     * Double click Toolbox.exe to run it.

3. File->Open and select all ten *.sbfres files.

4. Expand each sfbres to see the internal folders including "models" and
   "textures". The Tex1 files will have textures in the "textures" folder
   while the other files will have models in the "models" folder.

   NOTE: It is important to open all of the sbfres files at once because
   some models refer to textures inside multiple Tex1 files.

5. Right click a model folder and "Export All". Select a directory and
   click okay on all subsequent dialogs. You should now have exported a
   DAE and all the related textures as PNG. Repeat for the other model
   files.

6. Open the DAE in Blender and you should see the fully textured meshes.






