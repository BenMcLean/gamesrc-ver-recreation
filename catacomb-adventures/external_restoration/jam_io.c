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
#include <string.h>
#include <ctype.h>
#include <alloc.h>
#include <fcntl.h>
#include <dos.h>
#include <io.h>

#include "heads.h"
#include "gelib.h"
#include "jam_io.h"

//----------------------------------------------------------------------------
//
//	 						PTR/PTR COMPRESSION ROUTINES
//
//
//----------------------------------------------------------------------------



//---------------------------------------------------------------------------
// WritePtr()  -- Outputs data to a particular ptr type
//
//	PtrType MUST be of type DEST_TYPE.
//
// NOTE : For PtrTypes DEST_MEM a ZERO (0) is always returned.
//
//---------------------------------------------------------------------------
char WritePtr(long outfile, unsigned char data, unsigned PtrType)
{
	int returnval = 0;

	switch (PtrType & DEST_TYPES)
	{
//		case DEST_FILE:
//			write(*(int far *)outfile,(char *)&data,1);
//		break;

		case DEST_FILE:
		case DEST_IMEM:
			printf("WritePtr - unsupported ptr type\n");
			exit(0);
		break;

		case DEST_FFILE:
			returnval = putc(data, *(FILE **)outfile);
		break;

//		case DEST_IMEM:
//			printf("WritePtr - unsupported ptr type\n");
//			exit(0);
//		break;

		case DEST_MEM:
			*((char far *)*(char far **)outfile)++ = data;
		break;
	}

	return(returnval);

}


//---------------------------------------------------------------------------
// ReadPtr()  -- Reads data from a particular ptr type
//
//	PtrType MUST be of type SRC_TYPE.
//
// RETURNS :
//		The char read in or EOF for SRC_FFILE type of reads.
//
//
//---------------------------------------------------------------------------
int ReadPtr(long infile, unsigned PtrType)
{
	int returnval = 0;

	switch (PtrType & SRC_TYPES)
	{
		case SRC_FILE:
#ifdef GAMEVER_SLIDECAT
			TrashProg("You need more \"free conventional memory\" in order to view the\n"
			          "Demo of the Catacomb 3-D Trilogy.  At least 588K free memory\n"
			          "is required.  Try renaming your AUTOEXEC.BAT and CONFIG.SYS\n"
			          "files to other names, then reboot your computer, and try again.\n\n\n"
			);
#else
			printf("WritePtr - unsupported ptr type\n");
			exit(0);
#endif
		break;

		case SRC_FFILE:
			returnval = getc(*(FILE **)infile
			);
		break;

//		case SRC_BFILE:
//			returnval = bio_readch((BufferedIO *)*(void far **)infile);
//		break;

//		case SRC_IMEM:
//			printf("WritePtr - unsupported ptr type\n");
//			exit(0);
//		break;

		case SRC_MEM:
			returnval = (unsigned char)*((char far *)*(char far **)infile)++;
		break;
	}

	return(returnval);
}



