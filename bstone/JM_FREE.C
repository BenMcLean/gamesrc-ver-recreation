// JM_FREE.C

//
// Warning!
//
// All functions in this source file are designated usable by the memory
// manager after program initialization.
//

#include "ID_HEADS.H"
#pragma hdrstop

#include "3d_def.h"

/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
#define SKIP_CHECKSUMS					(false)
#define SHOW_CHECKSUM					(false)
#else
#define SKIP_CHECKSUMS					(true)
#define SHOW_CHECKSUM					(false)
#endif

/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
// Adding only what we use, although MAPTEMP_CHECKSUM is missing for BS3 v1.0.
#ifdef GAMEVER_RESTORATION_AOG_100

#if GAME_VERSION == SHAREWARE_VERSION

#define MAPTEMP_CHECKSUM		0x0003606E

#elif GAME_VERSION == MISSIONS_1_THR_3

#define MAPTEMP_CHECKSUM		0x????????
#define DIZFILE_CHECKSUM		0x00000879l

#else


#define MAPTEMP_CHECKSUM		0x0010892E
#define DIZFILE_CHECKSUM		0x00000879l

#endif

#else // Versions restoration

#if GAME_VERSION == SHAREWARE_VERSION

#define AUDIOT_CHECKSUM			0xFFF87142
#define MAPTEMP_CHECKSUM		0x000370C9
#define VGAGRAPH_CHECKSUM		0xFFFFDE44
#define DIZFILE_CHECKSUM		0x00000879l

#elif GAME_VERSION == MISSIONS_1_THR_3

#define AUDIOT_CHECKSUM			0xFFF87142
#define MAPTEMP_CHECKSUM		0x00084F1F
#define VGAGRAPH_CHECKSUM		0xFFFFDE44
#define DIZFILE_CHECKSUM		0x00000879l

#else


#define AUDIOT_CHECKSUM       0xfff912C9
#define MAPTEMP_CHECKSUM		0x00107739
#define VGAGRAPH_CHECKSUM		0xffff6C9A
#define DIZFILE_CHECKSUM		0x00000879l


#endif

#endif // Versions restoration

#pragma warn -pro
#pragma warn -use

void SDL_SBSetDMA(byte channel);
void SDL_SetupDigi(void);

//=========================================================================
//
//									 FAR FREE DATA
//
//=========================================================================

#if FREE_DATA

char far JM_FREE_DATA_START[1]={0};

#endif

#if TECH_SUPPORT_VERSION
char far EnterBetaCode[]="\n  TECH SUPPORT VERSION!\n\n  NO DISTRIBUTING!";
#elif BETA_TEST
char far EnterBetaCode[]="      !BETA VERSION!\n    DO NOT DISTRIBUTE\n UNDER PENALTY OF DEATH\n\n   ENTER BETA CODE";
#endif


/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_POST100
char    far * far JHParmStrings[] = {"no386",nil};
#elif (defined GAMEVER_RESTORATION_VSI)
char    far * far JHParmStrings[] = {"no386","is386",nil};
#endif

/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
// Relocate these for v1.0, and also edit show_text3
#ifndef GAMEVER_RESTORATION_AOG_100
char far show_text1[]="\n     SYSTEM INFO\n";
char far show_text2[]="=======================\n\n";
char far show_text3[]="-- Memory avail after game is loaded --\n\n";
char far show_text4[]="            ** Insufficient memory to run the game **";
char far show_text5[]="---- Extra Devices ----\n\n";

static	char far * far ParmStrings[] = {"HIDDENCARD",""};

/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
// Re-enable commented out entries for AOG, *and* relocate for v1.0
static  byte far wolfdigimap[] =
{
			// These first sounds are in the upload version

			ATKIONCANNONSND,					0,
			ATKCHARGEDSND,						1,
			ATKBURSTRIFLESND,             2,
			ATKGRENADESND,                46,

			OPENDOORSND,                  3,
			CLOSEDOORSND,                 4,
			HTECHDOOROPENSND,             5,
			HTECHDOORCLOSESND,            6,

			INFORMANTDEATHSND,            7,
			SCIENTISTHALTSND,             19,
			SCIENTISTDEATHSND,            20,

			GOLDSTERNHALTSND,             8,
			GOLDSTERNLAUGHSND,            24,

			HALTSND,                      9,			// Rent-A-Cop 1st sighting
			RENTDEATH1SND,                10,		// Rent-A-Cop Death

			EXPLODE1SND,                  11,

			GGUARDHALTSND,                12,
			GGUARDDEATHSND,               17,

			PROHALTSND,                   16,
			PROGUARDDEATHSND,             13,

			BLUEBOYDEATHSND,              18,
			BLUEBOYHALTSND,					51,

			SWATHALTSND,                  22,
			SWATDIESND,                   47,

			SCANHALTSND,                  15,
			SCANDEATHSND,                 23,

			PODHATCHSND,                  26,
			PODHALTSND,							50,
			PODDEATHSND,                  49,

			ELECTSHOTSND,                 27,

/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
// Also filter these for shareware releases
#if (GAME_VERSION != SHAREWARE_VERSION)
			DOGBOYHALTSND,                14,
			DOGBOYDEATHSND,               21,
			ELECARCDAMAGESND,             25,
			ELECAPPEARSND,                28,
			ELECDIESND,                   29,

			INFORMDEATH2SND,              39,		// Informant Death #2
			RENTDEATH2SND,                34,      // Rent-A-Cop Death #2
			PRODEATH2SND,                 42,	   // PRO Death #2
			SWATDEATH2SND,                48, 		// SWAT Death #2
			SCIDEATH2SND,					   53,		// Gen. Sci Death #2

			LIQUIDDIESND,                 30,

			GURNEYSND,                    31,
			GURNEYDEATHSND,               41,

			WARPINSND,                    32,
			WARPOUTSND,                   33,

			EXPLODE2SND,                  35,

			LCANHALTSND,                  36,
			LCANDEATHSND,                 37,

#ifdef GAMEVER_RESTORATION_AOG
			RENTDEATH3SND,		            38,		// Rent-A-Cop Death #3
#endif
			INFORMDEATH3SND,              40,		// Informant Death #3
#ifdef GAMEVER_RESTORATION_AOG
			PRODEATH3SND,                 43,      // PRO Death #3
			SWATDEATH3SND,						52,		// Swat Guard #3
#endif
			SCIDEATH3SND,						54,		// Gen. Sci Death #3

			LCANBREAKSND,                 44,
			SCANBREAKSND,                 45,
			CLAWATTACKSND,						56,
			SPITATTACKSND,						55,
			PUNCHATTACKSND,					57,
#endif // VERSIONS RESTORATION

			LASTSOUND
};
#endif // GAMEVER_RESTORATION_AOG_100


#if 0

static  byte far wolfdigimap[] =
{
			// These first sounds are in the upload version

			ATKIONCANNONSND,					0,
			ATKCHARGEDSND,						1,
			ATKBURSTRIFLESND,             2,
			ATKGRENADESND,                46,

			OPENDOORSND,                  3,
			CLOSEDOORSND,                 4,
			HTECHDOOROPENSND,             5,
			HTECHDOORCLOSESND,            6,

			INFORMANTDEATHSND,            7,
			SCIENTISTHALTSND,             19,
			SCIENTISTDEATHSND,            20,

			GOLDSTERNHALTSND,             8,
			GOLDSTERNLAUGHSND,            24,

			HALTSND,                      9,		// Rent-A-Cop 1st sighting
			RENTDEATH1SND,                10,		// Rent-A-Cop Death

			EXPLODE1SND,                  11,

			GGUARDHALTSND,                12,
			GGUARDDEATHSND,               17,

			PROHALTSND,                   16,
			PROGUARDDEATHSND,             13,

			BLUEBOYDEATHSND,              18,
			BLUEBOYHALTSND,					51,

			SWATHALTSND,                  22,
			SWATDIESND,                   47,

			SCANHALTSND,                  15,
			SCANDEATHSND,                 23,

			PODHATCHSND,                  26,
			PODHALTSND,							50,
			PODDEATHSND,                  49,

			ELECTSHOTSND,                 27,

			DOGBOYHALTSND,                14,
			DOGBOYDEATHSND,               21,
			ELECARCDAMAGESND,             25,
			ELECAPPEARSND,                28,
			ELECDIESND,                   29,

			INFORMDEATH2SND,              39,		// Informant Death #2
			RENTDEATH2SND,                34,      // Rent-A-Cop Death #2
			PRODEATH2SND,                 42,	   // PRO Death #2
			SWATDEATH2SND,                48, 		// SWAT Death #2
			SCIDEATH2SND,					   53,		// Gen. Sci Death #2

			LIQUIDDIESND,                 30,

			GURNEYSND,                    31,
			GURNEYDEATHSND,               41,

			WARPINSND,                    32,
			WARPOUTSND,                   33,

			EXPLODE2SND,                  35,

			LCANHALTSND,                  36,
			LCANDEATHSND,                 37,

//			RENTDEATH3SND,		            38,		// Rent-A-Cop Death #3
			INFORMDEATH3SND,              40,		// Informant Death #3
//			PRODEATH3SND,                 43,      // PRO Death #3
//			SWATDEATH3SND,						52,		// Swat Guard #3
			SCIDEATH3SND,						54,		// Gen. Sci Death #3

			LCANBREAKSND,                 44,
			SCANBREAKSND,                 45,
			CLAWATTACKSND,						56,
			SPITATTACKSND,						55,
			PUNCHATTACKSND,					57,

			LASTSOUND
};

#endif

/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
// Relocate this for v1.0
#ifndef GAMEVER_RESTORATION_AOG_100
char far cinfo_text[]=	"\n"
/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
								"BLAKE STONE: Aliens of Gold\n"
#else
								"Planet Strike\n"
#endif
								"Copyright (c) 1993 - JAM Productions, Inc.\n"
								"All rights reserved.\n";
#endif

#if BETA_TEST
char far dver_text[]="Download the latest version pal!";
#endif


#if FREE_DATA

char far JM_FREE_DATA_END[1]={0};

#endif

/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_100
extern byte far colormap[];
byte far * lightsource;
#endif

//=========================================================================
//
//								 FREE FUNCTIONS
//
//=========================================================================



#if FREE_FUNCTIONS

// This function is used as a label for the start of the
// functions used by the memory manager.
//
void JM_FREE_START()
{
}

#endif

// ------------------ ID Software 'startup' functions ---------------------

/*
======================
=
= CA_Startup
=
= Open all files and load in headers
=
======================
*/
void CA_Startup (void)
{
#ifdef PROFILE
	unlink ("PROFILE.TXT");
	profilehandle = open("PROFILE.TXT", O_CREAT | O_WRONLY | O_TEXT);
#endif

	CAL_SetupMapFile ();
	CAL_SetupGrFile ();
	CAL_SetupAudioFile ();

	mapon = -1;
	ca_levelbit = 1;
	ca_levelnum = 0;
}



