This repository hosts modifications of a few old games'
released source codes, done for the purpose of reproducing
originally released EXEs, byte-by-byte (or at least EXEs close to these).
A few related libraries are also covered.

Currently it has modified sources used to reproduce the following:  

- Catacomb 3-D v1.00 and The Catacomb Abyss Shareware release v1.13
(CATABYSS.EXE).  
- Various builds of Wolfenstein 3D and Spear of Destiny, as well
as recreated code for the DOS port of Super 3-D Noah's Ark (v1.0).
There's also a March 1992 Wolfenstein 3D alpha/beta build as a bonus.  
- Various builds of Blake Stone: Aliens of Gold and Planet Strike.
- A (somewhat) imperfect recreation of 4 Apogee releases of Rise of the Triad,
all with v1.3: Shareware, Commercial/Registered, Super CD and Site License;
2 releases of ROTT: Lasersoft Deluxe Editions (1.3) are covered, too.
- The game-side code of games based on the Duke Nukem 3D codebase. Out of
these, the contents of the Duke3D EXEs should differ just by garbage data
inserted by Watcom C 10.0. The other EXEs, of games in which Matt Saettler
was involved for the programming, should perfectly match the original ones,
when built with Watcom C 10.6.
The covered games are: Duke Nukem 3D: Atomic Edition 1.4-1.5,
NAM (NAPALM) Full Version 1.0, WW2GI Full Version 1.0
and Enhanced Duke (EDuke) 2.00.23, also known as EDuke 2.0;
NOT to be confused with EDuke32, nor with the exact EDuke 2.0
sources released on 2003, which probably match version 2.00.21.

Recreations of the the following libraries are additionally covered:

- An imperfect recreation of the Apogee Sound System,
a library used by ROTT, Duke3D and Shadow Warrior (SW). This covers
versions 1.04 (for ROTT 1.3), 1.09 (SW 1.0-1.2) and 1.1 (Duke3D 1.4-1.5).
1.04 has certain imperfections, 1.09 differs from the original just by
one register access (in a way that shouldn't practically matter) and 1.1 is
essentially perfect, if we ignore differing unused data inserted by Watcom C.
- The Build engine's object files, as used in Duke3D 1.4-1.5 and SW 1.0-1.2,
as well as the original public release of the "Ken-Build" test game
from 2000 (without really minor updates added on 2002).

Furthermore, source codes reconstructions (*not necessarily* reproducing
EXEs byte-by-byte) for LOADSCN.EXE as coming with The Catacomb Abyss
Shareware v1.13, as well as revisions of INTRO.EXE and DEMOCAT.EXE/HINTCAT.EXE
from this shareware release and the last registered release of all episodes,
are included. Except for the INTRO EXEs, these can be recreated byte-by-byte.
Note that there are no entire sources or patches for this registered release,
but there is a (really) minor patch for reconstruction
of The Catacomb Abyss v1.24 EXE.

Old descriptions of specific source code changes are found in the "patches"
subdirectory, but they may be a bit out-of-date, if they exist at all.
Also note that diffs to some files (like binary .OBJ files) may be absent.

The included "stripbss" program (or some other possible alternative)
was once required for the reproduction of a few executables, at the least.
This is not the case anymore, but it's currently left in for reference.

Thanks should be sent to members of a few communities at the least, for help
and other kinds of support; Anybody making the releases of these source codes
possible, the original dev. teams for the mere existence of the games, and
more individuals.
