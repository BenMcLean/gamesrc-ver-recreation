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

/* Reconstructed from the DEMOCAT.EXE file bundled with The Catacomb
 * Abyss Shareware v1.13, using available source files; Then modified to
 * optionally behave like any of the HINTCAT.EXE files from the last retail
 * release (Abyss v1.24, Armageddon v1.02, Apocalypse v1.01).
 */

#include <conio.h>
#include <stdarg.h>
#include <time.h>

#include "heads.h"
#include "gelib.h"

// File names
#ifdef GAMEVER_SHAREWARE
#define END_SCREEN "LAST.CAT"
#define SCRIPT_FILENAME "SCRIPT.CAT"
#else
#define SCRIPT_FILENAME "SCRIPT.HNT"
#endif

// Misc. text definitions
#ifdef GAMEVER_SHAREWARE

#define FRAMETOP_STR  "\xD5\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB8\r\n"
#define TITLE_STR     "\xB3 GAMER'S EDGE Electronic Catalog      \xB3\r\n"
#define AUTHOR_STR    "\xB3 by Nolan Martin                      \xB3\r\n"
#define COPYRIGHT_STR "\xB3 Copyright 1992 - Softdisk Publishing \xB3\r\n"
#define FRAMEBOT_STR  "\xD4\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBE\r\n"

#define VERSION_TITLE_STR "ELECTRONIC CATALOG"
#define VERSION_REV_STR " VERSION 1.00   QA[0]"

#elif (defined GAMEVER_CATABYSS)

#define FRAMETOP_STR  "\xD5\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB8\r\n"
#define TITLE_STR     "\xB3 CATACOMB ABYSS 3-D HINT BOOK            \xB3\r\n"
#define AUTHOR_STR    "\xB3 by Nolan Martin                         \xB3\r\n"
#define COPYRIGHT_STR "\xB3 Copyright 1992-93 - Softdisk Publishing \xB3\r\n"
#define FRAMEBOT_STR  "\xD4\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBE\r\n"

#define VERSION_TITLE_STR "CATACOMB ABYSS 3-D HINT BOOK"
#define VERSION_REV_STR " VERSION 1.01 rev 1"

#elif (defined GAMEVER_CATARM)

#define FRAMETOP_STR  "\xD5\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB8\r\n"
#define TITLE_STR     "\xB3 CATACOMB ARMAGEDDON 3-D HINT BOOK        \xB3\r\n"
#define AUTHOR_STR    "\xB3 by Nolan Martin                          \xB3\r\n"
#define COPYRIGHT_STR "\xB3 Copyright 1992-93 - Softdisk Publishing  \xB3\r\n"
#define FRAMEBOT_STR  "\xD4\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBE\r\n"

#define VERSION_TITLE_STR "CATACOMB ARMAGEDDON 3-D HINT BOOK"
#define VERSION_REV_STR " version 1.12  (Rev 1)"

#elif (defined GAMEVER_CATAPOC)

#define FRAMETOP_STR  "\xD5\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB8\r\n"
#define TITLE_STR     "\xB3 CATACOMB APOCALYPSE 3-D HINT BOOK       \xB3\r\n"
#define AUTHOR_STR    "\xB3 by Nolan Martin                         \xB3\r\n"
#define COPYRIGHT_STR "\xB3 Copyright 1992-93 - Softdisk Publishing \xB3\r\n"
#define FRAMEBOT_STR  "\xD4\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBE\r\n"

#define VERSION_TITLE_STR "CATACOMB APOCALYPSE 3-D HINT BOOK"
#define VERSION_REV_STR " VERSION 1.13  (Rev 1)"

#endif

void SetScreenMode (int mode);
void SetLineWidth (int width);
static boolean IsKeyPressed (void);
void WaitForKeyRelease (void);
static void Beep (void);

int screenmode;
#ifdef GAMEVER_SHAREWARE
long pg_t_end, pg_t_str;
#endif
int pg_curr;

byte far *pg_scr[30];

static boolean havebeep = true;
static int pg_last = 0;
static boolean returntointro = false;
static boolean returntostart = false;

