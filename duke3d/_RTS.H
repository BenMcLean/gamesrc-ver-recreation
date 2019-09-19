#ifndef __rts_private__
#define __rts_private__

//===============
//   TYPES
//===============

typedef struct
   {
   char name[8];
   int32 handle,position,size;
   } lumpinfo_t;

typedef struct
   {
   char identification[4];              // should be IWAD
   int32 numlumps;
   int32 infotableofs;
   } wadinfo_t;

typedef struct
   {
   int32 filepos;
   int32 size;
   char name[8];
   } filelump_t;

#endif
