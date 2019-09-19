*** WARNING: DO NOT TRY TOO HARD TO BUILD ANY OF THE ORIGINAL EXECUTABLES! ***

Please remember that any little difference, not matter how small it is,
can lead to a vastly different EXE layout. This includes differences in:

- The development tools (or parts of such); For instance, a compiler, a linker,
an assembler, or even a support library or header. A version number is not
a promise for having the exact tool used to reproduce some executable.
- The order in which source code files are listed in a given project file.
- Project settings.
- Source file specific settings in such a project.
- The order in which source code files are passed to a linker.
- Any modification to a source code file (especially a header file).
- More than any of the above.

Following the warning, a description of the ways in which the executables were
reproduced is given.

With the right tools, this patched codebase can be used to reproduce any
of the executables coming from the following original releases
(with minor differences for Aliens of Gold v1.0):

- Blake Stone: Aliens of Gold v1.0+2.0+2.1+3.0, 1 and 6 episodes releases.
- Blake Stone: Planet Strike v1.00+1.01.

What is this based on
---------------------

This codebase is based on the Planet Strike sources as originally released
by Apogee Software, LLC on 2013. These sources do not include data files
like VGAPAL or any project file. The data was extracted from one of
the EXEs, while a project file from a modified source tree (BS_SRC.7z)
was used as a base: http://wolf3d.darkbb.com/t2912-blake-stone-source

Alternative GFXV_BS1.H definitions, as well as song definitions in 3D_PLAY.C,
were edited based on the bstone source port by Boris Bendovsky.

Most of the recreation of AOG sources was done using earlier research work
by Braden Obrzut.

A portion of the released Wolfenstein 3D sources (mostly WL_SCALE.C) was
further used for the recreation of AOG v1.0.

How were the project files (and a bit more) prepared
----------------------------------------------------

- The released sources appear to be for version 1.01 of Planet Strike. There is
one change to actual code required for recreation of the original EXE, though.
The implementation of VL_WaitVBL as found in ID_VL_A.ASM was replaced with the
code from WaitVBL.ASM. The latter file is not a part of any project file.
- As stated above, a project file recreated earlier was used as a base. Some
changes are obviously applied as required, re-ordering of targets/objects being
a clear necessity. Note that the exact order may change between versions.
- In Borland C++, Source Debugging is set to "On", leading to the stripping
of the BSS segment (a bunch of zeros padded to the file's end) from the EXE.
- More settings, like optimizations, are appropriately chosen, partially
using earlier work on Wolfenstein 3D as a base.
- VGAPAL.OBJ and COLORMAP.OBJ are added as data to be embedded into the EXEs.
- The file C0.ASM from the Wolfenstein 3D sources as released by id Software is
included. It is used in a portion of the recreated Blake Stone project files.
- Each project should generate objects in a separate subdirectory.
- Paths to development environment (INCLUDE and LIB directories) are modified.
As expected there are chances you will still want to edit these, depending on
your setup of development tools.
- GAMEVER.H is added. Each project defines a version-identifier macro,
which is used to let the preprocessor define a few macros used in the
original codebase (like UPLOAD for the Apogee shareware release).
- This macro is separately added via a command line argument to the assembler
for a few ASM files, though, since the global project setting doesn't seem to
apply to ASM files. This ASM file does include a new GAMEVER.EQU file now. No
such change was done for any of the other ASM files because there's no need.
- A few chunks of 3D_MAIN.C and 3D_ACT2.C are relocated into the following two
files, "#included" from 3D_MAIN.C and 3D_ACT2.C: 3D_IDSTP.C, 3D_WSWTC.C.
This is done since each such chunk belongs to a different file in AOG v2.1/3.0
(JM_FREE.C instead of 3D_MAIN.C, and 3D_AGENT.C rather than 3D_ACT2.C),
and because this could otherwise lead to a lot of code duplication, with
possibly unexpected consequences for anybody tinkering with the code.
In fact, it happened while preparing Wolfenstein 3D projects for v1.1+1.2!
- There may be at least one other difference at the least. Obviously, source
code files other than GAMEVER.H are edited as required. This includes the
header file GFXV_BS1.h for the AOG builds, with resource definitions
taken off the bstone source port.

Building each EXE
=================

Required tools:

- Borland C++ 3.1 (and no other version).
- LZEXE 0.91.

Notes before trying to build anything:

- This may depend on luck. Maybe you'll get a bit different EXE.
- In fact, even when properly built, one difference or two of just
a few bytes *is* expected for each Aliens of Gold v1.0 EXE.
- In order to prepare for the construction of an EXE (including the removal
of older object files) and then build the EXE (in a possibly-initial form),
use a command similar to the following, if not the same: "prep BS1_210".
- LZEXE 0.91 should be used in a similar manner with the corresponding EXE as
the input, e.g., "lzexe BS1_210.EXE". LZEXE may ask you to confirm if the EXE
has trailing data (e.g., debugging symbols).
- It is assumed that you have a working DOS-compatible environment with a ready
installation of the correct version of Borland C++, including a properly set
PATH environment variable.
- If there are weird problems, try removing the SYM file and then
rebuilding. Remember, though, that luck is important here, and again you
may fail to get an EXE which is clearly close to an original one.

Building any of EXEs
--------------------

1. Prepare and open project with Borland C++ 3.1, using PREP.BAT.
2. Press on F9 to build.
3. Quit Borland C++ and use LZEXE 0.91 to pack the generated EXE.
4. Hopefully you should get exactly the original EXE, with exceptions
for AOG v1.0.

Expected differences for AOG v1.0:

- If the AOG 1-episode v1.0 EXE is built as above, a mention of the string
"LZ91" in the first 32 bytes can be found, although it's replaced with
4 zero bytes in the EXE as originally released.
- If the AOG 6-episodes v1.0 EXE is built, the mention of "LZ91" is not
the only difference. The EXE as originally released requires more memory
for running (a small difference, relatively, of about 9KiB), given
by two additional bytes out of the very first 32 in the EXE. These
two bytes are often used as the size of the so-called BSS section, but
it doesn't seem to be the case here. It is not clear how was this done.

A few final notes
-----------------

As said above, the source code as originally released by Apogee Software, LLC
seems to be for Planet Strike v1.01, although the implementation of VL_WaitVBL
as found in the original EXE is rather the code found in WAITVBL.ASM.
While the exact cause for the difference is not known, maybe
some kind of function symbol hijacking/renaming was done.
