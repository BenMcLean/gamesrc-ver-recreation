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

/* Reconstructed from the LOADSCN.EXE file bundled with The Catacomb Abyss
 * Shareware v1.13, using available source files
 */

#include <stdarg.h>

#include "heads.h"
#include "gelib.h"

static void SetScreenMode (int mode);
static void SetLineWidth (int width);
static boolean IsKeyPressed (void);
static void WaitForKeyRelease (void);

memptr endscreen;
struct Shape imagetoshow;
cardtype videocard;
int screenmode;

void main (void)
{
	int step;
	boolean pressedkey = false;
	if (!stricmp(_argv[1], "/?"))
	{
		clrscr();
		textcolor(15);
		textbackground(1);
		cprintf("\xD5\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB8\r\n");
		cprintf("\xB3 LOADSCN                              \xB3\r\n");
		cprintf("\xB3 by Nolan Martin                      \xB3\r\n");
		cprintf("\xB3 Copyright 1992 - Softdisk Publishing \xB3\r\n");
		cprintf("\xD4\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBE\r\n");
		printf("\n");
		printf("/VER  - version number\n");
		printf("/?    - this help\n");
		exit(0);
	}
	if (!stricmp(_argv[1], "/VER"))
	{
		clrscr();
		textcolor(15);
		textbackground(1);
		cprintf("\xD5\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB8\r\n");
		cprintf("\xB3 LOADSCN                              \xB3\r\n");
		cprintf("\xB3 by Nolan Martin                      \xB3\r\n");
		cprintf("\xB3 Copyright 1992 - Softdisk Publishing \xB3\r\n");
		cprintf("\xD4\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBE\r\n");
		printf("\n");
		printf("%s %s\n", "LOADSCN  ", " VERSION 1.10s   QA[0]");
		printf("\n");
		printf("This program requires an EGA monitor or better,\n");
		printf("                640K, and MS-DOS 3.0 or better.\n");
		exit(0);
	}
	if (stricmp(_argv[1], "LAST.SHL"))
		TrashProg("You must type START [ENTER] to run this program.\n");
	videocard = VideoID();
	if ((videocard != 3) && (videocard != 5))
		TrashProg("You need an EGA or VGA monitor to run this program.");
	screenmode = 3;
	SetScreenMode(screenmode);
	SetScreen(0,0);
	if (LoadShape("ARMAPC.ABS", &imagetoshow))
		TrashProg("ERROR : Can't load image.");
	MoveGfxDst(0, 200);
	UnpackEGAShapeToScreen(&imagetoshow, 0, 0);
	ScreenToScreen(8000, 0, 40, 200);
	for (step = 0; step < 10; ++step)
	{
		delay(500);
		if (IsKeyPressed())
		{
			pressedkey = true;
			WaitForKeyRelease();
		}
	}
	if (!pressedkey)
		bioskey(0);
	if (!BLoad("LAST.ABS", &endscreen))
		TrashProg("Can't load Compressed Text - Possibly corrupt file!");
	screenmode = 1;
	SetScreenMode(screenmode);
	_fmemcpy(MK_FP(0xB800,0), (byte far *)endscreen+7, 4000);
	gotoxy(1, 24);
	exit(0);
}

void TrashProg (char *OutMsg, ...)
{
	va_list ap;

	if (OutMsg)
	{
		if (screenmode != 1)
			SetScreenMode(1);

		va_start(ap, OutMsg);

		if (OutMsg && *OutMsg)
			vprintf(OutMsg,ap);

		va_end(ap);
	}

	exit(0);
}

static void SetScreenMode (int mode)
{
	switch (mode)
	{
	case 1:
		_AX = 3;
		geninterrupt (0x10);
		SetLineWidth(80);
		break;
	case 3:
		_AX = 0xd;
		geninterrupt (0x10);
		SetLineWidth(40);
		break;
	}
}

//===========================================================================

/*
====================
=
= VW_SetLineWidth
=
= Must be an even number of bytes
=
====================
*/

static void SetLineWidth (int width)
{
  int i,offset;

#if GRMODE == EGAGR
//
// set wide virtual screen
//
asm	mov	dx,CRTC_INDEX
asm	mov	al,CRTC_OFFSET
asm mov	ah,[BYTE PTR width]
asm	shr	ah,1
asm	out	dx,ax
#endif

//
// set up lookup tables
//
  //linewidth = width;

  offset = 0;

  for (i=0;i<VIRTUALHEIGHT;i++)
  {
	ylookup[i]=offset;
	offset += width;
  }
}


//===========================================================================

static boolean IsKeyPressed (void)
{
asm	mov ah, 1
asm	int 0x16
asm	jnz is_pressed

	return false;
	
is_pressed:
	return true;
}

static void WaitForKeyRelease (void)
{
	if (IsKeyPressed())
		while (IsKeyPressed())
			getch();
}
