#ifndef _ID_HEADS_H_
#define _ID_HEADS_H_

// ID_GLOB.H


#include <ALLOC.H>
#include <CTYPE.H>
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
#include <VALUES.H>
#include <DIR.H>
#define __ID_GLOB__

/*** BLAKE STONE VERSIONS RESTORATION ***/
#include "GAMEVER.H"

//--------------------------------------------------------------------------

#define DEBUG_VALUE
#define CEILING_FLOOR_COLORS


//#define CARMACIZED
#define WOLF
/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_100
#define FREE_FUNCTIONS					(true)
#else
#define FREE_FUNCTIONS					(false)
#endif
#define FREE_DATA							(false)
#define DEMOS_ENABLED					(true)
#define RESTART_PICTURE_PAUSE			(false)
#define GEORGE_CHEAT						(false)

/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
// A hack for disabling some ID_CA related calls not done in v1.0
#ifdef GAMEVER_RESTORATION_AOG_100
#define FORCE_FILE_CLOSE				(false)
#else
#define FORCE_FILE_CLOSE				(true)		// true - forces all files closed once they are used
#endif

//
// GAME VERSION TYPES
//

#define SHAREWARE_VERSION			0x0001
#define MISSIONS_1_THR_3			0x0003
#define MISSIONS_4_THR_6			0x0004
#define MISSIONS_1_THR_6			0x0007

//
// CURRENT GAME VERSION DEFINE - Change this define according to the
//											game release versions 1,1-3,4-6, or 1-6.

/*** BLAKE STONE VERSIONS RESTORATION ***/
#ifdef GAMEVER_RESTORATION_BS1
#define GAME_VERSION					(SHAREWARE_VERSION)
#else
#define GAME_VERSION					(MISSIONS_1_THR_6)
#endif
//#define GAME_VERSION					(MISSIONS_1_THR_6)
//#define GAME_VERSION      			(MISSIONS_1_THR_3)
//#define GAME_VERSION					(SHAREWARE_VERSION)


#define TECH_SUPPORT_VERSION		(false)
#define IN_DEVELOPMENT				(false)

#define ERROR_LOG						"ERROR.LOG"			// Text filename for critical memory errors
/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
#define DUAL_SWAP_FILES				(GAME_VERSION != SHAREWARE_VERSION)				// Support for Shadowed and NonShadowed page files
#else
#define DUAL_SWAP_FILES				(false)				//(GAME_VERSION != SHAREWARE_VERSION)				// Support for Shadowed and NonShadowed page files
#endif

extern  char            far signonv1;
#define introscn        signonv1

#ifndef SPEAR

/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
#include "GFXV_bs1.H"
#include "AUDIObs1.H"
#include "MAPSbs1.H"
#else
#include "GFXV_vsi.H"
#include "AUDIOvsi.H"
#include "MAPSvsi.H"
#endif

#else

#include "GFXV_SOD.H"
#include "AUDIOSOD.H"
#include "MAPSSOD.H"

#endif

//-----------------


#define GREXT   "VGA"

//
//      ID Engine
//      Types.h - Generic types, #defines, etc.
//      v1.0d1
//

typedef enum    {false,true}    boolean;
typedef unsigned        char            byte;
typedef unsigned        int                     word;
typedef unsigned        long            longword;
typedef byte *                                  Ptr;

typedef struct
		{
			int     x,y;
		} Point;
typedef struct
		{
			Point   ul,lr;
		} Rect;

#define nil     (0l)


#include "ID_MM.H"
#include "ID_PM.H"
#include "ID_CA.H"
#include "ID_VL.H"
#include "ID_VH.H"
#include "ID_IN.H"
#include "ID_SD.H"
#include "ID_US.H"

#include "jm_tp.h"
#include "jm_debug.h"
#include "jm_error.h"

#include "movie.h"

void    Quit (char *error,...);             // defined in user program

extern void CalcMemFree(void);

//
// replacing refresh manager with custom routines
//

#define PORTTILESWIDE           20      // all drawing takes place inside a
#define PORTTILESHIGH           13              // non displayed port of this size

#define UPDATEWIDE                      PORTTILESWIDE
#define UPDATEHIGH                      PORTTILESHIGH

#define MAXTICS                         10
#define DEMOTICS                        4

#define UPDATETERMINATE 0x0301

extern  unsigned        mapwidth,mapheight,tics,realtics;
extern  boolean         compatability;

extern  byte            *updateptr;
extern  unsigned        uwidthtable[UPDATEHIGH];
extern  unsigned        blockstarts[UPDATEWIDE*UPDATEHIGH];

extern  byte            fontcolor,backcolor;

#define SETFONTCOLOR(f,b) fontcolor=f;backcolor=b;

#include "3D_MENU.H"


#define CA_FarRead(h,d,s)	IO_FarRead((int)h,(byte far *)d,(long)s)



#endif
