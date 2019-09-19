// 3D_MAIN.C

#include "3D_DEF.H"
#pragma hdrstop
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <fcntl.h>
#include <io.h>
#include <dos.h>
#include <sys/stat.h>
#include <time.h>
#include <ctype.h>

#include "jm_io.h"
#include "jm_cio.h"
#include "jm_lzh.h"
#include "jm_error.h"

/*
=============================================================================

											BLAKE STONE
						 (C)opyright 1993, JAM Productions, Inc.

						 3D engine licensed by ID Software, Inc.
					Shareware distribution by Apogee Software, Inc.

=============================================================================
*/

/*
=============================================================================

						 LOCAL CONSTANTS

=============================================================================
*/

#define SKIP_TITLE_AND_CREDITS		(false)


#define FOCALLENGTH     (0x5700l)               // in global coordinates
#define VIEWGLOBAL      0x10000                 // globals visable flush to wall

#define VIEWWIDTH       256                     // size of view window
#define VIEWHEIGHT      144


/*** BLAKE STONE: ALIENS OF GOLD V2.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_PRE210
#define MAX_DEST_PATH_LEN	30
#endif

/*
=============================================================================

						 GLOBAL VARIABLES

=============================================================================
*/

extern int pickquick;


void DrawCreditsPage(void);
void unfreed_main(void);
void ShowPromo(void);

char far * far MainStrs[] = {
/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
// Note that in version 1.00R, powerball was originally replaced with spaces
// (also done for Wolfenstein 3D, albeit via hex-editing)
#ifdef GAMEVER_RESTORATION_BS1_100
										" ", " ", " ", " ",
										"version", "system",
#else
										"q","nowait","l","e",
										"version","system",
#ifdef GAMEVER_RESTORATION_AOG_100
										"dval","tics","mem","         ","music","d",
#else
										"dval","tics","mem","powerball","music","d",
#endif
										"radar",BETA_CODE,
#endif
#ifdef GAMEVER_RESTORATION_AOG_100
										nil,
#endif
										nil
};

/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_100
short starting_episode,starting_level,starting_difficulty;
#endif

/*** BLAKE STONE: ALIENS OF GOLD V2.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_PRE210
char destPath[MAX_DEST_PATH_LEN+1];
char tempPath[MAX_DEST_PATH_LEN+15];
#endif

#if BETA_TEST
char far bc_buffer[]=BETA_CODE;
#endif

void InitPlaytemp(void);


char QuitMsg[] = {"Unit: $%02x Error: $%02x"};

/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
signed char lastmap_tilex,lastmap_tiley;
#endif

#ifdef CEILING_FLOOR_COLORS
unsigned TopColor,BottomColor;
#endif

boolean         nospr;
boolean         IsA386;

int dirangle[9] = {0,ANGLES/8,2*ANGLES/8,3*ANGLES/8,4*ANGLES/8,5*ANGLES/8,6*ANGLES/8,7*ANGLES/8,ANGLES};

//
// proejection variables
//
fixed           focallength;
unsigned        screenofs;
int             viewwidth;
int             viewheight;
int             centerx;
int             shootdelta;                     // pixels away from centerx a target can be
fixed           scale,maxslope;
long            heightnumerator;
int                     minheightdiv;


boolean         startgame,loadedgame;
int             mouseadjustment;

char	configname[13]="CONFIG.";

short view_xl,view_xh,view_yl,view_yh;

#if IN_DEVELOPMENT
unsigned	democount=0,jim=0;
#endif

/*
=============================================================================

						 LOCAL VARIABLES

=============================================================================
*/

#if 0

unsigned mspeed;

void CalcSpeedRating()
{
	short loop;

	for (loop=0; loop<10; loop++)
	{
		ThreeDRefresh();
		mspeed += tics;
	}
}

#endif

/*
====================
=
= WriteConfig
=
====================
*/

