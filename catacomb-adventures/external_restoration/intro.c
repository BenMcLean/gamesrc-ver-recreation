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

/* Reconstructed from the INTRO.EXE file bundled with The Catacomb Abyss
 * Shareware v1.13, using available source files; Then modified to optionally
 * act like any of CATABYSS.EXE, CATARM.EXE or CATAPOC.EXE from the last
 * retail release (Abyss v1.24, Armageddon v1.02, Apocalypse v1.01).
 */

#include <conio.h>
#include <stdarg.h>

#include "heads.h"
#include "gelib.h"

#ifdef GAMEVER_CATABYSS
#define EXTENSION "ABS"
#elif defined GAMEVER_CATARM
#define EXTENSION "ARM"
#elif defined GAMEVER_CATAPOC
#define EXTENSION "APC"
#endif

#ifdef GAMEVER_SHAREWARE

#define FRAMETOP_STR  "\xD5\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB8\r\n"

#define TITLE_STR     "\xB3 GAMER'S EDGE Catacomb Abyss Introduction Program \xB3\r\n"
#define AUTHOR_STR    "\xB3 by Nolan Martin                                  \xB3\r\n"
#define COPYRIGHT_STR "\xB3 Copyright 1992 - Softdisk Publishing             \xB3\r\n"

#define FRAMEBOT_STR  "\xD4\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBE\r\n"

#define VERSION_TITLE_STR "THE CATACOMB ABYSS INTRODUCTION PROGRAM"
#define VERSION_REV_STR " VERSION 1.01   QA[0]"

#define GAMEEXE_FILENAME "CATABYSS.EXE"

#elif defined GAMEVER_CATABYSS

#define FRAMETOP_STR  "\xD5\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB8\r\n"

#define TITLE_STR     "\xB3 Catacomb Abyss 3-D Introduction Program  \xB3\r\n"
#define AUTHOR_STR    "\xB3 by Nolan Martin                          \xB3\r\n"
#define COPYRIGHT_STR "\xB3 Copyright 1992-1993 Softdisk Publishing  \xB3\r\n"

#define FRAMEBOT_STR  "\xD4\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBE\r\n"

#define VERSION_TITLE_STR "The Catacomb Abyss 3-D Introduction Program"
#define VERSION_REV_STR " version 1.06  (Rev 1) "

#define GAMEEXE_FILENAME "ABYSGAME.EXE"

#elif defined GAMEVER_CATARM

#define FRAMETOP_STR  "\xD5\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB8\r\n"

#define TITLE_STR     "\xB3 Catacomb Armageddon 3-D Introduction Program \xB3\r\n"
#define AUTHOR_STR    "\xB3 by Nolan Martin                              \xB3\r\n"
#define COPYRIGHT_STR "\xB3 Copyright 1992-93 - Softdisk Publishing      \xB3\r\n"

#define FRAMEBOT_STR  "\xD4\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBE\r\n"

#define VERSION_TITLE_STR "THE CATACOMB ARMAGEDDON 3-D INTRODUCTION PROGRAM"
#define VERSION_REV_STR " VERSION 1.04   (REV 1)"

#define GAMEEXE_FILENAME "ARMGAME.EXE"

#elif defined GAMEVER_CATAPOC

#define FRAMETOP_STR  "\xD5\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB8\r\n"

#define TITLE_STR     "\xB3 Catacomb Apocalypse 3-D Introduction Program \xB3\r\n"
#define AUTHOR_STR    "\xB3 by Nolan Martin                              \xB3\r\n"
#define COPYRIGHT_STR "\xB3 Copyright 1992-93 - Softdisk Publishing      \xB3\r\n"

#define FRAMEBOT_STR  "\xD4\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBE\r\n"

#define VERSION_TITLE_STR "THE CATACOMB APOCALYPSE 3-D INTRODUCTION PROGRAM"
#define VERSION_REV_STR " VERSION 1.05 rev 1"

#define GAMEEXE_FILENAME "APOCGAME.EXE"

#endif

static void SetScreenMode (int mode);
static void SetLineWidth (int width);
static boolean IsKeyPressed (void);
static void WaitForKeyRelease (void);
static void FreeAllShapes();

