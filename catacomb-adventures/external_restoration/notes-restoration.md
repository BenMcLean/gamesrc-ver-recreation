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
of the executables coming from the following original releases, albeit with
(relatively) small differences for the INTRO EXEs:

DEMOCAT.EXE/HINTCAT.EXE:

- Electronic Catalog version 1.00 QA[0] (Catacomb Abyss Shareware v1.13).
- Catacomb Abyss 3-D Hint Book version 1.01 rev 1 (from CatAbyss v1.24).
- Catacomb Armageddon 3-D Hint Book version 1.12 rev 1 (CatArm v1.02).
- Catacomb Apocalypse 3-D Hint Book version 1.13 rev 1 (CatApoc v1.01).

LOADSCN:

- LOADSCN version 1.10 QA[0] (CatAbyss v1.13).

INTRO:

- The Catacomb Abyss (3-D) Introduction Program, versions 1.01 QA[0]
and 1.06 rev 1 (bundled with CatAbyss versions 1.13 and 1.24, respectively).
- The Catacomb Armageddon 3-D Introduction Program, version 1.04 rev 1
(CatArm v1.02).
- The Catacomb Apocalypse 3-D Introduction Program, version 1.05 rev 1
(CatApoc v1.01).

This codebase is a RECONSTRUCTION of EXEs bundled with certain versions
of The Catacomb Adventure Series episodes.

It shall be noted that the original sources for these executables were not
available as of preparing this file (we do have the sources for LOADSCN.EXE
as coming with Keen Dreams, but it is much smaller that the Catacomb EXE).
However, a large chunk of these sources is available separately, possibly
with a few differences (e.g., not using ID_MM for memory management),
greatly assisting with the reconstructions. The revision of the INTRO
program from The Catacomb Apocalypse also appears to have an unused
4000-bytes long chunk embedded in the EXE, which *is* used
in the various DEMOCAT.EXE and HINTCAT.EXE builds.

Given this situation, it makes sense that you will *not* get the original EXEs
from these reconstructed sources, byte-by-byte; Or at least, not always.

The Electronic Catalog and Hint Book EXEs, as well as the LOADSCN EXE,
can be faithfully recreated with Borland C++ 2.0 and LZEXE 0.91. However,
while the recreated Intro EXEs will be more-or-less the same as the
originals, the locations of some variables in memory may differ.

Interestingly, originally, LOADSCN.EXE wasn't exactly recreated byte-by-byte,
either. However, this was resolved after figuring out (for DEMOCAT/HINTCAT)
that COMDEFs should *not* be generated (this is a Borland C++ project
setting). Renaming variables also seems to have an effect on the way
the Borland C++ 2.0 linker orders them (if not the compiler).

Borland C++ 2.0 for DOS should be used for these builds; Not Borland C++ 3.1
nor any version of Turbo C/C++, but precisely Borland C++ 2.0.
After opening the project with BC20, chances are you will need to set up
the correct LIB and INCLUDE paths in the project. Either way, you should
then be able to build the corresponding executable.

As stated above, in the case of the DEMOCAT/HINTCAT and LOADSCN EXEs,
(but *not* the INTRO EXEs), a call to LZEXE91 should be sufficient
before recreating exactly any original EXE from the 90s.