cardtype videocard;

struct Shape page_shapes[30];

#ifdef GAMEVER_SHAREWARE
static char *ParmStrings[] = {"auto","ver","s",NULL};
#else
static char *ParmStrings[] = {"ver","s",NULL};
#endif

void main(void)
{
	word last_key;
	byte far *script_file_ptr = NULL, far *script_ptr = NULL;
#ifdef GAMEVER_SHAREWARE
	boolean leave_loop = false, page_changed = false, auto_mode = false;
#else
	boolean leave_loop = false, page_changed = false;
#endif
	int i = 0, j, pages_left;

	if (!stricmp(_argv[1], "/?"))
	{
		clrscr();
		textcolor(15);
		textbackground(1);
		cprintf(FRAMETOP_STR);
		cprintf(TITLE_STR);
		cprintf(AUTHOR_STR);
		cprintf(COPYRIGHT_STR);
		cprintf(FRAMEBOT_STR);
		printf("\n");
		printf("/VER  - version number\n");
#ifdef GAMEVER_SHAREWARE
		printf("/AUTO - auto mode\n");
#endif
		printf("/S    - turn sound mode off\n");
		printf("/?    - this help\n");
		exit(0);
	}

	for (j=1;j<_argc;j++)
		switch (CheckParm(_argv[j], ParmStrings))
		{
#ifdef GAMEVER_SHAREWARE
#define PARAM_OFFSET 1
#else
#define PARAM_OFFSET 0
#endif
#ifdef GAMEVER_SHAREWARE
		case 0:
			auto_mode = true;
			break;
#endif
		case PARAM_OFFSET:
			clrscr();
			textcolor(15);
			textbackground(1);
			cprintf(FRAMETOP_STR);
			cprintf(TITLE_STR);
			cprintf(AUTHOR_STR);
			cprintf(COPYRIGHT_STR);
			cprintf(FRAMEBOT_STR);
			printf("\n");
			printf("%s %s\n", VERSION_TITLE_STR, VERSION_REV_STR);
			printf("\n");
			printf("This program requires an EGA monitor or better,\n");
			printf("                640K, and MS-DOS 3.0 or better.\n");
			exit(0);
			break;
		case PARAM_OFFSET+1:
			havebeep = false;
			break;
		}

#ifdef GAMEVER_SHAREWARE
	if (!stricmp(_argv[1], "#*-NM"))
		returntostart = true;
	else if (!stricmp(_argv[1], "^(a@&r`"))
		returntointro = true;
#endif
	videocard = VideoID();
	if ((videocard != 3) && (videocard != 5))
		TrashProg("You need an EGA or VGA monitor to run this program.");
	screenmode = 1;
	SetScreenMode(screenmode);
	_setcursortype(_NOCURSOR);

	ShowTextScreen(0);

	for (i=0;i<30;i++)
	{
		pg_scr[i] = farmalloc(14);
	}

	if (!BLoad(SCRIPT_FILENAME, &script_file_ptr))
		TrashProg("Can't load Script File - Possibly corrupt file!");

	i = 0;
	while (*script_file_ptr != 0x40)
	{
		for (;*script_file_ptr!=0xD;script_file_ptr++,i++)
		{
			*(pg_scr[pg_last] + i) = *script_file_ptr;
		}
		*(pg_scr[pg_last] + i) = 0;
		i = 0;
		script_file_ptr++;
		script_file_ptr++;
		if (*script_file_ptr != 0x40)
			pg_last++;
	}
	// VERSION RESTORATION - Yeah, pointer variable's may have changed,
	// but this is still the one passed to the function
	farfree(script_file_ptr);

	pages_left = pg_last + 1;
	for (i=0;i<=pg_last;i++)
	{
		if (IsKeyPressed())
			last_key = TryGetKey();
		// VERSION RESTORATION - Yeah, there's possibly an access to an uninitialized var here!
		if (last_key == 0x11B)
		{
			pg_last = pg_last - pages_left;
			TrashProg(NULL);
		}
		script_ptr = pg_scr[i];
		if (*script_ptr++ == 0x5E)
		{
			int k;
			char numstr[3], filename[13];
			itoa(pages_left--,numstr,10);
			textbackground(4);
			WriteColoredTextAt(14,56,6,"   ");
			WriteColoredTextAt(206,56,6,numstr);
			textbackground(0);
			switch (*script_ptr++)
			{
			case 0x56:
				TrashProg("VGA not available at the moment!\n");
				break;
			case 0x45:
				memset(filename,' ',13);
				for (k=0;k<12;k++)
					filename[k] = *script_ptr++;
				filename[12] = 0;
				if (LoadShape(filename, &page_shapes[i]))
					TrashProg( GAMEVER_SLIDECAT_ERR_STR " : Can't load image.");
				break;
			case 0x54:
				memset(filename,' ',13);
				for (k=0;k<12;k++)
					filename[k] = *script_ptr++;
				filename[12] = 0;
				if (!BLoad(filename, &page_shapes[i].Data))
					TrashProg("Can't load Compressed Text - Possibly corrupt file!");
				break;
			}
		}
		else
			TrashProg( GAMEVER_SLIDECAT_ERR_STR " : Bad script code.\n\n");
	}

	pg_curr = 0;
#ifdef GAMEVER_SHAREWARE
	pg_t_str = time(NULL);
	pg_t_end = pg_t_str;
#endif
	while (!leave_loop)
	{
		script_ptr = pg_scr[pg_curr];
		if (*script_ptr == 0x5E)
		{
			script_ptr++;
			switch (*script_ptr++)
			{
			case 0x56:
				TrashProg("VGA function not available yet!\n");
				break;
			case 0x45:
				if (screenmode != 3)
				{
					screenmode = 3;
					SetScreenMode(screenmode);
					SetScreen(0,0);
				}
				displayofs = 0;
				MoveGfxDst(0, 200);
				UnpackEGAShapeToScreen(&page_shapes[pg_curr], 0, 0);
				ScreenToScreen(8000, 0, 40, 200);
				Beep();
				break;
			case 0x54:
				if (screenmode != 1)
				{
					screenmode = 1;
					SetScreenMode(screenmode);
					_setcursortype(_NOCURSOR);
				}
				_fmemcpy(MK_FP(0xB800,0), (byte far *)(page_shapes[pg_curr].Data)+7, 4000);
				Beep();
				break;
			}
		}
		else
			TrashProg( GAMEVER_SLIDECAT_ERR_STR " : Bad script code\n");

#ifdef GAMEVER_SHAREWARE
		if (auto_mode)
		{
			byte s;
			for (s=0;s<=50;s++)
			{
				delay(100);
				last_key = TryGetKey();
				if (last_key)
				{
					if (last_key == 0x11B)
						TrashProg(NULL);
					else
					{
						auto_mode = false;
						page_changed = false;
						goto check_keys;
					}
				}
			}
			if (++pg_curr > pg_last)
				pg_curr = 0;
		}
		else
#endif
		{
#ifdef GAMEVER_SHAREWARE
			boolean halt_wait_for_key;
#endif
			page_changed = false;
			WaitForKeyRelease();
			while (!page_changed)
			{
				last_key = 0;
#ifdef GAMEVER_SHAREWARE
				halt_wait_for_key = false;
				while (!halt_wait_for_key)
				{
					last_key = TryGetKey();
					if (last_key)
						halt_wait_for_key = true;

					if (difftime(pg_t_end, pg_t_str) > 90.0f)
					{
						last_key = 0;
						halt_wait_for_key = true;
						page_changed = true;
						auto_mode = true;
						if (++pg_curr > pg_last)
							pg_curr = 0;
						break;
					}
					pg_t_end = time(NULL);
				}

				if (auto_mode)
					break;
check_keys:
				pg_t_str = pg_t_end = time(NULL);
#else
				while (!last_key)
					last_key = TryGetKey();
#endif
				switch (last_key)
				{
				case 0x4D36:
				case 0x4D00:
				case 0x5100:
				case 0x5000:
				case 0x5032:
				case 0x5133:
					if (++pg_curr > pg_last)
						pg_curr = 0;
					page_changed = true;
					break;
				case 0x4B00:
				case 0x4900:
				case 0x4800:
				case 0x4838:
				case 0x4939:
				case 0x4B34:
					if (!pg_curr)
						pg_curr = pg_last;
					else
						pg_curr--;
					page_changed = true;
					break;
				case 0x4737:
				case 0x4700:
					if (pg_curr)
					{
						pg_curr = 0;
						page_changed = true;
					}
					break;
				case 0x4F31:
				case 0x4F00:
					if (pg_curr < pg_last)
					{
						pg_curr = pg_last;
						page_changed = true;
					}
					break;
				case 0x11B:
					TrashProg(NULL);
					break;
#ifdef GAMEVER_SHAREWARE
				case 0x1970:
				case 0x1950:
					PrinterDialog();
					break;
#endif
				default:
					if (screenmode != 1)
					{
						SetScreenMode(1);
						_setcursortype(_NOCURSOR);
					}
					ShowTextScreen(1);
					WaitForKeyRelease();
					while (!(last_key = TryGetKey()))
						;
					last_key = 0;
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
					break;
				}
			}
		}
	}
	TrashProg("End of loop reached???????\n");
}

