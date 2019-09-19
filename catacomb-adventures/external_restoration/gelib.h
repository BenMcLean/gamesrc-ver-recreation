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

#include "SL_FILE.h"


///////////////////////////////////////////////////////////////////////////
//
// Defines
//

#define ANIM_USES_SHAPE_TABLE false
#define PI_MAX_ANIMS 10
#define PI_MAX_PAGES	40

#define SAVEVER_DATA "0.01"
#define FILENAME_LEN 15

#define  GAMENAME		"CATACOMB  APOCALYPSE 3-D"
#define	VERSION		"1.01"
#define  REVISION		"(rev 1)"

//#define BOBLIST 1                          //SP - Undefine if not using BOBList

#define AUDIO_DISK		(2)
#define VIDEO_DISK		(1)
#define LEVEL_DISK		(2)

#define BIO_BUFFER_LEN	(512)

//#define TrashProg Quit

//   #define AMIGA


//typedef struct {
//	memptr textptr;
//	char far *pages[MAX_TEXT_PAGES];
//	short totalpages;
//} textinfo;

#if 0
typedef struct {
	int handle;			// handle of file
	memptr buffer;		// pointer to buffer
	word offset;		// offset into buffer
	word status;		// read/write status
} BufferedIO;
#endif

typedef enum ANIMINFO {at_NONE,at_INIT,at_WAIT,at_ONCE,at_CYCLE,
							  at_REBOUND,at_EXTRA,
							  at_FWD,at_REV
} ANIMINFO;

struct BitMapHeader {
	unsigned int	w,h,x,y;
	unsigned char	d,trans,comp,pad;
};

struct BitMap {
	unsigned int Width;
	unsigned int Height;
	unsigned int Depth;
	unsigned int BytesPerRow;
	char far *Planes[8];
};

struct Shape {
	memptr Data;
	long size;
	unsigned int BPR;
	struct BitMapHeader bmHdr;
};


///////////////////////////////////////////////////////////////////////////
//
// Function prototypes
//
void MoveGfxDst(short x, short y);
//void DisplayText(textinfo *textinfo);
//long LoadTextFile(char *filename,textinfo *textinfo);
//void FreeTextFile(textinfo *textinfo);
//void InitTextFile(textinfo *textinfo);
long Verify(char *filename);

#ifdef BOBLIST


boolean UpdateBOBList(objtype *obj,struct Simple_Shape *Shape,shapeclass Class, short priority, spriteflags sprflags);
boolean RemoveBOBShape(objtype *obj, shapeclass Class);
void RemoveBOBList(objtype *obj);
void InitBOBList(objtype *obj, struct BOB_Shape *BOB_Shape, short NumElements);
void RefreshBOBList(objtype *obj);
#endif


unsigned long BLoad(char *SourceFile, memptr *DstPtr);
//void lzwDecompressFromRAM(byte far *SrcPtr, byte far *DstPtr, longword SrcLen);
//void lzwDecompressFromFile(BufferedIO *SrcPtr, byte far *DstPtr, longword SrcLen);
byte readch(int handle);

void SwapLong(long far *Var);
void SwapWord(unsigned int far *Var);
int LoadShape(char *Filename,struct Shape *SHP);
void FreeShape(struct Shape *shape);
int UnpackEGAShapeToScreen(struct Shape *SHP,int startx,int starty);
