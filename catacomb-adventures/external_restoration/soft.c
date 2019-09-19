/* Catacomb Apocalypse Source Code
 * Copyright (C) 1993-2014 Flat Rock Software
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

/* Modified for building LOADSCN.EXE as bundled with The Catacomb Abyss
 * Shareware v1.13
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <alloc.h>
#include <fcntl.h>
#include <dos.h>
#include <io.h>

#include "heads.h"
#include "gelib.h"
#include "soft.h"
#include "lzw.h"
#include "lzhuff.h"
#include "jam_io.h"






//===========================================================================
//
//										SWITCHES
//
//===========================================================================

#define LZH_SUPPORT		1
#define LZW_SUPPORT		0




//=========================================================================
//
//
//								GENERAL LOAD ROUTINES
//
//
//=========================================================================



//--------------------------------------------------------------------------
// BLoad()			-- THIS HAS NOT BEEN FULLY TESTED!
//
// NOTICE : This version of BLOAD is compatable with JAMPak V3.0 and the
//				new fileformat...
//--------------------------------------------------------------------------
unsigned long BLoad(char *SourceFile, memptr *DstPtr)
{
	int handle;

	memptr SrcPtr = NULL;
	unsigned long i, j, k, r, c;
	word flags;
	byte Buffer[8];
	unsigned long SrcLen,DstLen;
	struct CMP1Header CompHeader;
	boolean Compressed = false;
	unsigned offset;


	memset((void *)&CompHeader,0,sizeof(struct CMP1Header));

	//
	// Open file to load....
	//

	if ((handle = open(SourceFile, O_RDONLY|O_BINARY)) == -1)
#ifdef GAMEVER_SLIDECAT
	{
		SetScreenMode(1);
		printf("\n" GAMEVER_SLIDECAT_ERR_STR " : Can't open file. %s\n\n",SourceFile);
		exit(0);
	}
#else
		return(0);
#endif

	//
	// Look for JAMPAK headers
	//

	read(handle,Buffer,4);

	if (!strncmp(Buffer,COMP,4))
	{
		//
		// Compressed under OLD file format
		//

		Compressed = true;
		SrcLen = Verify(SourceFile);

		read(handle,(void *)&CompHeader.OrginalLen,4);
		CompHeader.CompType = ct_LZW;
		if (!(*DstPtr = farmalloc(CompHeader.OrginalLen)))
#ifdef GAMEVER_SLIDECAT
		{
			SetScreenMode(1);
			printf("You need more \"free conventional memory\" in order to view the\n"
			       "Demo of the Catacomb 3-D Trilogy.  At least 588K free memory\n"
			       "is required.  Try renaming your AUTOEXEC.BAT and CONFIG.SYS\n"
			       "files to other names, then reboot your computer, and try again.\n\n\n"
			);
			exit(0);
		}
#else
			return(0);
#endif
		offset = 8;
	}
	else
	if (!strncmp(Buffer,CMP1,4))
	{
		//
		// Compressed under new file format...
		//

		Compressed = true;
		SrcLen = Verify(SourceFile);

		read(handle,(void *)&CompHeader,sizeof(struct CMP1Header));
		offset = 14;
		if (!(*DstPtr = farmalloc(CompHeader.OrginalLen)))
#ifdef GAMEVER_SLIDECAT
		{
			SetScreenMode(1);
			printf("You need more \"free conventional memory\" in order to view the\n"
			       "Demo of the Catacomb 3-D Trilogy.  At least 588K free memory\n"
			       "is required.  Try renaming your AUTOEXEC.BAT and CONFIG.SYS\n"
			       "files to other names, then reboot your computer, and try again.\n\n\n"
			);
			exit(0);
		}
#else
			return(0);
#endif
	}
	else
		DstLen = Verify(SourceFile);


	//
	// Load the file in memory...
	//

	if (Compressed)
	{
		DstLen = CompHeader.OrginalLen;

		if ((farcoreleft() < 2*SrcLen) && (CompHeader.CompType))
		{
			//if (!InitBufferedIO(handle,&lzwBIO))
			//	TrashProg("No memory for buffered I/O.");

			switch (CompHeader.CompType)
			{
				#if LZW_SUPPORT
				case ct_LZW:
					lzwDecompress((void far *)(long)handle,*DstPtr,CompHeader.OrginalLen,(SRC_FILE|DEST_MEM));
				break;
				#endif

				#if LZH_SUPPORT
				case ct_LZH:
					lzhDecompress((void far *)(long)handle,*DstPtr,CompHeader.OrginalLen,CompHeader.CompressLen,(SRC_FILE|DEST_MEM));
				break;
				#endif

				default:
					TrashProg("BLoad() - Unrecognized/Supported compression");
				break;
			}

			//FreeBufferedIO(&lzwBIO);
		}
		else
		{
			LoadFile(SourceFile,&SrcPtr);
			switch (CompHeader.CompType)
			{
				#if LZW_SUPPORT
				case ct_LZW:
					lzwDecompress((byte far *)SrcPtr+offset,*DstPtr,CompHeader.OrginalLen,(SRC_MEM|DEST_MEM));
				break;
				#endif

				#if LZH_SUPPORT
				case ct_LZH:
					lzhDecompress((byte far *)SrcPtr+offset,*DstPtr,CompHeader.OrginalLen,CompHeader.CompressLen,(SRC_MEM|DEST_MEM));
				break;
				#endif

				default:
					TrashProg("BLoad() - Unrecognized/Supported compression");
				break;
			}
			farfree(SrcPtr);
		}
	}
	else
		LoadFile(SourceFile,DstPtr);

	close(handle);
	return(DstLen);
}



///////////////////////////////////////////////////////////////////////////
//
// LoadShape()
//
int LoadShape(char *Filename,struct Shape *SHP)
{
	#define CHUNK(Name)	(	\
		(*ptr == *Name) &&	\
		(*(ptr+1) == *(Name+1)) &&	\
		(*(ptr+2) == *(Name+2)) &&	\
		(*(ptr+3) == *(Name+3)) \
	)


	int RT_CODE;
//	struct ffblk ffblk;
	FILE *fp;
	char CHUNK[5];
	char far *ptr;
	memptr IFFfile = NULL;
	unsigned long FileLen, size, ChunkLen;
	int loop;


	RT_CODE = 1;

	// Decompress to ram and return ptr to data and return len of data in
	//	passed variable...

	if (!(FileLen = BLoad(Filename,&IFFfile)))
		TrashProg("Can't load Compressed Shape - Possibly corrupt file!");

	// Evaluate the file
	//
	ptr = IFFfile;
	if (!CHUNK("FORM"))
		goto EXIT_FUNC;
	ptr += 4;

	FileLen = *(long far *)ptr;
	SwapLong((long far *)&FileLen);
	ptr += 4;

	if (!CHUNK("ILBM"))
		goto EXIT_FUNC;
	ptr += 4;

	FileLen += 4;
	while (FileLen)
	{
		ChunkLen = *(long far *)(ptr+4);
		SwapLong((long far *)&ChunkLen);
		ChunkLen = (ChunkLen+1) & 0xFFFFFFFE;

		if (CHUNK("BMHD"))
		{
			ptr += 8;
			SHP->bmHdr.w = ((struct BitMapHeader far *)ptr)->w;
			SHP->bmHdr.h = ((struct BitMapHeader far *)ptr)->h;
			SHP->bmHdr.x = ((struct BitMapHeader far *)ptr)->x;
			SHP->bmHdr.y = ((struct BitMapHeader far *)ptr)->y;
			SHP->bmHdr.d = ((struct BitMapHeader far *)ptr)->d;
			SHP->bmHdr.trans = ((struct BitMapHeader far *)ptr)->trans;
			SHP->bmHdr.comp = ((struct BitMapHeader far *)ptr)->comp;
			SHP->bmHdr.pad = ((struct BitMapHeader far *)ptr)->pad;
			SwapWord(&SHP->bmHdr.w);
			SwapWord(&SHP->bmHdr.h);
			SwapWord(&SHP->bmHdr.x);
			SwapWord(&SHP->bmHdr.y);
			ptr += ChunkLen;
		}
		else
		if (CHUNK("BODY"))
		{
			ptr += 4;
			size = *((long far *)ptr);
			ptr += 4;
			SwapLong((long far *)&size);
			SHP->BPR = (SHP->bmHdr.w+7) >> 3;
			SHP->Data = farmalloc(size);
			if (!SHP->Data)
				goto EXIT_FUNC;
			movedata(FP_SEG(ptr),FP_OFF(ptr),FP_SEG(SHP->Data),FP_OFF(SHP->Data),size);
			ptr += ChunkLen;

			break;
		}
		else
			ptr += ChunkLen+8;

		FileLen -= ChunkLen+8;
	}

	RT_CODE = 0;

EXIT_FUNC:;
	if (IFFfile)
	{
//		segptr = (memptr)FP_SEG(IFFfile);
		farfree(IFFfile);
	}

	return (RT_CODE);
}


////////////////////////////////////////////////////////////////////////////
//
// FreeShape()
//
void FreeShape(struct Shape *shape)
{
	if (shape->Data)
		farfree(shape->Data);
}



///////////////////////////////////////////////////////////////////////////
//
// SwapLong()
//
void SwapLong(long far *Var)
{
	asm		les	bx,Var
	asm		mov	ax,[es:bx]
	asm		xchg	ah,al
	asm		xchg	ax,[es:bx+2]
	asm		xchg	ah,al
	asm 		mov	[es:bx],ax
}

///////////////////////////////////////////////////////////////////////////
//
// SwapWord()
//
void SwapWord(unsigned int far *Var)
{
	asm		les	bx,Var
	asm		mov	ax,[es:bx]
	asm		xchg	ah,al
	asm		mov	[es:bx],ax
}
