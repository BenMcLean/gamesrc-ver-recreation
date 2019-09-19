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
 * Shareware v1.13; Later modified to optionally behave like DEMECAT.EXE
 * as bundled with the same shareware release, as well as the
 * differing HINTCAT.EXE files from the last retail release
 * (Abyss v1.24, Armageddon v1.02, Apocalypse v1.01).
 */

#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <dir.h>
#include "mem.h"
#include "string.h"
#include "time.h"
#include "stdarg.h"
#include "io.h"

#include "HEADS.H"
#include "gelib.h"
#include "sl_file.h"


#define MAX_GAMELIST_NAMES 20
#define FNAME_LEN				9

#ifdef GAMEVER_SLIDECAT
extern byte far textscn[];
extern struct Shape page_shapes[];
extern int pg_curr;
extern int screenmode;
#endif
unsigned ylookup[VIRTUALHEIGHT];
unsigned displayofs;

////////////////////////////////////////////////////////////////////////////
//
// UnpackEGAShapeToScreen()
//
int UnpackEGAShapeToScreen(struct Shape *SHP,int startx,int starty)
{
	int currenty;
	signed char n, Rep, far *Src, far *Dst[8], loop, Plane;
	unsigned int BPR, Height;
	boolean NotWordAligned;

	NotWordAligned = SHP->BPR & 1;
	startx>>=3;
	Src = SHP->Data;
	currenty = starty;
	Plane = 0;
	Height = SHP->bmHdr.h;
	while (Height--)
	{
		Dst[0] = (MK_FP(0xA000,displayofs));
		Dst[0] += ylookup[currenty];
		Dst[0] += startx;
		for (loop=1; loop<SHP->bmHdr.d; loop++)
			Dst[loop] = Dst[0];


		for (Plane=0; Plane<SHP->bmHdr.d; Plane++)
		{
			outport(0x3c4,((1<<Plane)<<8)|2);

			BPR = ((SHP->BPR+1) >> 1) << 1;               // IGNORE WORD ALIGN
			while (BPR)
			{
				if (SHP->bmHdr.comp)
					n = *Src++;
				else
					n = BPR-1;

				if (n < 0)
				{
					if (n != -128)
					{
						n = (-n)+1;
						BPR -= n;
						Rep = *Src++;
						if ((!BPR) && (NotWordAligned))   // IGNORE WORD ALIGN
							n--;

						while (n--)
							*Dst[Plane]++ = Rep;
					}
					else
						BPR--;
				}
				else
				{
					n++;
					BPR -= n;
					if ((!BPR) && (NotWordAligned))     // IGNORE WORD ALIGN
						n--;

					while (n--)
						*Dst[Plane]++ = *Src++;

					if ((!BPR) && (NotWordAligned))     // IGNORE WORD ALIGN
						Src++;
				}
			}
		}
		currenty++;
	}

	return(0);
}

////////////////////////////////////////////////////////////////////////////
//
// Verify()
//
long Verify(char *filename)
{
	int handle;
	long size;

	if ((handle=open(filename,O_RDONLY))!=-1)
	{
		size=filelength(handle);
		close(handle);
	}
	else
	{
		size=0;
	}
	return(size);
}

// Unused in loadscn, used in intro and democat
int TryGetKey()
{
asm	mov ah, 1
asm	int 0x16
asm	mov ax, 0
asm	jz after_loop
asm	int 0x16
asm	mov bx, ax
asm	mov ah, 2
asm	int 0x16
asm	and ax, 0xc
asm	mov cl, 3
asm	shr al, cl
asm	adc al, 0
asm	shr ax, 1
asm	ror ax, 1
asm	or ax, bx

after_loop:
	return _AX;
}

#ifdef GAMEVER_SLIDECAT

