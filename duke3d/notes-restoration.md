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
- The order in which object or library files are passed to a linker.
- Any modification to a source code file (especially a header file).
- More than any of the above.

Following the warning, a description of the ways in which the executables were
reproduced is given.

With the right tools, this patched codebase can be used to reproduce any of
the executables coming from the following original releases, with some caveats
for the EXEs matching the Duke Nukem 3D: Atomic Edition versions:

- Duke Nukem 3D: Atomic Edition versions 1.4 and 1.5.
- NAM (NAPALM) Full Version 1.0 (same EXE for NAM and NAPALM).
- WW2GI Full Version 1.0.
- Enhanced Duke (EDuke) 2.00.23 (mostly known as EDuke 2.0, not to be
confused with the released sources, which appear to match v2.00.21).

The MAKEFILE bundled with the EDuke 2.00.21 sources (the initial release)
was used as a base. You shall *not* call "wmake" on
your own anymore. Instead, use DOBUILD.BAT.

List of releases by directory names
-----------------------------------

- DN3D14: Duke Nukem 3D: Atomic Edition v1.4.
- DN3D15: Duke Nukem 3D: Atomic Edition v1.5.
- NAM10: NAM (NAPALM) Full Version 1.0.
- WW2GI10: WW2GI Full Version 1.0.
- EDK20023: Enhanced Duke 2.00.23.

