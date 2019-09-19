*** WARNING: DO NOT TRY TOO HARD TO BUILD ANY OF THE ORIGINAL FILES! ***

Please remember that any little difference, not matter how small it is, can
lead to a vastly different OBJ or EXE layout. This includes differences in:

- The development tools (or parts of such); For instance, a compiler, a linker,
an assembler, or even a support library or header. A version number is not a
promise for having the exact tool used to reproduce some library or executable.
- The order in which source code files are listed in a given project or
makefile.
- Project settings.
- Source file specific settings in such a project.
- The order in which object or library files are passed to a linker.
- Any modification to a source code file (especially a header file).
- More than any of the above.

Following the warning, a description of the ways in which the objects and
executable were reproduced is given.

With the right tools, this patched codebase can be used to reproduce any of
the objects, or executable, as coming from the following original releases:

- A.OBJ as presumably prepared on 19960501, and used
in Duke3D 1.4-1.5 and SW 1.0-1.2.
- MMULTI.OBJ as prepared on 19960904 and used in Duke3D 1.4-1.5 and SW 1.0-1.2
(*presumably* also in 2DRAW, as available from Ken's site and prepared on 99).
- CACHE1D.OBJ and ENGINE.OBJ as present in Duke3D 1.4.
- An 19961012 revision of ENGINE.OBJ.
- CACHE1D.OBJ and ENGINE.OBJ as present in Duke3D 1.5; The latter was possibly
prepared on 19961112, while the former was *maybe* prepared on 19961207.
- ENGINE.OBJ as used in SW 1.0, possibly prepared on 19970212.
- ENGINE.OBJ as used in SW 1.1-1.2, possibly prepared on 19970522.
- The Ken-Build GAME.EXE file as originally prepared on 2000
(not to be confused with an updated EXE from 2002).

List of releases by LIB/directory file names
--------------------------------------------

Usually, a proper list would be given. However, unlike
the releases of other libraries as standalone library files
(e.g., .LIB), the Build engine was generally made available
as a collection of separate .OBJ files; So it's possible
that multiple files of different revisions would be used
in the same EXE.

In fact - there's evidence that this happened. Indeed, on the one hand,
SW 1.0-1.2 seem to use the same A.OBJ, CACHE1D.OBJ and MMULTI.OBJ code as
used in Duke3D 1.5 (Duke3D 1.4 is further matching on A.OBJ and MMULTI.OBJ).
These CACHE1D.OBJ and MMULTI.OBJ files were probably made with Watcom C 10.5.
However, the ENGINE.OBJ files used for SW 1.0-1.2 were apparently made using
Watcom C 10.6. In fact, a copy of the sources for ENGINE.OBJ as used
for SW 1.1-1.2 was found alongside SW sources under a directory
named "blddg", and evidence shows that these sources were
realy built by at least one SW dev, rather than Ken.

You can still select one or a few files to build/clean at a time,
using DOBUILD.BAT/DOCLEAN.BAT. A list of choices should be shown.

Usually a single directory will be created with the corresponding file(s).
As exceptions, DN3D14 should create 19960820 with the two OBJ files,
while DN3D15 should create 19961112\ENGINE.OBJ and 19961207\CACHE1D.OBJ.

How to identify code changes (and what's this BUILDREV thing)?
--------------------------------------------------------------

Different values of LIBVER_BUILDREV are defined for differing builds
of OBJ/EXE files. This macro is intended to represent a revision
of development of a part of the Build engine and/or the Ken-Build
test game. Usually, this revision value is based on some *guessed* date
(e.g., an original modification date of an OBJ file), but this does not
have to be the case.

Note that only C sources (and not ASM) are covered by the above. However,
two revisions of A.ASM are included. One of them is the file as released
on 2000, intended to be built with Watcom Assembler 11.0, at least for
recreating GAME.EXE as originally prepared on 2000. The other A.ASM file
is intended to be built with Macro Assembler 5.10, and should match A.OBJ
as used in Duke3D 1.4-1.5 and SW 1.0-1.2.

These are two good reasons for using BUILDREV as described above, referring
to similar work done for Wolfenstein 3D EXEs (built with Borland C++):

- WL1AP12 and WL6AP11 share the same code revision. However, WL1AP11
is of an earlier revision. Thus, the usage of WOLFREV can be
less confusing.
- WOLFREV is a good way to describe the early March 1992 build. While
it's commonly called just "alpha" or "beta", GAMEVER_WOLFREV
gives us a more explicit description.

What is this based on
---------------------

This codebase was more-or-less started from Ken Silverman's public Ken-Build
release of 2000 as a base. It also got a few (really) minor edits from 2002.

Additional thanks go to Ken for his consent to let other Build engine sources
become accessible under the same terms as of his 2000 release. Thus,
additional files could be used for the recreation efforts.
In particular, this included the sources for ENGINE.OBJ as used in SW 1.1-1.2,
an October 1996 revision of ENGINE.OBJ, and older engine sources from 1995.

Not long before the A.OBJ code used in Duke3D 1.4-1.5 and SW 1.0-1.2 was fully
recreated, Nuke.YKT came in to recreate ENGINE.OBJ as used in Duke3D 1.5, with
the assistance of the aforementioned SW 1.1-1.2 revision. In fact, originally
he wanted to recreate the revision used in Redneck Rampage, only that it
eventually turned out to match Duke3D 1.5's. CACHE1D.OBJ itself didn't
need that much changes, while MMULTI.OBJ as used in Duke3D 1.4-1.5 and
SW 1.0-1.2 essentially has the same code as in the public Ken-Build releases
(although at least the 2000 release uses a more recent build of MMULTI.OBJ).

Nuke.YKT also assisted with the recreation of Duke3D 1.4's revision of
ENGINE.OBJ. As in the case of 1.5, CACHE1D.OBJ didn't need that much changes.
The October 1996 revision of ENGINE.OBJ was initially used;
It is really close to Duke3D 1.5's revision. Later,
the 1995 sources were used for assistance.

How was the makefile (and a bit more) modified from the original
----------------------------------------------------------------

It's more-or-less based on the makefile from the public Ken-Build releases,
with changes gradually applied as the time had passed.

Building the files
==================

Required tools:

- For A.OBJ as presumably prepared on 19960501: MASM 5.10
(and no other version).
- For the 19970212 (SW 1.0) and 19970522 (SW 1.1-1.2) revisions
of ENGINE.OBJ: Watcom C 10.6 (and only this version).
- For Ken-Build as released on 20000614: Watcom C 11.0. (Not 11.0a/b/c, etc.)
- For anything else: Watcom C 10.5.

Notes before trying to build anything:

- This may depend on luck. Even if the code is generally 100% matching,
the OBJ files may still include data like original paths and timestamps
of source files (including local or system headers).
- Use DOBUILD.BAT to build the desired files (don't call wmake directly),
or DOCLEAN.BAT to remove them.

For reference, a list of such original paths in use is given here:
- MMULTI.OBJ: C:\C\CPROG\2DRAW for local files, c:\watcom\h for system headers.
- 19961207 (Duke3D 1.5) revision of CACHE1D.OBJ and 19970212 (SW 1.0)
revision of ENGINE.OBJ: C:\C\CPROG\BUILD for local files,
c:\watcom\h for system headers.
- 19961012, 19961112 (Duke3D 1.5) and 19970522 (SW 1.1-1.2) revisions
of ENGINE.OBJ: D: for local files, c:\watcom\h for system headers.

Building the LIB
----------------

1. Use DOBUILD.BAT, selecting the file(s) to create.
2. If you're building Ken-Build, hopefully you should get exactly the
original EXE. For all other choices, hopefully you should get perfectly
matching OBJ files, in terms of the code that gets added to EXEs later.
