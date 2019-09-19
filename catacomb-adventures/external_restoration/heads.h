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

#ifndef __HEADS_H__
#define __HEADS_H__

/*** VERSIONS RESTORATION ***/
#include "GAMEVER.H"

// Taken off ID_HEADS.H, WITH POSSIBLE MODIFICATIONS

#include <ALLOC.H>
// VERSION RESTORATION - Don't include this, so
// the isalpha function is used instead of the macro
//#include <CTYPE.H>
#include <DOS.H>
#include <ERRNO.H>
#include <FCNTL.H>
#include <IO.H>
#include <MEM.H>
#include <PROCESS.H>
#include <STDIO.H>
#include <STDLIB.H>
#include <STRING.H>
#include <SYS\STAT.H>

#define GRMODE EGAGR

//
//	ID Engine
//	Types.h - Generic types, #defines, etc.
//	v1.0d1
//

typedef enum {false,true} boolean;
typedef unsigned char byte;
typedef unsigned int word;
typedef unsigned long longword;

// WARNING: THIS IS *DIFFERENT* FROM THE ID_MM.H DEFINITION!!!

typedef void far * memptr;

// Taken off ID_VW.H

#define VIRTUALHEIGHT 300

#define CRTC_INDEX 0x3D4
#define CRTC_OFFSET 19

typedef enum {NOcard,MDAcard,CGAcard,EGAcard,MCGAcard,VGAcard,
              HGCcard=0x80,HGCPcard,HICcard} cardtype;

extern unsigned displayofs; // origin of port on visable screen
extern unsigned ylookup[VIRTUALHEIGHT];

void TrashProg (char *OutMsg, ...);

#endif