static int screenmode;
static cardtype videocard;

#ifndef GAMEVER_CATAPOC
static boolean havebeep = false;
#endif

static struct Shape app_start_shape,
                    page_1_shape, page_2_shape, page_3_shape,
                    page_4_shape, page_5_shape, page_6_shape, page_7_shape,
                    before_skill_choice_shape, after_loadgame_choice_shape,
                    novice_choice_shape, warrior_choice_shape, before_gamelaunch_shape;

// Looks like there were some unused shapes... and 2 more for Arm/Apoc
static struct Shape unused_1_shape, unused_2_shape, unused_3_shape, unused_4_shape,
                    unused_5_shape, unused_6_shape, unused_7_shape, unused_8_shape,
#ifndef GAMEVER_CATABYSS
                    unused_12_shape, unused_13_shape,
#endif
                    unused_9_shape, unused_10_shape, unused_11_shape;

#ifdef GAMEVER_CATAPOC
#define Beep() // HACK
#else
static void Beep(void)
{
	if (havebeep)
	{
		sound(800);
		delay(170);
		nosound();
	}
}
#endif

void main(void)
{
	boolean leave_init_sequence = false, leave_pre_skill_selection = false, leave_skill_selection = false, select_saved_game = false;
	int general_loop_var, init_sequence_iters_upperbound;
#if (defined GAMEVER_CATABYSS) && (!defined GAMEVER_SHAREWARE)
	// The di and si registers were found out to be swapped for an unknown reason...
	int last_key;
	int current_page = 0;
#else
	int current_page = 0, last_key;
#endif
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
		printf("/?    - this help\n");
		exit(0);
	}
	if (!stricmp(_argv[1], "/VER"))
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
		printf("%s %s\n", VERSION_TITLE_STR, VERSION_REV_STR);
		printf("\n");
		printf("This program requires an EGA monitor or better,\n");
		printf("                640K, and MS-DOS 3.0 or better.\n");
		exit(0);
	}
#ifndef GAMEVER_CATAPOC
	if (!stricmp(_argv[1], "/S") || !stricmp(_argv[2], "/S") || !stricmp(_argv[3], "/S") || !stricmp(_argv[4], "/S"))
		havebeep = false;
#endif
#ifdef GAMEVER_SHAREWARE
	if (stricmp(_argv[1], "^(a@&r`"))
	{
		TrashProg("You must type START [ENTER] to run CATACOMB APOCALYPSE!\n");
	}
#endif
	videocard = VideoID();
	if ((videocard != 3) && (videocard != 5))
		TrashProg("You need an EGA or VGA monitor to run this program.\n", "Please read the \"INSTRUCTIONS SECTION\" of the START program.\n");
	screenmode = 3;
	SetScreenMode(screenmode);
	SetScreen(0,0);

	// Prepare to enter the CATACOMB...
#ifdef GAMEVER_CATABYSS
	if (LoadShape("SHP05."EXTENSION, &app_start_shape))
#else
	if (LoadShape("SHP8."EXTENSION, &app_start_shape))
#endif
		TrashProg("ERROR : Can't load image.");
	MoveGfxDst(0, 200);
	UnpackEGAShapeToScreen(&app_start_shape, (320-app_start_shape.bmHdr.w)/2, (200-app_start_shape.bmHdr.h)/2);
	ScreenToScreen(8000, 0, 40, 200);
	FreeShape(&app_start_shape);
	WaitForKeyRelease();