//#if !IN_DEVELOPMENT

extern boolean IN_Started;
extern char far * far IN_ParmStrings[];
extern boolean INL_StartJoy(word joy);
extern boolean INL_StartMouse(void);
extern void INL_StartKbd(void);

///////////////////////////////////////////////////////////////////////////
//
//	INL_StartJoy() - Detects & auto-configures the specified joystick
//					The auto-config assumes the joystick is centered
//
///////////////////////////////////////////////////////////////////////////
boolean
INL_StartJoy(word joy)
{
	word		x,y;

	IN_GetJoyAbs(joy,&x,&y);

	if
	(
		((x == 0) || (x > MaxJoyValue - 10))
	||	((y == 0) || (y > MaxJoyValue - 10))
	)
		return(false);
	else
	{
		IN_SetupJoy(joy,0,x * 2,0,y * 2);
		return(true);
	}
}

///////////////////////////////////////////////////////////////////////////
//
//	IN_Startup() - Starts up the Input Mgr
//
///////////////////////////////////////////////////////////////////////////
void
IN_Startup(void)
{
	boolean	checkjoys,checkmouse,checkNG;
	word	i;

	if (IN_Started)
		return;

	checkjoys = true;
	checkmouse = true;
	/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_100
	checkNG = true;
#else
	checkNG = false;
#endif
	for (i = 1;i < _argc;i++)
	{
		switch (US_CheckParm(_argv[i],IN_ParmStrings))
		{
			case 0:
				checkjoys = false;
			break;

			case 1:
				checkmouse = false;
			break;

			case 2:
				/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_100
				checkNG = false;
#else
				checkNG = true;
#endif
			break;
		}
	}

	if (checkNG)
	{
		#define WORD_CODE(c1,c2)	((c2)|(c1<<8))

		NGjoy(0xf0);
		if ((_AX==WORD_CODE('S','G')) && _BX)
			NGinstalled=true;
	}

	INL_StartKbd();
	MousePresent = checkmouse? INL_StartMouse() : false;

	for (i = 0;i < MaxJoys;i++)
		JoysPresent[i] = checkjoys? INL_StartJoy(i) : false;

	IN_Started = true;
}

//#endif



/*
===================
=
= MM_Startup
=
= Grabs all space from turbo with malloc/farmalloc
= Allocates bufferseg misc buffer
=
===================
*/

extern boolean mmstarted,bombonerror;
extern mmblocktype far  mmblocks[], far *mmhead, far *mmfree,
						 far *mmnew, far *mmrover;
extern void far	*farheap;
extern void	*nearheap;

void MM_Startup (void)
{
	int i;
	unsigned 	long length;
	void far 	*start;
	unsigned 	segstart,seglength,endfree;

	if (mmstarted)
		MM_Shutdown ();


	mmstarted = true;
	bombonerror = true;
//
// set up the linked list (everything in the free list;
//
	mmhead = NULL;
	mmfree = &mmblocks[0];
	for (i=0;i<MAXBLOCKS-1;i++)
		mmblocks[i].next = &mmblocks[i+1];
	mmblocks[i].next = NULL;

//
// locked block of all memory until we punch out free space
//
	GETNEWBLOCK;
	mmhead = mmnew;				// this will allways be the first node
	mmnew->start = 0;
	mmnew->length = 0xffff;
	mmnew->attributes = LOCKBIT;
	mmnew->next = NULL;
	mmrover = mmhead;


//
// get all available near conventional memory segments
//
	length=coreleft();
	start = (void far *)(nearheap = malloc(length));

	length -= 16-(FP_OFF(start)&15);
	length -= SAVENEARHEAP;
	seglength = length / 16;			// now in paragraphs
	segstart = FP_SEG(start)+(FP_OFF(start)+15)/16;
	MML_UseSpace (segstart,seglength);
	mminfo.nearheap = length;



//
// get all available far conventional memory segments
//
	length=farcoreleft();
	start = farheap = farmalloc(length);
	length -= 16-(FP_OFF(start)&15);
	length -= SAVEFARHEAP;
	seglength = length / 16;			// now in paragraphs
	segstart = FP_SEG(start)+(FP_OFF(start)+15)/16;
	MML_UseSpace (segstart,seglength);
	mminfo.farheap = length;
	mminfo.mainmem = mminfo.nearheap + mminfo.farheap;

//	__SEGS_AVAILABLE__ = (long)(mminfo.EMSmem + mminfo.XMSmem + mminfo.mainmem) / 16;

//
// allocate the misc buffer
//
	mmrover = mmhead;		// start looking for space after low block

	MM_GetPtr (&bufferseg,BUFFERSIZE);
}

//
//	PML_StartupEMS() - Sets up EMS for Page Mgr's use
//		Checks to see if EMS driver is present
//      Verifies that EMS hardware is present
//		Make sure that EMS version is 3.2 or later
//		If there's more than our minimum (2 pages) available, allocate it (up
//			to the maximum we need)
//


#if !DUAL_SWAP_FILES

char	EMMDriverName[9] = "EMMXXXX0";
extern word		EMSAvail,EMSPagesAvail,EMSHandle,
					EMSPageFrame,EMSPhysicalPage;
extern EMSListStruct	EMSList[];


boolean
PML_StartupEMS(void)
{
	int		i;
	long	size;

	EMSPresent = false;			// Assume that we'll fail
	EMSAvail = 0;

	_DX = (word)EMMDriverName;
	_AX = 0x3d00;
	geninterrupt(0x21);			// try to open EMMXXXX0 device
asm	jnc	gothandle
	goto error;

gothandle:
	_BX = _AX;
	_AX = 0x4400;
	geninterrupt(0x21);			// get device info
asm	jnc	gotinfo;
	goto error;

gotinfo:
asm	and	dx,0x80
	if (!_DX)
		goto error;

	_AX = 0x4407;
	geninterrupt(0x21);			// get status
asm	jc	error
	if (!_AL)
		goto error;

	_AH = 0x3e;
	geninterrupt(0x21);			// close handle

	_AH = EMS_STATUS;
	geninterrupt(EMS_INT);
	if (_AH)
		goto error;				// make sure EMS hardware is present

	_AH = EMS_VERSION;
	geninterrupt(EMS_INT);
	if (_AH || (_AL < 0x32))	// only work on EMS 3.2 or greater (silly, but...)
		goto error;

	_AH = EMS_GETFRAME;
	geninterrupt(EMS_INT);
	if (_AH)
		goto error;				// find the page frame address
	EMSPageFrame = _BX;

	_AH = EMS_GETPAGES;
	geninterrupt(EMS_INT);
	if (_AH)
		goto error;
	if (_BX < 2)
		goto error;         	// Require at least 2 pages (32k)
	EMSAvail = _BX;

	// Don't hog all available EMS
	size = EMSAvail * (long)EMSPageSize;
	if (size - (EMSPageSize * 2) > (ChunksInFile * (long)PMPageSize))
	{
		size = (ChunksInFile * (long)PMPageSize) + EMSPageSize;
		EMSAvail = size / EMSPageSize;
	}

	_AH = EMS_ALLOCPAGES;
	_BX = EMSAvail;
	geninterrupt(EMS_INT);
	if (_AH)
		goto error;
	EMSHandle = _DX;

	mminfo.EMSmem += EMSAvail * (long)EMSPageSize;

	// Initialize EMS mapping cache
	for (i = 0;i < EMSFrameCount;i++)
		EMSList[i].baseEMSPage = -1;

	EMSPresent = true;			// We have EMS

error:
	return(EMSPresent);
}

//
//	PML_StartupXMS() - Starts up XMS for the Page Mgr's use
//		Checks for presence of an XMS driver
//		Makes sure that there's at least a page of XMS available
//		Allocates any remaining XMS (rounded down to the nearest page size)
//

extern boolean			XMSPresent;
extern word			XMSAvail,XMSPagesAvail,XMSHandle;
extern longword		XMSDriver;
extern int				XMSProtectPage;

boolean
PML_StartupXMS(void)
{
	XMSPresent = false;					// Assume failure
	XMSAvail = 0;

asm	mov	ax,0x4300
asm	int	XMS_INT         				// Check for presence of XMS driver
	if (_AL != 0x80)
		goto error;

asm	mov	ax,0x4310
asm	int	XMS_INT							// Get address of XMS driver
asm	mov	[WORD PTR XMSDriver],bx
asm	mov	[WORD PTR XMSDriver+2],es		// function pointer to XMS driver

	XMS_CALL(XMS_QUERYFREE);			// Find out how much XMS is available
	XMSAvail = _AX;
	/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
	// What preceded bugfix (also in Wolfenstein 3D)?
#ifdef GAMEVER_RESTORATION_AOG_100
	if (_BL)
#else
	if (!_AX)				// AJR: bugfix 10/8/92
#endif
		goto error;

	XMSAvail &= ~(PMPageSizeKB - 1);	// Round off to nearest page size
	if (XMSAvail < (PMPageSizeKB * 2))	// Need at least 2 pages
		goto error;

	_DX = XMSAvail;
	XMS_CALL(XMS_ALLOC);				// And do the allocation
	XMSHandle = _DX;
	/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
	// What preceded bugfix (also in Wolfenstein 3D)?
#ifdef GAMEVER_RESTORATION_AOG_100
	if (_BL)
#else
	if (!_AX)				// AJR: bugfix 10/8/92
#endif
	{
		XMSAvail = 0;
		goto error;
	}

	mminfo.XMSmem += XMSAvail * 1024;

	XMSPresent = true;
error:

	return(XMSPresent);
}

//
//
//	PML_StartupMainMem() - Allocates as much main memory as is possible for
//		the Page Mgr. The memory is allocated as non-purgeable, so if it's
//		necessary to make requests of the Memory Mgr, PM_UnlockMainMem()
//		needs to be called.
//

extern boolean			MainPresent;
extern memptr			MainMemPages[PMMaxMainMem];
extern PMBlockAttr		MainMemUsed[PMMaxMainMem];
extern int				MainPagesAvail;

void
PML_StartupMainMem(void)
{
	int		i,n;
	memptr	*p;

	MainPagesAvail = 0;
	MM_BombOnError(false);
	for (i = 0,p = MainMemPages;i < PMMaxMainMem;i++,p++)
	{
		MM_GetPtr(p,PMPageSize);
		if (mmerror)
			break;

		MainPagesAvail++;
		MainMemUsed[i] = pmba_Allocated;
	}
	MM_BombOnError(true);
	if (mmerror)
		mmerror = false;
	if (MainPagesAvail < PMMinMainMem)
		PM_ERROR(PML_STARTUPMAINMEM_LOW);
	MainPresent = true;
}

