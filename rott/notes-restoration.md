*** WARNING: DO NOT TRY TOO HARD TO BUILD ANY OF THE ORIGINAL EXECUTABLES! ***

Please remember that any little difference, not matter how small it is,
can lead to a vastly different EXE layout. This includes differences in:

- The development tools (or parts of such); For instance, a compiler, a linker,
an assembler, or even a support library or header. A version number is not
a promise for having the exact tool used to reproduce some executable.
- The order in which source code files are listed in a given project or
makefile.
- Project settings.
- Source file specific settings in such a project.
- The order in which source code files are passed to a linker.
- Any modification to a source code file (especially a header file).
- More than any of the above.

Following the warning, a description of the ways in which the executables were
reproduced is given.

With the right tools, this patched codebase can be used to reproduce
executables that at least *behave closely* (but are *not* identical)
to the ones from the following original releases:

- Rise of the Triad Lasersoft Deluxe Version 1.3, May and July 95 releases.
- Rise of the Triad, Shareware + Registered + Super CD + Site License
releases, Apogee v1.3.

The originally released MAKEFILE was used as a base. You shall *not* call
"wmake" on your own anymore. Instead, use BUILD.BAT or BUILDWA.BAT.

List of releases by directory names
-----------------------------------

- RTLD13A: ROTT Lasersoft Deluxe Version 1.3 May 95 release.
- RTLD13B: ROTT Lasersoft Deluxe Version 1.3 July 95 release.
- RTSW13: ROTT Shareware Apogee v1.3.
- RTRG13: ROTT Registered/Commercial Apogee v1.3.
- RTCD13: ROTT Super CD Apogee v1.3.
- RTSL13: ROTT Site License Apogee v1.3.

How to identify code changes (and what's this ROTTREV thing)?
-------------------------------------------------------------

Check out DEVELOP.H. Basically, for each EXE being built, a corresponding
EXEDEF macro shall be defined. For instance, when building RTRG13,
the macro APPVER_EXEDEF_RTRG13 is defined.

In addition, for the C sources, there's a separate APPVER_EXEDEF macro
defined. For instance, for RTRG13, APPVER_EXEDEF is defined to RTRG13.

Note that only C sources (and not ASM) are covered by the above for now.

Other than DEVELOP.H, the APPVER_EXEDEF macros are not used *anywhere*.
Instead, other macros are used. Some of them are old macros added to
control specific features, like SHAREWARE, SUPERROTT and SITELICENSE.
Any new macro may also be introduced if useful.

APPVER_ROTTREV is defined in all builds, with different values.
It is intended to represent a revision of development of
the Rise of the Triad codebase. Usually, this revision value is based on
some *guessed* date (e.g., an original modification date of the EXE),
but this does not have to be the case.

These are two good reasons for using ROTTREV as described above, referring
to similar work done for Wolfenstein 3D EXEs (built with Borland C++):

- WL1AP12 and WL6AP11 share the same code revision. However, WL1AP11
is of an earlier revision. Thus, the usage of WOLFREV can be
less confusing.
- WOLFREV is a good way to describe the early March 1992 build. While
it's commonly called just "alpha" or "beta", GAMEVER_WOLFREV
gives us a more explicit description.

Is looking for "#if (APPVER_ROTTREV <= AV_RR_...)" (or >) sufficient?
---------------------------------------------------------------------

Nope!

Examples from Wolf3D/SOD:

For a project with GAMEVER_WOLFREV == GV_WR_SDMFG10,
the condition GAMEVER_WOLFREV <= GV_WR_SDMFG10 holds.
However, so does GAMEVER_WOLFREV <= GV_WR_WJ6IM14,
and also GAMEVER_WOLFREV > GV_WR_WL1AP10.
Furthermore, PML_StartupXMS (ID_PM.C) has two mentions of a bug fix
dating 10/8/92, for which the GAMEVER_WOLFREV test was chosen
appropriately. The exact range of WOLFREV values from this test
is not based on any specific build/release of an EXE.

What is this based on
---------------------

This codebase is based on the Rise of the Triad sources as originally
released by Apogee Software, Ltd. (DBA 3D Realms) on 2002. While the
2002 release includes a RT_ERR.OBJ data file, another version of
this file's data was extracted from an original EXE.

How was the makefile (and a bit more) modified from the original
----------------------------------------------------------------

As of the initial release of this, there aren't a lot of changes
to the ROTT codebase itself. Almost all changes were done to
the Apogee Sound System library.
As for ROTT, the released sources appear to be a little later
than Apogee v1.3, as given by the defined version number of 1.4
and a few more hints (like misc. "MED" comments).

Building each EXE
=================

Required tools (also applying to AUDIOLIB v1.04):

- Watcom C 10.0b (and no other version), for all Apogee v1.3 releases of ROTT.
- Turbo Assembler v3.1 (from Borland C++ 3.1).

Notes before trying to build anything:

- This may depend on luck. In fact, as of now, it *is* known that you'll get
a different EXE.
- Each ROTT EXE depends on the Apogee Sound System library (AUDIOLIB).
If the corresponding version is ready then you can use BUILD.BAT,
otherwise use BUILDWA.BAT so AUDIOLIB is built first.
- Similarly, you may use CLEAN.BAT to clean older ROTT object and executable
files, or CLEANWA.BAT to further clean the corresponding AUDIOLIB version.

Building any of the Rise of the Triad EXEs
------------------------------------------

1. Use BUILD.BAT or BUILDWA.BAT, passing the corresponding output directory
name as an argument (e.g., RTSW13 for ROTT Shareware Apogee v1.3).
2. Hopefully you should get an EXE that *behaves close to the original*,
but do *not* expect it to be identical.

Known issues
------------

First of all, you should be aware that each constructed EXE will
*not* include a built-in copy of the DOS4GW loader. Rather, it'll
have a DOS4GW stub that looks for an external DOS4GW.EXE file.

Secondly, even if it weren't an issue, there are still known differences
in the outputs that should be listed, compared to the original ROTT EXEs:

- Differences in the generated AUDIOLIB code. For more details,
see ../audiolib/notes-restoration.md.
- Misc. global variables found in locations differing from the originals
in the recreated EXE layout.

Furthermore, most chances are that paddings between string literals, or
possibly less commonly between global variables, will be filled with different
values. Reason is that apparently, for each compilation unit, Watcom C fills
a buffer with the input source code (or at least a variant of it), and then
it *reuses* the buffer for the relevant strings or global variables.

If you still want to compare ROTT EXEs, you may use "SUNSYS Bind Utility"
(SB.COM from DOS/32) to unbind the EXEs, get ROTT LE output files
(without the DOS4GW extender/stub) and finally compare these.

Furthermore, see the ../misc directory for assistance with comparing
LST files outputted by IDA Free v4.1, for two LE files in which global
variables are the same, up to their exact locations in the EXEs' layouts.