#ifndef GAMEVER_CATARM
int IsPrinterAvailable(void)
{
	union REGS regs;
	regs.h.ah = 2;
	regs.x.dx = 0;
	int86(0x17,&regs,&regs);
	if (regs.h.ah == 0x90)
		return 1;
	else
		return 0;
}

void PageBreak(void)
{
asm	mov ah, 5
asm	mov dl, 0xc
asm	int 0x21
}
#endif

void WriteColoredTextAt(int color, int x, int y, char *text)
{
	textcolor(color);
	gotoxy(x,y);
	cprintf(text);
}

#ifdef GAMEVER_SHAREWARE
void PrinterDialog(void)
{
	char str[81];
	int last_key;
	boolean do_finish, leave_loop, got_selection;
	byte far *textptr, far *s;

	leave_loop = false;
	textbackground(7);
	if (screenmode != 1)
	{
		SetScreenMode(1);
		_setcursortype(_NOCURSOR);
	}
	movedata(FP_SEG(textscn),FP_OFF(textscn),0xb800,0,4000);

	while (!leave_loop)
	{
		got_selection = false;
		WriteColoredTextAt(0,27,5,"You have chosen to print out");
		WriteColoredTextAt(0,25,6,"the \"written information\" section");
		WriteColoredTextAt(0,37,7,"of this");
		WriteColoredTextAt(1,34,9,"GAMER'S EDGE");
		WriteColoredTextAt(1,31,10,"Electronic Catalog");
		WriteColoredTextAt(1,35,11,"Volume #1");
		WriteColoredTextAt(0,7,13,"Your options now are as follows:");
		WriteColoredTextAt(0,10,14,"1. Prepare your printer to print.");
		WriteColoredTextAt(0,10,15,"2. Press       to print out the \"written information\" section.");
		WriteColoredTextAt(4,19,15,"ENTER");
		WriteColoredTextAt(0,10,16,"3. Press     at any time to abort this printing operation.");
		WriteColoredTextAt(4,19,16,"ESC");
		WriteColoredTextAt(0,7,19,"If you have difficulty using this GAMER'S EDGE Electronic Catalog,");
		WriteColoredTextAt(0,8,20,"or, if you have any questions about the products presented here,");
		WriteColoredTextAt(0,22,21,"or, if you wish to make a purchase,");
		WriteColoredTextAt(0,8,22,"please call               , M-F 8am-5pm CST, for immediate help.");
		WriteColoredTextAt(5,20,22,"1-800-831-2694");

		while (!got_selection)
		{
			last_key = TryGetKey();
			if ((last_key == 0x11B) || (last_key == 0x1C0D))
				got_selection = true;
		}

		if (last_key == 0x11B)
		{
			leave_loop = true;
			continue;
		}

		if (IsPrinterAvailable())
		{
			textptr = 0;
			do_finish = false;

			movedata(FP_SEG(textscn),FP_OFF(textscn),0xb800,0,4000);
			WriteColoredTextAt(0,35,11,"Now Printing");
			WriteColoredTextAt(0,32,14,"Press");
			WriteColoredTextAt(4,38,14,"ESC");
			WriteColoredTextAt(0,42,14,"to abort.");

			if (!BLoad("PRINTFIL.TXT",&textptr))
				TrashProg("Can't load Compressed Printer Text - Possibly corrupt file!");

			last_key = 0;
			while (!do_finish)
			{
				memset(str, ' ', 80);
				s = str;
				while (*textptr == '\r')
				{
					fprintf(stdprn,"\r\n");
					textptr += 2;
				}

				if (*textptr == 0x5E)
				{
					PageBreak();
					textptr += 3;
				}

				if (*textptr == 0x40)
				{
					do_finish = true;
					break;
				}

				while (*textptr != '\r')
					*s++ = *textptr++;
				str[80-1] = '\0';

				fprintf(stdprn,str);
				fprintf(stdprn,"\r\n");

				textptr += 2;

				last_key = TryGetKey();
				if (last_key == 0x11B)
				{
					movedata(FP_SEG(textscn),FP_OFF(textscn),0xb800,0,4000);
					textcolor(15);
					textbackground(4);
					gotoxy(30,12);
					cprintf("  Printing Aborted  ");
					do_finish = true;
					textbackground(7);
					continue;
				}
			}

			if (last_key != 0x11B)
			{
				movedata(FP_SEG(textscn),FP_OFF(textscn),0xb800,0,4000);
				WriteColoredTextAt(0,32,11,"Printing is Done.");
				WriteColoredTextAt(4,28,14,"Press any key to continue.");
				WaitForKeyRelease();
				while (!TryGetKey())
					;
			}
			leave_loop = true;
		}
		else
		{
			do_finish = false;
			movedata(FP_SEG(textscn),FP_OFF(textscn),0xb800,0,4000);
			WriteColoredTextAt(4,28,10,"There seems to be a problem");
			WriteColoredTextAt(4,31,12,"starting the printer.");
			WriteColoredTextAt(4,23,14,"Please check again, then press ENTER.");

			while (!do_finish)
			{
				last_key = TryGetKey();
				if ((last_key == 0x11B) || (last_key == 0x1C0D))
					do_finish = true;
			}

			if (last_key == 0x11B)
				leave_loop = true;
			else
				movedata(FP_SEG(textscn),FP_OFF(textscn),0xb800,0,4000);
		}
	}

	switch (screenmode)
	{
	case 1:
		_fmemcpy(MK_FP(0xB800,0), (byte far *)(page_shapes[pg_curr].Data)+7, 4000);
		break;
	case 3:
		SetScreenMode(screenmode);
		displayofs = 0;
		MoveGfxDst(0, 200);
		UnpackEGAShapeToScreen(&page_shapes[pg_curr], 0, 0);
		ScreenToScreen(8000, 0, 40, 200);
		break;
	}
}
#endif