//
//	PM_Startup() - Start up the Page Mgr
//

extern boolean PMStarted;
extern char far * far PM_ParmStrings[];

void
PM_Startup(void)
{
	boolean	nomain,noems,noxms;
	int		i;

	if (PMStarted)
		return;

	nomain = noems = noxms = false;
	for (i = 1;i < _argc;i++)
	{
		switch (US_CheckParm(_argv[i],PM_ParmStrings))
		{
		case 0:
			nomain = true;
			break;
		case 1:
			noems = true;
			break;
		case 2:
			noxms = true;
			break;
		}
	}

	OpenPageFile();

	if (!noems)
		PML_StartupEMS();
	if (!noxms)
		PML_StartupXMS();

	if (nomain && !EMSPresent)
		PM_ERROR(PM_STARTUP_NO_MAIN_EMS);
	else
		PML_StartupMainMem();

	PM_Reset();

	PMStarted = true;
}

#endif

/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
// Code originally relocated from ID_SD.C in AOG v1.0, although SoundUserHook
// is *not* set (probably since it's an unused static variable)
//
// Also, for some weird reason US_Started should be here for the restoration.
#ifdef GAMEVER_RESTORATION_AOG_100
///////////////////////////////////////////////////////////////////////////
//
//	SD_Startup() - starts up the Sound Mgr
//		Detects all additional sound hardware and installs my ISR
//
///////////////////////////////////////////////////////////////////////////


extern	char far * 		far SD_ParmStrings[];

extern	word		ssPort;
extern	boolean			SD_Started;
extern	boolean		SoundSourcePresent,
				AdLibPresent,
				SoundBlasterPresent,SBProPresent,
				NeedsDigitized,NeedsMusic,
				SoundPositioned;
extern	boolean		ssIsTandy;
extern	boolean				ssNoCheck;
extern	boolean			alNoCheck;
extern	boolean					sbNoCheck,sbNoProCheck;
extern	void interrupt	(*t0OldService)(void);
extern	long			LocalTime;
extern	longword		alTimeCount;

extern	word			pcSoundLookup[255];

extern boolean US_Started; // ??

extern	void interrupt			(*sbOldIntHand)(void);
extern	byte					sbpOldFMMix,sbpOldVOCMix;
extern	word				NumDigi;
extern	word				_seg *DigiList;
extern	byte					sbDMA,sbDMAa1,sbDMAa2,sbDMAa3,
						sba1Vals[],
						sba2Vals[],
						sba3Vals[];
extern	int						sbLocation,sbInterrupt,sbIntVec,sbIntVectors[];
extern	word				ssControl,ssStatus,ssData;
extern	byte				ssOn,ssOff;

static boolean SDL_DetectSoundBlaster(int port);
static void SDL_StartSB(void);
static boolean SDL_DetectSoundSource(void);

void interrupt SDL_SBService(void);

void SDL_StartSS(void);
void SDL_ShutSS(void);

// Macros for SoundBlaster stuff
#define	sbOut(n,b)				outportb((n) + sbLocation,b)
#define	sbIn(n)					inportb((n) + sbLocation)
#define	sbWriteDelay()	while (sbIn(sbWriteStat) & 0x80); // AOG v1.0 (and Wolfenstein 3D) implementation

void
SD_Startup(void)
{
	int	i;

	if (SD_Started)
		return;

	SDL_SetDS();

	ssIsTandy = false;
	ssNoCheck = false;
	alNoCheck = false;
	sbNoCheck = false;
	sbNoProCheck = false;
#ifndef	_MUSE_
	for (i = 1;i < _argc;i++)
	{
		switch (US_CheckParm(_argv[i],SD_ParmStrings))
		{
		case 0:						// No AdLib detection
			alNoCheck = true;
			break;
		case 1:						// No SoundBlaster detection
			sbNoCheck = true;
			break;
		case 2:						// No SoundBlaster Pro detection
			sbNoProCheck = true;
			break;
		case 3:
			ssNoCheck = true;		// No Sound Source detection
			break;
		case 4:						// Tandy Sound Source handling
			ssIsTandy = true;
			break;
		case 5:						// Sound Source present at LPT1
			ssPort = 1;
			ssNoCheck = SoundSourcePresent = true;
			break;
		case 6:                     // Sound Source present at LPT2
			ssPort = 2;
			ssNoCheck = SoundSourcePresent = true;
			break;
		case 7:                     // Sound Source present at LPT3
			ssPort = 3;
			ssNoCheck = SoundSourcePresent = true;
			break;
		}
	}
#endif

	//SoundUserHook = 0;

	t0OldService = getvect(8);	// Get old timer 0 ISR

	LocalTime = TimeCount = alTimeCount = 0;

	SD_SetSoundMode(sdm_Off);
	SD_SetMusicMode(smm_Off);

	if (!ssNoCheck)
		SoundSourcePresent = SDL_DetectSoundSource();

	if (!alNoCheck)
	{
		AdLibPresent = SDL_DetectAdLib();
		if (AdLibPresent && !sbNoCheck)
		{
			int port = -1;
			char *env = getenv("BLASTER");
			if (env)
			{
				long temp;
				while (*env)
				{
					while (isspace(*env))
						env++;

					switch (toupper(*env))
					{
					case 'A':
						temp = strtol(env + 1,&env,16);
						if
						(
							(temp >= 0x210)
							/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_100
						&&	(temp <= 0x260)
#else
						&&	(temp <= 0x280)
#endif
						&&	(!(temp & 0x00f))
						)
							port = (temp - 0x200) >> 4;
						else
							SD_ERROR(SD_STARTUP_BAD_ADDRESS);
						break;
					case 'I':
						temp = strtol(env + 1,&env,10);
						if
						(
							(temp >= 0)
						&&	(temp <= 10)
						&&	(sbIntVectors[temp] != -1)
						)
						{
							sbInterrupt = temp;
							sbIntVec = sbIntVectors[sbInterrupt];
						}
						else
							SD_ERROR(SD_STARTUP_BAD_INTERRUPT);
						break;
					case 'D':
						temp = strtol(env + 1,&env,10);
						if ((temp == 0) || (temp == 1) || (temp == 3))
							SDL_SBSetDMA(temp);
						else
							SD_ERROR(SD_STARTUP_BAD_DMA);
						break;
					default:
						while (isspace(*env))
							env++;
						while (*env && !isspace(*env))
							env++;
						break;
					}
				}
			}
			SoundBlasterPresent = SDL_DetectSoundBlaster(port);
		}
	}

	for (i = 0;i < 255;i++)
		pcSoundLookup[i] = i * 60;

	if (SoundBlasterPresent)
		SDL_StartSB();

	SDL_SetupDigi();

	SD_Started = true;
}
#endif

///////////////////////////////////////////////////////////////////////////
//
//	US_Startup() - Starts the User Mgr
//
///////////////////////////////////////////////////////////////////////////

extern boolean US_Started;
extern char far * far US_ParmStrings[];
extern char far * far US_ParmStrings2[];
extern int USL_HardError(word errval,int ax,int bp,int si);

void
US_Startup(void)
{
	int	i,n;

	if (US_Started)
		return;

	harderr(USL_HardError);	// Install the fatal error handler

	US_InitRndT(true);		// Initialize the random number generator

	for (i = 1;i < _argc;i++)
	{
		switch (US_CheckParm(_argv[i],US_ParmStrings2))
		{
		case 0:
			compatability = true;
			break;
		case 1:
			compatability = false;
			break;
		}
	}

	// Check for TED launching here
	for (i = 1;i < _argc;i++)
	{
		n = US_CheckParm(_argv[i],US_ParmStrings);
		switch(n)
		{
		 case 0:
#if 0
			tedlevelnum = atoi(_argv[i + 1]);
//		   if (tedlevelnum >= 0)
			  tedlevel = true;
#endif
			break;

//		 case 1:
//			NoWait = true;
//			break;
		}
	}

	US_Started = true;
}

/*
=======================
=
= VL_Startup	// WOLFENSTEIN HACK
=
=======================
*/

/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
// Relocate this for v1.0
#ifdef GAMEVER_RESTORATION_AOG_100
static	char far * far ParmStrings[] = {"HIDDENCARD",""};
#endif

void	VL_Startup (void)
{
	int i,videocard;

	asm	cld;

	videocard = VL_VideoID ();
	for (i = 1;i < _argc;i++)
		if (US_CheckParm(_argv[i],ParmStrings) == 0)
		{
			videocard = 5;
			break;
		}

	if (videocard != 5)
		Quit ("Improper video card! Try the -HIDDENCARD command line parameter!");

}

#if !RESTART_PICTURE_PAUSE

/*
=======================
=
= VL_SetVGAPlaneMode
=
=======================
*/

void	VL_SetVGAPlaneMode (void)
{
asm	mov	ax,0x13
asm	int	0x10
	VL_DePlaneVGA ();
	VGAMAPMASK(15);
	VL_SetLineWidth (40);
}

/*
=================
=
= VL_ClearVideo
=
= Fill the entire video buffer with a given color
=
=================
*/

void VL_ClearVideo (byte color)
{
asm	mov	dx,GC_INDEX
asm	mov	al,GC_MODE
asm	out	dx,al
asm	inc	dx
asm	in	al,dx
asm	and	al,0xfc				// write mode 0 to store directly to video
asm	out	dx,al

asm	mov	dx,SC_INDEX
asm	mov	ax,SC_MAPMASK+15*256
asm	out	dx,ax				// write through all four planes

asm	mov	ax,SCREENSEG
asm	mov	es,ax
asm	mov	al,[color]
asm	mov	ah,al
asm	mov	cx,0x8000			// 0x8000 words, clearing 8 video bytes/word
asm	xor	di,di
asm	rep	stosw
}

/*
=================
=
= VL_DePlaneVGA
=
=================
*/

void VL_DePlaneVGA (void)
{

//
// change CPU addressing to non linear mode
//

//
// turn off chain 4 and odd/even
//
	outportb (SC_INDEX,SC_MEMMODE);
	outportb (SC_INDEX+1,(inportb(SC_INDEX+1)&~8)|4);

	outportb (SC_INDEX,SC_MAPMASK);		// leave this set throughought

//
// turn off odd/even and set write mode 0
//
	outportb (GC_INDEX,GC_MODE);
	outportb (GC_INDEX+1,inportb(GC_INDEX+1)&~0x13);

//
// turn off chain
//
	outportb (GC_INDEX,GC_MISCELLANEOUS);
	outportb (GC_INDEX+1,inportb(GC_INDEX+1)&~2);

//
// clear the entire buffer space, because int 10h only did 16 k / plane
//
	VL_ClearVideo (0);

//
// change CRTC scanning from doubleword to byte mode, allowing >64k scans
//
	outportb (CRTC_INDEX,CRTC_UNDERLINE);
	outportb (CRTC_INDEX+1,inportb(CRTC_INDEX+1)&~0x40);

	outportb (CRTC_INDEX,CRTC_MODE);
	outportb (CRTC_INDEX+1,inportb(CRTC_INDEX+1)|0x40);
}