How to identify code changes (and what's this DN3DREV thing)?
-------------------------------------------------------------

Check out GAMEVER.H. Basically, for each EXE being built, the
macro APPVER_EXEDEF should be defined accordingly. For instance,
when building NAM10, APPVER_EXEDEF is defined to be NAM10.

Note that only C sources (and not ASM) are covered by the above,
although there are no actual ASM sources in the Duke3D game code,
so it's mostly irrelevant.

Other than GAMEVER.H, the APPVER_EXEDEF macro is not used *anywhere*.
Instead, other macros are used. Some of them are old macros added to
control specific features, like NAM, WW2 and EDUKE. As of this release,
the latter three macros are defined by passing arguments to the compiler,
as originally done by Matt Saettler and done here with APPVER_EXEDEF.

Any new macro may also be introduced if useful. Note that the WW2GI macro
does *not* have the same meaning as WW2 - apparently it's useless.
WW2 is generally the macro originally used for "WW2GI and later",
albeit not always in this way.

APPVER_DN3DREV is defined in all builds, with different values. It is
intended to represent a revision of development of the Duke Nukem 3D
codebase. Usually, this revision value is based on some evidenced
date (e.g., any date taken from Matt Saettler's EDuke changelog),
or a *guessed* date (say, an original modification date of the EXE).
Any other case is also a possibility.

These are two good reasons for using DN3DREV as described above, referring
to similar work done for Wolfenstein 3D EXEs (built with Borland C++):

- WL1AP12 and WL6AP11 share the same code revision. However, WL1AP11
is of an earlier revision. Thus, the usage of WOLFREV can be
less confusing.
- WOLFREV is a good way to describe the early March 1992 build. While
it's commonly called just "alpha" or "beta", GAMEVER_WOLFREV
gives us a more explicit description.

Is looking for "#if (APPVER_DN3DREV <= AV_DR_...)" (or >) sufficient?
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

This codebase was originally based on the EDuke 2.00.21 sources
as released by Matt Saettler on 2003, while also using a few bits of
the EDuke 2.1.41 sources. As for the Duke Nukem 3D sources released
by 3D Realms beforehand, they were mostly used for reference,
say for attempting to recreate the behaviors of Duke3D v1.5.
Later, the same sources (as released by 3D Realms) were
used in order to recreate the behaviors of Duke3D v1.4,
before finally bringing the work to the usual repository.
Apart from actual C sources, the usage of the EDuke 2.00.21 source tree
includes the MAKEFILE, as well as the following binary (non-source)
OBJ/LIB files (also turning out to be present in 3DR's sources),
at least for Duke3D v1.5 and the later releases:

- The Build Engine (A.OBJ, CACHE1D.OBJ, ENGINE.OBJ and MMULTI.OBJ).
- The Apogee Sound System (AUDIO_WF.LIB).
- The MACT library (MACT386.LIB).
- The Total Entertainment Network (TEN) library (BUTWCD4.LIB).

A few missing headers from the MACT library were copied from 3DR's sources.
Their MAKEFILE.LNK file was also used as a base.

As a side-note on MAKEFILE.LNK, using the "file" directive even for the
libraries, and further issuing the "segment" directives, were all essential
for reproducing exactly the original EXEs as built by Matt.

The idea to look into the EDuke 2.00.21 sources
(rather than just 3DR's sources) came from Evan Ramos.
Further thanks shall be sent to Barry Duncan, Jarmo Kylmäaho
and Richard Gobeille for any assistance and/or other way of showing support.
Special thanks go to Ken Silverman for his consent to release additional
Build engine sources under the same terms as for his 2000 release.
This also covers sources for the revision of ENGINE.OBJ used in
Shadow Warrior versions 1.1 and 1.2, as well as an October 1996
revision, an early 1995 revision, and possibly also other files.
Additional credits go to Nuke.YKT, for using the aforementioned SW revision
of the ENGINE.OBJ code in order to recreate the code used in Duke3D 1.5,
and later assisting with the recreation of the Duke3D 1.4 revision.
It's probably also a good chance to send my thanks to various other members
of the Duke4.net community for their great support during all of these years!

How was the makefile (and a bit more) modified from the original
----------------------------------------------------------------

Compared to the EDuke 2.00.21 sources as released by Matt, there aren't
that many changes, although it's true that large chunks of code were
possibly, originally, added in-between certain games/EXEs.
There is a small amount of changes between versions 2.00.21 and 2.00.23,
backported from one of the EDuke 2.1 source archives that was released.

What is *not* included
----------------------

There are no sources for the MACT library (MACT386.LIB), as,well
as the Total Entertainment Network i.e., TEN library (BUTWCD4.LIB).

In addition, while the Build Engine and the Apogee Sound System were
open sourced, currently the binary files from the EDuke 2.00.21 sources
(or equivalently 3DR's released sources) are used, except for CACHE1D.OBJ
and ENGINE.OBJ in the case of Duke3D 1.4. As hinted by the original
modification date of Dec 9 1996 that all binary files share,
the exact same binary library code was used for Duke3D 1.5.

Building any of the EXEs
========================

Required tools:

- For Duke3D versions 1.4 and 1.5 i.e., Duke Nukem 3D Atomic Edition 1.4/1.5:
Watcom C 10.0 (and no other version, not even 10.0a or 10.0b).
- For any other EXE: Watcom C 10.6 (and no other version).
- (Optional) For Duke3D 1.4/1.5: DOS/4GW Professional Bind Utility version 1.3,
along with DOS/4GW Professional Protected Mode Run Time version 1.96.

Additionally, for Duke3D 1.4:
- You'll also need to build matching CACHE1D.OBJ and ENGINE.OBJ files
in the ..\kenbuild subdirectory.

Notes before trying to build anything:

- This may depend on luck. In the cases of Duke Nukem 3D: Atomic Edition
versions 1.4 and 1.5, you *will* get different EXEs, especially
if you don't use DOS/4GW Professional (but also if you do).
Even with other EXEs, luck may have its part.
- Further note that any customized patch, like copy protection removal,
shall *not* be applied here. This may lead to an additional
minor difference of one byte, if not much more.
- You may use DOBUILD.BAT to build each EXE, and DOCLEAN.BAT to clean
any previously built object and executable files.

Building the Duke Nukem 3D: Atomic Edition 1.4 or 1.5 EXE
=========================================================

1. If you want to build 1.4, don't forget to build the matching
CACHE1D.OBJ and ENGINE.OBJ files under "kenbuild" first.
2. Use DOBUILD.BAT, selecting DN3D14 or DN3D15 as the
output directory name, depending on the version.
3. Hopefully you should get an EXE essentially behaving like the original.

Expected differences from the original:

- A few unused gaps, mostly between C string literals, seem to be filled with
values depending on the environment while running the Watcom C compiler
(e.g., the exact contents of each compilation unit). This seems to be
related to Watcom C v10.0(a/b), and less to 10.6.
2. The created GAME.EXE file will require an external DOS4GW EXE
(or compatible). You may optionally use DOS/4GW Professional to
bind its loader to the EXE, but chances are there'll still be an
*additional* difference of, say, 6 bytes from the original EXE.

Building the NAM, WW2GI or EDUKE EXE
====================================

1. Use DOBUILD.BAT, selecting the desired directory name.
2. Hopefully you should get exactly the original EXE.