void WriteConfig(void)
{
	int                     file;

	/*** BLAKE STONE: ALIENS OF GOLD V2.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_PRE210
	MakeDestPath(configname);
	file = open(tempPath,O_CREAT | O_BINARY | O_WRONLY,
				S_IREAD | S_IWRITE | S_IFREG);
#else
	file = open(configname,O_CREAT | O_BINARY | O_WRONLY,
				S_IREAD | S_IWRITE | S_IFREG);
#endif

	if (file != -1)
	{
		write(file,Scores,sizeof(HighScore) * MaxScores);

		write(file,&SoundMode,sizeof(SoundMode));
		write(file,&MusicMode,sizeof(MusicMode));
		write(file,&DigiMode,sizeof(DigiMode));

		write(file,&mouseenabled,sizeof(mouseenabled));
		write(file,&joystickenabled,sizeof(joystickenabled));
		write(file,&joypadenabled,sizeof(joypadenabled));
		write(file,&joystickprogressive,sizeof(joystickprogressive));
		write(file,&joystickport,sizeof(joystickport));

		write(file,&dirscan,sizeof(dirscan));
		write(file,&buttonscan,sizeof(buttonscan));
		write(file,&buttonmouse,sizeof(buttonmouse));
		write(file,&buttonjoy,sizeof(buttonjoy));

		write(file,&viewsize,sizeof(viewsize));
		write(file,&mouseadjustment,sizeof(mouseadjustment));

		write(file,&gamestate.flags,sizeof(gamestate.flags));		

		close(file);
	}
}


//===========================================================================

/*
=====================
=
= NewGame
=
= Set up new game to start from the beginning
=
=====================
*/

boolean ShowQuickMsg;
void NewGame (int difficulty,int episode)
{
/*** BLAKE STONE: ALIENS OF GOLD V2.1+3.0 RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_POST200
	longword oldf=gamestate.flags;
	unsigned loop;
#else
	unsigned oldf=gamestate.flags,loop;
#endif

	InitPlaytemp();
	playstate = ex_stillplaying;

	ShowQuickMsg=true;
	_fmemset (&gamestuff,0,sizeof(gamestuff));
	memset (&gamestate,0,sizeof(gamestate));

	memset(&gamestate.barrier_table,0xff,sizeof(gamestate.barrier_table));
	memset(&gamestate.old_barrier_table,0xff,sizeof(gamestate.old_barrier_table));
	gamestate.flags = oldf & ~(GS_KILL_INF_WARN);
//	LoadAccessCodes();

	gamestate.difficulty = difficulty;


//
// The following are set to 0 by the memset() to gamestate - Good catch! :JR
//
//	gamestate.rzoom
//	gamestate.rpower
//	gamestate.old_door_bombs
// gamestate.plasma_detonators
//

	gamestate.weapons	 = 1<<wp_autocharge;			// |1<<wp_plasma_detonators;
	gamestate.weapon = gamestate.chosenweapon = wp_autocharge;
	gamestate.old_weapons[0] = gamestate.weapons;
	gamestate.old_weapons[1] = gamestate.weapon;
	gamestate.old_weapons[2] = gamestate.chosenweapon;

	gamestate.health = 100;
	gamestate.old_ammo = gamestate.ammo = STARTAMMO;
//	gamestate.dollars = START_DOLLARS;
//	gamestate.cents   = START_CENTS;
	gamestate.lives = 3;
	gamestate.nextextra = EXTRAPOINTS;
	gamestate.episode=episode;
	gamestate.flags |= (GS_CLIP_WALLS|GS_ATTACK_INFOAREA);	//|GS_DRAW_CEILING|GS_DRAW_FLOOR);

/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#if IN_DEVELOPMENT || TECH_SUPPORT_VERSION || (defined GAMEVER_RESTORATION_AOG_100)
//#if IN_DEVELOPMENT || TECH_SUPPORT_VERSION
	if (gamestate.flags & GS_STARTLEVEL)
	{
		gamestate.mapon = starting_level;
		gamestate.difficulty = starting_difficulty;
		gamestate.episode = starting_episode;
	}
	else
#endif
/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
		gamestate.mapon = 1;
#else
		gamestate.mapon = 0;
#endif

	gamestate.key_floor = gamestate.mapon+1;
	startgame = true;

	/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
	lastmap_tilex = lastmap_tiley = 0xFF;
	gamestuff.old_levelinfo[0].locked = gamestuff.old_levelinfo[1].locked = gamestuff.old_levelinfo[12].locked = gamestuff.old_levelinfo[13].locked = gamestuff.old_levelinfo[14].locked = false;

	gamestuff.old_levelinfo[2].locked = gamestuff.old_levelinfo[3].locked = gamestuff.old_levelinfo[4].locked = gamestuff.old_levelinfo[5].locked = gamestuff.old_levelinfo[6].locked = gamestuff.old_levelinfo[7].locked = gamestuff.old_levelinfo[8].locked = gamestuff.old_levelinfo[9].locked = gamestuff.old_levelinfo[10].locked = gamestuff.old_levelinfo[11].locked = true;

	gamestuff.old_levelinfo[2].stats.overall_floor = gamestuff.old_levelinfo[3].stats.overall_floor = gamestuff.old_levelinfo[4].stats.overall_floor = gamestuff.old_levelinfo[5].stats.overall_floor = gamestuff.old_levelinfo[6].stats.overall_floor = gamestuff.old_levelinfo[7].stats.overall_floor = gamestuff.old_levelinfo[8].stats.overall_floor = gamestuff.old_levelinfo[9].stats.overall_floor = 100;
#else
	for (loop=0; loop<MAPS_WITH_STATS; loop++)
	{
		gamestuff.old_levelinfo[loop].stats.overall_floor=100;
		if (loop)
			gamestuff.old_levelinfo[loop].locked=true;
	}
#endif

	/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_POST100
	normalshade_div = SHADE_DIV;
	shade_max = SHADE_MAX;
#else
//	normalshade_div = SHADE_DIV;
//	shade_max = SHADE_MAX;
#endif
#ifndef GAMEVER_RESTORATION_AOG_100
	ExtraRadarFlags = InstantWin = InstantQuit = 0;
#endif

	pickquick = 0;
}

//===========================================================================

//==========================================================================
//
//             'LOAD/SAVE game' and 'LOAD/SAVE level' code
//
//==========================================================================

boolean LevelInPlaytemp(char levelnum);

#define WriteIt(c,p,s)	cksize+=WriteInfo(c,(char far *)p,s,handle)
#define ReadIt(d,p,s)	ReadInfo(d,(char far *)p,s,handle)

#define LZH_WORK_BUFFER_SIZE	8192		

memptr lzh_work_buffer;
long checksum;

/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
// Unused "clones" of texts from 3D_MENU.C without the carriage-return character
#ifdef GAMEVER_RESTORATION_AOG_100
char far LOADSAVE_MAIN_MSG[2][32]={"^ST1^CELoading Game^XX",
											  "^ST1^CESaving Game^XX"};
#endif


//--------------------------------------------------------------------------
// InitPlaytemp()
//--------------------------------------------------------------------------
void InitPlaytemp()
{
	int handle;
	long size;

	/*** BLAKE STONE: ALIENS OF GOLD V2.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_PRE210
	MakeDestPath(PLAYTEMP_FILE);
	if ((handle=open(tempPath,O_CREAT|O_TRUNC|O_RDWR|O_BINARY,S_IREAD|S_IWRITE))==-1)
		MAIN_ERROR(INITPLAYTEMP_OPEN_ERR);
#else
	if ((handle=open(PLAYTEMP_FILE,O_CREAT|O_TRUNC|O_RDWR|O_BINARY,S_IREAD|S_IWRITE))==-1)
		MAIN_ERROR(INITPLAYTEMP_OPEN_ERR);
#endif

	close(handle);
}

//--------------------------------------------------------------------------
// DoChecksum()
//--------------------------------------------------------------------------
long DoChecksum(byte far *source,unsigned size,long checksum)
{
	unsigned i;

	for (i=0;i<size-1;i++)
		checksum += source[i]^source[i+1];

	return(checksum);
}

//--------------------------------------------------------------------------
// FindChunk()
//--------------------------------------------------------------------------
long FindChunk(int file, char *chunk)
{
	long chunklen;
	char fchunk[5]={0,0,0,0,0};

	while (1)
	{
		if (read(file,fchunk,4)!=4)			// read chunk id
			break;
		read(file,&chunklen,4);					// read chunk length

		if (strstr(fchunk,chunk))				// look for chunk (sub-check!)
			return(chunklen);						// chunk found!

		lseek(file,chunklen,SEEK_CUR);		// skip this chunk
	}

	lseek(file,0,SEEK_END);						// make sure we're at the end
	return(0);
}

/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG
//--------------------------------------------------------------------------
// NextChunk()
//--------------------------------------------------------------------------
long NextChunk(int file)
{
	long chunklen;
	char fchunk[5]={0,0,0,0,0};

	if (read(file,fchunk,4) != 4)			// read chunk id
	{
		lseek(file,0,SEEK_END);				// make sure we're at the end
		return(0);
	}

	read(file,&chunklen,4);					// read chunk length
	return(chunklen);
}
#endif

char LS_current=-1,LS_total=-1;

//--------------------------------------------------------------------------
// ReadInfo()
//--------------------------------------------------------------------------
void ReadInfo(boolean decompress,char far *dst, unsigned size, int file)
{
	unsigned csize,dsize;

	PreloadUpdate(LS_current++,LS_total);

	if (decompress)
	{
		IO_FarRead(file,(char far *)&csize,sizeof(csize));
		IO_FarRead(file,lzh_work_buffer,csize);
		checksum=DoChecksum(lzh_work_buffer,csize,checksum);
		dsize=LZH_Decompress(lzh_work_buffer,dst,size,csize,SRC_MEM|DEST_MEM);
		if (dsize != size)
			MAIN_ERROR(READINFO_BAD_DECOMP);
	}
	else
	{
		IO_FarRead(file,dst,size);
		checksum=DoChecksum(dst,size,checksum);
	}
}

//--------------------------------------------------------------------------
// WriteInfo()
//--------------------------------------------------------------------------
unsigned WriteInfo(boolean compress, char far *src, unsigned size, int file)
{
	unsigned csize;

	PreloadUpdate(LS_current++,LS_total);

	if (compress)
	{
		csize=LZH_Compress(src,lzh_work_buffer,size,SRC_MEM|DEST_MEM);
		if (csize > LZH_WORK_BUFFER_SIZE)
			MAIN_ERROR(WRITEINFO_BIGGER_BUF);
		IO_FarWrite (file,(char far *)&csize,sizeof(csize));
		IO_FarWrite (file,lzh_work_buffer,csize);
		checksum=DoChecksum(lzh_work_buffer,csize,checksum);
		csize += sizeof(csize);
	}
	else
	{
		IO_FarWrite (file,src,size);
		checksum=DoChecksum(src,size,checksum);
		csize=size;
	}

	return(csize);
}



//--------------------------------------------------------------------------
// LoadLevel()
//--------------------------------------------------------------------------
boolean LoadLevel(short levelnum)
{
	extern boolean ShowQuickMsg;
	extern boolean ForceLoadDefault;
	extern unsigned destoff;

	boolean oldloaded=loadedgame;
	long oldchecksum;
	objtype *ob;
	statobj_t *statptr;
	int handle,picnum;
	memptr temp;
	unsigned count;
	char far *ptr;
	char chunk[5]="LVxx";

/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG
extern int nsd_table[];
extern int sm_table[];
#endif

char mod;

	WindowY=181;
/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG
	gamestuff.level[levelnum].locked=false;

	mod = levelnum % 6;
	normalshade_div = nsd_table[mod];
	shade_max = sm_table[mod];
	normalshade=(3*(maxscale>>2))/normalshade_div;
#endif

// Open PLAYTEMP file
//
	/*** BLAKE STONE: ALIENS OF GOLD V2.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_PRE210
	MakeDestPath(PLAYTEMP_FILE);
	handle=open(tempPath,O_RDONLY|O_BINARY);
#else
	handle=open(PLAYTEMP_FILE,O_RDONLY|O_BINARY);
#endif

// If level exists in PLAYTEMP file, use it; otherwise, load it from scratch!
//
	sprintf(&chunk[2],"%02x",levelnum);
	if ((handle==-1) || (!FindChunk(handle,chunk)) || ForceLoadDefault)
	{
		close(handle);

		PreloadUpdate(LS_current+((LS_total-LS_current)>>1),LS_total);
		SetupGameLevel();
/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
		AlignPlayerInElevator();
#endif
		gamestate.flags |= GS_VIRGIN_LEVEL;
		gamestate.turn_around=0;

		PreloadUpdate(1,1);
		ForceLoadDefault=false;
		goto overlay;
	}

	gamestate.flags &= ~GS_VIRGIN_LEVEL;
	/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_100
	FreeScaleDirectory();
#endif

// Setup for LZH decompression
//
	LZH_Startup();
	MM_GetPtr(&lzh_work_buffer,LZH_WORK_BUFFER_SIZE);

// Read all sorts of stuff...
//
	checksum = 0;

	loadedgame=true;
	SetupGameLevel();
	loadedgame=oldloaded;

	ReadIt(true, tilemap, sizeof(tilemap));
	ReadIt(true, actorat, sizeof(actorat));
	ReadIt(true, areaconnect, sizeof(areaconnect));
	ReadIt(true, areabyplayer, sizeof(areabyplayer));

// Restore 'save game' actors
//
	ReadIt(false, &count, sizeof(count));
	MM_GetPtr(&temp,count*sizeof(*ob));
	ReadIt(true, temp, count*sizeof(*ob));
	ptr=temp;

	InitActorList ();							// start with "player" actor
	_fmemcpy(new,ptr,sizeof(*ob)-4);		// don't copy over links!
	ptr += sizeof(*ob);						//

	while (--count)
	{
		GetNewActor();
		_fmemcpy(new,ptr,sizeof(*ob)-4);		// don't copy over links!
		actorat[new->tilex][new->tiley]=new;
#if LOOK_FOR_DEAD_GUYS
		if (new->flags & FL_DEADGUY)
			DeadGuys[NumDeadGuys++]=new;
#endif
		ptr += sizeof(*ob);
	}
	MM_FreePtr(&temp);


   //
	//  Re-Establish links to barrier switches
	//

#pragma warn -pia

	ob = objlist;
	do
	{
		switch (ob->obclass)
		{
			case arc_barrierobj:
			case post_barrierobj:
/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG
         case vspike_barrierobj:
         case vpost_barrierobj:
#endif
				ob->temp2 = ScanBarrierTable(ob->tilex,ob->tiley);
			break;
		}
	} while (ob = ob->next);

#pragma warn +pia

	ConnectBarriers();

// Read all sorts of stuff...
//
	ReadIt(false, &laststatobj, sizeof(laststatobj));
	ReadIt(true, statobjlist, sizeof(statobjlist));
	ReadIt(true, doorposition, sizeof(doorposition));
	ReadIt(true, doorobjlist, sizeof(doorobjlist));
	ReadIt(false, &pwallstate, sizeof(pwallstate));
	ReadIt(false, &pwallx, sizeof(pwallx));
	ReadIt(false, &pwally, sizeof(pwally));
	ReadIt(false, &pwalldir, sizeof(pwalldir));
	ReadIt(false, &pwallpos, sizeof(pwallpos));
	ReadIt(false, &pwalldist, sizeof(pwalldist));
	ReadIt(true, TravelTable, sizeof(TravelTable));
	ReadIt(true, &ConHintList, sizeof(ConHintList));
	ReadIt(true, eaList, sizeof(eaWallInfo)*MAXEAWALLS);
	ReadIt(true, &GoldsternInfo, sizeof(GoldsternInfo));
   ReadIt(true, &GoldieList,sizeof(GoldieList));			
/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_POST100
	ReadIt(true, &gamestate.secrettotal, sizeof(gamestate.secrettotal));
#elif (defined GAMEVER_RESTORATION_VSI)
	ReadIt(false, gamestate.barrier_table,sizeof(gamestate.barrier_table));
	ReadIt(false, &gamestate.plasma_detonators,sizeof(gamestate.plasma_detonators));
#endif

// Read and evaluate checksum
//
	PreloadUpdate(LS_current++,LS_total);
	IO_FarRead (handle,(void far *)&oldchecksum,sizeof(oldchecksum));

	if (oldchecksum != checksum)
	{
		int old_wx=WindowX,old_wy=WindowY,old_ww=WindowW,old_wh=WindowH,
			 old_px=px,old_py=py;

		WindowX=0; WindowY=16; WindowW=320; WindowH=168;
		CacheMessage(BADINFO_TEXT);
		WindowX=old_wx; WindowY=old_wy; WindowW=old_ww; WindowH=old_wh;
		px=old_px; py=old_py;

		IN_ClearKeysDown();
		IN_Ack();

		gamestate.score = 0;
		gamestate.nextextra = EXTRAPOINTS;
		gamestate.lives = 1;

		gamestate.weapon = gamestate.chosenweapon = wp_autocharge;
		gamestate.weapons = 1<<wp_autocharge;		// |1<<wp_plasma_detonators;

		gamestate.ammo = 8;
	}

	close(handle);

// Clean-up LZH compression
//
	MM_FreePtr(&lzh_work_buffer);
	LZH_Shutdown();
	NewViewSize(viewsize);

/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
	if (playstate == ex_transported)
		AlignPlayerOnTransporter();
	else
		AlignPlayerInElevator();
#endif

// Check for Strange Door and Actor combos
//
/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_100
	CleanUpDoors_N_Actors();
#endif


overlay:;

	return(true);
}

//--------------------------------------------------------------------------
// SaveLevel()
//--------------------------------------------------------------------------
boolean SaveLevel(short levelnum)
{
	objtype *ob;
	int handle;
	struct ffblk finfo;
	/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
	// DeleteChunk stuff
#ifdef GAMEVER_RESTORATION_AOG
	long filesize;
#endif
	long offset,cksize;
	char chunk[5]="LVxx";
	unsigned gflags = gamestate.flags;
	boolean rt_value=false;
	memptr temp;
	unsigned count;
	char far *ptr;
	char oldmapon;
	/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
	// DeleteChunk stuff
#ifdef GAMEVER_RESTORATION_AOG
	long bmove;
	int dhandle;
#endif

	WindowY=181;

// Make sure floor stats are saved!
//
	oldmapon=gamestate.mapon;
	gamestate.mapon=gamestate.lastmapon;
	/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
	ShowStats(0,0,ss_justcalc);
#else
	ShowStats(0,0,ss_justcalc,&gamestuff.level[gamestate.mapon].stats);
#endif
	gamestate.mapon=oldmapon;

	/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_100
	FreeScaleDirectory();
#endif
// Yeah! We're no longer a virgin!
//
	gamestate.flags &= ~GS_VIRGIN_LEVEL;

// Open PLAYTEMP file
//
	/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
#ifndef GAMEVER_RESTORATION_AOG_PRE210
	MakeDestPath(PLAYTEMP_FILE);
	if (findfirst(tempPath,&finfo,0))
#else
	if (findfirst(PLAYTEMP_FILE,&finfo,0))
#endif
		filesize = 0;
	else
		filesize = finfo.ff_fsize;
#endif
#ifndef GAMEVER_RESTORATION_AOG_PRE210
	MakeDestPath(PLAYTEMP_FILE);
	if ((handle=open(tempPath,O_CREAT|O_RDWR|O_BINARY,S_IREAD|S_IWRITE))==-1)
#else
	if ((handle=open(PLAYTEMP_FILE,O_CREAT|O_RDWR|O_BINARY,S_IREAD|S_IWRITE))==-1)
#endif
		MAIN_ERROR(SAVELEVEL_DISKERR);

// Remove level chunk from file
//
	sprintf(&chunk[2],"%02x",levelnum);
	/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
	// Apparently DeleteChunk was originally "inlined" in some AOG EXE
#ifdef GAMEVER_RESTORATION_AOG
	if (cksize=FindChunk(handle,chunk))
	{
		/** (RESTORATION) Copy-and-pasted from DeleteChunk (for most) **/

		offset=lseek(handle,0,SEEK_CUR)-8; 		// move back to CKID/SIZE
		bmove=filesize-(offset+8+cksize);	 	// figure bytes to move

		if (bmove)										// any data to move?
		{
		// Move data: FROM --> the start of NEXT chunk through the end of file.
		//              TO --> the start of THIS chunk.
		//
		// (ie: erase THIS chunk and re-write it at the end of the file!)
		//
			lseek(handle,cksize,SEEK_CUR);			// seek source to NEXT chunk

			/*** BLAKE STONE: ALIENS OF GOLD V2.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_PRE210
			MakeDestPath(PLAYTEMP_FILE);
			if ((dhandle=open(tempPath,O_CREAT|O_RDWR|O_BINARY,S_IREAD|S_IWRITE))==-1)
#else
			if ((dhandle=open(PLAYTEMP_FILE,O_CREAT|O_RDWR|O_BINARY,S_IREAD|S_IWRITE))==-1)
#endif
				MAIN_ERROR(SAVELEVEL_DISKERR);

			lseek(dhandle,offset,SEEK_SET);  		// seek dest to THIS chunk
			IO_CopyHandle(handle,dhandle,bmove);	// copy "bmove" bytes

			close(dhandle);

			lseek(handle,offset+bmove,SEEK_SET);	// go to end of data moved
		}
		else
			lseek(handle,offset,SEEK_SET);
	}
#else
	DeleteChunk(handle,chunk);
#endif

// Setup LZH compression
//
	LZH_Startup();
	MM_GetPtr(&lzh_work_buffer,LZH_WORK_BUFFER_SIZE);

// Write level chunk id
//
	write(handle,chunk,4);
	lseek(handle,4,SEEK_CUR);		// leave four bytes for chunk size

// Write all sorts of info...
//
	checksum = cksize = 0;
	WriteIt(true, tilemap, sizeof(tilemap));
	WriteIt(true, actorat, sizeof(actorat));
	WriteIt(true, areaconnect, sizeof(areaconnect));
	WriteIt(true, areabyplayer, sizeof(areabyplayer));

// Write actor list...
//
	MM_GetPtr(&temp,sizeof(objlist));
	for (ob=player,count=0,ptr=temp; ob; ob=ob->next,count++,ptr+=sizeof(*ob))
		_fmemcpy(ptr,ob,sizeof(*ob));
	WriteIt(false, &count, sizeof(count));
	WriteIt(true, temp, count*sizeof(*ob));
	MM_FreePtr(&temp);

// Write all sorts of info...
//
	WriteIt(false, &laststatobj, sizeof(laststatobj));
	WriteIt(true, statobjlist, sizeof(statobjlist));
	WriteIt(true, doorposition, sizeof(doorposition));
	WriteIt(true, doorobjlist, sizeof(doorobjlist));
	WriteIt(false, &pwallstate, sizeof(pwallstate));
	WriteIt(false, &pwallx, sizeof(pwallx));
	WriteIt(false, &pwally, sizeof(pwally));
	WriteIt(false, &pwalldir, sizeof(pwalldir));
	WriteIt(false, &pwallpos, sizeof(pwallpos));
	WriteIt(false, &pwalldist, sizeof(pwalldist));
	WriteIt(true, TravelTable, sizeof(TravelTable));
	WriteIt(true, &ConHintList, sizeof(ConHintList));
	WriteIt(true, eaList, sizeof(eaWallInfo)*MAXEAWALLS);
	WriteIt(true, &GoldsternInfo, sizeof(GoldsternInfo));
	WriteIt(true, &GoldieList,sizeof(GoldieList));
/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_POST100
	WriteIt(true, &gamestate.secrettotal, sizeof(gamestate.secrettotal));
#elif (defined GAMEVER_RESTORATION_VSI)
	WriteIt(false, gamestate.barrier_table,sizeof(gamestate.barrier_table));
	WriteIt(false, &gamestate.plasma_detonators,sizeof(gamestate.plasma_detonators));
#endif

// Write checksum and determine size of file
//
	WriteIt(false, &checksum, sizeof(checksum));
	offset=tell(handle);

// Write chunk size, set file size, and close file
//
	lseek(handle,-(cksize+4),SEEK_CUR);
	write(handle,&cksize,4);

	chsize(handle,offset);
	close(handle);
	rt_value=true;

// Clean-up LZH compression
//
exit_func:;
	MM_FreePtr(&lzh_work_buffer);
	LZH_Shutdown();
	NewViewSize(viewsize);
	gamestate.flags = gflags;

	return(rt_value);
}

/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG
#pragma warn -pia

//--------------------------------------------------------------------------
// DeleteChunk()
//--------------------------------------------------------------------------
long DeleteChunk(int handle, char *chunk)
{
	long filesize,cksize,offset,bmove;
	int dhandle;

	lseek(handle,0,SEEK_SET);
	filesize=lseek(handle,0,SEEK_END);
	lseek(handle,0,SEEK_SET);

	if (cksize=FindChunk(handle,chunk))
	{
		offset=lseek(handle,0,SEEK_CUR)-8; 		// move back to CKID/SIZE
		bmove=filesize-(offset+8+cksize);	 	// figure bytes to move

		if (bmove)										// any data to move?
		{
		// Move data: FROM --> the start of NEXT chunk through the end of file.
		//              TO --> the start of THIS chunk.
		//
		// (ie: erase THIS chunk and re-write it at the end of the file!)
		//
			lseek(handle,cksize,SEEK_CUR);			// seek source to NEXT chunk

			MakeDestPath(PLAYTEMP_FILE);
			if ((dhandle=open(tempPath,O_CREAT|O_RDWR|O_BINARY,S_IREAD|S_IWRITE))==-1)
				MAIN_ERROR(SAVELEVEL_DISKERR);

			lseek(dhandle,offset,SEEK_SET);  		// seek dest to THIS chunk
			IO_CopyHandle(handle,dhandle,bmove);	// copy "bmove" bytes

			close(dhandle);

			lseek(handle,offset+bmove,SEEK_SET);	// go to end of data moved
		}
		else
			lseek(handle,offset,SEEK_SET);
	}

	return(cksize);
}

#pragma warn +pia
#endif // GAMEVER RESTORATION



char far SavegameInfoText[]="\n\r"
									 "\n\r"
									 "-------------------------------------\n\r"
									 "    Blake Stone: Aliens Of Gold\n\r"
									 "Copyright 1993, JAM Productions, Inc.\n\r"
									 "\n\r"
									 "SAVEGAME file is from version: "__VERSION__"\n\r"
									 " Compile Date :"GAMEVER_RESTORATION_DATE" : "GAMEVER_RESTORATION_TIME"\n\r"
									 "-------------------------------------\n\r"
									 "\x1a";


//--------------------------------------------------------------------------
// LoadTheGame()
//--------------------------------------------------------------------------
boolean LoadTheGame(int handle)
{
	extern int lastmenumusic;

	int shandle;
	long cksize;
	memptr temp=NULL;
	boolean rt_value=false;
   char InfoSpace[400];
   memptr tempspace;

	/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_100
	FreeScaleDirectory();
#endif
// Setup LZH decompression
//
	LZH_Startup();
	MM_GetPtr(&lzh_work_buffer,LZH_WORK_BUFFER_SIZE);


	/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_100
// Read in VERSion chunk
//
	/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
	if (!FindChunk(handle,"INFO"))
#else
	if (!FindChunk(handle,"VERS"))
#endif
		goto cleanup;

	cksize = sizeof(SavegameInfoText);
	read(handle, InfoSpace, cksize);
	if (_fmemcmp(InfoSpace, SavegameInfoText, cksize))
   {
		// Old Version of game

		int old_wx=WindowX,old_wy=WindowY,old_ww=WindowW,old_wh=WindowH,
			 old_px=px,old_py=py;

		WindowX=0; WindowY=16; WindowW=320; WindowH=168;
		CacheMessage(BADSAVEGAME_TEXT);
		SD_PlaySound (NOWAYSND);
		WindowX=old_wx; WindowY=old_wy; WindowW=old_ww; WindowH=old_wh;
		px=old_px; py=old_py;

	  	IN_ClearKeysDown();
	  	IN_Ack();

      VW_FadeOut();
      screenfaded = true;

     	goto cleanup;
	}
#endif

// Read in HEAD chunk
//
	if (!FindChunk(handle,"HEAD"))
		goto cleanup;

	ReadIt(true, &gamestate, sizeof(gamestate));
	ReadIt(true, &gamestuff, sizeof(gamestuff));

// Reinitialize page manager
//
#if DUAL_SWAP_FILES
	PM_Shutdown();
	PM_Startup ();
	PM_UnlockMainMem();
#endif


// Start music for the starting level in this loaded game.
//

	FreeMusic();
	StartMusic(false);

// Copy all remaining chunks to PLAYTEMP file
//
	/*** BLAKE STONE: ALIENS OF GOLD V2.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_PRE210
	MakeDestPath(PLAYTEMP_FILE);
	if ((shandle=open(tempPath,O_CREAT|O_RDWR|O_TRUNC|O_BINARY,S_IREAD|S_IWRITE))==-1)
#else
	if ((shandle=open(PLAYTEMP_FILE,O_CREAT|O_RDWR|O_TRUNC|O_BINARY,S_IREAD|S_IWRITE))==-1)
#endif
		goto cleanup;

#pragma warn -pia
/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
	while (cksize=FindChunk(handle,"LV"))
#else
	while (cksize=NextChunk(handle))
#endif
	{
		cksize += 8;								// include chunk ID and LENGTH
		lseek(handle,-8,SEEK_CUR);				// seek to start of chunk
		MM_GetPtr(&temp,cksize);				// alloc temp buffer
		IO_FarRead(handle,temp,cksize);		// read chunk from SAVEGAME file
		IO_FarWrite(shandle,temp,cksize);	// write chunk to PLAYTEMP file
		MM_FreePtr(&temp);						// free temp buffer
	}
#pragma warn +pia

	close(shandle);
	rt_value=true;

// Clean-up LZH decompression
//
cleanup:;
	MM_FreePtr(&lzh_work_buffer);
	LZH_Shutdown();
	NewViewSize(viewsize);

// Load current level
//
	if (rt_value)
	{
/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
		lastmap_tilex = lastmap_tiley = 0xFF;
#endif
		LoadLevel(0xff);
		ShowQuickMsg=false;
	}

	return(rt_value);
}


//--------------------------------------------------------------------------
// SaveTheGame()
//--------------------------------------------------------------------------
boolean SaveTheGame(int handle, char far *description)
{
	struct ffblk finfo;
	unsigned long cksize,offset;
	int shandle;
	memptr temp;
	char nbuff[GAME_DESCRIPTION_LEN+1];
	boolean rt_value=false,exists;

//
// Save PLAYTEMP becuase we'll want to restore it to the way it was
// before the save.
//
//	IO_CopyFile(PLAYTEMP_FILE,OLD_PLAYTEMP_FILE);
//

// Save current level -- saves it into PLAYTEMP.
//
	SaveLevel(0xff);

	/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_100
	FreeScaleDirectory();
#endif
// Setup LZH compression
//
	LZH_Startup();
	MM_GetPtr(&lzh_work_buffer,LZH_WORK_BUFFER_SIZE);

// Write VERSion chunk
//
	cksize=sizeof(SavegameInfoText);
	/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
	write(handle,"INFO",4);
#else
	write(handle,"VERS",4);
#endif
	write(handle,&cksize,4);
	IO_FarWrite(handle,SavegameInfoText,cksize);

// Write DESC chunk
//
	_fmemcpy(nbuff,description,sizeof(nbuff));
	cksize=strlen(nbuff)+1;
	write(handle,"DESC",4);
	write(handle,&cksize,4);
	write(handle,nbuff,cksize);

// Write HEAD chunk
//
	cksize=0;
	write(handle,"HEAD",4);
	lseek(handle,4,SEEK_CUR);		// leave four bytes for chunk size

	WriteIt(true, &gamestate, sizeof(gamestate));
	WriteIt(true, &gamestuff, sizeof(gamestuff));

	lseek(handle,-(cksize+4),SEEK_CUR);
	write(handle,&cksize,4);
	lseek(handle,cksize,SEEK_CUR);

// Append PLAYTEMP file to savegame file
//
	/*** BLAKE STONE: ALIENS OF GOLD V2.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_PRE210
	MakeDestPath(PLAYTEMP_FILE);
	if (findfirst(tempPath,&finfo,0))
#else
	if (findfirst(PLAYTEMP_FILE,&finfo,0))
#endif
		goto cleanup;
	/*** BLAKE STONE: ALIENS OF GOLD V2.1+3.0 RESTORATION ***/
#if (defined GAMEVER_RESTORATION_AOG) && (!defined GAMEVER_RESTORATION_AOG_PRE210)
	MakeDestPath(PLAYTEMP_FILE);
#endif

	/*** BLAKE STONE: ALIENS OF GOLD V2.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_PRE210
	if ((shandle=open(tempPath,O_RDONLY|O_BINARY))==-1)
#else
	if ((shandle=open(PLAYTEMP_FILE,O_RDONLY|O_BINARY))==-1)
#endif
		goto cleanup;

	IO_CopyHandle(shandle,handle,-1);

	close(shandle);
	rt_value=true;

// Clean-up LZH compression
//
cleanup:;
	MM_FreePtr(&lzh_work_buffer);
	LZH_Shutdown();
	NewViewSize(viewsize);

//
// Return PLAYTEMP to original state!
//
//	remove(PLAYTEMP_FILE);
//	rename(OLD_PLAYTEMP_FILE,PLAYTEMP_FILE);
//

	return(rt_value);
}

//--------------------------------------------------------------------------
// LevelInPlaytemp()
//--------------------------------------------------------------------------
boolean LevelInPlaytemp(char levelnum)
{
	int handle;
	char chunk[5]="LVxx";
	boolean rt_value;

// Open PLAYTEMP file
//
	/*** BLAKE STONE: ALIENS OF GOLD V2.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_PRE210
	MakeDestPath(PLAYTEMP_FILE);
	handle=open(tempPath,O_RDONLY|O_BINARY);
#else
	handle=open(PLAYTEMP_FILE,O_RDONLY|O_BINARY);
#endif

// See if level exists in PLAYTEMP file...
//
	sprintf(&chunk[2],"%02x",levelnum);
	rt_value=FindChunk(handle,chunk);

// Close PLAYTEMP file
//
	close(handle);

	return(rt_value);
}

//--------------------------------------------------------------------------
// CheckDiskSpace()
//--------------------------------------------------------------------------
boolean CheckDiskSpace(long needed,char far *text,cds_io_type io_type)
{
	struct ffblk finfo;
	struct diskfree_t dfree;
	long avail;

// Figure amount of space free on hard disk and let the gamer know if
// disk space is too low.
//
	if (_dos_getdiskfree(0,&dfree))
		MAIN_ERROR(CHECKDISK_GDFREE);

	avail = (long)dfree.avail_clusters *
					  dfree.bytes_per_sector *
					  dfree.sectors_per_cluster;

	if (avail < needed)
	{
		unsigned old_DS=_DS;

		switch (io_type)
		{
			case cds_dos_print:
				_DS=FP_SEG(text);
				printf("%s",text);
				_DS=old_DS;
				exit(0);
			break;

			case cds_menu_print:
			case cds_id_print:
				WindowX=0; WindowY=16; WindowW=320; WindowH=168;
				SD_PlaySound (NOWAYSND);
				Message(text);
				IN_ClearKeysDown();
				IN_Ack();
				if (io_type==cds_menu_print)
					MenuFadeOut();
			break;
		}

		return(false);
	}

	return(true);
}



/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_100
//--------------------------------------------------------------------------
// CleanUpDoors_N_Actors()
//--------------------------------------------------------------------------
void CleanUpDoors_N_Actors(void)
{
	char x,y;
   objtype *obj;
   objtype **actor_ptr;
   byte *tile_ptr;
	unsigned door;

   actor_ptr = (objtype **)actorat;
	tile_ptr = (byte *)tilemap;

   for (y=0;y<mapheight;y++)
	   for (x=0;x<mapwidth;x++)
      {
      	if (*tile_ptr & 0x80)
         {
         	// Found a door
            //

            obj = *actor_ptr;
            if ((obj >= objlist) && (obj < &objlist[MAXACTORS]))
            {
             	// Found an actor

            	// Determine door number...

	         	door = *tile_ptr & 0x3F;

			/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
					if (obj->flags & FL_SOLID)
#else
					if ((obj->flags & (FL_SOLID|FL_DEADGUY)) == (FL_SOLID|FL_DEADGUY))
#endif
   	         	obj->flags &= ~(FL_SHOOTABLE | FL_SOLID | FL_FAKE_STATIC);

					// Make sure door is open

					doorobjlist[door].ticcount = 0;
					doorobjlist[door].action = dr_open;
					doorposition[door] = 0xffff;
            }
         }

         tile_ptr++;
      	actor_ptr++;
      }
}
#endif

/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
void AlignPlayerOnTransporter(void)
{
	player->tilex = playerwarp.tilex;
	player->tiley = playerwarp.tiley;
	player->x = ((fixed)player->tilex<<TILESHIFT) + 0x8000;
	player->y = ((fixed)player->tiley<<TILESHIFT) + 0x8000;
	player->dir = playerwarp.dir;
	player->angle = playerwarp.dir*45;
}

void AlignPlayerInElevator(void)
{
	char tilex = 0;
	word origtilex, origtiley;
	if ((lastmap_tilex == -1) || (lastmap_tiley == -1) || (playstate == ex_transported))
		return;

	origtilex = lastmap_tilex;
	origtiley = lastmap_tiley;
	if ((tilemap[origtilex+1][origtiley]&63)!=21 && (tilemap[origtilex-1][origtiley]&63)!=21)
	{
		if ((tilemap[origtilex-2][origtiley]&63)!=21)
		{
			for (tilex=origtilex-1; tilex; tilex--)
			{
				if ((tilemap[tilex][origtiley]&63)!=21)
					continue;
				if (((tilemap[tilex-1][origtiley-1]&63)==21) || ((tilemap[tilex-1][origtiley+1]&63)==21))
					tilex--;
				else
					tilex++;
				break;
			}
		}
		if (((tilemap[origtilex+2][origtiley]&63)!=21) && (!tilex))
		{
			for (tilex=origtilex+1; tilex<MAPSIZE; tilex++)
			{
				if ((tilemap[tilex][origtiley]&63)!=21)
					continue;
				if (((tilemap[tilex+1][origtiley-1]&63)==21) || ((tilemap[tilex+1][origtiley+1]&63)==21))
					tilex++;
				else
					tilex--;
				break;
			}
		}
	}
	if (!tilex)
		tilex = lastmap_tilex;
	if (tilex < MAPSIZE)
	{
		if (tilemap[tilex+1][origtiley+1] & 0x80)
		{
			origtiley++;
			tilex--;
			player->dir = northeast;
		}
		else if (tilemap[tilex+1][origtiley-1] & 0x80)
		{
			origtiley--;
			tilex--;
			player->dir = northeast;
		}
		else if (tilemap[tilex-1][origtiley+1] & 0x80)
		{
			origtiley++;
			tilex++;
			player->dir = northwest;
		}
		else if (tilemap[tilex-1][origtiley-1] & 0x80)
		{
			origtiley--;
			tilex++;
			player->dir = northwest;
		}
	}
	else
		tilex = origtilex;

	player->x = ((fixed)tilex<<TILESHIFT)+0x8000;
	player->y = ((fixed)origtiley<<TILESHIFT)+0x8000;
	player->angle = (1-player->dir)*90;
	if (player->angle < 0)
		player->angle += 360;
	lastmap_tilex = lastmap_tiley = 0xFF;
}
#endif


//--------------------------------------------------------------------------
// ClearNClose() - Use when changing levels via standard elevator.
//
//               - This code doesn't CLEAR the elevator door as originally
//                 planned because, actors were coded to stay out of the
//                 elevator doorway.
//
//--------------------------------------------------------------------------
void ClearNClose()
{
	char x,y,tx=0,ty=0,px=player->x>>TILESHIFT,py=player->y>>TILESHIFT;

	// Locate the door.
	//
	for (x=-1; x<2 && !tx; x+=2)
		for (y=-1; y<2; y+=2)
			if (tilemap[px+x][py+y] & 0x80)
			{
				tx=px+x;
				ty=py+y;
				break;
			}

	// Close the door!
	//
	if (tx)
	{
		char doornum=tilemap[tx][ty]&63;

		doorobjlist[doornum].action = dr_closed;		// this door is closed!
		doorposition[doornum]=0;							// draw it closed!
		(unsigned)actorat[tx][ty] = doornum | 0x80;	// make it solid!
	}
}

//--------------------------------------------------------------------------
// CycleColors()
//--------------------------------------------------------------------------
void CycleColors()
{
	#define NUM_RANGES 	5
	#define CRNG_LOW		0xf0
	#define CRNG_HIGH		0xfe
	#define CRNG_SIZE		(CRNG_HIGH-CRNG_LOW+1)

	static CycleInfo crng[NUM_RANGES] = {{7,0,0xf0,0xf1},
													 {15,0,0xf2,0xf3},
													 {30,0,0xf4,0xf5},
													 {10,0,0xf6,0xf9},
													 {12,0,0xfa,0xfe},
													};

	byte loop,cbuffer[CRNG_SIZE][3];
	boolean changes=false;

	for (loop=0; loop<NUM_RANGES; loop++)
	{
		CycleInfo *c=&crng[loop];

		if (tics >= c->delay_count)
		{
			byte temp[3],first,last,numregs;

			if (!changes)
			{
				VL_GetPalette(CRNG_LOW,CRNG_SIZE,(byte far *)cbuffer);
				changes=true;
			}

			first = c->firstreg-CRNG_LOW;
			numregs = c->lastreg-c->firstreg;	// is one less than in range
			last = first+numregs;

			memcpy(temp,cbuffer[last],3);
			memmove(cbuffer[first+1],cbuffer[first],numregs*3);
			memcpy(cbuffer[first],temp,3);

			c->delay_count = c->init_delay;
		}
		else
			c->delay_count -= tics;
	}

	if (changes)
		VL_SetPalette(CRNG_LOW,CRNG_SIZE,(byte far *)cbuffer);
	else
		VW_WaitVBL(1);
}


//===========================================================================

/*
==========================
=
= ShutdownId
=
= Shuts down all ID_?? managers
=
==========================
*/

void ShutdownId (void)
{
	US_Shutdown ();
	SD_Shutdown ();
	PM_Shutdown ();
	IN_Shutdown ();
	VW_Shutdown ();
	CA_Shutdown ();
	MM_Shutdown ();
}


//===========================================================================


/*
====================
=
= CalcProjection
=
= Uses focallength
=
====================
*/

void CalcProjection (long focal)
{
	int             i;
	long            intang;
	float   angle;
	double  tang;
	double  planedist;
	double  globinhalf;
	int             halfview;
	double  halfangle,facedist;


	focallength = focal;
	facedist = focal+MINDIST;
	halfview = viewwidth/2;                                 // half view in pixels

//
// calculate scale value for vertical height calculations
// and sprite x calculations
//
	scale = halfview*facedist/(VIEWGLOBAL/2);

//
// divide heightnumerator by a posts distance to get the posts height for
// the heightbuffer.  The pixel height is height>>2
//
	heightnumerator = (TILEGLOBAL*scale)>>6;
	minheightdiv = heightnumerator/0x7fff +1;

//
// calculate the angle offset from view angle of each pixel's ray
//

	for (i=0;i<halfview;i++)
	{
	// start 1/2 pixel over, so viewangle bisects two middle pixels
		tang = (long)i*VIEWGLOBAL/viewwidth/facedist;
		angle = atan(tang);
		intang = angle*radtoint;
		pixelangle[halfview-1-i] = intang;
		pixelangle[halfview+i] = -intang;
	}

//
// if a point's abs(y/x) is greater than maxslope, the point is outside
// the view area
//
	maxslope = finetangent[pixelangle[0]];
	maxslope >>= 8;
}



//===========================================================================

//--------------------------------------------------------------------------
// DoMovie()
//--------------------------------------------------------------------------
/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
boolean DoMovie(movie_t movie)
#else
boolean DoMovie(movie_t movie, memptr palette)
#endif
{
	boolean  ReturnVal;
//	StopMusic();
	SD_StopSound();

	ClearMemory();
	UnCacheLump(STARTFONT,STARTFONT+NUMFONT);
	CA_LoadAllSounds();

	/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG
   if (palette)
   	Movies[movie].palette = palette;
   else
   	Movies[movie].palette = (memptr)FP_SEG(&vgapal);
#endif

	ReturnVal = MOVIE_Play(&Movies[movie]);

	SD_StopSound();
	ClearMemory();
	LoadFonts();

	return(ReturnVal);
}

//===========================================================================

/*
=================
=
= MS_CheckParm
=
=================
*/

boolean MS_CheckParm (char far *check)
{
	int             i;
	char    *parm;

	for (i = 1;i<_argc;i++)
	{
		parm = _argv[i];

		while ( !isalpha(*parm) )       // skip - / \ etc.. in front of parm
			if (!*parm++)
				break;                          // hit end of string without an alphanum

		if ( !_fstricmp(check,parm) )
			return true;
	}

	return false;
}

//===========================================================================

//--------------------------------------------------------------------------
// LoadFonts()
//--------------------------------------------------------------------------
void LoadFonts(void)
{
	CA_CacheGrChunk(STARTFONT+4);
	MM_SetLock (&grsegs[STARTFONT+4],true);

	CA_CacheGrChunk(STARTFONT+2);
	MM_SetLock (&grsegs[STARTFONT+2],true);
}

//===========================================================================

/*
==========================
=
= SetViewSize
=
==========================
*/

boolean SetViewSize (unsigned width, unsigned height)
{
	viewwidth = width&~15;                  // must be divisable by 16
	viewheight = height&~1;                 // must be even
	centerx = viewwidth/2-1;
	shootdelta = viewwidth/10;
	screenofs = ((200-STATUSLINES-viewheight+TOP_STRIP_HEIGHT)/2*SCREENWIDTH+(320-viewwidth)/8);

//
// calculate trace angles and projection constants
//
	CalcProjection (FOCALLENGTH);

//
// build all needed compiled scalers
//
	SetupScaling (viewwidth*1.5);

	view_xl=0;
	view_xh=view_xl+viewwidth-1;
	view_yl=0;
	view_yh=view_yl+viewheight-1;

	return true;
}


void ShowViewSize (int width)
{
	int     oldwidth,oldheight;

	oldwidth = viewwidth;
	oldheight = viewheight;

	viewwidth = width*16;
	viewheight = width*16*HEIGHTRATIO;
	/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
	// Uncomment bottom code line for v1.0
#ifndef GAMEVER_RESTORATION_AOG_100
	VWB_Bar (0,TOP_STRIP_HEIGHT,320,200-STATUSLINES-TOP_STRIP_HEIGHT,BORDER_MED_COLOR);
#else
	VWB_Bar (0,0,320,200-STATUSLINES,BORDER_MED_COLOR);
#endif
	DrawPlayBorder ();

	viewheight = oldheight;
	viewwidth = oldwidth;
}


void NewViewSize (int width)
{
	CA_UpLevel ();
	MM_SortMem ();
	viewsize = width;
	while (1)
	{
		if (SetViewSize (width*16,width*16*HEIGHTRATIO))
			break;
		width--;
	};
	CA_DownLevel ();
}


//===========================================================================

/*
==========================
=
= Quit
=
==========================
*/


void Quit (char *error,...)
{
	unsigned        finscreen;
	memptr			diz;
	char far *screen;
	unsigned unit,err;
	va_list ap;

	va_start(ap,error);

	/*** BLAKE STONE: ALIENS OF GOLD V2.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_PRE210
	MakeDestPath(PLAYTEMP_FILE);
	remove(tempPath);
#else
	remove(PLAYTEMP_FILE);
#endif
	ClearMemory ();

	if (!*error)
	{
#if GAME_VERSION != SHAREWARE_VERSION
		if (gamestate.flags & GS_BAD_DIZ_FILE)
		{
			char far *end;

			CA_CacheGrChunk(DIZ_ERR_TEXT);
			diz = grsegs[DIZ_ERR_TEXT];
			end=_fstrstr(diz,"^XX");
			*end=0;
		}
		/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG
		else
		if (!IsA386)
		{
			CA_CacheGrChunk (NO386SCREEN);
			screen = MK_FP(grsegs[NO386SCREEN],7);
		}
#else
		else
#endif
#endif

		/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
		{
			CA_CacheGrChunk (ORDERSCREEN);
			finscreen = grsegs[ORDERSCREEN];
		}
#endif
	}
	else
	{
		CA_CacheGrChunk (ERRORSCREEN);
		/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
		finscreen = grsegs[ERRORSCREEN];
#else
		screen = MK_FP(grsegs[ERRORSCREEN],7);
#endif
	}

	WriteConfig ();
	ShutdownId ();

	if (error && *error)
	{
		FILE *fp;

		unit=va_arg(ap,unsigned);
		err=va_arg(ap,unsigned);
		/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
		movedata (finscreen,7,0xb800,0,7*160);
#else
		_fmemcpy(MK_FP(0xB800,0), screen, 7*160);
#endif

		textcolor(14);
		textbackground(4);
		gotoxy (10,4);
		cprintf(error,unit,err);

		/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_POST100
		gotoxy (64-strlen(__VERSION__),2);
		cprintf(" Ver :%s ",__VERSION__);
#elif (defined GAMEVER_RESTORATION_VSI)
		gotoxy (65-strlen(__VERSION__),2);
		cprintf(" Ver:%s ",__VERSION__);
#endif

		gotoxy (1,8);

		/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_PRE210
#ifdef GAMEVER_RESTORATION_AOG
		MakeDestPath("BS_AOG.ERR");
#else
		MakeDestPath("BS_VSI.ERR");
#endif
		fp = fopen(tempPath,"wb");
#else
		fp = fopen("BS_AOG.ERR","wb");
#endif
		fprintf(fp,"$%02x%02x",unit,err);
		if (fp)
			fclose(fp);

		exit(1);
	}

		/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
//#if 0
	if (!error || !(*error))
	{
		unsigned far *clear = MK_FP(0xb800,23*80*2);
		unsigned len = 0;

		clrscr();
#if GAME_VERSION != SHAREWARE_VERSION
		if (gamestate.flags & GS_BAD_DIZ_FILE)
			fprint(diz);
		else
#endif
		{
			/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
			movedata (finscreen,0,0xb800,0,4000);
#else
//			movedata ((unsigned)screen,0,0xb800,0,4000);
			_fmemcpy(MK_FP(0xB800,0),screen,4000);
#endif

			// Far mem set (WORD)! - This is STUPID! Borland SUCKS!

			while (len != 80*2)
			{
				*clear++ = 0x700;
				len++;
			}
			gotoxy (1,24);
		}
	}
#endif

	va_end(ap);
	exit(0);
}


//===========================================================================

/*
=====================
=
= DemoLoop
=
=====================
*/

void    DemoLoop (void)
{
	int     i,level;
	/*** BLAKE STONE: ALIENS OF GOLD V3.0 RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_300
	int 	LastDemo=3;
#else
	int 	LastDemo=0;
	boolean breakit;
#endif
	unsigned old_bufferofs;

	while (1)
	{
		playstate = ex_title;
		if (!screenfaded)
			VW_FadeOut();
		VL_SetPaletteIntensity(0,255,&vgapal,0);

		while (!(gamestate.flags & GS_NOWAIT))
		{
			extern boolean sqActive;

		// Start music when coming from menu...
		//
			if (!sqActive)
			{
			// Load and start music
			//
				CA_CacheAudioChunk(STARTMUSIC+TITLE_LOOP_MUSIC);
				SD_StartMusic((MusicGroup far *)audiosegs[STARTMUSIC+TITLE_LOOP_MUSIC]);
			}
			/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
			MM_SortMem();
#endif

//
// title page
//
#if !SKIP_TITLE_AND_CREDITS
			/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
			CA_CacheScreen(TITLEPIC);
#else
			breakit = false;

			CA_CacheScreen(TITLE1PIC);
#endif
			CA_CacheGrChunk(TITLEPALETTE);
			old_bufferofs = bufferofs;
			bufferofs=displayofs;
			VW_Bar(0,0,320,200,0);
			bufferofs=old_bufferofs;
			VL_SetPalette (0,256,grsegs[TITLEPALETTE]);
			VL_SetPaletteIntensity(0,255,grsegs[TITLEPALETTE],0);

			/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_100
			fontnumber = 2;
			/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
			PrintX = WindowX = 290;
			PrintY = WindowY = 5;
			WindowW = 29;
			WindowH = 10;
#else
			PrintX = WindowX = 270;
			PrintY = WindowY = 179;
			WindowW = 29;
			WindowH = 8;
#endif
			VWB_Bar(WindowX,WindowY-1,WindowW,WindowH,VERSION_TEXT_BKCOLOR);
			SETFONTCOLOR(VERSION_TEXT_COLOR, VERSION_TEXT_BKCOLOR);
			US_Print(__VERSION__);
#endif

			VW_UpdateScreen();
			VL_FadeIn(0,255,grsegs[TITLEPALETTE],30);
			UNCACHEGRCHUNK(TITLEPALETTE);
			if (IN_UserInput(TickBase*6))
				/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
				break;
#else
				breakit= true;
#endif

			/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG
		// Cache screen 2 with Warnings and Copyrights

			CA_CacheScreen(TITLE2PIC);
			fontnumber = 2;
			PrintX = WindowX = 270;
			PrintY = WindowY = 179;
			WindowW = 29;
			WindowH = 8;
			VWB_Bar(WindowX,WindowY-1,WindowW,WindowH,VERSION_TEXT_BKCOLOR);
			SETFONTCOLOR(VERSION_TEXT_COLOR, VERSION_TEXT_BKCOLOR);
			US_Print(__VERSION__);

			// Fizzle whole screen incase of any last minute changes needed
			// on title intro.

			FizzleFade(bufferofs,displayofs,320,200,70,false);
			IN_UserInput(TickBase*2);
			if (breakit || IN_UserInput(TickBase*6))
				break;
#endif
			VW_FadeOut();

//
// credits page
//
			DrawCreditsPage();
			VW_UpdateScreen();
			VW_FadeIn();
			if (IN_UserInput(TickBase*6))
				break;
			VW_FadeOut();

#endif

//
// demo
//

#if DEMOS_ENABLED
			/*** BLAKE STONE: ALIENS OF GOLD VERSIONS RESTORATION ***/
#if (IN_DEVELOPMENT) || (defined GAMEVER_RESTORATION_AOG)
//#if IN_DEVELOPMENT
		if (!MS_CheckParm("recdemo"))
#endif
#ifdef GAMEVER_RESTORATION_BS1_300
			PlayDemo(LastDemo++%3);
#elif defined GAMEVER_RESTORATION_BS1
			PlayDemo(LastDemo++%4);
#elif defined GAMEVER_RESTORATION_BS6_300
			PlayDemo(LastDemo++%5);
#else
			PlayDemo(LastDemo++%6);
#endif

			if (playstate == ex_abort)
				break;
			else
			{
			// Start music when coming from menu...
			//
				if (!sqActive)
//				if (!SD_MusicPlaying())
				{
				// Load and start music
				//
					CA_CacheAudioChunk(STARTMUSIC+TITLE_LOOP_MUSIC);
					SD_StartMusic((MusicGroup far *)audiosegs[STARTMUSIC+TITLE_LOOP_MUSIC]);
				}
			}
#endif

//
// high scores
//
#if !SKIP_TITLE_AND_CREDITS
			CA_CacheScreen (BACKGROUND_SCREENPIC);
			DrawHighScores ();
			VW_UpdateScreen ();
			VW_FadeIn ();

			if (IN_UserInput(TickBase*9))
				break;
			VW_FadeOut();
#endif
		}


		if (audiosegs[STARTMUSIC+TITLE_LOOP_MUSIC])
			MM_FreePtr((memptr *)&audiosegs[STARTMUSIC+TITLE_LOOP_MUSIC]);

		if (!screenfaded)
			VW_FadeOut();

#ifdef DEMOS_EXTERN
		if (MS_CheckParm("recdemo"))
			RecordDemo ();
		else
#endif
		{
			/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#if IN_DEVELOPMENT || TECH_SUPPORT_VERSION || (defined GAMEVER_RESTORATION_AOG_100)
//#if IN_DEVELOPMENT || TECH_SUPPORT_VERSION
			if (gamestate.flags & GS_QUICKRUN)
			{
				ReadGameNames();
				CA_LoadAllSounds();
				/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_100
				starting_level %= MAPS_PER_EPISODE;
#endif
				NewGame(2,gamestate.episode);
				startgame = true;
			}
			else
#endif													 
				US_ControlPanel (0);
		}
		if (startgame || loadedgame)
			GameLoop ();
	}
}

//-------------------------------------------------------------------------
// DrawCreditsPage()
//-------------------------------------------------------------------------
void DrawCreditsPage()
{
	PresenterInfo pi;

	CA_CacheScreen(BACKGROUND_SCREENPIC);

	memset(&pi,0,sizeof(pi));
	pi.flags = TPF_CACHE_NO_GFX;
	pi.xl=38;
	pi.yl=28;
	pi.xh=281;
	pi.yh=170;
	pi.bgcolor = 2;
	pi.ltcolor = BORDER_HI_COLOR;
	fontcolor = BORDER_TEXT_COLOR;
	pi.shcolor = pi.dkcolor = 0;
	pi.fontnumber=fontnumber;

#ifdef ID_CACHE_CREDITS
	TP_LoadScript(NULL,&pi,CREDITSTEXT);
#else
	TP_LoadScript("CREDITS.TXT",&pi,0);
#endif

	TP_Presenter(&pi);
}


//===========================================================================


extern void JM_FREE_START();
extern void JM_FREE_END();

/*
==========================
=
= main
=
==========================
*/

//char    *nosprtxt[] = {"nospr",nil};
/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_100
short starting_episode=0,starting_level=1,starting_difficulty=2;
#endif
#if IN_DEVELOPMENT || TECH_SUPPORT_VERSION
short starting_episode=0,starting_level=0,starting_difficulty=2;
#endif
short debug_value=0;

void main (void)
{
	/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG_POST200
	InitDestPath();
#endif

#if IN_DEVELOPMENT
	MakeDestPath(ERROR_LOG);
	remove(tempPath);
#endif

	/*** BLAKE STONE: ALIENS OF GOLD V2.0 RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_PRE210
	MakeDestPath(PLAYTEMP_FILE);
	remove(tempPath);
#else
	remove(PLAYTEMP_FILE);
#endif

	freed_main();

	/*** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***/
	// Comment out second call with data start and end
#if FREE_FUNCTIONS
	UseFunc((char huge *)JM_FREE_START,(char huge *)JM_FREE_END);
	//UseFunc((char huge *)JM_FREE_DATA_START,(char huge *)JM_FREE_DATA_END);
#endif

	DemoLoop();

	Quit(NULL);
}

#if FREE_FUNCTIONS

//-------------------------------------------------------------------------
// UseFunc()
//-------------------------------------------------------------------------
unsigned UseFunc(char huge *first, char huge *next)
{
	unsigned start,end;
	unsigned pars;

	first += 15;
	next++;
	next--;

	start = FP_SEG(first);
	end = FP_SEG(next);
	if (!FP_OFF(next))
		end--;
	pars = end - start - 1;
	_fmemset(MK_FP(start,0),0,pars*16);
	MML_UseSpace(start,pars);

	return(pars);
}

#endif


//-------------------------------------------------------------------------
// fprint()
//-------------------------------------------------------------------------
void fprint(char far *text)
{
	while (*text)
		printf("%c",*text++);
}


/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
// Relocated code to a separate file, since this is a part of JM_FREE.C in
// AOG v2.1/3.0, rather than 3D_MAIN.C as in PS. Note that it is NOT
// a part of AOG v2.0 anywhere.
#ifndef GAMEVER_RESTORATION_AOG
#include "3D_IDSTP.C"
#endif

/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifndef GAMEVER_RESTORATION_AOG_PRE210
//-------------------------------------------------------------------------
// MakeDestPath()
//-------------------------------------------------------------------------
/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
#ifdef GAMEVER_RESTORATION_AOG
void MakeDestPath(char *file)
{
	strcpy(tempPath,destPath);
	strcat(tempPath,file);
}
#else
void MakeDestPath(char far *file)
{
	_fstrcpy(tempPath,destPath);
	_fstrcat(tempPath,file);
}
#endif
#endif

#if IN_DEVELOPMENT

//-------------------------------------------------------------------------
// ShowMemory()
//-------------------------------------------------------------------------
void ShowMemory(void)
{
	long psize,size;

	size = MM_TotalFree();
	psize = MM_LargestAvail();
	mprintf("Mem free: %ld   %ld\n",size,psize);
}

#endif