void ShowTextScreen(int screen)
{
	int offset = 0;
	movedata(FP_SEG(textscn),FP_OFF(textscn),0xb800,0,4000);
	textbackground(7);

	if (!screen)
	{
		textbackground(4);
#ifdef GAMEVER_SHAREWARE
		WriteColoredTextAt(14,5,3," GAMER'S EDGE Electronic Catalog - Vol.1 - The Catacomb 3-D Adventures  ");
#elif (defined GAMEVER_CATABYSS)
		WriteColoredTextAt(14,5,3,"              Hints & Solutions for THE CATACOMB ABYSS 3-D              ");
#elif (defined GAMEVER_CATARM)
		WriteColoredTextAt(14,5,3,"           Hints & Solutions for THE CATACOMB ARMAGEDDON 3-D            ");
#elif (defined GAMEVER_CATAPOC)
		WriteColoredTextAt(14,5,3,"           Hints & Solutions for THE CATACOMB APOCALYPSE 3-D            ");
#endif
		WriteColoredTextAt(14,20,5," \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB ");
		WriteColoredTextAt(14,20,6," \xBA  Now loading, please stand by...    \xBA ");
		WriteColoredTextAt(14,20,7," \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC ");
		offset = 1;
		textbackground(7);
	}
	else
	{
		WriteColoredTextAt(4,29,3,"\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB");
		WriteColoredTextAt(4,29,4,"\xBA                      \xBA");
		WriteColoredTextAt(0,33,4,"How to use this");
		WriteColoredTextAt(4,15,5,"* HELP *");
		WriteColoredTextAt(4,29,5,"\xBA                      \xBA");
#ifdef GAMEVER_SHAREWARE
		WriteColoredTextAt(0,32,5,"Electronic Catalog");
#else
		WriteColoredTextAt(0,32,5,"    Hint Book     ");
#endif
		WriteColoredTextAt(4,59,5,"* HELP *");
		WriteColoredTextAt(4,29,6,"\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC");
	}

#ifdef GAMEVER_SHAREWARE
	WriteColoredTextAt(1,8,offset+8,"VIEWING THIS ELECTRONIC CATALOG");
	WriteColoredTextAt(0,10,offset+9,"\xF9 Use the        or      keys to view the screens in this catalog.");
	WriteColoredTextAt(4,20,offset+9,"ARROWS");
	WriteColoredTextAt(4,30,offset+9,"PAGE");
	WriteColoredTextAt(0,10,offset+10,"\xF9 Use the      key to jump to the beginning of the catalog.");
	WriteColoredTextAt(4,20,offset+10,"HOME");
	WriteColoredTextAt(0,10,offset+11,"\xF9 Use the     key to jump to the end of the catalog.");
	WriteColoredTextAt(4,20,offset+11,"END");
	WriteColoredTextAt(1,8,offset+13,"PRINTING THIS ELECTRONIC CATALOG");
	WriteColoredTextAt(0,10,offset+14,"\xF9 Press the     key at any time for a print out of more");
	WriteColoredTextAt(4,22,offset+14,"\"P\"");
	WriteColoredTextAt(0,12,offset+15,"information.");
	WriteColoredTextAt(1,8,offset+17,"QUITTING THIS ELECTRONIC CATALOG");
	WriteColoredTextAt(0,10,offset+18,"\xF9 Press the     key at any time to quit the catalog.");
	WriteColoredTextAt(4,22,offset+18,"ESC");
	WriteColoredTextAt(0,14,offset+20,"Call 1-800-831-2694 or 1-318-221-8718 if you're having");
	WriteColoredTextAt(0,14,offset+21,"             trouble running this program.");

	if (screen)
		WriteColoredTextAt(8,13,23,"- Press any key now to return to the Electronic Catalog. -");
#else

#ifdef GAMEVER_CATABYSS
#define EP_OFFSET 0
#else
#define EP_OFFSET 2
#endif

	WriteColoredTextAt(1,8,offset+8+EP_OFFSET,"VIEWING THE HINTS & SOLUTIONS SCREENS");
	WriteColoredTextAt(0,10,offset+9+EP_OFFSET,"\xF9 Use the        or      keys to view the screens.");
	WriteColoredTextAt(4,20,offset+9+EP_OFFSET,"ARROWS");
	WriteColoredTextAt(4,30,offset+9+EP_OFFSET,"PAGE");
	WriteColoredTextAt(0,10,offset+10+EP_OFFSET,"\xF9 Use the      key to jump to the beginning.");
	WriteColoredTextAt(4,20,offset+10+EP_OFFSET,"HOME");
	WriteColoredTextAt(0,10,offset+11+EP_OFFSET,"\xF9 Use the     key to jump to the end.");
	WriteColoredTextAt(4,20,offset+11+EP_OFFSET,"END");
	WriteColoredTextAt(1,8,offset+17-EP_OFFSET,"QUITTING THIS HINTS & SOLUTIONS PROGRAM");
	WriteColoredTextAt(0,10,offset+18-EP_OFFSET,"\xF9 Press the     key at any time to quit this program.");
	WriteColoredTextAt(4,22,offset+18-EP_OFFSET,"ESC");
#ifdef GAMEVER_CATABYSS
	WriteColoredTextAt(1,8,offset+20,"\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB");
	WriteColoredTextAt(1,8,offset+21,"\xBA                                                                 \xBA");
	WriteColoredTextAt(4,9,offset+21,"   This software is NOT shareware.  Please do not distribute!");
	WriteColoredTextAt(1,8,offset+22,"\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC");
#endif

	if (screen)
		WriteColoredTextAt(8,13,23,"  - Press any key now to return to Hints and Solutions. -");
#endif
}

#endif // GAMEVER_SLIDECAT

// MoveGfxDst()
//
void MoveGfxDst(short x, short y)
{
	unsigned address;

	address = (y*40)+(x/8);
	displayofs = address;
}