#ifdef GAMEVER_CATABYSS
	if (LoadShape("SHP01."EXTENSION, &page_2_shape))
		TrashProg("ERROR : Can't load image.");
	WaitForKeyRelease();
	if (LoadShape("SHP02."EXTENSION, &page_3_shape))
		TrashProg("ERROR : Can't load image.");
	WaitForKeyRelease();
	if (LoadShape("SHP03."EXTENSION, &page_4_shape))
		TrashProg("ERROR : Can't load image.");
	WaitForKeyRelease();
	if (LoadShape("SHP04."EXTENSION, &app_start_shape))
		TrashProg("ERROR : Can't load image.");
	WaitForKeyRelease();
	if (LoadShape("SHP06."EXTENSION, &before_gamelaunch_shape))
		TrashProg("ERROR : Can't load image.");
	WaitForKeyRelease();
	if (LoadShape("SHP07."EXTENSION, &before_skill_choice_shape))
		TrashProg("ERROR : Can't load image.");
	WaitForKeyRelease();
	if (LoadShape("SHP08."EXTENSION, &novice_choice_shape))
		TrashProg("ERROR : Can't load image.");
	WaitForKeyRelease();
	if (LoadShape("SHP09."EXTENSION, &warrior_choice_shape))
		TrashProg("ERROR : Can't load image.");
	WaitForKeyRelease();
	if (LoadShape("SHP10."EXTENSION, &after_loadgame_choice_shape))
		TrashProg("ERROR : Can't load image.");
	WaitForKeyRelease();
	if (LoadShape("SHP11."EXTENSION, &page_5_shape))
		TrashProg("ERROR : Can't load image.");
	WaitForKeyRelease();
	if (LoadShape("SHP12."EXTENSION, &page_1_shape))
		TrashProg("ERROR : Can't load image.");
	WaitForKeyRelease();
#else
	if (LoadShape("SHP1."EXTENSION, &page_2_shape))
		TrashProg("ERROR : Can't load image.");
	WaitForKeyRelease();
	if (LoadShape("SHP2."EXTENSION, &page_3_shape))
		TrashProg("ERROR : Can't load image.");
	WaitForKeyRelease();
	if (LoadShape("SHP3."EXTENSION, &page_4_shape))
		TrashProg("ERROR : Can't load image.");
	WaitForKeyRelease();
	if (LoadShape("SHP4."EXTENSION, &page_5_shape))
		TrashProg("ERROR : Can't load image.");
	WaitForKeyRelease();
	if (LoadShape("SHP5."EXTENSION, &page_6_shape))
		TrashProg("ERROR : Can't load image.");
	WaitForKeyRelease();
	if (LoadShape("SHP6."EXTENSION, &page_7_shape))
		TrashProg("ERROR : Can't load image.");
	WaitForKeyRelease();
	if (LoadShape("SHP7."EXTENSION, &app_start_shape))
		TrashProg("ERROR : Can't load image.");
	WaitForKeyRelease();
	if (LoadShape("SHP9."EXTENSION, &before_gamelaunch_shape))
		TrashProg("ERROR : Can't load image.");
	WaitForKeyRelease();
	if (LoadShape("SHP10."EXTENSION, &before_skill_choice_shape))
		TrashProg("ERROR : Can't load image.");
	WaitForKeyRelease();
	if (LoadShape("SHP11."EXTENSION, &novice_choice_shape))
		TrashProg("ERROR : Can't load image.");
	WaitForKeyRelease();
	if (LoadShape("SHP12."EXTENSION, &warrior_choice_shape))
		TrashProg("ERROR : Can't load image.");
	WaitForKeyRelease();
	if (LoadShape("SHP13."EXTENSION, &after_loadgame_choice_shape))
		TrashProg("ERROR : Can't load image.");
	WaitForKeyRelease();
	if (LoadShape("SHP14."EXTENSION, &page_1_shape))
		TrashProg("ERROR : Can't load image.");
	WaitForKeyRelease();