/*
====================
=
= VL_SetLineWidth
=
= Line witdh is in WORDS, 40 words is normal width for vgaplanegr
=
====================
*/

void VL_SetLineWidth (unsigned width)
{
	int i,offset;

//
// set wide virtual screen
//
	outport (CRTC_INDEX,CRTC_OFFSET+width*256);

//
// set up lookup tables
//
	linewidth = width*2;

	offset = 0;

	for (i=0;i<MAXSCANLINES;i++)
	{
		ylookup[i]=offset;
		offset += linewidth;
	}
}

#endif


/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
// Code originally relocated from ID_SD.C in AOG v1.0,
// with minor changes to SDL_StartSB
#ifdef GAMEVER_RESTORATION_AOG_100
///////////////////////////////////////////////////////////////////////////
//
//	SDL_CheckSB() - Checks to see if a SoundBlaster resides at a
//		particular I/O location
//
///////////////////////////////////////////////////////////////////////////
static boolean
SDL_CheckSB(int port)
{
	int	i;

	sbLocation = port << 4;		// Initialize stuff for later use

	sbOut(sbReset,true);		// Reset the SoundBlaster DSP
asm	mov	dx,alFMStatus			// Wait >4usec
asm	in	al, dx
asm	in	al, dx
asm	in	al, dx
asm	in	al, dx
asm	in	al, dx
asm	in	al, dx
asm	in	al, dx
asm	in	al, dx
asm	in	al, dx

	sbOut(sbReset,false);		// Turn off sb DSP reset
asm	mov	dx,alFMStatus			// Wait >100usec
asm	mov	cx,100
usecloop:
asm	in	al,dx
asm	loop usecloop

	for (i = 0;i < 100;i++)
	{
		if (sbIn(sbDataAvail) & 0x80)		// If data is available...
		{
			if (sbIn(sbReadData) == 0xaa)	// If it matches correct value
				return(true);
			else
			{
				sbLocation = -1;			// Otherwise not a SoundBlaster
				return(false);
			}
		}
	}
	sbLocation = -1;						// Retry count exceeded - fail
	return(false);
}

///////////////////////////////////////////////////////////////////////////
//
//	Checks to see if a SoundBlaster is in the system. If the port passed is
//		-1, then it scans through all possible I/O locations. If the port
//		passed is 0, then it uses the default (2). If the port is >0, then
//		it just passes it directly to SDL_CheckSB()
//
///////////////////////////////////////////////////////////////////////////
static boolean
SDL_DetectSoundBlaster(int port)
{
	int	i;

	if (port == 0)					// If user specifies default, use 2
		port = 2;
	if (port == -1)
	{
		if (SDL_CheckSB(2))			// Check default before scanning
			return(true);

		if (SDL_CheckSB(4))			// Check other SB Pro location before scan
			return(true);

		for (i = 1;i <= 6;i++)		// Scan through possible SB locations
		{
			if ((i == 2) || (i == 4))
				continue;

			if (SDL_CheckSB(i))		// If found at this address,
				return(true);		//	return success
		}
		return(false);				// All addresses failed, return failure
	}
	else
		return(SDL_CheckSB(port));	// User specified address or default
}

///////////////////////////////////////////////////////////////////////////
//
//	SDL_SBSetDMA() - Sets the DMA channel to be used by the SoundBlaster
//		code. Sets up sbDMA, and sbDMAa1-sbDMAa3 (used by SDL_SBPlaySeg()).
//
///////////////////////////////////////////////////////////////////////////
void
SDL_SBSetDMA(byte channel)
{
	if (channel > 3)
		/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_100
		SD_ERROR(SDL_SBSETDMA_BAD_DMA);
#else
		SD_ERROR(SD_STARTUP_BAD_DMA);
#endif

	sbDMA = channel;
	sbDMAa1 = sba1Vals[channel];
	sbDMAa2 = sba2Vals[channel];
	sbDMAa3 = sba3Vals[channel];
}

///////////////////////////////////////////////////////////////////////////
//
//	SDL_StartSB() - Turns on the SoundBlaster
//
///////////////////////////////////////////////////////////////////////////
static void
SDL_StartSB(void)
{
	byte	timevalue,test;

	sbIntVec = sbIntVectors[sbInterrupt];
	if (sbIntVec < 0)
		/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_100
		SD_ERROR(SDL_STARTSB_BAD_INTERRUPT);
#else
		SD_ERROR(SD_STARTUP_BAD_INTERRUPT);
#endif

	//sbPIC1Mask = 1 << (sbInterrupt & 7);
	//sbPIC2Mask = 1 << 2;

	sbOldIntHand = getvect(sbIntVec);	// Get old interrupt handler
	setvect(sbIntVec,SDL_SBService);	// Set mine

	//SDL_EnableDMAInt();					// Enable DMA interrupt

	sbWriteDelay();
	sbOut(sbWriteCmd,0xd1);				// Turn on DSP speaker

	// Set the SoundBlaster DAC time constant for 7KHz
	timevalue = 256 - (1000000 / 7000);
	//sbLastTimeValue = timevalue;
	sbWriteDelay();
	sbOut(sbWriteCmd,0x40);
	sbWriteDelay();
	sbOut(sbWriteData,timevalue);

	SBProPresent = false;
	if (sbNoProCheck)
		return;

	// Check to see if this is a SB Pro
	sbOut(sbpMixerAddr,sbpmFMVol);
	sbpOldFMMix = sbIn(sbpMixerData);
	sbOut(sbpMixerData,0xbb);
	test = sbIn(sbpMixerData);
	if (test == 0xbb)
	{
		// Boost FM output levels to be equivilent with digitized output
		sbOut(sbpMixerData,0xff);
		test = sbIn(sbpMixerData);
		if (test == 0xff)
		{
			SBProPresent = true;

			// Save old Voice output levels (SB Pro)
			sbOut(sbpMixerAddr,sbpmVoiceVol);
			sbpOldVOCMix = sbIn(sbpMixerData);

			// Turn SB Pro stereo DAC off
			sbOut(sbpMixerAddr,sbpmControl);
			sbOut(sbpMixerData,0);				// 0=off,2=on
		}
	}
}


void
SDL_SetupDigi(void)
{
	memptr	list;
	word	far *p,
			pg;
	int		i;

	PM_UnlockMainMem();
	MM_GetPtr(&list,PMPageSize);
	PM_CheckMainMem();
	p = (word far *)MK_FP(PM_GetPage(ChunksInFile - 1),0);
	_fmemcpy((void far *)list,(void far *)p,PMPageSize);
	pg = PMSoundStart;
	for (i = 0;i < PMPageSize / (sizeof(word) * 2);i++,p += 2)
	{
		if (pg >= ChunksInFile - 1)
			break;
		pg += (p[1] + (PMPageSize - 1)) / PMPageSize;
	}
	PM_UnlockMainMem();
	MM_GetPtr((memptr *)&DigiList,i * sizeof(word) * 2);
	_fmemcpy((void far *)DigiList,(void far *)list,i * sizeof(word) * 2);
	MM_FreePtr(&list);
	NumDigi = i;

	for (i = 0;i < LASTSOUND;i++)
		DigiMap[i] = -1;
}



///////////////////////////////////////////////////////////////////////////
//
//	SDL_CheckSS() - Checks to see if a Sound Source is present at the
//		location specified by the sound source variables
//
///////////////////////////////////////////////////////////////////////////
static boolean
SDL_CheckSS(void)
{
	boolean		present = false;
	longword	lasttime;

	// Turn the Sound Source on and wait awhile (4 ticks)
	SDL_StartSS();

	lasttime = TimeCount;
	while (TimeCount < lasttime + 4)
		;

asm	mov		dx,[ssStatus]	// Check to see if FIFO is currently empty
asm	in		al,dx
asm	test	al,0x40
asm	jnz		checkdone		// Nope - Sound Source not here

asm	mov		cx,32			// Force FIFO overflow (FIFO is 16 bytes)
outloop:
asm	mov		dx,[ssData]		// Pump a neutral value out
asm	mov		al,0x80
asm	out		dx,al

asm	mov		dx,[ssControl]	// Pulse printer select
asm	mov		al,[ssOff]
asm	out		dx,al
asm	push	ax
asm	pop		ax
asm	mov		al,[ssOn]
asm	out		dx,al

asm	push	ax				// Delay a short while before we do this again
asm	pop		ax
asm	push	ax
asm	pop		ax

asm	loop	outloop

asm	mov		dx,[ssStatus]	// Is FIFO overflowed now?
asm	in		al,dx
asm	test	al,0x40
asm	jz		checkdone		// Nope, still not - Sound Source not here

	present = true;			// Yes - it's here!

checkdone:
	SDL_ShutSS();
	return(present);
}

static boolean
SDL_DetectSoundSource(void)
{
	for (ssPort = 1;ssPort <= 3;ssPort++)
		if (SDL_CheckSS())
			return(true);
	return(false);
}
#endif


/*
==================
=
= BuildTables
=
= Calculates:
=
= scale                 projection constant
= sintable/costable     overlapping fractional tables
=
==================
*/

const   float   radtoint = (float)FINEANGLES/2/PI;

