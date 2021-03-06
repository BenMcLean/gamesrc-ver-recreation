









// SOURCE CODE FOR DUKE NUKEM 3D IS COPYRIGHTED BY TODD REPLOGLE AND MAY
// _NOT_ BE DISTRIBUTED EXCEPT AS AUTHORIZED BY 3DREALMS ENTERTAINMENT.
















#include "duke3d.h"

//=============
// STATICS
//=============

int32 numlumps;
static void  **lumpcache;
static lumpinfo_t *lumpinfo;              // location of each lump on disk
static boolean RTS_Started = false;

char lumplockbyte[11];

/*
============================================================================

                                                LUMP BASED ROUTINES

============================================================================
*/

/*
====================
=
= RTS_AddFile
=
= All files are optional, but at least one file must be found
= Files with a .rts extension are wadlink files with multiple lumps
= Other files are single lumps with the base filename for the lump name
=
====================
*/

void RTS_AddFile (char *filename)
   {
   wadinfo_t  header;
   lumpinfo_t *lump_p;
   uint32     i;
   int32      handle, length;
   int32      startlump;
   filelump_t *fileinfo;

//
// read the entire file in
//      FIXME: shared opens

   handle = SafeOpenRead( filename, filetype_binary );

   startlump = numlumps;

   // WAD file
   printf("    Adding %s.\n",filename);
   SafeRead( handle, &header, sizeof( header ) );
   if (strncmp(header.identification,"IWAD",4))
      Error ("RTS file %s doesn't have IWAD id\n",filename);
   header.numlumps = IntelLong(header.numlumps);
   header.infotableofs = IntelLong(header.infotableofs);
   length = header.numlumps*sizeof(filelump_t);
   fileinfo = alloca (length);
   if (!fileinfo)
      Error ("RTS file could not allocate header info on stack");
   lseek (handle, header.infotableofs, SEEK_SET);
   SafeRead (handle, fileinfo, length);
   numlumps += header.numlumps;

//
// Fill in lumpinfo
//
   SafeRealloc(&lumpinfo,numlumps*sizeof(lumpinfo_t));
   lump_p = &lumpinfo[startlump];

   for (i=startlump ; i<numlumps ; i++,lump_p++, fileinfo++)
      {
      lump_p->handle = handle;
      lump_p->position = IntelLong(fileinfo->filepos);
      lump_p->size = IntelLong(fileinfo->size);
      strncpy (lump_p->name, fileinfo->name, 8);
      }
   }

/*
====================
=
= RTS_Init
=
= Files with a .rts extension are idlink files with multiple lumps
=
====================
*/

void RTS_Init (char *filename)
   {
   int32 length;
   //
   // open all the files, load headers, and count lumps
   //
   numlumps = 0;
   lumpinfo = SafeMalloc(5);   // will be realloced as lumps are added

   printf("RTS Manager Started.\n");
   if (SafeFileExists(filename))
      RTS_AddFile (filename);

   if (!numlumps) return;

   //
   // set up caching
   //
   length = (numlumps) * sizeof( *lumpcache );
   lumpcache = SafeMalloc(length);
   memset(lumpcache,0,length);
   RTS_Started = true;
   }


/*
====================
=
= RTS_NumSounds
=
====================
*/

int32 RTS_NumSounds (void)
   {
   return numlumps-1;
   }

/*
====================
=
= RTS_SoundLength
=
= Returns the buffer size needed to load the given lump
=
====================
*/

int32 RTS_SoundLength (int32 lump)
   {
   lump++;
   if (lump >= numlumps)
      Error ("RTS_SoundLength: %i >= numlumps",lump);
   return lumpinfo[lump].size;
   }

/*
====================
=
= RTS_GetSoundName
=
====================
*/

char * RTS_GetSoundName (int32 i)
   {
   i++;
   if (i>=numlumps)
      Error ("RTS_GetSoundName: %i >= numlumps",i);
   return &(lumpinfo[i].name[0]);
   }

/*
====================
=
= RTS_ReadLump
=
= Loads the lump into the given buffer, which must be >= RTS_SoundLength()
=
====================
*/
void RTS_ReadLump (int32 lump, void *dest)
   {
   lumpinfo_t *l;

   if (lump >= numlumps)
      Error ("RTS_ReadLump: %i >= numlumps",lump);
   if (lump < 0)
      Error ("RTS_ReadLump: %i < 0",lump);
   l = lumpinfo+lump;
   lseek (l->handle, l->position, SEEK_SET);
   SafeRead(l->handle,dest,l->size);
   }

/*
====================
=
= RTS_GetSound
=
====================
*/
void *RTS_GetSound (int32 lump)
{
   lump++;
   if ((uint32)lump >= numlumps)
      Error ("RTS_GetSound: %i >= %i\n",lump,numlumps);

   if (lumpcache[lump] == NULL)
   {
      lumplockbyte[lump] = 200;
      allocache((char *)&lumpcache[lump],(long)RTS_SoundLength(lump-1),&lumplockbyte[lump]);
      RTS_ReadLump(lump, lumpcache[lump]);
   }
   else
   {
      if (lumplockbyte[lump] < 200)
         lumplockbyte[lump] = 200;
      else
         lumplockbyte[lump]++;
   }
   return lumpcache[lump];
}