void TrashProg (char *OutMsg, ...)
{
	va_list ap;

	memptr endscreen = NULL;
	int i;

	for (i=0;i<30;i++)
		farfree(pg_scr[i]);
	for (i=0;i<=pg_last;i++)
		if (page_shapes[i].Data)
			FreeShape(&page_shapes[i]);

	WaitForKeyRelease();
	SetScreenMode(1);

	if (!(*OutMsg))
	{
#ifdef GAMEVER_SHAREWARE
		if (returntostart)
		{
			if (execv("START.EXE", _argv) == -1)
			{
				printf("ERROR : Can't find executable.\n");
				exit(0);
			}
		}
		else if (returntointro)
		{
			if (execv("INTRO.EXE", _argv) == -1)
			{
				printf("ERROR : Can't find executable.\n");
				exit(0);
			}
		}
		else
		{
			if (!BLoad(END_SCREEN, &endscreen))
			{
				// VERSION RESTORATION - The way printf is called here
				// is the reason we use the macro END_SCREEN, rather
				// than a direct mention of the string
				printf("ERROR : Can't load end screen, %s\n", END_SCREEN);
				exit(0);
			}
			_fmemcpy(MK_FP(0xB800,0), (byte far *)endscreen+7, 4000);
			farfree(endscreen);
			gotoxy(1,24);
		}
#elif (defined GAMEVER_CATABYSS)
		exit(0);
#endif
	}
	else
		printf(OutMsg);

	WaitForKeyRelease();
	exit(0);
}

void SetScreenMode (int mode)
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

void SetLineWidth (int width)
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

void WaitForKeyRelease (void)
{
	if (IsKeyPressed())
		while (IsKeyPressed())
			getch();
}


static void Beep(void)
{
	if (havebeep)
	{
		sound(100);
		delay(1);
		nosound();
	}
}


///////////////////////////////////////////////////////////////////////////
//
//      US_CheckParm() - checks to see if a string matches one of a set of
//              strings. The check is case insensitive. The routine returns the
//              index of the string that matched, or -1 if no matches were found
//
///////////////////////////////////////////////////////////////////////////
int
CheckParm(char *parm,char **strings)
{
	char    cp,cs,
			*p,*s;
	int             i;

	while (!isalpha(*parm)) // Skip non-alphas
		parm++;

	for (i = 0;*strings && **strings;i++)
	{
		for (s = *strings++,p = parm,cs = cp = 0;cs == cp;)
		{
			cs = *s++;
			if (!cs)
				return(i);
			cp = *p++;

			if (isupper(cs))
				cs = tolower(cs);
			if (isupper(cp))
				cp = tolower(cp);
		}
	}
	return(-1);
}
