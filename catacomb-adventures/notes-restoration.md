This subtree contains restored code for the following EXEs:

- Source code that can be used to reconstruct The Catacomb Abyss v1.13 EXE.
- Not byte-by-byte precise, but should be functionally identical to: Versions
of INTRO.EXE bundled with Catacomb Abyss v1.13, Abyss v1.24 (as CATABYSS.EXE),
Armageddon v1.02 (CATARM.EXE) and Apocalypse v1.01 (CATAPOC.EXE).

Notes about the lack of source modifications for construction of the game EXEs
from any registered release:

- For Catacomb Abyss v1.24, the only required change is really small, which
is an edit of gfxe_abs.equ (but NOT gfxe_abs.h) so STARTTILE8 is defined to
be 314 rather than 315. This may actually be a compiler glitch, the result of
having an old out-of-date (but not that much) OBJ file, or any other reason.
- There are no source modifications for the other two episodes in the series.
While there may be no problem with STARTTILE8, (very) few bits of code are
generated a bit differently, although their behaviors should be the same
(assuming no e.g., undefined behaviors).

Places found to have generated code a bit different from what's found in the
originally released EXEs:

- C5_DRAW.C:DrawVWall, C6_DRAW.C:DrawVWall.
- Sometimes in C5_TRACE.C:FinishWall, possibly depending on the way the project
is built with BC++ 2.0 (can either select project from the IDE before building,
or just ask to build).
- Possibly similar (but not necessarily of the exact same nature) glitches
with C6_PLAY.C:PlayLoop, C6_PLAY.C:DisplayStatus.
