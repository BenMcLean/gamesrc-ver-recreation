/*
Copyright (C) 1994-1995 Apogee Software, Ltd.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
#ifndef _develop_public
#define _develop_public

// *** VERSIONS RESTORATION ***
// Note that as of Apogee v1.3, this file (DEVELOP.H) shall be included
// from any compiled C file, except for USRHOOKS.C.

// APPVER_ROTTREV definitions
#define AV_RR_RTLD13A 19950504L
#define AV_RR_RTLD13B 19950704L
#define AV_RR_RTSW13 19950808L
#define AV_RR_RTRG13 19950808L
#define AV_RR_RTCD13 19950808L
#define AV_RR_RTSL13 19950808L
#define AV_RR_RTSRC 20021225L

// Now define APPVER_ROTTREV to one of the above,
// based on the definition of APPVER_EXEDEF

#define APPVER_CONCAT1(x,y) x ## y
#define APPVER_CONCAT2(x,y) APPVER_CONCAT1(x,y)
#define APPVER_ROTTREV APPVER_CONCAT2(AV_RR_,APPVER_EXEDEF)

// Note that we may use a *separate* APPVER_EXEDEF_*** macro later

#define NOMEMCHECK
#define DEBUG 0
#define DEVELOPMENT 0
#define BETA 0
#define SOUNDTEST 0
#define PRECACHETEST 0
#define ELEVATORTEST 0
#define TEAMTEST     0
#define LOADSAVETEST 0
#define WEAPONCHEAT  1
#define MEMORYCORRUPTIONTEST  0
#define SYNCCHECK    1
#define DATACORRUPTIONTEST    0
#define BATTLECHECK 0 // This should be turned off for release, on for beta
#define BATTLEINFO  0 // This should be turned off for release

// *** VERSIONS RESTORATION ***
#if (defined APPVER_EXEDEF_RTLD13A) || (defined APPVER_EXEDEF_RTLD13B)
#define DELUXE   1
#else
#define DELUXE   0
#endif
#define LOWCOST  0
// Make sure only one of the following are on at one time

// *** VERSIONS RESTORATION ***
#ifdef APPVER_EXEDEF_RTRG13
#define SHAREWARE   0
#define SUPERROTT   0
#define SITELICENSE 0
#elif (defined APPVER_EXEDEF_RTLD13A) || (defined APPVER_EXEDEF_RTLD13B) || (defined APPVER_EXEDEF_RTSW13)
#define SHAREWARE   1
#define SUPERROTT   0
#define SITELICENSE 0
#elif (defined APPVER_EXEDEF_RTCD13)
#define SHAREWARE   0
#define SUPERROTT   1
#define SITELICENSE 0
#elif (defined APPVER_EXEDEF_RTSL13)
#define SHAREWARE   0
#define SUPERROTT   0
#define SITELICENSE 1
#endif

// okay?

#define TEXTMENUS   1
#define TEDLAUNCH   0
#define SOFTERROR   0
#define RANDOMTEST  0
#define WHEREAMI    0




#if (WHEREAMI==1)

#define wami(val)      \
   {                   \
   programlocation=val;\
   }

#define waminot()
//   {                  \
//   programlocation=-1;\
//   }

#else

#define wami(val)
#define waminot()

#endif

#endif