#endif

	current_page = 0;
	if (_argc < 3)
	{
		for (general_loop_var = _argc; general_loop_var <= 3; ++general_loop_var)
		{
			_argv[general_loop_var] = "0";
		}
		_argc = 4;
		_argv[_argc] = NULL;
	}
	do
	{
		for (leave_init_sequence = false; !leave_init_sequence;)
		{
			switch (current_page)
			{
			case 0: // Present
				MoveGfxDst(0, 200);
				UnpackEGAShapeToScreen(&page_1_shape, 0, 0);
				ScreenToScreen(8000, 0, 40, 200);
				++current_page;
				Beep();
				break;
			case 1: // A SoftDisk Publishing production
				MoveGfxDst(0, 200);
				UnpackEGAShapeToScreen(&page_2_shape, 0, 0);
				ScreenToScreen(8000, 0, 40, 200);
				++current_page;
				Beep();
				break;
			case 2: // Title screen
				MoveGfxDst(0, 200);
				UnpackEGAShapeToScreen(&page_3_shape, 0, 0);
				ScreenToScreen(8000, 0, 40, 200);
				++current_page;
				Beep();
				break;
			case 3: // Credits #1
				MoveGfxDst(0, 200);
				UnpackEGAShapeToScreen(&page_4_shape, 0, 0);
				ScreenToScreen(8000, 0, 40, 200);
				++current_page;
				Beep();
				break;
			case 4: // Credits #2 / The Catacomb Adventure Series
				MoveGfxDst(0, 200);
				UnpackEGAShapeToScreen(&page_5_shape, 0, 0);
				ScreenToScreen(8000, 0, 40, 200);
#ifdef GAMEVER_CATABYSS
				current_page = 0;
#else
				++current_page;
#endif
				Beep();
				break;
#ifndef GAMEVER_CATABYSS
			case 5: // Credits #3
				MoveGfxDst(0, 200);
				UnpackEGAShapeToScreen(&page_6_shape, 0, 0);
				ScreenToScreen(8000, 0, 40, 200);
				++current_page;
				Beep();
				break;
			case 6: // Credits #1
				MoveGfxDst(0, 200);
				UnpackEGAShapeToScreen(&page_7_shape, 0, 0);
				ScreenToScreen(8000, 0, 40, 200);
				current_page = 0;
				Beep();
				break;
#endif
			}
#ifdef GAMEVER_CATABYSS
			if (current_page == 2)
				init_sequence_iters_upperbound = 150;
			else
				init_sequence_iters_upperbound = 100;
#else
			if (current_page == 2)
				init_sequence_iters_upperbound = 240;
			else
				init_sequence_iters_upperbound = 120;
#endif
			for (general_loop_var = 0; general_loop_var <= init_sequence_iters_upperbound; ++general_loop_var)
			{
				delay(50);
				last_key = TryGetKey();
				if (last_key == 0x11B) // ESC
				{
					FreeAllShapes();
					SetScreenMode(1);
#ifdef GAMEVER_SHAREWARE
					_argc = 2;
					_argv[1] = "LAST.SHL";
					_argv[2] = "ENDSCN.SCN";
					_argv[3] = NULL;
					if (execv("LOADSCN.EXE", _argv) == -1)
					{
						SetScreenMode(1);
						puts("Couldn't find executable LOADSCN.EXE.\n");
						exit(1);
					}
#else
					exit(0);
#endif
				}
				else if (last_key == 0x1C0D) // Enter
				{
					leave_init_sequence = true;
					general_loop_var = 600;
				}
				else if (last_key == 0x3E00) // F4
				{
					leave_init_sequence = true;
					select_saved_game = true;
					general_loop_var = 600;
				}
#ifdef GAMEVER_SHAREWARE
				else if (last_key == 0x4400) // F10 (Demo)
				{
					SetScreenMode(1);
					if (execv("DEMOCAT.EXE", _argv) == -1)
					{
						printf("ERROR : Can't find executable.\n");
						exit(0);
					}
				}
#endif
			}
		}
		for (leave_pre_skill_selection = false; !leave_pre_skill_selection; )
		{
			if (select_saved_game) // Launch CATABYSS.EXE and select saved game
			{
				if (!_argv[3])
				{
					_argv[_argc++] = "1";
				}
				else
				{
					_argv[_argc++] = _argv[3];
					_argv[3] = "1";
				}
				MoveGfxDst(0, 200);
				UnpackEGAShapeToScreen(&before_gamelaunch_shape, 0, 0);
				UnpackEGAShapeToScreen(&after_loadgame_choice_shape, (320-after_loadgame_choice_shape.bmHdr.w)/2, 192);
				ScreenToScreen(8000, 0, 40, 200);
				Beep();
				TrashProg(NULL);
			}
			else
			{
				if (!_argv[3])
				{
					_argv[_argc++] = "0";
				}
				else
				{
					_argv[_argc++] = _argv[3];
					_argv[3] = "0";
				}
				MoveGfxDst(0, 200);
				UnpackEGAShapeToScreen(&before_skill_choice_shape, 0, 0);
				ScreenToScreen(8000, 0, 40, 200);
				Beep();
				for (leave_skill_selection = false; !leave_skill_selection; )
				{
					last_key = TryGetKey();
					if ((last_key == 0x1157) || (last_key == 0x1177)) // W or w (Warrior)
					{
						if (!_argv[2])
						{
							_argv[_argc++] = "0";
						}
						else
						{
							_argv[_argc++] = _argv[2];
							_argv[2] = "0";
						}
						MoveGfxDst(0, 200);
						UnpackEGAShapeToScreen(&before_gamelaunch_shape, 0, 0);
						UnpackEGAShapeToScreen(&warrior_choice_shape, (320-warrior_choice_shape.bmHdr.w)/2, 192);
						ScreenToScreen(8000, 0, 40, 200);
						Beep();
						WaitForKeyRelease();
						while (!(last_key = TryGetKey()))
							;
#if 0
						do
							last_key = TryGetKey();
						while (!last_key);
#endif
						if (last_key == 0x11B) // ESC
							leave_skill_selection = true;
						else
						{
							MoveGfxDst(0, 200);
							UnpackEGAShapeToScreen(&app_start_shape, 0, 0);
							ScreenToScreen(8000, 0, 40, 200);
							Beep();
							bioskey(0);
							TrashProg(NULL);
						}
					}
					else if ((last_key == 0x314E) || (last_key == 0x316E)) // N or n (Novice)
					{
						if (!_argv[2])
						{
							_argv[_argc++] = "1";
						}
						else
						{
							_argv[_argc++] = _argv[2];
							_argv[2] = "1";
						}
						MoveGfxDst(0, 200);
						UnpackEGAShapeToScreen(&before_gamelaunch_shape, 0, 0);
						UnpackEGAShapeToScreen(&novice_choice_shape, (320-novice_choice_shape.bmHdr.w)/2, 192);
						ScreenToScreen(8000, 0, 40, 200);
						Beep();
						WaitForKeyRelease();
						while (!(last_key = TryGetKey()))
							;
#if 0
						do
							last_key = TryGetKey();
						while (!last_key);
#endif
						if (last_key == 0x11B)
							leave_skill_selection = true;
						else
						{
							MoveGfxDst(0, 200);
							UnpackEGAShapeToScreen(&app_start_shape, 0, 0);
							ScreenToScreen(8000, 0, 40, 200);
							Beep();
							bioskey(0);
							TrashProg(NULL);
						}
					}
					else if (last_key == 0x11B) // ESC
					{
						leave_pre_skill_selection = true;
						leave_skill_selection = true;
#ifdef GAMEVER_SHAREWARE
						current_page = 1;
#else
						current_page = 2;
#endif
					}
				}
			}
		}
	} while (1);
}