void BuildTables (void)
{
  int           i;
  float         angle,anglestep;
  double        tang;
  fixed         value;
  byte far *    temp;


//
// calculate fine tangents
//

	for (i=0;i<FINEANGLES/8;i++)
	{
		tang = tan( (i+0.5)/radtoint);
		finetangent[i] = tang*TILEGLOBAL;
		finetangent[FINEANGLES/4-1-i] = 1/tang*TILEGLOBAL;
	}

//
// costable overlays sintable with a quarter phase shift
// ANGLES is assumed to be divisable by four
//
// The low word of the value is the fraction, the high bit is the sign bit,
// bits 16-30 should be 0
//

  angle = 0;
  anglestep = PI/2/ANGLEQUAD;
  for (i=0;i<=ANGLEQUAD;i++)
  {
	value=GLOBAL1*sin(angle);
	sintable[i]=
	  sintable[i+ANGLES]=
	  sintable[ANGLES/2-i] = value;
	sintable[ANGLES-i]=
	  sintable[ANGLES/2+i] = value | 0x80000000l;
	angle += anglestep;
  }
  /*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_100
// Fix ColorMap
  MM_GetPtr(&(memptr)temp,16896);
  _fmemcpy(temp,colormap,16896);
  lightsource=(byte far *)(((long)colormap + 255)&~0xff);
  _fmemcpy(lightsource,temp,16384);
#endif
}

/*
===================
=
= SetupWalls
=
= Map tile values to scaled pics
=
===================
*/

void SetupWalls (void)
{
	int     i;

	//
	// Hey! Yea You! This is where you can VERY easly setup to use a
	// specific 'BANK' of wall graphics.... JTR
	//

	for (i=1;i<MAXWALLTILES;i++)
	{
		horizwall[i]=(i-1)*2;
		vertwall[i]=(i-1)*2+1;
	}
}




/*
=====================
=
= InitDigiMap
=
=====================
*/
// 3D_GAME.C

/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
// Re-enable commented out entries for AOG, *and* relocate for v1.0
#ifdef GAMEVER_RESTORATION_AOG_100
static  byte far wolfdigimap[] =
{
			// These first sounds are in the upload version

			ATKIONCANNONSND,					0,
			ATKCHARGEDSND,						1,
			ATKBURSTRIFLESND,             2,
			ATKGRENADESND,                46,

			OPENDOORSND,                  3,
			CLOSEDOORSND,                 4,
			HTECHDOOROPENSND,             5,
			HTECHDOORCLOSESND,            6,

			INFORMANTDEATHSND,            7,
			SCIENTISTHALTSND,             19,
			SCIENTISTDEATHSND,            20,

			GOLDSTERNHALTSND,             8,
			GOLDSTERNLAUGHSND,            24,

			HALTSND,                      9,			// Rent-A-Cop 1st sighting
			RENTDEATH1SND,                10,		// Rent-A-Cop Death

			EXPLODE1SND,                  11,

			GGUARDHALTSND,                12,
			GGUARDDEATHSND,               17,

			PROHALTSND,                   16,
			PROGUARDDEATHSND,             13,

			BLUEBOYDEATHSND,              18,
			BLUEBOYHALTSND,					51,

			SWATHALTSND,                  22,
			SWATDIESND,                   47,

			SCANHALTSND,                  15,
			SCANDEATHSND,                 23,

			PODHATCHSND,                  26,
			PODHALTSND,							50,
			PODDEATHSND,                  49,

			ELECTSHOTSND,                 27,

/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
// Also filter these for shareware releases
#if (GAME_VERSION != SHAREWARE_VERSION)
			DOGBOYHALTSND,                14,
			DOGBOYDEATHSND,               21,
			ELECARCDAMAGESND,             25,
			ELECAPPEARSND,                28,
			ELECDIESND,                   29,

			INFORMDEATH2SND,              39,		// Informant Death #2
			RENTDEATH2SND,                34,      // Rent-A-Cop Death #2
			PRODEATH2SND,                 42,	   // PRO Death #2
			SWATDEATH2SND,                48, 		// SWAT Death #2
			SCIDEATH2SND,					   53,		// Gen. Sci Death #2

			LIQUIDDIESND,                 30,

			GURNEYSND,                    31,
			GURNEYDEATHSND,               41,

			WARPINSND,                    32,
			WARPOUTSND,                   33,

			EXPLODE2SND,                  35,

			LCANHALTSND,                  36,
			LCANDEATHSND,                 37,

			RENTDEATH3SND,		            38,		// Rent-A-Cop Death #3
			INFORMDEATH3SND,              40,		// Informant Death #3
			PRODEATH3SND,                 43,      // PRO Death #3
			SWATDEATH3SND,						52,		// Swat Guard #3
			SCIDEATH3SND,						54,		// Gen. Sci Death #3

			LCANBREAKSND,                 44,
			SCANBREAKSND,                 45,
			CLAWATTACKSND,						56,
			SPITATTACKSND,						55,
			PUNCHATTACKSND,					57,
#endif // VERSIONS RESTORATION

			LASTSOUND
};
#endif // GAMEVER_RESTORATION_AOG_100

void InitDigiMap (void)
{
	char far *map;

	for (map = wolfdigimap;*map != LASTSOUND;map += 2)
		DigiMap[map[0]] = map[1];
}



/*
======================
=
= CAL_SetupAudioFile
=
======================
*/

void CAL_SetupAudioFile (void)
{
	int handle;
	long length;
	char fname[13];

//
// load maphead.ext (offsets and tileinfo for map file)
//
#ifndef AUDIOHEADERLINKED
	strcpy(fname,aheadname);
	strcat(fname,extension);

	if ((handle = open(fname,
		 O_RDONLY | O_BINARY, S_IREAD)) == -1)
		CA_CannotOpen(fname);

	length = filelength(handle);
	MM_GetPtr (&(memptr)audiostarts,length);
	CA_FarRead(handle, (byte far *)audiostarts, length);
	close(handle);
#else
	audiohuffman = (huffnode *)&audiodict;
	CAL_OptimizeNodes (audiohuffman);
	audiostarts = (long _seg *)FP_SEG(&audiohead);
#endif

//
// open the data file
//
	/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_100
#ifndef AUDIOHEADERLINKED
	strcpy(fname,afilename);
	strcat(fname,extension);

	if ((audiohandle = open(fname,
		 O_RDONLY | O_BINARY, S_IREAD)) == -1)
		CA_CannotOpen(fname);
#else
	if ((audiohandle = open("AUDIO."EXTENSION,
		 O_RDONLY | O_BINARY, S_IREAD)) == -1)
		CA_ERROR(SETUPAUDIO_CANT_OPEN);
#endif
#else
	OpenAudioFile();
#endif
}



/*
======================
=
= CAL_SetupGrFile
=
======================
*/
void CAL_SetupGrFile (void)
{
	char fname[13];
	int handle;
	memptr compseg;

#ifdef GRHEADERLINKED

	grhuffman = (huffnode *)&EGAdict;
	grstarts = (long _seg *)FP_SEG(&EGAhead);

	CAL_OptimizeNodes (grhuffman);

#else

//
// load ???dict.ext (huffman dictionary for graphics files)
//

	strcpy(fname,gdictname);
	strcat(fname,extension);

	if ((handle = open(fname,
		 O_RDONLY | O_BINARY, S_IREAD)) == -1)
		CA_CannotOpen(fname);

	read(handle, &grhuffman, sizeof(grhuffman));
	close(handle);
	CAL_OptimizeNodes (grhuffman);
//
// load the data offsets from ???head.ext
//
	MM_GetPtr (&(memptr)grstarts,(NUMCHUNKS+1)*FILEPOSSIZE);

	strcpy(fname,gheadname);
	strcat(fname,extension);

	if ((handle = open(fname,
		 O_RDONLY | O_BINARY, S_IREAD)) == -1)
		CA_CannotOpen(fname);

	CA_FarRead(handle, (memptr)grstarts, (NUMCHUNKS+1)*FILEPOSSIZE);

	close(handle);


#endif

//
// Open the graphics file, leaving it open until the game is finished
//
	/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_100
	strcpy(fname,gfilename);
	strcat(fname,extension);

	grhandle = open(fname, O_RDONLY | O_BINARY);
	if (grhandle == -1)
		CA_CannotOpen(fname);
#else
	OpenGrFile();
#endif

//
// load the pic and sprite headers into the arrays in the data segment
//
	MM_GetPtr(&(memptr)pictable,NUMPICS*sizeof(pictabletype));
	CAL_GetGrChunkLength(STRUCTPIC);		// position file pointer
	MM_GetPtr(&compseg,chunkcomplen);
	CA_FarRead (grhandle,compseg,chunkcomplen);
	CAL_HuffExpand (compseg, (byte huge *)pictable,NUMPICS*sizeof(pictabletype),grhuffman,false);
	MM_FreePtr(&compseg);


// MDM begin
#if 0
	MM_GetPtr(&(memptr)picmtable,NUMPICM*sizeof(pictabletype));
	CAL_GetGrChunkLength(STRUCTPICM);		// position file pointer
	MM_GetPtr(&compseg,chunkcomplen);
	CA_FarRead (grhandle,compseg,chunkcomplen);
	CAL_HuffExpand (compseg, (byte huge *)picmtable,NUMPICS*sizeof(pictabletype),grhuffman,false);
	MM_FreePtr(&compseg);
#endif
// MDM end

}




/*
======================
=
= CAL_SetupMapFile
=
======================
*/

void CAL_SetupMapFile (void)
{
	int	i;
	int handle;
	long length,pos;
	char fname[13];

//
// load maphead.ext (offsets and tileinfo for map file)
//
#ifndef MAPHEADERLINKED
	strcpy(fname,mheadname);
	strcat(fname,extension);

	if ((handle = open(fname,
		 O_RDONLY | O_BINARY, S_IREAD)) == -1)
		CA_CannotOpen(fname);

	length = filelength(handle);
	MM_GetPtr (&(memptr)tinf,length);
	CA_FarRead(handle, tinf, length);
	close(handle);
#else

	tinf = (byte _seg *)FP_SEG(&maphead);

#endif

//
// open the data file
//
	/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_100
#ifdef CARMACIZED
	strcpy(fname,"GAMEMAPS.");
	strcat(fname,extension);

	if ((maphandle = open(fname,
		 O_RDONLY | O_BINARY, S_IREAD)) == -1)
		CA_CannotOpen(fname);
#else
	strcpy(fname,mfilename);
	strcat(fname,extension);

	if ((maphandle = open(fname,
		 O_RDONLY | O_BINARY, S_IREAD)) == -1)
		CA_CannotOpen(fname);
#endif
#else
	OpenMapFile();
#endif

//
// load all map header
//
	for (i=0;i<NUMMAPS;i++)
	{
		pos = ((mapfiletype	_seg *)tinf)->headeroffsets[i];
		if (pos<0)						// $FFFFFFFF start is a sparse map
			continue;

		MM_GetPtr(&(memptr)mapheaderseg[i],sizeof(maptype));
		MM_SetLock(&(memptr)mapheaderseg[i],true);
		lseek(maphandle,pos,SEEK_SET);
		CA_FarRead (maphandle,(memptr)mapheaderseg[i],sizeof(maptype));
	}

//
// allocate space for 3 64*64 planes
//
	for (i=0;i<MAPPLANES;i++)
	{
		MM_GetPtr (&(memptr)mapsegs[i],64*64*2);
		MM_SetLock (&(memptr)mapsegs[i],true);
	}

#if FORCE_FILE_CLOSE
   CloseMapFile();
#endif

}


// --------------------- Other general functions ------------------------


/*
====================
=
= ReadConfig
=
====================
*/

void ReadConfig(void)
{
	int                     file;
	SDMode          sd;
	SMMode          sm;
	SDSMode         sds;

	boolean config_found=false;
/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_POST200
	long flags=gamestate.flags;
#else
	unsigned flags=gamestate.flags;
#endif
#ifndef GAMEVER_RESTORATION_AOG_PRE210
	MakeDestPath(configname);

	if ( (file = open(tempPath,O_BINARY | O_RDONLY)) != -1)
#else
	if ( (file = open(configname,O_BINARY | O_RDONLY)) != -1)
#endif
	{
	//
	// valid config file
	//
		read(file,Scores,sizeof(HighScore) * MaxScores);

		read(file,&sd,sizeof(sd));
		read(file,&sm,sizeof(sm));
		read(file,&sds,sizeof(sds));

		read(file,&mouseenabled,sizeof(mouseenabled));
		read(file,&joystickenabled,sizeof(joystickenabled));
		read(file,&joypadenabled,sizeof(joypadenabled));
		read(file,&joystickprogressive,sizeof(joystickprogressive));
		read(file,&joystickport,sizeof(joystickport));

		read(file,&dirscan,sizeof(dirscan));
		read(file,&buttonscan,sizeof(buttonscan));
		read(file,&buttonmouse,sizeof(buttonmouse));
		read(file,&buttonjoy,sizeof(buttonjoy));

		read(file,&viewsize,sizeof(viewsize));
		read(file,&mouseadjustment,sizeof(mouseadjustment));

		read(file,&flags,sizeof(flags));		// Use temp so we don't destroy pre-sets.
		/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_100
		flags &= GS_HEARTB_SOUND|GS_ATTACK_INFOAREA|GS_DRAW_CEILING|GS_DRAW_FLOOR;			 	// Mask out the useful flags!
#elif (!defined GAMEVER_RESTORATION_AOG_POST200) // Includes Planet Strike
		flags &= GS_HEARTB_SOUND|GS_ATTACK_INFOAREA|GS_LIGHTING|GS_DRAW_CEILING|GS_DRAW_FLOOR;			 	// Mask out the useful flags!
#else
		flags &= GS_HEARTB_SOUND|GS_ATTACK_INFOAREA|GS_LIGHTING|GS_DRAW_CEILING|GS_DRAW_FLOOR|GS_TAB_ROTATED_MAP;			 	// Mask out the useful flags!
#endif
#ifdef GAMEVER_RESTORATION_AOG
		if (IsA386 == false)
			flags &= ~(GS_DRAW_CEILING|GS_DRAW_FLOOR);
#endif

		gamestate.flags |= flags;				// Must "OR", some flags are already set.
		close(file);

		/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
//#if 0
#ifdef CEILING_FLOOR_COLORS
		if (gamestate.flags & GS_DRAW_FLOOR)
		{
			PM_Shutdown();
			PM_Startup ();
			PM_UnlockMainMem ();
		}
#endif
#endif

		if (sd == sdm_AdLib &&
			(!AdLibPresent || !SoundBlasterPresent))
		{
			sd = sdm_PC;
			sd = smm_Off;
		}

		if ((sds == sds_SoundBlaster && !SoundBlasterPresent) ||
			(sds == sds_SoundSource && !SoundSourcePresent))
			sds = sds_Off;

		if (!MousePresent)
			mouseenabled = false;
		if (!JoysPresent[joystickport])
			joystickenabled = false;

		MainMenu[6].active=1;
		MainItems.curpos=0;

		config_found=true;
	}

	if ((!config_found) || (!viewsize))
	{
	//
	// no config file, so select by hardware
	//
		if (SoundBlasterPresent || AdLibPresent)
		{
			sd = sdm_AdLib;
			sm = smm_AdLib;
		}
		else
		{
			sd = sdm_PC;
			sm = smm_Off;
		}

		if (SoundBlasterPresent)
			sds = sds_SoundBlaster;
		else if (SoundSourcePresent)
			sds = sds_SoundSource;
		else
			sds = sds_Off;

		if (MousePresent)
			mouseenabled = true;

		joystickenabled = false;
		joypadenabled = false;
		joystickport = 0;
		joystickprogressive = false;

		viewsize = 17;
		mouseadjustment=5;
		/*** BLAKE STONE: ALIENS OF GOLD V2.1+3.0 RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_POST200
		gamestate.flags |= GS_HEARTB_SOUND|GS_ATTACK_INFOAREA|GS_TAB_ROTATED_MAP;
#else
		gamestate.flags |= GS_HEARTB_SOUND|GS_ATTACK_INFOAREA;
#endif

		/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
		if (IsA386)
		{
#endif
#ifdef GAMEVER_RESTORATION_AOG_100
#ifdef CEILING_FLOOR_COLORS
			gamestate.flags |= GS_DRAW_CEILING|GS_DRAW_FLOOR;
#endif
#else
#ifdef CEILING_FLOOR_COLORS
			gamestate.flags |= GS_DRAW_CEILING|GS_DRAW_FLOOR|GS_LIGHTING;
#else
			gamestate.flags |= GS_LIGHTING;
#endif
#endif

		/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
//#if 0
			PM_Shutdown();
			PM_Startup ();
			PM_UnlockMainMem ();
		}
#endif
	}

	SD_SetMusicMode (sm);
	SD_SetSoundMode (sd);
	SD_SetDigiDevice (sds);

}

/*
========================
=
= Patch386
=
= Patch ldiv to use 32 bit instructions
=
========================
*/

/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
// Relocate this for v1.0
#ifdef GAMEVER_RESTORATION_AOG_100
char    far * far JHParmStrings[] = {"no386",nil};
#endif

void Patch386 (void)
{
extern void far jabhack2(void);
extern int far  CheckIs386(void);

	int     i;

	for (i = 1;i < _argc;i++)
		/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
		if (!US_CheckParm(_argv[i],JHParmStrings))
		{
			IsA386 = false;
			return;
		}
#else
		switch (US_CheckParm(_argv[i],JHParmStrings))
      {
      	case 0:
				IsA386 = false;
			return;

         case 1:
         	IsA386 = true;
         return;
		}
#endif

	if (CheckIs386())
	{
		IsA386 = true;
		jabhack2();
	}
	else
		IsA386 = false;
}

#pragma warn -rvl

#if 0

//------------------------------------------------------------------------
// CheckIs386()
//------------------------------------------------------------------------
int CheckIs386()
{

asm	pushf						// Save flag registers, we use them here
asm	xor	ax,ax				// Clear AX and...
asm	push	ax					// ...push it onto the stack
asm	popf						// Pop 0 into flag registers (all bits to 0),
asm	pushf						// attempting to set bits 12-15 of flags to 0's
asm	pop	ax					// Recover the save flags
asm	and	ax,08000h		// If bits 12-15 of flags are set to
asm	cmp	ax,08000h		// zero then it's 8088/86 or 80188/186
asm	jz	not386

asm	mov	ax,07000h		// Try to set flag bits 12-14 to 1's
asm	push	ax					// Push the test value onto the stack
asm	popf						// Pop it into the flag register
asm	pushf						// Push it back onto the stack
asm	pop	ax					// Pop it into AX for check
asm	and	ax,07000h		// if bits 12-14 are cleared then
asm	jz	not386				// the chip is an 80286

asm	mov	ax,1				// We now assume it's a 80386 or better
asm	popf
asm	retf

not386:
asm	xor	ax,ax
asm	popf
asm	retf

}

#endif

#pragma warn +rvl

#define CHECK_FOR_EPISODES

extern CP_itemtype far NewEmenu[];
extern int EpisodeSelect[];

/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG

//-------------------------------------------------------------------------
// CheckForEpisodes() - CHECK FOR VERSION/EXTESION
//-------------------------------------------------------------------------
void CheckForEpisodes(void)
{
	struct ffblk f;
	short i;

#if (GAME_VERSION != SHAREWARE_VERSION)
	if (!findfirst("*.VSI",&f,FA_ARCH))
		strcpy(extension,"VSI");
#else
	if (!findfirst("*.FSW",&f,FA_ARCH))
		strcpy(extension,"FSW");
#endif
	else
	{
		printf("No Fire Strike data files found!");
		exit(0);
	}

	for (i=0;i<mv_NUM_MOVIES;i++)
		strcat(Movies[i].FName,extension);

#ifdef ACTIVATE_TERMINAL
	strcat(term_com_name,extension);
	strcat(term_msg_name,extension);
#endif

	strcat(configname,extension);
	_fstrcat(SaveName,extension);
	strcat(PageFileName,extension);
	strcat(audioname,extension);
	strcat(demoname,extension);

#if DUAL_SWAP_FILES
	strcat(AltPageFileName,extension);
	ShadowsAvail = (!findfirst(AltPageFileName,&f,FA_ARCH));
#endif
}

#else
//#if 0

//
// ORGINAL used in Aliens of Gold
//
//-------------------------------------------------------------------------
// CheckForEpisodes() - CHECK FOR EPISODES
//-------------------------------------------------------------------------
void CheckForEpisodes(void)
{
	struct ffblk f;
	short i;

#if (GAME_VERSION != SHAREWARE_VERSION)
#ifdef CHECK_FOR_EPISODES
	if (!findfirst("*.BS6",&f,FA_ARCH))
#else
	if (!findfirst("*.BS1",&f,FA_ARCH))
#endif
	{
#ifdef CHECK_FOR_EPISODES
		strcpy(extension,"BS6");
#else
		strcpy(extension,"BS1");
#endif
		NewEmenu[1].active =
		NewEmenu[2].active =
		NewEmenu[3].active =
		NewEmenu[4].active =
		NewEmenu[5].active =
		EpisodeSelect[1] =
		EpisodeSelect[2] =
		EpisodeSelect[3] =
		EpisodeSelect[4] =
		EpisodeSelect[5] = AT_ENABLED;
	}
	else
#ifdef CHECK_FOR_EPISODES
		if (!findfirst("*.BS3",&f,FA_ARCH))
#else
		if (!findfirst("*.BS1",&f,FA_ARCH))
#endif
		{
#ifdef CHECK_FOR_EPISODES
			strcpy(extension,"BS3");
#else
			strcpy(extension,"BS1");
#endif
			NewEmenu[1].active =
			NewEmenu[2].active =
			EpisodeSelect[1] =
			EpisodeSelect[2] = AT_ENABLED;
		}
		else
#endif
			if (!findfirst("*.BS1",&f,FA_ARCH))
			{
				strcpy(extension,"BS1");
			}
			else
			{
				printf("No Blake Stone data files found!");
				exit(0);
			}

#if BETA_TEST
// This enables specific missions for beta testers.
//
	NewEmenu[1].active =
	EpisodeSelect[1] =
	NewEmenu[2].active =
	EpisodeSelect[2] =
	NewEmenu[3].active =
	EpisodeSelect[3] =
	NewEmenu[4].active =
	EpisodeSelect[4] =
	NewEmenu[5].active =
	EpisodeSelect[5] = AT_ENABLED;
#endif

	for (i=0;i<mv_NUM_MOVIES;i++)
		strcat(Movies[i].FName,extension);

#ifdef ACTIVATE_TERMINAL
	strcat(term_com_name,extension);
	strcat(term_msg_name,extension);
#endif

	strcat(configname,extension);
	_fstrcat(SaveName,extension);
	strcat(PageFileName,extension);
	strcat(audioname,extension);
	strcat(demoname,extension);

#if DUAL_SWAP_FILES
	strcat(AltPageFileName,extension);
	/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_100
	ShadowsAvail = (!findfirst(AltPageFileName,&f,FA_ARCH));
#endif
#endif
}
#endif // RESTORATION: AOG / PS


extern char far * far MainStrs[];
extern char far bc_buffer[];

//------------------------------------------------------------------------
// PreDemo()
//------------------------------------------------------------------------
void PreDemo()
{
	int i;


#if TECH_SUPPORT_VERSION

	fontnumber=4;
	SETFONTCOLOR(0,15*3);
	CenterWindow (26,7);
	US_Print(EnterBetaCode);
	VW_UpdateScreen();
	CA_LoadAllSounds();
	PM_CheckMainMem();
	SD_PlaySound(INFORMDEATH2SND);		// Nooooo!
	IN_UserInput(TickBase*20);
	ClearMemory();

#elif BETA_TEST

	boolean param=false;

	for (i=1; i<_argc; i++)
		switch (US_CheckParm(_argv[i],MainStrs))
		{
			case 13:
				param=true;
			break;
		}

	if (!param)
	{
		char buffer[15] = {0};

		fontnumber=4;
		CenterWindow (26,7);
		US_Print(EnterBetaCode);
		VW_UpdateScreen();
		SETFONTCOLOR(0,15*3);
		US_LineInput(24*8,92,buffer,buffer,true,14,100);
		if (_fstricmp(buffer,bc_buffer))
			Quit("Bad beta code!");
	}
#endif



	/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_100
#if GAME_VERSION == SHAREWARE_VERSION
#if IN_DEVELOPMENT || GEORGE_CHEAT
	if (!MS_CheckParm("nochex"))
#endif
	{
#if  (!SKIP_CHECKSUMS)
//	CheckValidity("MAPTEMP.",MAPTEMP_CHECKSUM,"LEVELS");
	CheckValidity("MAPTEMP.",MAPTEMP_CHECKSUM);
#endif
	}
#else
#if  (!SKIP_CHECKSUMS)
	if (ChecksumFile("FILE_ID.DIZ",0) != DIZFILE_CHECKSUM)
		gamestate.flags |= GS_BAD_DIZ_FILE;
#endif
#endif
#endif

	VL_SetPaletteIntensity(0,255,&vgapal,0);

	if (!(gamestate.flags & GS_NOWAIT))
	{
/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#if (defined GAMEVER_RESTORATION_AOG) && (GAME_VERSION != SHAREWARE_VERSION)
//#if (0)				// GAME_VERSION != SHAREWARE_VERSION
//---------------------
// Anti-piracy screen
//---------------------
	// Cache pic
	//
		CA_CacheScreen(PIRACYPIC);

	// Cache and set palette.  AND  Fade it in!
	//
		CA_CacheGrChunk(PIRACYPALETTE);
		VL_SetPalette (0,256,grsegs[PIRACYPALETTE]);
		VL_SetPaletteIntensity(0,255,grsegs[PIRACYPALETTE],0);
		VW_UpdateScreen();

/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG
		VL_FadeOut (0, 255, 0, 0, 25, 20);
#endif
		VL_FadeIn(0,255,grsegs[PIRACYPALETTE],30);

	// Wait a little
	//
		IN_UserInput(TickBase*20);

	// Free palette
	//
		UNCACHEGRCHUNK(PIRACYPALETTE);

/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG
		VL_FadeOut (0, 255, 0, 0, 25, 20);
#endif
		VW_FadeOut();

	// Cleanup screen for upcoming SetPalette call
	//
		{
		unsigned old_bufferofs=bufferofs;

		bufferofs=displayofs;
		VL_Bar(0,0,320,200,0);
		bufferofs=old_bufferofs;
		}
#endif

//---------------------
// Apogee presents
//---------------------
	// Cache pic
	//
		CA_CacheScreen(APOGEEPIC);

	// Load and start music
	//
		CA_CacheAudioChunk(STARTMUSIC+APOGFNFM_MUS);
		SD_StartMusic((MusicGroup far *)audiosegs[STARTMUSIC+APOGFNFM_MUS]);

	// Cache and set palette.  AND  Fade it in!
	//
		CA_CacheGrChunk(APOGEEPALETTE);
		VL_SetPalette (0,256,grsegs[APOGEEPALETTE]);
		VL_SetPaletteIntensity(0,255,grsegs[APOGEEPALETTE],0);
		VW_UpdateScreen();
		/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG
		VL_FadeOut (0, 255, 25, 29, 53, 20);
#endif
		VL_FadeIn(0,255,grsegs[APOGEEPALETTE],30);

	// Wait for end of fanfare
	//
		if (MusicMode==smm_AdLib)
		{
			IN_StartAck();
			while ((!sqPlayedOnce) && (!IN_CheckAck()));
      }
		else
			IN_UserInput(TickBase*6);

		SD_MusicOff();

	// Free palette and music.  AND  Restore palette
	//
		UNCACHEGRCHUNK(APOGEEPALETTE);
		MM_FreePtr((memptr *)&audiosegs[STARTMUSIC+APOGFNFM_MUS]);

      // Do A Blue Flash!

      /*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG
      VL_FadeOut (0, 255, 25, 29, 53, 20);
#endif
      VL_FadeOut (0, 255, 0, 	0,  0,  30);

//---------------------
// JAM logo intro
//---------------------
	// Load and start music
	//
		CA_CacheAudioChunk(STARTMUSIC+TITLE_LOOP_MUSIC);
		SD_StartMusic((MusicGroup far *)audiosegs[STARTMUSIC+TITLE_LOOP_MUSIC]);

	// Show JAM logo
	//
		/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
		if (!DoMovie(mv_intro))
#else
		if (!DoMovie(mv_intro,0))
#endif
			MAIN_ERROR(PREDEMO_NOJAM);

	/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_100
		if (PowerBall)
      {
      	int i;

			for (i=0;i<60 && (!DebugOk);i++)
   	   {
      		VL_WaitVBL(1);

				if (Keyboard[sc_LShift] && Keyboard[sc_RShift])
		      {
					CA_LoadAllSounds();
					PM_CheckMainMem();

					SD_MusicOff();

				   SD_PlaySound(SHOOTDOORSND);
		         SD_WaitSoundDone();

				   ClearMemory();
		      	DebugOk = 1;

					CA_CacheAudioChunk(STARTMUSIC+TITLE_LOOP_MUSIC);
					SD_StartMusic((MusicGroup far *)audiosegs[STARTMUSIC+TITLE_LOOP_MUSIC]);
      		}
         }
      }
#endif

//---------------------
// PC-13
//---------------------
		VL_Bar(0,0,320,200,0x14);
		VW_MarkUpdateBlock(0,0,319,199);
		CacheDrawPic(0,64,PC13PIC);
		VW_UpdateScreen();
		VW_FadeIn();
		IN_UserInput(TickBase*2);

      // Do A Red Flash!

/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG
      VL_FadeOut (0, 255, 39, 0, 0, 20);
#endif
		VW_FadeOut();
	}
}

//------------------------------------------------------------------------
// InitGame()
//------------------------------------------------------------------------
void InitGame (void)
{
	int                     i,x,y;
	unsigned        *blockstart;
//long mmsize;

	MM_Startup ();                  // so the signon screen can be freed
#if IN_DEVELOPMENT || GEORGE_CHEAT || SHOW_CHECKSUM
	if (MS_CheckParm("checksum"))
	{
		ShowChecksums();
		MM_Shutdown();
		exit(0);
	}
#endif
	CA_Startup ();

// Any problems with this version of the game?
//
#if IN_DEVELOPMENT || TECH_SUPPORT_VERSION
	if (!MS_CheckParm("nochex"))
#endif

#if !SKIP_CHECKSUMS
		CheckValidity("MAPTEMP.",MAPTEMP_CHECKSUM);

#if GAME_VERSION != SHAREWARE_VERSION
	if (ChecksumFile("FILE_ID.DIZ",0) != DIZFILE_CHECKSUM)
		gamestate.flags |= GS_BAD_DIZ_FILE;
#endif
#endif

	VL_SetVGAPlaneMode ();
	VL_SetPalette (0,256,&vgapal);

	VW_Startup ();
	IN_Startup ();
	PM_Startup ();
	PM_UnlockMainMem ();
	SD_Startup ();
	US_Startup ();

	/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_100
	if (CheckForSpecialCode(POWERBALLTEXT))
#if IN_DEVELOPMENT
		DebugOk = true;
#else
		PowerBall = true;
#endif

	if (CheckForSpecialCode(TICSTEXT))
		gamestate.flags |= GS_TICS_FOR_SCORE;

	if (CheckForSpecialCode(MUSICTEXT))
		gamestate.flags |= GS_MUSIC_TEST;

	if (CheckForSpecialCode(RADARTEXT))
		gamestate.flags |= GS_SHOW_OVERHEAD;
#endif

//mmsize = mminfo.mainmem;

#if (!IN_DEVELOPMENT)
	if (mminfo.mainmem < MIN_MEM_NEEDED)
	{
	 memptr screen;
	 CA_CacheGrChunk (ERRORSCREEN);
	 screen = grsegs[ERRORSCREEN];
	 ShutdownId();
	 movedata ((unsigned)screen,7+7*160,0xb800,0,17*160);
	 gotoxy (1,23);
	 exit(0);
	}
#endif

#if IN_DEVELOPMENT
	//
	// Clear Monocrome
	//
	_fmemset(MK_FP(0xb000,0x0000),0,4000);
#endif

//
// build some tables
//
	InitDigiMap ();

	for (i=0;i<MAPSIZE;i++)
	{
		nearmapylookup[i] = &tilemap[0][0]+MAPSIZE*i;
		farmapylookup[i] = i*64;
	}

	for (i=0;i<PORTTILESHIGH;i++)
		uwidthtable[i] = UPDATEWIDE*i;

	blockstart = &blockstarts[0];
	for (y=0;y<UPDATEHIGH;y++)
		for (x=0;x<UPDATEWIDE;x++)
			*blockstart++ = SCREENWIDTH*16*y+x*TILEWIDTH;

	updateptr = &update[0];

	bufferofs = 0;
	displayofs = 0;
	ReadConfig ();

//
// draw intro screen stuff
//
//	if (!(gamestate.flags & GS_QUICKRUN))
//		IntroScreen ();

//
// load in and lock down some basic chunks
//

	LoadFonts();

	LoadLatchMem ();
	BuildTables ();          // trig tables
	SetupWalls ();
	NewViewSize (viewsize);

//
// initialize variables
//
	InitRedShifts ();
}

//-------------------------------------------------------------------------
// ShowSystem()
//-------------------------------------------------------------------------

/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
// Relocate this for v1.0, and also edit show_text3
#ifdef GAMEVER_RESTORATION_AOG_100
/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
char far show_text1[]="\n     SYSTEM INFO\n";
char far show_text2[]="=======================\n\n";
char far show_text3[]="-- Available  Memory --\n\n";
char far show_text4[]="            ** Insufficient memory to run the game **";
char far show_text5[]="---- Extra Devices ----\n\n";

char far cinfo_text[]=	"\n"
								"BLAKE STONE: Aliens of Gold\n"
								"Copyright (c) 1993 - JAM Productions, Inc.\n"
								"All rights reserved.\n";
#endif

void ShowSystem()
{
	char avail[2][8]={"None","Present"};

	MM_Startup ();
	CA_Startup ();
	IN_Startup ();
	PM_Startup ();
	SD_Startup ();

	fprint(show_text1);
	fprint(show_text2);
	fprint(show_text3);

	printf("     MAIN: %ld",mminfo.nearheap+mminfo.farheap);
	if (mminfo.nearheap+mminfo.farheap < MIN_MEM_NEEDED)
		fprint(show_text4);
	printf("\n");
	printf("      EMS: %ld\n",4l*EMSPagesAvail*1024l);
	printf("      XMS: %ld\n\n",4l*XMSPagesAvail*1024l);

	fprint(show_text5);

	printf("        Mouse: %s\n",avail[MousePresent]);
	printf("     Joystick: %s\n",avail[JoysPresent[0]||JoysPresent[1]]);
	printf("        AdLib: %s\n",avail[AdLibPresent&&!SoundBlasterPresent]);
	printf("Sound Blaster: %s\n",avail[SoundBlasterPresent]);
	printf(" Sound Source: %s\n\n",avail[SoundSourcePresent]);
	fprint(show_text2);

	SD_Shutdown ();
	PM_Shutdown ();
	IN_Shutdown ();
	CA_Shutdown ();
	MM_Shutdown ();
}

//-------------------------------------------------------------------------
// scan_atoi()
//-------------------------------------------------------------------------
unsigned scan_atoi(char *s)
{
	while (*s && (!isdigit(*s)))			// First scans for a digit...
		s++;

	return(atoi(s));							// Then converts to integer...
}

extern char far * far MainStrs[];
extern short starting_episode,starting_level,starting_difficulty;


//-------------------------------------------------------------------------
// freed_main()
//-------------------------------------------------------------------------
void freed_main()
{
	int     i;
	struct dosdate_t d;

// Setup for APOGEECD thingie.
//
	/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG
	InitDestPath();
#endif

// Make sure there's room to play the game
//
	CheckDiskSpace(DISK_SPACE_NEEDED,CANT_PLAY_TXT,cds_dos_print);

// Which version is this? (SHAREWARE? 1-3? 1-6?)
//
	CheckForEpisodes();

	Patch386();

	for (i=1; i<_argc; i++)
		switch (US_CheckParm(_argv[i],MainStrs))
		{
#if IN_DEVELOPMENT || TECH_SUPPORT_VERSION
			case 0:											// quick run
				gamestate.flags |= GS_QUICKRUN;

			case 1:											// no wait
				gamestate.flags |= GS_NOWAIT;
			break;
#endif

			/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_100
			case 2:											// starting level
				gamestate.flags |= GS_STARTLEVEL;
				starting_level=scan_atoi(_argv[i]);
			break;

			case 3:
				gamestate.flags |= GS_STARTLEVEL;
				starting_episode=scan_atoi(_argv[i])-1;
			break;
#endif

			case 4:
				fprint(cinfo_text);

				printf("\n"
						 "     Version: %s\n"
						 "COMPILE DATE: %s\n\n",
						 __VERSION__,GAMEVER_RESTORATION_DATE);
				exit(0);
			break;

			case 5:
				ShowSystem();
				exit(0);
			break;

#if IN_DEVELOPMENT
#ifdef DEBUG_VALUE
			case 6:
				debug_value=scan_atoi(_argv[i]);
			break;
#endif
#endif

			/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_100
			case 7:
				gamestate.flags |= GS_TICS_FOR_SCORE;
			break;

			case 8:
//				gamestate.flags |= GS_MEM_FOR_SCORE;
			break;
#endif

#ifndef GAMEVER_RESTORATION_BS1_100
			case 9:
#ifdef GAMEVER_RESTORATION_AOG_100
				DebugOk = 1;
#else
				PowerBall = 1;
#endif
			break;
#endif

#ifndef GAMEVER_RESTORATION_AOG_100
			case 11:
				gamestate.flags |= GS_STARTLEVEL;
				starting_difficulty=scan_atoi(_argv[i])-1;
			break;
#endif

#ifndef GAMEVER_RESTORATION_BS1_100
			case 10:
				gamestate.flags |= GS_MUSIC_TEST;
			break;
#endif

#ifndef GAMEVER_RESTORATION_AOG_100
			case 12:
				gamestate.flags |= GS_SHOW_OVERHEAD;
			break;
#endif
		}


#if BETA_TEST
	//
	// THIS IS FOR BETA ONLY!
	//

	_dos_getdate(&d);
	if ((d.year > BETA_YEAR) ||
		 ((d.year == BETA_YEAR) && (d.month > BETA_MONTH)) ||
		 ((d.year == BETA_YEAR) && (d.month == BETA_MONTH) && (d.day >= BETA_DAY)))
	{
		FILE *out;
		char name[20]="VSWAP.";

		strcat(name,extension);
		out = fopen(name,"w");
		fprintf(out,"\n\n SELF DESTRUCTED \n");
		fclose(out);
		remove("vswap.bs1");
		fprint(dver_text);
		exit(0);
	}
#endif

	InitGame ();

	/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG
	if (!IsA386)
		Quit(NULL);
#endif

	bufferofs=SCREENSIZE;

	PreDemo();
}


//-------------------------------------------------------------------------
// CheckValidity()
//-------------------------------------------------------------------------
void CheckValidity(char *file, long valid_checksum)
{
	char filename[13];
	long checksum;

	if (strlen(file) > 9)
		MAIN_ERROR(CHECK_FILENAME_TOO_LONG);

	strcpy(filename,file);
	strcat(filename,extension);

	checksum=ChecksumFile(filename,0);
	if (checksum != valid_checksum)
#if GAME_VERSION != SHAREWARE_VERSION
		if (strstr(file,"MAP"))
			InvalidLevels();
#else
			BadChecksum();
#endif
}

#define CFC_BUFFERSIZE 65535

memptr cfc_buffer;

//-------------------------------------------------------------------------
// ChecksumFile()
//-------------------------------------------------------------------------
long ChecksumFile(char *file, long checksum)
{
	#define JUMPSIZE 8

	int handle;
	long size,readlen,i;
	char far *p;

	MM_GetPtr(&cfc_buffer,CFC_BUFFERSIZE);
	p=cfc_buffer;

	if ((handle=open(file,O_RDONLY|O_BINARY)) == -1)
	{
		checksum=0;
		goto exit_func;
	}

	size=filelength(handle);
	while (size)
	{
		if (size >= CFC_BUFFERSIZE)
			readlen = CFC_BUFFERSIZE;
		else
			readlen = size;

		IO_FarRead(handle,cfc_buffer,readlen);

		for (i=0;i<readlen-JUMPSIZE;i += JUMPSIZE)
			checksum += p[i]^p[i+1];

		size -= readlen;
	}

	close(handle);

exit_func:;
	MM_FreePtr(&cfc_buffer);

	return(checksum);
}

#if IN_DEVELOPMENT || GEORGE_CHEAT || SHOW_CHECKSUM


//-------------------------------------------------------------------------
// ShowChecksums()
//-------------------------------------------------------------------------
void ShowChecksums()
{
#if GAME_VERSION == SHAREWARE_VERSION
	char mapname[23]="SWMAPS\\MAPTEMP.";
#elif GAME_VERSION == MISSIONS_1_THR_3
	char mapname[23]="1_3MAPS\\MAPTEMP.";
#else
	char mapname[13]="MAPTEMP.";
#endif
	char gfxname[13]="VGAGRAPH.";
	char audioname[13]="AUDIOT.";
	char dizname[]="FILE_ID.DIZ";

	strcat(gfxname,extension);
	strcat(mapname,extension);
	strcat(audioname,extension);

	printf("\n");
	printf("%s: %lx\n",audioname,ChecksumFile(audioname,0));
	printf("%s: %lx\n",mapname,ChecksumFile(mapname,0));
	printf("%s: %lx\n",gfxname,ChecksumFile(gfxname,0));
	printf("%s: %lx\n",dizname,ChecksumFile(dizname,0));
	printf("\n");
}


#endif

#if GAME_VERSION != SHAREWARE_VERSION

//-------------------------------------------------------------------------
// InvalidLevels()
//-------------------------------------------------------------------------
void InvalidLevels()
{
	char far *chunkptr;

	CA_CacheGrChunk(BADLEVELSTEXT);
	chunkptr = grsegs[BADLEVELSTEXT];
	*(_fstrstr(chunkptr,"^XX"))=0;

	fprint(chunkptr);

	while (!bioskey(1));
	bioskey(0);

	UNCACHEGRCHUNK(BADLEVELSTEXT);
}

#endif

#if GAME_VERSION == SHAREWARE_VERSION

//-------------------------------------------------------------------------
// BadChecksum()
//-------------------------------------------------------------------------
void BadChecksum()
{
	char far *chunkptr;

	CA_CacheGrChunk(BADCHECKSUMTEXT);
	chunkptr = grsegs[BADCHECKSUMTEXT];
	*(_fstrstr(chunkptr,"^XX")) = 0;

	CA_Shutdown();
	MM_Shutdown();

	fprint(chunkptr);

	exit(0);
}

#endif



/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
// Relocated code from 3D_MAIN.C to a separate file, since this is a part of
// JM_FREE.C in AOG v2.1/3.0, rather than 3D_MAIN.C as in PS. Note that
// it is NOT a part of AOG v2.0 anywhere.
// Furthermore, we defined MAX_DEST_PATH_LEN here since it is
// already defined in 3D_MAIN.C earlier as of PS.
#ifdef GAMEVER_RESTORATION_AOG_POST200
#define MAX_DEST_PATH_LEN	30
#include "3D_IDSTP.C"
#endif



#if FREE_FUNCTIONS

// This function is used as a label for the end of the
// functions used by the memory manager.
//
void JM_FREE_END()
{
}

#endif
