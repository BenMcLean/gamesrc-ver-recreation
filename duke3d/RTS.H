//***************************************************************************
//
//    RTS.H
//
//***************************************************************************

#ifndef __rts_public__
#define __rts_public__

/*
====================
=
= RTS_Init
=
= Files with a .rts extension are idlink files with multiple lumps
=
====================
*/

void RTS_Init (char *filename);
/*
====================
=
= RTS_NumSounds
=
====================
*/

int32 RTS_NumSounds (void);
/*
====================
=
= RTS_SoundLength
=
= Returns the buffer size needed to load the given lump
=
====================
*/

int32 RTS_SoundLength (int32 lump);
/*
====================
=
= RTS_GetSoundName
=
====================
*/

char * RTS_GetSoundName (int32 i);
/*
====================
=
= RTS_GetSound
=
====================
*/
void *RTS_GetSound (int32 lump);
#endif