void TrashProg (char *OutMsg, ...)
{
	va_list ap;

	FreeAllShapes();
	_setcursortype(_NORMALCURSOR);

	if (!OutMsg)
	{
		if (!_argv[1])
		{
			_argv[_argc++] = "^(a@&r`";
		}
		else
		{
			_argv[_argc++] = _argv[1];
			_argv[1] = "^(a@&r`";
		}
		_argv[_argc++] = "/NODR";
		_argv[_argc] = NULL;
		if (execv(GAMEEXE_FILENAME, _argv) == -1)
		{
			SetScreenMode(1);
			printf("ERROR : Can't find executable.\n");
			exit(0);
		}
	}
	else
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

static void FreeAllShapes()
{
#ifdef GAMEVER_CATABYSS
	FreeShape(&page_3_shape);
	FreeShape(&page_2_shape);
	FreeShape(&page_4_shape);
#else
	FreeShape(&page_4_shape);
	FreeShape(&page_5_shape);
	FreeShape(&page_6_shape);
	FreeShape(&page_7_shape);
	FreeShape(&page_3_shape);
	FreeShape(&page_2_shape);
#endif
	FreeShape(&app_start_shape);
	FreeShape(&before_skill_choice_shape);
	FreeShape(&before_gamelaunch_shape);
	FreeShape(&novice_choice_shape);
	FreeShape(&warrior_choice_shape);
	FreeShape(&after_loadgame_choice_shape);
}
