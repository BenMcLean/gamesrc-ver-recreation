








// SOURCE CODE FOR DUKE NUKEM 3D IS COPYRIGHTED BY TODD REPLOGLE AND MAY
// _NOT_ BE DISTRIBUTED EXCEPT AS AUTHORIZED BY 3DREALMS ENTERTAINMENT.




#ifdef EDUKE
// build number
#if (APPVER_DN3DREV >= AV_DR_EDK20023)
#define VERSIONCHECK	23
#else
#define VERSIONCHECK	21
#endif
#endif









#include "duke3d.h"

#if (APPVER_DN3DREV >= AV_DR_WW2GI10)
char g_szBuf[1024];
#endif

#ifdef WW2
long *aplWeaponClip[MAX_WEAPONS];		// number of items in clip
long *aplWeaponReload[MAX_WEAPONS];		// delay to reload (include fire)
long *aplWeaponFireDelay[MAX_WEAPONS];	// delay to fire
long *aplWeaponHoldDelay[MAX_WEAPONS];	// delay after release fire button to fire (0 for none)
long *aplWeaponTotalTime[MAX_WEAPONS];	// The total time the weapon is cycling before next fire.
long *aplWeaponFlags[MAX_WEAPONS];		// Flags for weapon
long *aplWeaponShoots[MAX_WEAPONS];		// what the weapon shoots
long *aplWeaponSpawnTime[MAX_WEAPONS];	// the frame at which to spawn an item
long *aplWeaponSpawn[MAX_WEAPONS];		// the item to spawn
long *aplWeaponShotsPerBurst[MAX_WEAPONS];	// number of shots per 'burst' (one ammo per 'burst'
long *aplWeaponWorksLike[MAX_WEAPONS];	// What original the weapon works like
long *aplWeaponInitialSound[MAX_WEAPONS];	// Sound made when initialy firing. zero for no sound
long *aplWeaponFireSound[MAX_WEAPONS];	// Sound made when firing (each time for automatic)
long *aplWeaponSound2Time[MAX_WEAPONS];	// Alternate sound time
long *aplWeaponSound2Sound[MAX_WEAPONS];	// Alternate sound sound ID

int g_iReturnVarID=-1;	// var ID of "RETURN"
int g_iWeaponVarID=-1;	// var ID of "WEAPON"
int g_iWorksLikeVarID=-1;	// var ID of "WORKSLIKE"
int g_iZRangeVarID=-1;	// var ID of "ZRANGE"
int g_iAngRangeVarID=-1;	// var ID of "ANGRANGE"
int g_iAimAngleVarID=-1;	// var ID of "AUTOAIMANGLE"
#ifdef EDUKE
int g_iLoTagID=-1;			// var ID of "LOTAG"
int g_iHiTagID=-1;			// ver ID of "HITAG"
int g_iTextureID=-1;		// var ID of "TEXTURE"
int g_iThisActorID=-1;		// var ID of "THISACTOR"

char g_bEnhanced=0;	// are we 'enhanced' (more minerals, etc)

long *actorLoadEventScrptr[MAXTILES];

#endif

#endif

extern short otherp;

static short total_lines,line_number;
static char checking_ifelse,parsing_state,*last_used_text;
static short num_squigilly_brackets;
static long last_used_size;

static short g_i,g_p;
static long g_x;
static long *g_t;
static spritetype *g_sp;
#ifdef EDUKE
#define NUMKEYWORDS	179
#else
#ifdef WW2
#define NUMKEYWORDS		127
#else
#define NUMKEYWORDS		112
#endif
#endif

char *keyw[NUMKEYWORDS] =
{
	"definelevelname",	// 0
	"actor",			// 1	[#]
	"addammo",	 // 2	 [#]
	"ifrnd",			// 3	[C]
	"enda",				// 4	[:]
	"ifcansee",			// 5	[C]
	"ifhitweapon",		// 6	[#]
	"action",			// 7	[#]
	"ifpdistl",			// 8	[#]
	"ifpdistg",			// 9	[#]
	"else",				// 10	[#]
	"strength",			// 11	[#]
	"break",			// 12	[#]
	"shoot",			// 13	[#]
	"palfrom",			// 14	[#]
	"sound",			// 15	[filename.voc]
	"fall",				// 16	[]
	"state",			// 17
	"ends",				// 18
	"define",			// 19
	"//",				// 20
	"ifai",				// 21
	"killit",			// 22
	"addweapon",		// 23
	"ai",				// 24
	"addphealth",		// 25
	"ifdead",			// 26
	"ifsquished",		// 27
	"sizeto",			// 28
	"{",				// 29
	"}",				// 30
	"spawn",			// 31
	"move",				// 32
	"ifwasweapon",		// 33
	"ifaction",			// 34
	"ifactioncount",	// 35
	"resetactioncount", // 36
	"debris",			// 37
	"pstomp",			// 38
	"/*",				// 39
	"cstat",			// 40
	"ifmove",			// 41
	"resetplayer",		// 42
	"ifonwater",		// 43
	"ifinwater",		// 44
	"ifcanshoottarget", // 45
	"ifcount",			// 46
	"resetcount",		// 47
	"addinventory",		// 48
	"ifactornotstayput",// 49
	"hitradius",		// 50
	"ifp",				// 51
	"count",			// 52
	"ifactor",			// 53
	"music",			// 54
	"include",			// 55
	"ifstrength",		// 56
	"definesound",		// 57
	"guts",				// 58
	"ifspawnedby",		// 59
	"gamestartup",		// 60
	"wackplayer",		// 61
	"ifgapzl",			// 62
	"ifhitspace",		// 63
	"ifoutside",		// 64
	"ifmultiplayer",	// 65
	"operate",			// 66
	"ifinspace",		// 67
	"debug",			// 68
	"endofgame",		// 69
	"ifbulletnear",		// 70
	"ifrespawn",		// 71
	"iffloordistl",		// 72
	"ifceilingdistl",	// 73
	"spritepal",		// 74
	"ifpinventory",		// 75
	"betaname",			// 76
	"cactor",			// 77
	"ifphealthl",		// 78
	"definequote",		// 79
	"quote",			// 80
	"ifinouterspace",	// 81
	"ifnotmoving",		// 82
	"respawnhitag",		   // 83
	"tip",			   // 84
	"ifspritepal",		// 85
	"money",		 // 86
	"soundonce",		 // 87
	"addkills",			// 88
	"stopsound",		// 89
	"ifawayfromwall",		// 90
	"ifcanseetarget",	// 91
	"globalsound",	// 92
	"lotsofglass", // 93
	"ifgotweaponce", // 94
	"getlastpal", // 95
	"pkick",  // 96
	"mikesnd", // 97
	"useractor",  // 98
	"sizeat",  // 99
	"addstrength", // 100	[#]
	"cstator", // 101
	"mail", // 102
	"paper", // 103
	"tossweapon", // 104
	"sleeptime", // 105
	"nullop", // 106
	"definevolumename", // 107
	"defineskillname", // 108
	"ifnosounds", // 109
	"clipdist", // 110
	"ifangdiffl" // 111
#ifdef WW2
	,"gamevar"	// 112
#define CON_GAMEVAR	112
			
	,"ifvarl"	// 113
#define CON_IFVARL	113
			
	,"ifvarg"	// 114
#define CON_IFVARG	114

	,"setvarvar"	// 115
#define CON_SETVARVAR	115
			
	,"setvar"	// 116
#define CON_SETVAR	116
			
	,"addvarvar"	// 117
#define CON_ADDVARVAR	117
			
	,"addvar"	// 118
#define CON_ADDVAR	118
			
	,"ifvarvarl"	// 119
#define CON_IFVARVARL	119

	,"ifvarvarg"	// 120
#define CON_IFVARVARG	120

	,"addlogvar"	// 121
#define CON_ADDLOGVAR	121
			
	,"addlog"	// 122
#define CON_ADDLOG	122

	,"onevent"	// 123
#define CON_ONEVENT	123

	,"endevent"	// 124
#define CON_ENDEVENT	124

	,"ifvare"	// 125
#define CON_IFVARE	125

	,"ifvarvare"	// 126
#define CON_IFVARVARE	126
#ifdef EDUKE			
	,"spgetlotag"		// 127
#define CON_SPGETLOTAG	127
			
	,"spgethitag"		// 128
#define CON_SPGETHITAG	128
			
	,"sectgetlotag"		// 129
#define CON_SECTGETLOTAG	129
			
	,"sectgethitag"		// 130
#define CON_SECTGETHITAG	130
			
	,"ifsound"		// 131
#define CON_IFSOUND	131
	,"gettexturefloor"		// 132
#define CON_GETTEXTUREFLOOR	132
	,"gettextureceiling"		// 133
#define CON_GETTEXTURECEILING	133
	,"gettexturewall"		// 134
#define CON_GETTEXTUREWALL	134
	,"starttrack"		// 135
#define CON_STARTTRACK	135
	,"randvar"		// 136
#define CON_RANDVAR	136
	,"enhanced"		// 137
#define CON_ENHANCED	137
	,"getangletotarget"		// 138
#define CON_GETANGLETOTARGET	138
	,"getactorangle"		// 139
#define CON_GETACTORANGLE	139
	,"setactorangle"		// 140
#define CON_SETACTORANGLE	140
	,"mulvar"		// 141
#define CON_MULVAR	141
	,"mulvarvar"		// 142
#define CON_MULVARVAR	142
	,"divvar"		// 143
#define CON_DIVVAR	143
	,"divvarvar"		// 144
#define CON_DIVVARVAR	144
	,"modvar"		// 145
#define CON_MODVAR	145
	,"modvarvar"		// 146
#define CON_MODVARVAR	146
	,"andvar"		// 147
#define CON_ANDVAR	147
	,"andvarvar"		// 148
#define CON_ANDVARVAR	148
	,"orvar"		// 149
#define CON_ORVAR	149
	,"orvarvar"		// 150
#define CON_ORVARVAR	150
	,"getplayerangle"		// 151
#define CON_GETPLAYERANGLE	151
	,"setplayerangle"		// 152
#define CON_SETPLAYERANGLE	152
	,"lockplayer"		// 153
#define CON_LOCKPLAYER	153
	,"setsector"		// 154
#define CON_SETSECTOR	154
	,"getsector"		// 155
#define CON_GETSECTOR	155
	,"setactor"		// 156
#define CON_SETACTOR	156
	,"getactor"		// 157
#define CON_GETACTOR	157
	,"setwall"		// 158
#define CON_SETWALL	158
	,"getwall"		// 159
#define CON_GETWALL	159
	,"findnearactor"		// 160
#define CON_FINDNEARACTOR	160
	,"findnearactorvar"		// 161
#define CON_FINDNEARACTORVAR	161
	,"setactorvar"		// 162
#define CON_SETACTORVAR	162
	,"getactorvar"		// 163
#define CON_GETACTORVAR	163
	,"espawn"		// 164
#define CON_ESPAWN	164
	,"getplayer"		// 165
#define CON_GETPLAYER	165
	,"setplayer"		// 166
#define CON_SETPLAYER	166
	,"sqrt"		// 167
#define CON_SQRT	167
	,"eventloadactor"		// 168
#define CON_EVENTLOADACTOR	168
	,"espawnvar"		// 169
#define CON_ESPAWNVAR	169
	,"getuserdef"		// 170
#define CON_GETUSERDEF	170
	,"setuserdef"		// 171
#define CON_SETUSERDEF	171
	,"subvarvar"	// 172
#define CON_SUBVARVAR	172
	,"subvar"	// 173
#define CON_SUBVAR	173
	,"ifvarn"	// 174
#define CON_IFVARN	174
	,"ifvarvarn"	// 175
#define CON_IFVARVARN	175
	,"ifvarand"	// 176
#define CON_IFVARAND	176
	,"ifvarvarand"	// 177
#define CON_IFVARVARAND	177
	
			
#endif
// TODO: add playanm <id> <id2> (called on OnAction(NEWGAME) )
#endif
};

#ifdef WW2

#if (APPVER_DN3DREV >= AV_DR_EDK20021)
typedef struct _labels
{
	char *name;
	long lId;
} LABELS;

LABELS sectorlabels[]=
 {
#define SECTOR_WALLPTR	1
  {	"wallptr", SECTOR_WALLPTR },
#define SECTOR_WALLNUM	2
  { "wallnum", SECTOR_WALLNUM },
#define SECTOR_CEILINGZ	3
  { "ceilingz", SECTOR_CEILINGZ },
#define SECTOR_FLOORZ	4
  { "floorz", SECTOR_FLOORZ },
#define SECTOR_CEILINGSTAT	5
  { "ceilingstat", SECTOR_CEILINGSTAT },
#define SECTOR_FLOORSTAT	6
  { "floorstat", SECTOR_FLOORSTAT },
#define SECTOR_CEILINGPICNUM 7
  { "ceilingpicnum", SECTOR_CEILINGPICNUM },
#define SECTOR_CEILINGSLOPE 8
  { "ceilingslope", SECTOR_CEILINGSLOPE },
#define SECTOR_CEILINGSHADE 9
  { "ceilingshade", SECTOR_CEILINGSHADE },
#define SECTOR_CEILINGPAL 10
  { "ceilingpal", SECTOR_CEILINGPAL },
#define SECTOR_CEILINGXPANNING 11
  { "ceilingxpanning", SECTOR_CEILINGXPANNING },
#define SECTOR_CEILINGYPANNING 12
  { "ceilingypanning", SECTOR_CEILINGYPANNING },
#define SECTOR_FLOORPICNUM 13
  { "floorpicnum", SECTOR_FLOORPICNUM },
#define SECTOR_FLOORSLOPE 14
  { "floorslope", SECTOR_FLOORSLOPE },
#define SECTOR_FLOORSHADE 15
  { "floorshade", SECTOR_FLOORSHADE },
#define SECTOR_FLOORPAL 16
  { "floorpal", SECTOR_FLOORPAL },
#define SECTOR_FLOORXPANNING 17
  { "floorxpanning", SECTOR_FLOORXPANNING },
#define SECTOR_FLOORYPANNING 18
  { "floorypanning", SECTOR_FLOORYPANNING },
#define SECTOR_VISIBILITY 19
  { "visibility", SECTOR_VISIBILITY },
#define SECTOR_ALIGNTO 20
  { "alignto", SECTOR_ALIGNTO },
#define SECTOR_LOTAG 21
  { "lotag", SECTOR_LOTAG },
#define SECTOR_HITAG 22
  { "hitag", SECTOR_HITAG },
#define SECTOR_EXTRA 23
  { "extra", SECTOR_EXTRA },

  { "", -1 }	// END OF LIST
 };

LABELS walllabels[]=
{
#define WALL_X 1
	{ "x", WALL_X },
#define WALL_Y 2
	{ "y", WALL_Y },
#define WALL_POINT2 3
	{ "point2", WALL_POINT2 },
#define WALL_NEXTWALL 4
	{ "nextwall", WALL_NEXTWALL },
#define WALL_NEXTSECTOR 5
	{ "nextsector", WALL_NEXTSECTOR },
#define WALL_CSTAT 6
	{ "cstat", WALL_CSTAT },
#define WALL_PICNUM 7
	{ "picnum", WALL_PICNUM },
#define WALL_OVERPICNUM 8
	{ "overpicnum", WALL_OVERPICNUM },
#define WALL_SHADE 9
	{ "shade", WALL_SHADE },
#define WALL_PAL 10
	{ "pal", WALL_PAL },
#define WALL_XREPEAT 11
	{ "xrepeat", WALL_XREPEAT },
#define WALL_YREPEAT 12
	{ "yrepeat", WALL_YREPEAT },
#define WALL_XPANNING 13
	{ "xpanning", WALL_XPANNING },
#define WALL_YPANNING 14
	{ "ypanning", WALL_YPANNING },
#define WALL_LOTAG 15
	{ "lotag", WALL_LOTAG },
#define WALL_HITAG 16
	{ "hitag", WALL_HITAG },
#define WALL_EXTRA 17
	{ "extra", WALL_EXTRA },
	
  { "", -1 }	// END OF LIST

};

LABELS actorlabels[]=
{
#define ACTOR_X 1
	{ "x", ACTOR_X },
#define ACTOR_Y 2
	{ "y", ACTOR_Y },
#define ACTOR_Z 3
	{ "z", ACTOR_Z },
#define ACTOR_CSTAT 4
	{ "cstat", ACTOR_CSTAT },
#define ACTOR_PICNUM 5
	{ "picnum", ACTOR_PICNUM },
#define ACTOR_SHADE 6
	{ "shade", ACTOR_SHADE },
#define ACTOR_PAL 7
	{ "pal", ACTOR_PAL },
#define ACTOR_CLIPDIST 8
	{ "clipdist", ACTOR_CLIPDIST },
#define ACTOR_DETAIL 9
	{ "detail", ACTOR_DETAIL },
#define ACTOR_XREPEAT 10
	{ "xrepeat", ACTOR_XREPEAT },
#define ACTOR_YREPEAT 11
	{ "yrepeat", ACTOR_YREPEAT },
#define ACTOR_XOFFSET 12
	{ "xoffset", ACTOR_XOFFSET },
#define ACTOR_YOFFSET 13
	{ "yoffset", ACTOR_YOFFSET },
#define ACTOR_SECTNUM 14
	{ "sectnum", ACTOR_SECTNUM },
#define ACTOR_STATNUM 15
	{ "statnum", ACTOR_STATNUM },
#define ACTOR_ANG 16
	{ "ang", ACTOR_ANG },
#define ACTOR_OWNER 17
	{ "owner", ACTOR_OWNER },
#define ACTOR_XVEL 18
	{ "xvel", ACTOR_XVEL },
#define ACTOR_YVEL 19
	{ "yvel", ACTOR_YVEL },
#define ACTOR_ZVEL 20
	{ "zvel", ACTOR_ZVEL },
#define ACTOR_LOTAG 21
	{ "lotag", ACTOR_LOTAG },
#define ACTOR_HITAG 22
	{ "hitag", ACTOR_HITAG },
#define ACTOR_EXTRA 23
	{ "extra", ACTOR_EXTRA },

	// hittype labels...
#define ACTOR_HTCGG 50
	{ "htcgg", ACTOR_HTCGG },
#define ACTOR_HTPICNUM 51
	{ "htpicnum", ACTOR_HTPICNUM },
#define ACTOR_HTANG 52
	{ "htang", ACTOR_HTANG },
#define ACTOR_HTEXTRA 53
	{ "htextra", ACTOR_HTEXTRA },
#define ACTOR_HTOWNER 54
	{ "htowner", ACTOR_HTOWNER },
#define ACTOR_HTMOVFLAG 55
	{ "htmovflag", ACTOR_HTMOVFLAG },
#define ACTOR_HTTEMPANG 56
	{ "httempang", ACTOR_HTTEMPANG },
#define ACTOR_HTACTORSTAYPUT 57
	{ "htactorstayput", ACTOR_HTACTORSTAYPUT },
#define ACTOR_HTDISPICNUM 58
	{ "htdispicnum", ACTOR_HTDISPICNUM },
#define ACTOR_HTTIMETOSLEEP 59
	{ "httimetosleep", ACTOR_HTTIMETOSLEEP },
#define ACTOR_HTFLOORZ 60
	{ "htfloorz", ACTOR_HTFLOORZ },
#define ACTOR_HTCEILINGZ 61
	{ "htceilingz", ACTOR_HTCEILINGZ },
#define ACTOR_HTLASTVX 62
	{ "htlastvx", ACTOR_HTLASTVX },
#define ACTOR_HTLASTVY 63
	{ "htlastvy", ACTOR_HTLASTVY },
#define ACTOR_HTBPOSX 64
	{ "htbposx", ACTOR_HTBPOSX },
#define ACTOR_HTBPOSY 65
	{ "htbposy", ACTOR_HTBPOSY },
#define ACTOR_HTBPOSZ 66
	{ "htbposz", ACTOR_HTBPOSZ },
#define ACTOR_HTG_T0 67
	{ "htg_t[0]", ACTOR_HTG_T0 },
#define ACTOR_HTG_T1 68
	{ "htg_t[1]", ACTOR_HTG_T1 },
#define ACTOR_HTG_T2 69
	{ "htg_t[2]", ACTOR_HTG_T2 },
#define ACTOR_HTG_T3 70
	{ "htg_t[3]", ACTOR_HTG_T3 },
#define ACTOR_HTG_T4 71
	{ "htg_t[4]", ACTOR_HTG_T4 },
#define ACTOR_HTG_T5 72
	{ "htg_t[5]", ACTOR_HTG_T5 },

  { "", -1 }	// END OF LIST
	
};


//////////////////////////////////

LABELS playerlabels[]=
{
#define PLAYER_ZOOM 1
	{ "zoom", PLAYER_ZOOM },
#define PLAYER_EXITX 2
	{ "exitx", PLAYER_EXITX },
#define PLAYER_EXITY 3
	{ "exity", PLAYER_EXITY },
#define PLAYER_LOOGIEX 4
	{ "loogiex[64]", PLAYER_LOOGIEX },
#define PLAYER_LOOGIEY 5
	{ "loogiey[64]", PLAYER_LOOGIEY },
#define PLAYER_NUMLOOGS 6
	{ "numloogs", PLAYER_NUMLOOGS },
#define PLAYER_LOOGCNT 7
	{ "loogcnt", PLAYER_LOOGCNT },
#define PLAYER_POSX 8
	{ "posx", PLAYER_POSX },
#define PLAYER_POSY 9
	{ "posy", PLAYER_POSY },
#define PLAYER_POSZ 10
	{ "posz", PLAYER_POSZ },
#define PLAYER_HORIZ 11
	{ "horiz", PLAYER_HORIZ },
#define PLAYER_OHORIZ 12
	{ "ohoriz", PLAYER_OHORIZ },
#define PLAYER_OHORIZOFF 13
	{ "ohorizoff", PLAYER_OHORIZOFF },
#define PLAYER_INVDISPTIME 14
	{ "invdisptime", PLAYER_INVDISPTIME },
#define PLAYER_BOBPOSX 15
	{ "bobposx", PLAYER_BOBPOSX },
#define PLAYER_BOBPOSY 16
	{ "bobposy", PLAYER_BOBPOSY },
#define PLAYER_OPOSX 17
	{ "oposx", PLAYER_OPOSX },
#define PLAYER_OPOSY 18
	{ "oposy", PLAYER_OPOSY },
#define PLAYER_OPOSZ 19
	{ "oposz", PLAYER_OPOSZ },
#define PLAYER_PYOFF 20
	{ "pyoff", PLAYER_PYOFF },
#define PLAYER_OPYOFF 21
	{ "opyoff", PLAYER_OPYOFF },
#define PLAYER_POSXV 22
	{ "posxv", PLAYER_POSXV },
#define PLAYER_POSYV 23
	{ "posyv", PLAYER_POSYV },
#define PLAYER_POSZV 24
	{ "poszv", PLAYER_POSZV },
#define PLAYER_LAST_PISSED_TIME 25
	{ "last_pissed_time", PLAYER_LAST_PISSED_TIME },
#define PLAYER_TRUEFZ 26
	{ "truefz", PLAYER_TRUEFZ },
#define PLAYER_TRUECZ 27
	{ "truecz", PLAYER_TRUECZ },
#define PLAYER_PLAYER_PAR 28
	{ "player_par", PLAYER_PLAYER_PAR },
#define PLAYER_VISIBILITY 29
	{ "visibility", PLAYER_VISIBILITY },
#define PLAYER_BOBCOUNTER 30
	{ "bobcounter", PLAYER_BOBCOUNTER },
#define PLAYER_WEAPON_SWAY 31
	{ "weapon_sway", PLAYER_WEAPON_SWAY },
#define PLAYER_PALS_TIME 32
	{ "pals_time", PLAYER_PALS_TIME },
#define PLAYER_RANDOMFLAMEX 33
	{ "randomflamex", PLAYER_RANDOMFLAMEX },
#define PLAYER_CRACK_TIME 34
	{ "crack_time", PLAYER_CRACK_TIME },
#define PLAYER_AIM_MODE 35
	{ "aim_mode", PLAYER_AIM_MODE },
#define PLAYER_ANG 36
	{ "ang", PLAYER_ANG },
#define PLAYER_OANG 37
	{ "oang", PLAYER_OANG },
#define PLAYER_ANGVEL 38
	{ "angvel", PLAYER_ANGVEL },
#define PLAYER_CURSECTNUM 39
	{ "cursectnum", PLAYER_CURSECTNUM },
#define PLAYER_LOOK_ANG 40
	{ "look_ang", PLAYER_LOOK_ANG },
#define PLAYER_LAST_EXTRA 41
	{ "last_extra", PLAYER_LAST_EXTRA },
#define PLAYER_SUBWEAPON 42
	{ "subweapon", PLAYER_SUBWEAPON },
#define PLAYER_AMMO_AMOUNT 43
	{ "ammo_amount[MAX_WEAPONS]", PLAYER_AMMO_AMOUNT },
#define PLAYER_WACKEDBYACTOR 44
	{ "wackedbyactor", PLAYER_WACKEDBYACTOR },
#define PLAYER_FRAG 45
	{ "frag", PLAYER_FRAG },
#define PLAYER_FRAGGEDSELF 945
	{ "fraggedself", PLAYER_FRAGGEDSELF },
#define PLAYER_CURR_WEAPON 46
	{ "curr_weapon", PLAYER_CURR_WEAPON },
#define PLAYER_LAST_WEAPON 47
	{ "last_weapon", PLAYER_LAST_WEAPON },
#define PLAYER_TIPINCS 48
	{ "tipincs", PLAYER_TIPINCS },
#define PLAYER_HORIZOFF 49
	{ "horizoff", PLAYER_HORIZOFF },
#define PLAYER_WANTWEAPONFIRE 50
	{ "wantweaponfire", PLAYER_WANTWEAPONFIRE },
#define PLAYER_HOLODUKE_AMOUNT 51
	{ "holoduke_amount", PLAYER_HOLODUKE_AMOUNT },
#define PLAYER_NEWOWNER 52
	{ "newowner", PLAYER_NEWOWNER },
#define PLAYER_HURT_DELAY 53
	{ "hurt_delay", PLAYER_HURT_DELAY },
#define PLAYER_HBOMB_HOLD_DELAY 54
	{ "hbomb_hold_delay", PLAYER_HBOMB_HOLD_DELAY },
#define PLAYER_JUMPING_COUNTER 55
	{ "jumping_counter", PLAYER_JUMPING_COUNTER },
#define PLAYER_AIRLEFT 56
	{ "airleft", PLAYER_AIRLEFT },
#define PLAYER_KNEE_INCS 57
	{ "knee_incs", PLAYER_KNEE_INCS },
#define PLAYER_ACCESS_INCS 58
	{ "access_incs", PLAYER_ACCESS_INCS },
#define PLAYER_FTA 59
	{ "fta", PLAYER_FTA },
#define PLAYER_FTQ 60
	{ "ftq", PLAYER_FTQ },
#define PLAYER_ACCESS_WALLNUM 61
	{ "access_wallnum", PLAYER_ACCESS_WALLNUM },
#define PLAYER_ACCESS_SPRITENUM 62
	{ "access_spritenum", PLAYER_ACCESS_SPRITENUM },
#define PLAYER_KICKBACK_PIC 63
	{ "kickback_pic", PLAYER_KICKBACK_PIC },
#define PLAYER_GOT_ACCESS 64
	{ "got_access", PLAYER_GOT_ACCESS },
#define PLAYER_WEAPON_ANG 65
	{ "weapon_ang", PLAYER_WEAPON_ANG },
#define PLAYER_FIRSTAID_AMOUNT 66
	{ "firstaid_amount", PLAYER_FIRSTAID_AMOUNT },
#define PLAYER_SOMETHINGONPLAYER 67
	{ "somethingonplayer", PLAYER_SOMETHINGONPLAYER },
#define PLAYER_ON_CRANE 68
	{ "on_crane", PLAYER_ON_CRANE },
#define PLAYER_I 69
	{ "i", PLAYER_I },
#define PLAYER_ONE_PARALLAX_SECTNUM 70
	{ "one_parallax_sectnum", PLAYER_ONE_PARALLAX_SECTNUM },
#define PLAYER_OVER_SHOULDER_ON 71
	{ "over_shoulder_on", PLAYER_OVER_SHOULDER_ON },
#define PLAYER_RANDOM_CLUB_FRAME 72
	{ "random_club_frame", PLAYER_RANDOM_CLUB_FRAME },
#define PLAYER_FIST_INCS 73
	{ "fist_incs", PLAYER_FIST_INCS },
#define PLAYER_ONE_EIGHTY_COUNT 74
	{ "one_eighty_count", PLAYER_ONE_EIGHTY_COUNT },
#define PLAYER_CHEAT_PHASE 75
	{ "cheat_phase", PLAYER_CHEAT_PHASE },
#define PLAYER_DUMMYPLAYERSPRITE 76
	{ "dummyplayersprite", PLAYER_DUMMYPLAYERSPRITE },
#define PLAYER_EXTRA_EXTRA8 77
	{ "extra_extra8", PLAYER_EXTRA_EXTRA8 },
#define PLAYER_QUICK_KICK 78
	{ "quick_kick", PLAYER_QUICK_KICK },
#define PLAYER_HEAT_AMOUNT 79
	{ "heat_amount", PLAYER_HEAT_AMOUNT },
#define PLAYER_ACTORSQU 80
	{ "actorsqu", PLAYER_ACTORSQU },
#define PLAYER_TIMEBEFOREEXIT 81
	{ "timebeforeexit", PLAYER_TIMEBEFOREEXIT },
#define PLAYER_CUSTOMEXITSOUND 82
	{ "customexitsound", PLAYER_CUSTOMEXITSOUND },
#define PLAYER_WEAPRECS 83
	{ "weaprecs[16]", PLAYER_WEAPRECS },
#define PLAYER_WEAPRECCNT 84
	{ "weapreccnt", PLAYER_WEAPRECCNT },
#define PLAYER_INTERFACE_TOGGLE_FLAG 85
	{ "interface_toggle_flag", PLAYER_INTERFACE_TOGGLE_FLAG },
#define PLAYER_ROTSCRNANG 86
	{ "rotscrnang", PLAYER_ROTSCRNANG },
#define PLAYER_DEAD_FLAG 87
	{ "dead_flag", PLAYER_DEAD_FLAG },
#define PLAYER_SHOW_EMPTY_WEAPON 88
	{ "show_empty_weapon", PLAYER_SHOW_EMPTY_WEAPON },
#define PLAYER_SCUBA_AMOUNT 89
	{ "scuba_amount", PLAYER_SCUBA_AMOUNT },
#define PLAYER_JETPACK_AMOUNT 90
	{ "jetpack_amount", PLAYER_JETPACK_AMOUNT },
#define PLAYER_STEROIDS_AMOUNT 91
	{ "steroids_amount", PLAYER_STEROIDS_AMOUNT },
#define PLAYER_SHIELD_AMOUNT 92
	{ "shield_amount", PLAYER_SHIELD_AMOUNT },
#define PLAYER_HOLODUKE_ON 93
	{ "holoduke_on", PLAYER_HOLODUKE_ON },
#define PLAYER_PYCOUNT 94
	{ "pycount", PLAYER_PYCOUNT },
#define PLAYER_WEAPON_POS 95
	{ "weapon_pos", PLAYER_WEAPON_POS },
#define PLAYER_FRAG_PS 96
	{ "frag_ps", PLAYER_FRAG_PS },
#define PLAYER_TRANSPORTER_HOLD 97
	{ "transporter_hold", PLAYER_TRANSPORTER_HOLD },
#define PLAYER_LAST_FULL_WEAPON 98
	{ "last_full_weapon", PLAYER_LAST_FULL_WEAPON },
#define PLAYER_FOOTPRINTSHADE 99
	{ "footprintshade", PLAYER_FOOTPRINTSHADE },
#define PLAYER_BOOT_AMOUNT 100
	{ "boot_amount", PLAYER_BOOT_AMOUNT },
#define PLAYER_SCREAM_VOICE 101
	{ "scream_voice", PLAYER_SCREAM_VOICE },
#define PLAYER_GM 102
	{ "gm", PLAYER_GM },
#define PLAYER_ON_WARPING_SECTOR 103
	{ "on_warping_sector", PLAYER_ON_WARPING_SECTOR },
#define PLAYER_FOOTPRINTCOUNT 104
	{ "footprintcount", PLAYER_FOOTPRINTCOUNT },
#define PLAYER_HBOMB_ON 105
	{ "hbomb_on", PLAYER_HBOMB_ON },
#define PLAYER_JUMPING_TOGGLE 106
	{ "jumping_toggle", PLAYER_JUMPING_TOGGLE },
#define PLAYER_RAPID_FIRE_HOLD 107
	{ "rapid_fire_hold", PLAYER_RAPID_FIRE_HOLD },
#define PLAYER_ON_GROUND 108
	{ "on_ground", PLAYER_ON_GROUND },
#define PLAYER_NAME 109
	{ "name[32]", PLAYER_NAME },
#define PLAYER_INVEN_ICON 110
	{ "inven_icon", PLAYER_INVEN_ICON },
#define PLAYER_BUTTONPALETTE 111
	{ "buttonpalette", PLAYER_BUTTONPALETTE },
#define PLAYER_JETPACK_ON 112
	{ "jetpack_on", PLAYER_JETPACK_ON },
#define PLAYER_SPRITEBRIDGE 113
	{ "spritebridge", PLAYER_SPRITEBRIDGE },
#define PLAYER_LASTRANDOMSPOT 114
	{ "lastrandomspot", PLAYER_LASTRANDOMSPOT },
#define PLAYER_SCUBA_ON 115
	{ "scuba_on", PLAYER_SCUBA_ON },
#define PLAYER_FOOTPRINTPAL 116
	{ "footprintpal", PLAYER_FOOTPRINTPAL },
#define PLAYER_HEAT_ON 117
	{ "heat_on", PLAYER_HEAT_ON },
#define PLAYER_HOLSTER_WEAPON 118
	{ "holster_weapon", PLAYER_HOLSTER_WEAPON },
#define PLAYER_FALLING_COUNTER 119
	{ "falling_counter", PLAYER_FALLING_COUNTER },
#define PLAYER_GOTWEAPON 120
	{ "gotweapon[MAX_WEAPONS]", PLAYER_GOTWEAPON },
#define PLAYER_REFRESH_INVENTORY 121
	{ "refresh_inventory", PLAYER_REFRESH_INVENTORY },
#define PLAYER_PALETTE 122
	{ "palette", PLAYER_PALETTE },
#define PLAYER_TOGGLE_KEY_FLAG 123
	{ "toggle_key_flag", PLAYER_TOGGLE_KEY_FLAG },
#define PLAYER_KNUCKLE_INCS 124
	{ "knuckle_incs", PLAYER_KNUCKLE_INCS },
#define PLAYER_WALKING_SND_TOGGLE 125
	{ "walking_snd_toggle", PLAYER_WALKING_SND_TOGGLE },
#define PLAYER_PALOOKUP 126
	{ "palookup", PLAYER_PALOOKUP },
#define PLAYER_HARD_LANDING 127
	{ "hard_landing", PLAYER_HARD_LANDING },
#define PLAYER_MAX_SECRET_ROOMS 128
	{ "max_secret_rooms", PLAYER_MAX_SECRET_ROOMS },
#define PLAYER_SECRET_ROOMS 129
	{ "secret_rooms", PLAYER_SECRET_ROOMS },
#define PLAYER_PALS 130
	{ "pals[3]", PLAYER_PALS },
#define PLAYER_MAX_ACTORS_KILLED 131
	{ "max_actors_killed", PLAYER_MAX_ACTORS_KILLED },
#define PLAYER_ACTORS_KILLED 132
	{ "actors_killed", PLAYER_ACTORS_KILLED },
#define PLAYER_RETURN_TO_CENTER 133
	{ "return_to_center", PLAYER_RETURN_TO_CENTER },
	
  { "", -1 }	// END OF LIST
	
};

///////////////////////////////////////

LABELS userdefslabels[]=
{
#define USERDEFS_GOD 2
	{ "god", USERDEFS_GOD },
#define USERDEFS_WARP_ON 3
	{ "warp_on", USERDEFS_WARP_ON },
#define USERDEFS_CASHMAN 4
	{ "cashman", USERDEFS_CASHMAN },
#define USERDEFS_EOG 5
	{ "eog", USERDEFS_EOG },
#define USERDEFS_SHOWALLMAP			 6
	{ "showallmap", USERDEFS_SHOWALLMAP },
#define USERDEFS_SHOW_HELP 7
	{ "show_help", USERDEFS_SHOW_HELP },
#define USERDEFS_SCROLLMODE 8
	{ "scrollmode", USERDEFS_SCROLLMODE },
#define USERDEFS_CLIPPING 9
	{ "clipping", USERDEFS_CLIPPING },
#define USERDEFS_USER_NAME 10
	{ "user_name[MAXPLAYERS][32]", USERDEFS_USER_NAME },
#define USERDEFS_RIDECULE 11
	{ "ridecule[10][40]", USERDEFS_RIDECULE },
#define USERDEFS_SAVEGAME 12
	{ "savegame[10][22]", USERDEFS_SAVEGAME },
#define USERDEFS_PWLOCKOUT 13
	{ "pwlockout[128]", USERDEFS_PWLOCKOUT },
#define USERDEFS_RTSNAME 14
	{ "rtsname[128];", USERDEFS_RTSNAME },
#define USERDEFS_OVERHEAD_ON 15
 { "overhead_on", USERDEFS_OVERHEAD_ON },
#define USERDEFS_LAST_OVERHEAD 16
 { "last_overhead", USERDEFS_LAST_OVERHEAD },
#define USERDEFS_SHOWWEAPONS 17
 { "showweapons", USERDEFS_SHOWWEAPONS },

#define USERDEFS_PAUSE_ON 18
 { "pause_on", USERDEFS_PAUSE_ON },
#define USERDEFS_FROM_BONUS 19
 { "from_bonus", USERDEFS_FROM_BONUS },
#define USERDEFS_CAMERASPRITE 20
 { "camerasprite", USERDEFS_CAMERASPRITE },
#define USERDEFS_LAST_CAMSPRITE 21
 { "last_camsprite", USERDEFS_LAST_CAMSPRITE },
#define USERDEFS_LAST_LEVEL 22
 { "last_level", USERDEFS_LAST_LEVEL },
#define USERDEFS_SECRETLEVEL 23
 { "secretlevel", USERDEFS_SECRETLEVEL },

#define USERDEFS_CONST_VISIBILITY 24
 { "const_visibility", USERDEFS_CONST_VISIBILITY },
#define USERDEFS_UW_FRAMERATE 25
 { "uw_framerate", USERDEFS_UW_FRAMERATE },
#define USERDEFS_CAMERA_TIME 26
 { "camera_time", USERDEFS_CAMERA_TIME },
#define USERDEFS_FOLFVEL 27
 { "folfvel", USERDEFS_FOLFVEL },
#define USERDEFS_FOLAVEL 28
 { "folavel", USERDEFS_FOLAVEL },
#define USERDEFS_FOLX 29
 { "folx", USERDEFS_FOLX },
#define USERDEFS_FOLY 30
 { "foly", USERDEFS_FOLY },
#define USERDEFS_FOLA 31
 { "fola", USERDEFS_FOLA },
#define USERDEFS_RECCNT 32
 { "reccnt", USERDEFS_RECCNT },

#define USERDEFS_ENTERED_NAME 33
 { "entered_name", USERDEFS_ENTERED_NAME },
#define USERDEFS_SCREEN_TILTING 34
 { "screen_tilting", USERDEFS_SCREEN_TILTING },
#define USERDEFS_SHADOWS 35
 { "shadows", USERDEFS_SHADOWS },
#define USERDEFS_FTA_ON 36
 { "fta_on", USERDEFS_FTA_ON },
#define USERDEFS_EXECUTIONS 37
 { "executions", USERDEFS_EXECUTIONS },
#define USERDEFS_AUTO_RUN 38
 { "auto_run", USERDEFS_AUTO_RUN },
#define USERDEFS_COORDS 39
 { "coords", USERDEFS_COORDS },
#define USERDEFS_TICKRATE 40
 { "tickrate", USERDEFS_TICKRATE },
#define USERDEFS_M_COOP 41
 { "m_coop", USERDEFS_M_COOP },
#define USERDEFS_COOP 42
 { "coop", USERDEFS_COOP },
#define USERDEFS_SCREEN_SIZE 43
 { "screen_size", USERDEFS_SCREEN_SIZE },
#define USERDEFS_LOCKOUT 44
 { "lockout", USERDEFS_LOCKOUT },
#define USERDEFS_CROSSHAIR 45
 { "crosshair", USERDEFS_CROSSHAIR },
#define USERDEFS_WCHOICE 46
 { "wchoice[MAXPLAYERS][MAX_WEAPONS]", USERDEFS_WCHOICE },
#define USERDEFS_PLAYERAI 47
 { "playerai", USERDEFS_PLAYERAI },
#define USERDEFS_RESPAWN_MONSTERS 48
 { "respawn_monsters", USERDEFS_RESPAWN_MONSTERS },
#define USERDEFS_RESPAWN_ITEMS 49
 { "respawn_items", USERDEFS_RESPAWN_ITEMS },
#define USERDEFS_RESPAWN_INVENTORY 50
 { "respawn_inventory", USERDEFS_RESPAWN_INVENTORY },
#define USERDEFS_RECSTAT 51
 { "recstat", USERDEFS_RECSTAT },
#define USERDEFS_MONSTERS_OFF 52
 { "monsters_off", USERDEFS_MONSTERS_OFF },
#define USERDEFS_BRIGHTNESS 53
 { "brightness", USERDEFS_BRIGHTNESS },
#define USERDEFS_M_RESPAWN_ITEMS 54
 { "m_respawn_items", USERDEFS_M_RESPAWN_ITEMS },
#define USERDEFS_M_RESPAWN_MONSTERS 55
 { "m_respawn_monsters", USERDEFS_M_RESPAWN_MONSTERS },
#define USERDEFS_M_RESPAWN_INVENTORY 56
 { "m_respawn_inventory", USERDEFS_M_RESPAWN_INVENTORY },
#define USERDEFS_M_RECSTAT 57
 { "m_recstat", USERDEFS_M_RECSTAT },
#define USERDEFS_M_MONSTERS_OFF 58
 { "m_monsters_off", USERDEFS_M_MONSTERS_OFF },
#define USERDEFS_DETAIL 59
 { "detail", USERDEFS_DETAIL },
#define USERDEFS_M_FFIRE 60
 { "m_ffire", USERDEFS_M_FFIRE },
#define USERDEFS_FFIRE 61
 { "ffire", USERDEFS_FFIRE },
#define USERDEFS_M_PLAYER_SKILL 62
 { "m_player_skill", USERDEFS_M_PLAYER_SKILL },
#define USERDEFS_M_LEVEL_NUMBER 63
 { "m_level_number", USERDEFS_M_LEVEL_NUMBER },
#define USERDEFS_M_VOLUME_NUMBER 64
 { "m_volume_number", USERDEFS_M_VOLUME_NUMBER },
#define USERDEFS_MULTIMODE 65
 { "multimode", USERDEFS_MULTIMODE },
#define USERDEFS_PLAYER_SKILL 66
 { "player_skill", USERDEFS_PLAYER_SKILL },
#define USERDEFS_LEVEL_NUMBER 67
 { "level_number", USERDEFS_LEVEL_NUMBER },
#define USERDEFS_VOLUME_NUMBER 68
 { "volume_number", USERDEFS_VOLUME_NUMBER },
#define USERDEFS_M_MARKER 69
 { "m_marker", USERDEFS_M_MARKER },
#define USERDEFS_MARKER 70
 { "marker", USERDEFS_MARKER },
#define USERDEFS_MOUSEFLIP 71
 { "mouseflip", USERDEFS_MOUSEFLIP },

  { "", -1 }	// END OF LIST
	
};


///////////////////////////////////////////
void DoUserDef(char bSet, long lVar1, long lLabelID, long lVar2, short sActor, short sPlayer)
{
	int iPlayer;
	long lValue;

	lValue=GetGameVarID((int)lVar2, sActor, sPlayer);
	
	switch(lLabelID)
	{
		case PLAYER_ZOOM:
			if(bSet)
			{
				ps[iPlayer].zoom=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].zoom, sActor, sPlayer);
			}
			break;

		case USERDEFS_GOD:
			if(bSet)
			{
				ud.god = lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ud.god, sActor, sPlayer);
			}
			break;

		case USERDEFS_WARP_ON:
			if(bSet)
			{
				ud.warp_on = lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ud.warp_on, sActor, sPlayer);
			}
			break;

		case USERDEFS_CASHMAN:
			if(bSet)
			{
				ud.cashman = lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ud.cashman, sActor, sPlayer);
			}
			break;

	case USERDEFS_EOG:
			if(bSet)
			{
				ud.eog = lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ud.eog, sActor, sPlayer);
			}
			break;

	case USERDEFS_SHOWALLMAP:
		if(bSet)
		{
			ud.showallmap = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.showallmap, sActor, sPlayer);
		}
		break;

	case USERDEFS_SHOW_HELP:
		if(bSet)
		{
			ud.show_help = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.show_help, sActor, sPlayer);
		}
		break;

	case USERDEFS_SCROLLMODE:
		if(bSet)
		{
			ud.scrollmode = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.scrollmode, sActor, sPlayer);
		}
		break;

	case USERDEFS_CLIPPING:
		if(bSet)
		{
			ud.clipping = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.clipping, sActor, sPlayer);
		}
		break;

//	case USERDEFS_USER_NAME:
//		if(bSet)
//		{
//			ud.user_name[MAXPLAYERS][32] = lValue;
//		}
//		else
//		{
//			SetGameVarID((int)lVar2, ud.user_name[MAXPLAYERS][32], sActor, sPlayer);
//		}
//		break;

//	case USERDEFS_RIDECULE:
//		if(bSet)
//		{
//			ud.ridecule = lValue;
//		}
//		else
//		{
//			SetGameVarID((int)lVar2, ud.ridecule, sActor, sPlayer);
//		}
//		break;

//	case USERDEFS_SAVEGAME:
//		if(bSet)
//		{
//			ud.savegame = lValue;
//		}
//		else
//		{
//			SetGameVarID((int)lVar2, ud.savegame, sActor, sPlayer);
//		}
//		break;

//	case USERDEFS_PWLOCKOUT:
//		if(bSet)
//		{
//			ud.pwlockout = lValue;
//		}
//		else
//		{
//			SetGameVarID((int)lVar2, ud.pwlockout, sActor, sPlayer);
//		}
//		break;

//	case USERDEFS_RTSNAME:
//		if(bSet)
//		{
//			ud.rtsname = lValue;
//		}
//		else
//		{
//			SetGameVarID((int)lVar2, ud.rtsname, sActor, sPlayer);
//		}
//		break;

	case USERDEFS_OVERHEAD_ON:
		if(bSet)
		{
			ud.overhead_on = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.overhead_on, sActor, sPlayer);
		}
		break;

	case USERDEFS_LAST_OVERHEAD:
		if(bSet)
		{
			ud.last_overhead = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.last_overhead, sActor, sPlayer);
		}
		break;

	case USERDEFS_SHOWWEAPONS:
		if(bSet)
		{
			ud.showweapons = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.showweapons, sActor, sPlayer);
		}
		break;


	case USERDEFS_PAUSE_ON:
		if(bSet)
		{
			ud.pause_on = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.pause_on, sActor, sPlayer);
		}
		break;

	case USERDEFS_FROM_BONUS:
		if(bSet)
		{
			ud.from_bonus = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.from_bonus, sActor, sPlayer);
		}
		break;

	case USERDEFS_CAMERASPRITE:
		if(bSet)
		{
			ud.camerasprite = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.camerasprite, sActor, sPlayer);
		}
		break;

	case USERDEFS_LAST_CAMSPRITE:
		if(bSet)
		{
			ud.last_camsprite = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.last_camsprite, sActor, sPlayer);
		}
		break;

	case USERDEFS_LAST_LEVEL:
		if(bSet)
		{
			ud.last_level = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.last_level, sActor, sPlayer);
		}
		break;

	case USERDEFS_SECRETLEVEL:
		if(bSet)
		{
			ud.secretlevel = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.secretlevel, sActor, sPlayer);
		}
		break;


	case USERDEFS_CONST_VISIBILITY:
		if(bSet)
		{
			ud.const_visibility = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.const_visibility, sActor, sPlayer);
		}
		break;

	case USERDEFS_UW_FRAMERATE:
		if(bSet)
		{
			ud.uw_framerate = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.uw_framerate, sActor, sPlayer);
		}
		break;

	case USERDEFS_CAMERA_TIME:
		if(bSet)
		{
			ud.camera_time = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.camera_time, sActor, sPlayer);
		}
		break;

	case USERDEFS_FOLFVEL:
		if(bSet)
		{
			ud.folfvel = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.folfvel, sActor, sPlayer);
		}
		break;

	case USERDEFS_FOLAVEL:
		if(bSet)
		{
			ud.folavel = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.folavel, sActor, sPlayer);
		}
		break;

	case USERDEFS_FOLX:
		if(bSet)
		{
			ud.folx = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.folx, sActor, sPlayer);
		}
		break;

	case USERDEFS_FOLY:
		if(bSet)
		{
			ud.foly = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.foly, sActor, sPlayer);
		}
		break;

	case USERDEFS_FOLA:
		if(bSet)
		{
			ud.fola = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.fola, sActor, sPlayer);
		}
		break;

	case USERDEFS_RECCNT:
		if(bSet)
		{
			ud.reccnt = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.reccnt, sActor, sPlayer);
		}
		break;


	case USERDEFS_ENTERED_NAME:
		if(bSet)
		{
			ud.entered_name = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.entered_name, sActor, sPlayer);
		}
		break;

	case USERDEFS_SCREEN_TILTING:
		if(bSet)
		{
			ud.screen_tilting = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.screen_tilting, sActor, sPlayer);
		}
		break;

	case USERDEFS_SHADOWS:
		if(bSet)
		{
			ud.shadows = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.shadows, sActor, sPlayer);
		}
		break;

	case USERDEFS_FTA_ON:
		if(bSet)
		{
			ud.fta_on = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.fta_on, sActor, sPlayer);
		}
		break;

	case USERDEFS_EXECUTIONS:
		if(bSet)
		{
			ud.executions = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.executions, sActor, sPlayer);
		}
		break;

	case USERDEFS_AUTO_RUN:
		if(bSet)
		{
			ud.auto_run = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.auto_run, sActor, sPlayer);
		}
		break;

	case USERDEFS_COORDS:
		if(bSet)
		{
			ud.coords = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.coords, sActor, sPlayer);
		}
		break;

	case USERDEFS_TICKRATE:
		if(bSet)
		{
			ud.tickrate = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.tickrate, sActor, sPlayer);
		}
		break;

	case USERDEFS_M_COOP:
		if(bSet)
		{
			ud.m_coop = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.m_coop, sActor, sPlayer);
		}
		break;

	case USERDEFS_COOP:
		if(bSet)
		{
			ud.coop = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.coop, sActor, sPlayer);
		}
		break;

	case USERDEFS_SCREEN_SIZE:
		if(bSet)
		{
			ud.screen_size = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.screen_size, sActor, sPlayer);
		}
		break;

	case USERDEFS_LOCKOUT:
		if(bSet)
		{
			ud.lockout = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.lockout, sActor, sPlayer);
		}
		break;

	case USERDEFS_CROSSHAIR:
		if(bSet)
		{
			ud.crosshair = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.crosshair, sActor, sPlayer);
		}
		break;

//	case USERDEFS_WCHOICE:
//		if(bSet)
//		{
//			ud.wchoice = lValue;
//		}
//		else
//		{
//			SetGameVarID((int)lVar2, ud.wchoice, sActor, sPlayer);
//		}
//		break;

	case USERDEFS_PLAYERAI:
		if(bSet)
		{
			ud.playerai = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.playerai, sActor, sPlayer);
		}
		break;

	case USERDEFS_RESPAWN_MONSTERS:
		if(bSet)
		{
			ud.respawn_monsters = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.respawn_monsters, sActor, sPlayer);
		}
		break;

	case USERDEFS_RESPAWN_ITEMS:
		if(bSet)
		{
			ud.respawn_items = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.respawn_items, sActor, sPlayer);
		}
		break;

	case USERDEFS_RESPAWN_INVENTORY:
		if(bSet)
		{
			ud.respawn_inventory = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.respawn_inventory, sActor, sPlayer);
		}
		break;

	case USERDEFS_RECSTAT:
		if(bSet)
		{
			ud.recstat = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.recstat, sActor, sPlayer);
		}
		break;

	case USERDEFS_MONSTERS_OFF:
		if(bSet)
		{
			ud.monsters_off = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.monsters_off, sActor, sPlayer);
		}
		break;

	case USERDEFS_BRIGHTNESS:
		if(bSet)
		{
			ud.brightness = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.brightness, sActor, sPlayer);
		}
		break;

	case USERDEFS_M_RESPAWN_ITEMS:
		if(bSet)
		{
			ud.m_respawn_items = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.m_respawn_items, sActor, sPlayer);
		}
		break;

	case USERDEFS_M_RESPAWN_MONSTERS:
		if(bSet)
		{
			ud.m_respawn_monsters = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.m_respawn_monsters, sActor, sPlayer);
		}
		break;

	case USERDEFS_M_RESPAWN_INVENTORY:
		if(bSet)
		{
			ud.m_respawn_inventory = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.m_respawn_inventory, sActor, sPlayer);
		}
		break;

	case USERDEFS_M_RECSTAT:
		if(bSet)
		{
			ud.m_recstat = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.m_recstat, sActor, sPlayer);
		}
		break;

	case USERDEFS_M_MONSTERS_OFF:
		if(bSet)
		{
			ud.m_monsters_off = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.m_monsters_off, sActor, sPlayer);
		}
		break;

	case USERDEFS_DETAIL:
		if(bSet)
		{
			ud.detail = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.detail, sActor, sPlayer);
		}
		break;

	case USERDEFS_M_FFIRE:
		if(bSet)
		{
			ud.m_ffire = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.m_ffire, sActor, sPlayer);
		}
		break;

	case USERDEFS_FFIRE:
		if(bSet)
		{
			ud.ffire = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.ffire, sActor, sPlayer);
		}
		break;

	case USERDEFS_M_PLAYER_SKILL:
		if(bSet)
		{
			ud.m_player_skill = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.m_player_skill, sActor, sPlayer);
		}
		break;

	case USERDEFS_M_LEVEL_NUMBER:
		if(bSet)
		{
			ud.m_level_number = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.m_level_number, sActor, sPlayer);
		}
		break;

	case USERDEFS_M_VOLUME_NUMBER:
		if(bSet)
		{
			ud.m_volume_number = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.m_volume_number, sActor, sPlayer);
		}
		break;

	case USERDEFS_MULTIMODE:
		if(bSet)
		{
			ud.multimode = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.multimode, sActor, sPlayer);
		}
		break;

	case USERDEFS_PLAYER_SKILL:
		if(bSet)
		{
			ud.player_skill = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.player_skill, sActor, sPlayer);
		}
		break;

	case USERDEFS_LEVEL_NUMBER:
		if(bSet)
		{
			ud.level_number = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.level_number, sActor, sPlayer);
		}
		break;

	case USERDEFS_VOLUME_NUMBER:
		if(bSet)
		{
			ud.volume_number = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.volume_number, sActor, sPlayer);
		}
		break;

	case USERDEFS_M_MARKER:
		if(bSet)
		{
			ud.m_marker = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.m_marker, sActor, sPlayer);
		}
		break;

	case USERDEFS_MARKER:
		if(bSet)
		{
			ud.marker = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.marker, sActor, sPlayer);
		}
		break;

	case USERDEFS_MOUSEFLIP:
		if(bSet)
		{
			ud.mouseflip = lValue;
		}
		else
		{
			SetGameVarID((int)lVar2, ud.mouseflip, sActor, sPlayer);
		}
		break;


			
		default:
			break;
	}
	return;
}

///////////////////////////////////////////
void DoPlayer(char bSet, long lVar1, long lLabelID, long lVar2, short sActor, short sPlayer)
{
	int iPlayer;
	long lValue;

	lValue=GetGameVarID((int)lVar2, sActor, sPlayer);
	
	if(lVar1 == g_iThisActorID )
	{
		// if they've asked for 'this', then use 'this player'...
		iPlayer=g_p;
	}
	else
	{
		iPlayer=GetGameVarID((int)lVar1, sActor, sPlayer);
	}
	
	if(iPlayer<0 || iPlayer >= MAXPLAYERS)
		return;
	
	switch(lLabelID)
	{
		case PLAYER_ZOOM:
			if(bSet)
			{
				ps[iPlayer].zoom=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].zoom, sActor, sPlayer);
			}
			break;

		case PLAYER_EXITX:
			if(bSet)
			{
				ps[iPlayer].exitx=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].exitx, sActor, sPlayer);
			}
			break;

		case PLAYER_EXITY:
			if(bSet)
			{
				ps[iPlayer].exity=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].exity, sActor, sPlayer);
			}
			break;

		case PLAYER_LOOGIEX:
			if(bSet)
			{
				ps[iPlayer].loogiex[64]=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].loogiex[64], sActor, sPlayer);
			}
			break;

		case PLAYER_LOOGIEY:
			if(bSet)
			{
				ps[iPlayer].loogiey[64]=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].loogiey[64], sActor, sPlayer);
			}
			break;

		case PLAYER_NUMLOOGS:
			if(bSet)
			{
				ps[iPlayer].numloogs=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].numloogs, sActor, sPlayer);
			}
			break;

		case PLAYER_LOOGCNT:
			if(bSet)
			{
				ps[iPlayer].loogcnt=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].loogcnt, sActor, sPlayer);
			}
			break;

		case PLAYER_POSX:
			if(bSet)
			{
				ps[iPlayer].posx=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].posx, sActor, sPlayer);
			}
			break;

		case PLAYER_POSY:
			if(bSet)
			{
				ps[iPlayer].posy=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].posy, sActor, sPlayer);
			}
			break;

		case PLAYER_POSZ:
			if(bSet)
			{
				ps[iPlayer].posz=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].posz, sActor, sPlayer);
			}
			break;

		case PLAYER_HORIZ:
			if(bSet)
			{
				ps[iPlayer].horiz=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].horiz, sActor, sPlayer);
			}
			break;

		case PLAYER_OHORIZ:
			if(bSet)
			{
				ps[iPlayer].ohoriz=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].ohoriz, sActor, sPlayer);
			}
			break;

		case PLAYER_OHORIZOFF:
			if(bSet)
			{
				ps[iPlayer].ohorizoff=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].ohorizoff, sActor, sPlayer);
			}
			break;

		case PLAYER_INVDISPTIME:
			if(bSet)
			{
				ps[iPlayer].invdisptime=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].invdisptime, sActor, sPlayer);
			}
			break;

		case PLAYER_BOBPOSX:
			if(bSet)
			{
				ps[iPlayer].bobposx=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].bobposx, sActor, sPlayer);
			}
			break;

		case PLAYER_BOBPOSY:
			if(bSet)
			{
				ps[iPlayer].bobposy=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].bobposy, sActor, sPlayer);
			}
			break;

		case PLAYER_OPOSX:
			if(bSet)
			{
				ps[iPlayer].oposx=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].oposx, sActor, sPlayer);
			}
			break;

		case PLAYER_OPOSY:
			if(bSet)
			{
				ps[iPlayer].oposy=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].oposy, sActor, sPlayer);
			}
			break;

		case PLAYER_OPOSZ:
			if(bSet)
			{
				ps[iPlayer].oposz=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].oposz, sActor, sPlayer);
			}
			break;

		case PLAYER_PYOFF:
			if(bSet)
			{
				ps[iPlayer].pyoff=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].pyoff, sActor, sPlayer);
			}
			break;

		case PLAYER_OPYOFF:
			if(bSet)
			{
				ps[iPlayer].opyoff=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].opyoff, sActor, sPlayer);
			}
			break;

		case PLAYER_POSXV:
			if(bSet)
			{
				ps[iPlayer].posxv=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].posxv, sActor, sPlayer);
			}
			break;

		case PLAYER_POSYV:
			if(bSet)
			{
				ps[iPlayer].posyv=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].posyv, sActor, sPlayer);
			}
			break;

		case PLAYER_POSZV:
			if(bSet)
			{
				ps[iPlayer].poszv=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].poszv, sActor, sPlayer);
			}
			break;

		case PLAYER_LAST_PISSED_TIME:
			if(bSet)
			{
				ps[iPlayer].last_pissed_time=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].last_pissed_time, sActor, sPlayer);
			}
			break;

		case PLAYER_TRUEFZ:
			if(bSet)
			{
				ps[iPlayer].truefz=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].truefz, sActor, sPlayer);
			}
			break;

		case PLAYER_TRUECZ:
			if(bSet)
			{
				ps[iPlayer].truecz=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].truecz, sActor, sPlayer);
			}
			break;

		case PLAYER_PLAYER_PAR:
			if(bSet)
			{
				ps[iPlayer].player_par=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].player_par, sActor, sPlayer);
			}
			break;

		case PLAYER_VISIBILITY:
			if(bSet)
			{
				ps[iPlayer].visibility=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].visibility, sActor, sPlayer);
			}
			break;

		case PLAYER_BOBCOUNTER:
			if(bSet)
			{
				ps[iPlayer].bobcounter=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].bobcounter, sActor, sPlayer);
			}
			break;

		case PLAYER_WEAPON_SWAY:
			if(bSet)
			{
				ps[iPlayer].weapon_sway=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].weapon_sway, sActor, sPlayer);
			}
			break;

		case PLAYER_PALS_TIME:
			if(bSet)
			{
				ps[iPlayer].pals_time=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].pals_time, sActor, sPlayer);
			}
			break;

		case PLAYER_RANDOMFLAMEX:
			if(bSet)
			{
				ps[iPlayer].randomflamex=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].randomflamex, sActor, sPlayer);
			}
			break;

		case PLAYER_CRACK_TIME:
			if(bSet)
			{
				ps[iPlayer].crack_time=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].crack_time, sActor, sPlayer);
			}
			break;

		case PLAYER_AIM_MODE:
			if(bSet)
			{
				ps[iPlayer].aim_mode=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].aim_mode, sActor, sPlayer);
			}
			break;

		case PLAYER_ANG:
			if(bSet)
			{
				ps[iPlayer].ang=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].ang, sActor, sPlayer);
			}
			break;

		case PLAYER_OANG:
			if(bSet)
			{
				ps[iPlayer].oang=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].oang, sActor, sPlayer);
			}
			break;

		case PLAYER_ANGVEL:
			if(bSet)
			{
				ps[iPlayer].angvel=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].angvel, sActor, sPlayer);
			}
			break;

		case PLAYER_CURSECTNUM:
			if(bSet)
			{
				ps[iPlayer].cursectnum=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].cursectnum, sActor, sPlayer);
			}
			break;

		case PLAYER_LOOK_ANG:
			if(bSet)
			{
				ps[iPlayer].look_ang=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].look_ang, sActor, sPlayer);
			}
			break;

		case PLAYER_LAST_EXTRA:
			if(bSet)
			{
				ps[iPlayer].last_extra=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].last_extra, sActor, sPlayer);
			}
			break;

		case PLAYER_SUBWEAPON:
			if(bSet)
			{
				ps[iPlayer].subweapon=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].subweapon, sActor, sPlayer);
			}
			break;

		case PLAYER_AMMO_AMOUNT:
			if(bSet)
			{
				ps[iPlayer].ammo_amount[MAX_WEAPONS]=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].ammo_amount[MAX_WEAPONS], sActor, sPlayer);
			}
			break;

		case PLAYER_WACKEDBYACTOR:
			if(bSet)
			{
				ps[iPlayer].wackedbyactor=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].wackedbyactor, sActor, sPlayer);
			}
			break;

		case PLAYER_FRAG:
			if(bSet)
			{
				ps[iPlayer].frag=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].frag, sActor, sPlayer);
			}
			break;

		case PLAYER_FRAGGEDSELF:
			if(bSet)
			{
				ps[iPlayer].fraggedself=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].fraggedself, sActor, sPlayer);
			}
			break;

		case PLAYER_CURR_WEAPON:
			if(bSet)
			{
				ps[iPlayer].curr_weapon=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].curr_weapon, sActor, sPlayer);
			}
			break;

		case PLAYER_LAST_WEAPON:
			if(bSet)
			{
				ps[iPlayer].last_weapon=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].last_weapon, sActor, sPlayer);
			}
			break;

		case PLAYER_TIPINCS:
			if(bSet)
			{
				ps[iPlayer].tipincs=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].tipincs, sActor, sPlayer);
			}
			break;

		case PLAYER_HORIZOFF:
			if(bSet)
			{
				ps[iPlayer].horizoff=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].horizoff, sActor, sPlayer);
			}
			break;

		case PLAYER_WANTWEAPONFIRE:
			if(bSet)
			{
				ps[iPlayer].wantweaponfire=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].wantweaponfire, sActor, sPlayer);
			}
			break;

		case PLAYER_HOLODUKE_AMOUNT:
			if(bSet)
			{
				ps[iPlayer].holoduke_amount=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].holoduke_amount, sActor, sPlayer);
			}
			break;

		case PLAYER_NEWOWNER:
			if(bSet)
			{
				ps[iPlayer].newowner=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].newowner, sActor, sPlayer);
			}
			break;

		case PLAYER_HURT_DELAY:
			if(bSet)
			{
				ps[iPlayer].hurt_delay=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].hurt_delay, sActor, sPlayer);
			}
			break;

		case PLAYER_HBOMB_HOLD_DELAY:
			if(bSet)
			{
				ps[iPlayer].hbomb_hold_delay=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].hbomb_hold_delay, sActor, sPlayer);
			}
			break;

		case PLAYER_JUMPING_COUNTER:
			if(bSet)
			{
				ps[iPlayer].jumping_counter=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].jumping_counter, sActor, sPlayer);
			}
			break;

		case PLAYER_AIRLEFT:
			if(bSet)
			{
				ps[iPlayer].airleft=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].airleft, sActor, sPlayer);
			}
			break;

		case PLAYER_KNEE_INCS:
			if(bSet)
			{
				ps[iPlayer].knee_incs=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].knee_incs, sActor, sPlayer);
			}
			break;

		case PLAYER_ACCESS_INCS:
			if(bSet)
			{
				ps[iPlayer].access_incs=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].access_incs, sActor, sPlayer);
			}
			break;

		case PLAYER_FTA:
			if(bSet)
			{
				ps[iPlayer].fta=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].fta, sActor, sPlayer);
			}
			break;

		case PLAYER_FTQ:
			if(bSet)
			{
				ps[iPlayer].ftq=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].ftq, sActor, sPlayer);
			}
			break;

		case PLAYER_ACCESS_WALLNUM:
			if(bSet)
			{
				ps[iPlayer].access_wallnum=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].access_wallnum, sActor, sPlayer);
			}
			break;

		case PLAYER_ACCESS_SPRITENUM:
			if(bSet)
			{
				ps[iPlayer].access_spritenum=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].access_spritenum, sActor, sPlayer);
			}
			break;

		case PLAYER_KICKBACK_PIC:
			if(bSet)
			{
				ps[iPlayer].kickback_pic=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].kickback_pic, sActor, sPlayer);
			}
			break;

		case PLAYER_GOT_ACCESS:
			if(bSet)
			{
				ps[iPlayer].got_access=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].got_access, sActor, sPlayer);
			}
			break;

		case PLAYER_WEAPON_ANG:
			if(bSet)
			{
				ps[iPlayer].weapon_ang=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].weapon_ang, sActor, sPlayer);
			}
			break;

		case PLAYER_FIRSTAID_AMOUNT:
			if(bSet)
			{
				ps[iPlayer].firstaid_amount=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].firstaid_amount, sActor, sPlayer);
			}
			break;

		case PLAYER_SOMETHINGONPLAYER:
			if(bSet)
			{
				ps[iPlayer].somethingonplayer=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].somethingonplayer, sActor, sPlayer);
			}
			break;

		case PLAYER_ON_CRANE:
			if(bSet)
			{
				ps[iPlayer].on_crane=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].on_crane, sActor, sPlayer);
			}
			break;

		case PLAYER_I:
			if(bSet)
			{
				ps[iPlayer].i=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].i, sActor, sPlayer);
			}
			break;

		case PLAYER_ONE_PARALLAX_SECTNUM:
			if(bSet)
			{
				ps[iPlayer].one_parallax_sectnum=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].one_parallax_sectnum, sActor, sPlayer);
			}
			break;

		case PLAYER_OVER_SHOULDER_ON:
			if(bSet)
			{
				ps[iPlayer].over_shoulder_on=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].over_shoulder_on, sActor, sPlayer);
			}
			break;

		case PLAYER_RANDOM_CLUB_FRAME:
			if(bSet)
			{
				ps[iPlayer].random_club_frame=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].random_club_frame, sActor, sPlayer);
			}
			break;

		case PLAYER_FIST_INCS:
			if(bSet)
			{
				ps[iPlayer].fist_incs=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].fist_incs, sActor, sPlayer);
			}
			break;

		case PLAYER_ONE_EIGHTY_COUNT:
			if(bSet)
			{
				ps[iPlayer].one_eighty_count=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].one_eighty_count, sActor, sPlayer);
			}
			break;

		case PLAYER_CHEAT_PHASE:
			if(bSet)
			{
				ps[iPlayer].cheat_phase=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].cheat_phase, sActor, sPlayer);
			}
			break;

		case PLAYER_DUMMYPLAYERSPRITE:
			if(bSet)
			{
				ps[iPlayer].dummyplayersprite=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].dummyplayersprite, sActor, sPlayer);
			}
			break;

		case PLAYER_EXTRA_EXTRA8:
			if(bSet)
			{
				ps[iPlayer].extra_extra8=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].extra_extra8, sActor, sPlayer);
			}
			break;

		case PLAYER_QUICK_KICK:
			if(bSet)
			{
				ps[iPlayer].quick_kick=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].quick_kick, sActor, sPlayer);
			}
			break;

		case PLAYER_HEAT_AMOUNT:
			if(bSet)
			{
				ps[iPlayer].heat_amount=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].heat_amount, sActor, sPlayer);
			}
			break;

		case PLAYER_ACTORSQU:
			if(bSet)
			{
				ps[iPlayer].actorsqu=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].actorsqu, sActor, sPlayer);
			}
			break;

		case PLAYER_TIMEBEFOREEXIT:
			if(bSet)
			{
				ps[iPlayer].timebeforeexit=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].timebeforeexit, sActor, sPlayer);
			}
			break;

		case PLAYER_CUSTOMEXITSOUND:
			if(bSet)
			{
				ps[iPlayer].customexitsound=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].customexitsound, sActor, sPlayer);
			}
			break;

		case PLAYER_WEAPRECS:
			if(bSet)
			{
				ps[iPlayer].weaprecs[16]=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].weaprecs[16], sActor, sPlayer);
			}
			break;

		case PLAYER_WEAPRECCNT:
			if(bSet)
			{
				ps[iPlayer].weapreccnt=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].weapreccnt, sActor, sPlayer);
			}
			break;

		case PLAYER_INTERFACE_TOGGLE_FLAG:
			if(bSet)
			{
				ps[iPlayer].interface_toggle_flag=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].interface_toggle_flag, sActor, sPlayer);
			}
			break;

		case PLAYER_ROTSCRNANG:
			if(bSet)
			{
				ps[iPlayer].rotscrnang=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].rotscrnang, sActor, sPlayer);
			}
			break;

		case PLAYER_DEAD_FLAG:
			if(bSet)
			{
				ps[iPlayer].dead_flag=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].dead_flag, sActor, sPlayer);
			}
			break;

		case PLAYER_SHOW_EMPTY_WEAPON:
			if(bSet)
			{
				ps[iPlayer].show_empty_weapon=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].show_empty_weapon, sActor, sPlayer);
			}
			break;

		case PLAYER_SCUBA_AMOUNT:
			if(bSet)
			{
				ps[iPlayer].scuba_amount=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].scuba_amount, sActor, sPlayer);
			}
			break;

		case PLAYER_JETPACK_AMOUNT:
			if(bSet)
			{
				ps[iPlayer].jetpack_amount=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].jetpack_amount, sActor, sPlayer);
			}
			break;

		case PLAYER_STEROIDS_AMOUNT:
			if(bSet)
			{
				ps[iPlayer].steroids_amount=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].steroids_amount, sActor, sPlayer);
			}
			break;

		case PLAYER_SHIELD_AMOUNT:
			if(bSet)
			{
				ps[iPlayer].shield_amount=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].shield_amount, sActor, sPlayer);
			}
			break;

		case PLAYER_HOLODUKE_ON:
			if(bSet)
			{
				ps[iPlayer].holoduke_on=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].holoduke_on, sActor, sPlayer);
			}
			break;

		case PLAYER_PYCOUNT:
			if(bSet)
			{
				ps[iPlayer].pycount=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].pycount, sActor, sPlayer);
			}
			break;

		case PLAYER_WEAPON_POS:
			if(bSet)
			{
				ps[iPlayer].weapon_pos=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].weapon_pos, sActor, sPlayer);
			}
			break;

		case PLAYER_FRAG_PS:
			if(bSet)
			{
				ps[iPlayer].frag_ps=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].frag_ps, sActor, sPlayer);
			}
			break;

		case PLAYER_TRANSPORTER_HOLD:
			if(bSet)
			{
				ps[iPlayer].transporter_hold=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].transporter_hold, sActor, sPlayer);
			}
			break;

		case PLAYER_LAST_FULL_WEAPON:
			if(bSet)
			{
				ps[iPlayer].last_full_weapon=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].last_full_weapon, sActor, sPlayer);
			}
			break;

		case PLAYER_FOOTPRINTSHADE:
			if(bSet)
			{
				ps[iPlayer].footprintshade=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].footprintshade, sActor, sPlayer);
			}
			break;

		case PLAYER_BOOT_AMOUNT:
			if(bSet)
			{
				ps[iPlayer].boot_amount=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].boot_amount, sActor, sPlayer);
			}
			break;

		case PLAYER_SCREAM_VOICE:
			if(bSet)
			{
				ps[iPlayer].scream_voice=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].scream_voice, sActor, sPlayer);
			}
			break;

		case PLAYER_GM:
			if(bSet)
			{
				ps[iPlayer].gm=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].gm, sActor, sPlayer);
			}
			break;

		case PLAYER_ON_WARPING_SECTOR:
			if(bSet)
			{
				ps[iPlayer].on_warping_sector=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].on_warping_sector, sActor, sPlayer);
			}
			break;

		case PLAYER_FOOTPRINTCOUNT:
			if(bSet)
			{
				ps[iPlayer].footprintcount=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].footprintcount, sActor, sPlayer);
			}
			break;

		case PLAYER_HBOMB_ON:
			if(bSet)
			{
				ps[iPlayer].hbomb_on=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].hbomb_on, sActor, sPlayer);
			}
			break;

		case PLAYER_JUMPING_TOGGLE:
			if(bSet)
			{
				ps[iPlayer].jumping_toggle=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].jumping_toggle, sActor, sPlayer);
			}
			break;

		case PLAYER_RAPID_FIRE_HOLD:
			if(bSet)
			{
				ps[iPlayer].rapid_fire_hold=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].rapid_fire_hold, sActor, sPlayer);
			}
			break;

		case PLAYER_ON_GROUND:
			if(bSet)
			{
				ps[iPlayer].on_ground=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].on_ground, sActor, sPlayer);
			}
			break;

		case PLAYER_NAME:
			if(bSet)
			{
				ps[iPlayer].name[32]=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].name[32], sActor, sPlayer);
			}
			break;

		case PLAYER_INVEN_ICON:
			if(bSet)
			{
				ps[iPlayer].inven_icon=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].inven_icon, sActor, sPlayer);
			}
			break;

		case PLAYER_BUTTONPALETTE:
			if(bSet)
			{
				ps[iPlayer].buttonpalette=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].buttonpalette, sActor, sPlayer);
			}
			break;

		case PLAYER_JETPACK_ON:
			if(bSet)
			{
				ps[iPlayer].jetpack_on=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].jetpack_on, sActor, sPlayer);
			}
			break;

		case PLAYER_SPRITEBRIDGE:
			if(bSet)
			{
				ps[iPlayer].spritebridge=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].spritebridge, sActor, sPlayer);
			}
			break;

		case PLAYER_LASTRANDOMSPOT:
			if(bSet)
			{
				ps[iPlayer].lastrandomspot=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].lastrandomspot, sActor, sPlayer);
			}
			break;

		case PLAYER_SCUBA_ON:
			if(bSet)
			{
				ps[iPlayer].scuba_on=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].scuba_on, sActor, sPlayer);
			}
			break;

		case PLAYER_FOOTPRINTPAL:
			if(bSet)
			{
				ps[iPlayer].footprintpal=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].footprintpal, sActor, sPlayer);
			}
			break;

		case PLAYER_HEAT_ON:
			if(bSet)
			{
				ps[iPlayer].heat_on=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].heat_on, sActor, sPlayer);
			}
			break;

		case PLAYER_HOLSTER_WEAPON:
			if(bSet)
			{
				ps[iPlayer].holster_weapon=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].holster_weapon, sActor, sPlayer);
			}
			break;

		case PLAYER_FALLING_COUNTER:
			if(bSet)
			{
				ps[iPlayer].falling_counter=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].falling_counter, sActor, sPlayer);
			}
			break;

		case PLAYER_GOTWEAPON:
			if(bSet)
			{
				ps[iPlayer].gotweapon[MAX_WEAPONS]=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].gotweapon[MAX_WEAPONS], sActor, sPlayer);
			}
			break;

		case PLAYER_REFRESH_INVENTORY:
			if(bSet)
			{
				ps[iPlayer].refresh_inventory=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].refresh_inventory, sActor, sPlayer);
			}
			break;

//		case PLAYER_PALETTE:
//			if(bSet)
//			{
//				ps[iPlayer].palette=lValue;
//			}
//			else
//			{
//				SetGameVarID((int)lVar2, ps[iPlayer].palette, sActor, sPlayer);
//			}
//			break;

		case PLAYER_TOGGLE_KEY_FLAG:
			if(bSet)
			{
				ps[iPlayer].toggle_key_flag=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].toggle_key_flag, sActor, sPlayer);
			}
			break;

		case PLAYER_KNUCKLE_INCS:
			if(bSet)
			{
				ps[iPlayer].knuckle_incs=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].knuckle_incs, sActor, sPlayer);
			}
			break;

		case PLAYER_WALKING_SND_TOGGLE:
			if(bSet)
			{
				ps[iPlayer].walking_snd_toggle=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].walking_snd_toggle, sActor, sPlayer);
			}
			break;

		case PLAYER_PALOOKUP:
			if(bSet)
			{
				ps[iPlayer].palookup=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].palookup, sActor, sPlayer);
			}
			break;

		case PLAYER_HARD_LANDING:
			if(bSet)
			{
				ps[iPlayer].hard_landing=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].hard_landing, sActor, sPlayer);
			}
			break;

		case PLAYER_MAX_SECRET_ROOMS:
			if(bSet)
			{
				ps[iPlayer].max_secret_rooms=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].max_secret_rooms, sActor, sPlayer);
			}
			break;

		case PLAYER_SECRET_ROOMS:
			if(bSet)
			{
				ps[iPlayer].secret_rooms=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].secret_rooms, sActor, sPlayer);
			}
			break;

		case PLAYER_PALS:
			if(bSet)
			{
				ps[iPlayer].pals[3]=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].pals[3], sActor, sPlayer);
			}
			break;

		case PLAYER_MAX_ACTORS_KILLED:
			if(bSet)
			{
				ps[iPlayer].max_actors_killed=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].max_actors_killed, sActor, sPlayer);
			}
			break;

		case PLAYER_ACTORS_KILLED:
			if(bSet)
			{
				ps[iPlayer].actors_killed=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].actors_killed, sActor, sPlayer);
			}
			break;

		case PLAYER_RETURN_TO_CENTER:
			if(bSet)
			{
				ps[iPlayer].return_to_center=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, ps[iPlayer].return_to_center, sActor, sPlayer);
			}
			break;

			
		default:
			break;
	}
	return;
}

////////////////////
void DoWall(char bSet, long lVar1, long lLabelID, long lVar2, short sActor, short sPlayer)
{
	int iWall;
	long lValue;

	lValue=GetGameVarID((int)lVar2, sActor, sPlayer);
	
	iWall=GetGameVarID((int)lVar1, sActor, sPlayer);
	
	if(iWall<0 || iWall >= MAXWALLS)
		return;
	
	switch(lLabelID)
	{
		case WALL_X:
			if(bSet)
			{
				wall[iWall].x=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, wall[iWall].x, sActor, sPlayer);
			}
			break;
		case WALL_Y:
			if(bSet)
			{
				wall[iWall].y=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, wall[iWall].y, sActor, sPlayer);
			}
			break;
		case WALL_POINT2:
			if(bSet)
			{
				wall[iWall].point2=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, wall[iWall].point2, sActor, sPlayer);
			}
			break;
		case WALL_NEXTWALL:
			if(bSet)
			{
				wall[iWall].nextwall=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, wall[iWall].nextwall, sActor, sPlayer);
			}
			break;
		case WALL_NEXTSECTOR:
			if(bSet)
			{
				wall[iWall].nextsector=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, wall[iWall].nextsector, sActor, sPlayer);
			}
			break;
		case WALL_CSTAT:
			if(bSet)
			{
				wall[iWall].cstat=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, wall[iWall].cstat, sActor, sPlayer);
			}
			break;
		case WALL_PICNUM:
			if(bSet)
			{
				wall[iWall].picnum=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, wall[iWall].picnum, sActor, sPlayer);
			}
			break;
		case WALL_OVERPICNUM:
			if(bSet)
			{
				wall[iWall].overpicnum=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, wall[iWall].overpicnum, sActor, sPlayer);
			}
			break;
		case WALL_SHADE:
			if(bSet)
			{
				wall[iWall].x=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, wall[iWall].shade, sActor, sPlayer);
			}
			break;
		case WALL_PAL:
			if(bSet)
			{
				wall[iWall].pal=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, wall[iWall].pal, sActor, sPlayer);
			}
			break;
		case WALL_XREPEAT:
			if(bSet)
			{
				wall[iWall].xrepeat=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, wall[iWall].xrepeat, sActor, sPlayer);
			}
			break;
		case WALL_YREPEAT:
			if(bSet)
			{
				wall[iWall].yrepeat=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, wall[iWall].yrepeat, sActor, sPlayer);
			}
			break;
		case WALL_XPANNING:
			if(bSet)
			{
				wall[iWall].xpanning=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, wall[iWall].xpanning, sActor, sPlayer);
			}
			break;
		case WALL_YPANNING:
			if(bSet)
			{
				wall[iWall].ypanning=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, wall[iWall].ypanning, sActor, sPlayer);
			}
			break;
		case WALL_LOTAG:
			if(bSet)
			{
				wall[iWall].lotag=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, wall[iWall].lotag, sActor, sPlayer);
			}
			break;
		case WALL_HITAG:
			if(bSet)
			{
				wall[iWall].hitag=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, wall[iWall].hitag, sActor, sPlayer);
			}
			break;
		case WALL_EXTRA:
			if(bSet)
			{
				wall[iWall].x=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, wall[iWall].x, sActor, sPlayer);
			}
			break;
		default:
			break;
	}
	return;
}

void DoSector(char bSet, long lVar1, long lLabelID, long lVar2, short sActor, short sPlayer)
{
	int iSector;
	long lValue;

	
	if(lVar1 == g_iThisActorID )
	{
		// if they've asked for 'this', then use 'this'...
		iSector=sprite[g_i].sectnum;
	}
	else
	{
		iSector=GetGameVarID((int)lVar1, sActor, sPlayer);
	}
	
	if(iSector<0 || iSector >= MAXSECTORS)
		return;

	lValue=GetGameVarID((int)lVar2, sActor, sPlayer);
	
	switch(lLabelID)
	{
		case SECTOR_WALLPTR:
			if(bSet)
			{
				sector[iSector].wallptr=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sector[iSector].wallptr,sActor,sPlayer);
			}
			break;
		case SECTOR_WALLNUM:
			if(bSet)
			{
				sector[iSector].wallnum=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sector[iSector].wallnum,sActor,sPlayer);
			}
			break;
		case SECTOR_CEILINGZ:
			if(bSet)
			{
				sector[iSector].ceilingz=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sector[iSector].ceilingz,sActor,sPlayer);
			}
			break;
		case SECTOR_FLOORZ:
			if(bSet)
			{
				sector[iSector].floorz=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sector[iSector].floorz,sActor,sPlayer);
			}
			break;
		case SECTOR_CEILINGSTAT:
			if(bSet)
			{
				sector[iSector].ceilingstat=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sector[iSector].ceilingstat,sActor,sPlayer);
			}
			break;
		case SECTOR_FLOORSTAT:
			if(bSet)
			{
				sector[iSector].floorstat=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sector[iSector].floorstat,sActor,sPlayer);
			}
			break;
		case SECTOR_CEILINGPICNUM:
			if(bSet)
			{
				sector[iSector].ceilingpicnum=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sector[iSector].ceilingpicnum,sActor,sPlayer);
			}
			break;
		case SECTOR_CEILINGSLOPE:
			if(bSet)
			{
				sector[iSector].ceilingheinum=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sector[iSector].ceilingheinum,sActor,sPlayer);
			}
			break;
		case SECTOR_CEILINGSHADE:
			if(bSet)
			{
				sector[iSector].ceilingshade=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sector[iSector].ceilingshade,sActor,sPlayer);
			}
			break;
		case SECTOR_CEILINGPAL:
			if(bSet)
			{
				sector[iSector].ceilingpal=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sector[iSector].ceilingpal,sActor,sPlayer);
			}
			break;
		case SECTOR_CEILINGXPANNING:
			if(bSet)
			{
				sector[iSector].ceilingxpanning=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sector[iSector].ceilingypanning,sActor,sPlayer);
			}
			break;
		case SECTOR_FLOORPICNUM:
			if(bSet)
			{
				sector[iSector].floorpicnum=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sector[iSector].floorpicnum,sActor,sPlayer);
			}
			break;
		case SECTOR_FLOORSLOPE:
			if(bSet)
			{
				sector[iSector].floorheinum=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sector[iSector].floorheinum,sActor,sPlayer);
			}
			break;
		case SECTOR_FLOORSHADE:
			if(bSet)
			{
				sector[iSector].floorshade=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sector[iSector].floorshade,sActor,sPlayer);
			}
			break;
		case SECTOR_FLOORPAL:
			if(bSet)
			{
				sector[iSector].floorpal=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sector[iSector].floorpal,sActor,sPlayer);
			}
			break;
		case SECTOR_FLOORXPANNING:
			if(bSet)
			{
				sector[iSector].floorxpanning=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sector[iSector].floorxpanning,sActor,sPlayer);
			}
			break;
		case SECTOR_FLOORYPANNING:
			if(bSet)
			{
				sector[iSector].floorypanning=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sector[iSector].floorypanning,sActor,sPlayer);
			}
			break;
		case SECTOR_VISIBILITY:
			if(bSet)
			{
				sector[iSector].visibility=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sector[iSector].visibility,sActor,sPlayer);
			}
			break;
		case SECTOR_ALIGNTO:
			if(bSet)
			{
				sector[iSector].filler=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sector[iSector].filler,sActor,sPlayer);
			}
			break;
		case SECTOR_LOTAG:
			if(bSet)
			{
				sector[iSector].lotag=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sector[iSector].lotag,sActor,sPlayer);
			}
			break;
		case SECTOR_HITAG:
			if(bSet)
			{
				sector[iSector].hitag=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sector[iSector].hitag,sActor,sPlayer);
			}
			break;
		case SECTOR_EXTRA:
			if(bSet)
			{
				sector[iSector].extra=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sector[iSector].extra,sActor,sPlayer);
			}
			
			break;
		default:
			break;
			
	}
	return;
}
void DoActor(char bSet, long lVar1, long lLabelID, long lVar2, short sActor, short sPlayer)
{
	int iActor;
	long lValue;

	lValue=GetGameVarID((int)lVar2, sActor, sPlayer);

	if(lVar1 == g_iThisActorID )
	{
		// if they've asked for 'this', then use 'this'...
		iActor=g_i;
	}
	else
	{
		iActor=GetGameVarID((int)lVar1, sActor, sPlayer);
	}
	
	if(iActor < 0 || iActor >= MAXSPRITES)
		return;
	
	switch(lLabelID)
	{
		case ACTOR_X:
			if(bSet)
			{
				sprite[iActor].x=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sprite[iActor].x,sActor,sPlayer);
			}
			break;
		case ACTOR_Y:
			if(bSet)
			{
				sprite[iActor].y=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sprite[iActor].y,sActor,sPlayer);
			}
			break;
		case ACTOR_Z:
			if(bSet)
			{
				sprite[iActor].z=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sprite[iActor].z,sActor,sPlayer);
			}
			break;
		case ACTOR_CSTAT:
			if(bSet)
			{
				sprite[iActor].cstat=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sprite[iActor].cstat,sActor,sPlayer);
			}
			break;
		case ACTOR_PICNUM:
			if(bSet)
			{
				sprite[iActor].picnum=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sprite[iActor].picnum,sActor,sPlayer);
			}
			break;
		case ACTOR_SHADE:
			if(bSet)
			{
				sprite[iActor].shade=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sprite[iActor].shade,sActor,sPlayer);
			}
			break;
		case ACTOR_PAL:
			if(bSet)
			{
				sprite[iActor].pal=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sprite[iActor].pal,sActor,sPlayer);
			}
			break;
		case ACTOR_CLIPDIST:
			if(bSet)
			{
				sprite[iActor].clipdist=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sprite[iActor].clipdist,sActor,sPlayer);
			}
			break;
		case ACTOR_DETAIL:
			if(bSet)
			{
				sprite[iActor].filler=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sprite[iActor].filler,sActor,sPlayer);
			}
			break;
		case ACTOR_XREPEAT:
			if(bSet)
			{
				sprite[iActor].xrepeat=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sprite[iActor].xrepeat,sActor,sPlayer);
			}
			break;
		case ACTOR_YREPEAT:
			if(bSet)
			{
				sprite[iActor].yrepeat=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sprite[iActor].yrepeat,sActor,sPlayer);
			}
			break;
		case ACTOR_XOFFSET:
			if(bSet)
			{
				sprite[iActor].xoffset=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sprite[iActor].xoffset,sActor,sPlayer);
			}
			break;
		case ACTOR_YOFFSET:
			if(bSet)
			{
				sprite[iActor].yoffset=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sprite[iActor].yoffset,sActor,sPlayer);
			}
			break;
		case ACTOR_SECTNUM:
			if(bSet)
			{
				sprite[iActor].sectnum=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sprite[iActor].sectnum,sActor,sPlayer);
			}
			break;
		case ACTOR_STATNUM:
			if(bSet)
			{
				sprite[iActor].statnum=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sprite[iActor].statnum,sActor,sPlayer);
			}
			break;
		case ACTOR_ANG:
			if(bSet)
			{
				sprite[iActor].ang=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sprite[iActor].ang,sActor,sPlayer);
			}
			break;
		case ACTOR_OWNER:
			if(bSet)
			{
				sprite[iActor].owner=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sprite[iActor].owner,sActor,sPlayer);
			}
			break;
		case ACTOR_XVEL:
			if(bSet)
			{
				sprite[iActor].xvel=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sprite[iActor].xvel,sActor,sPlayer);
			}
			break;
		case ACTOR_YVEL:
			if(bSet)
			{
				sprite[iActor].yvel=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sprite[iActor].yvel,sActor,sPlayer);
			}
			break;
		case ACTOR_ZVEL:
			if(bSet)
			{
				sprite[iActor].zvel=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sprite[iActor].zvel,sActor,sPlayer);
			}
			break;
		case ACTOR_LOTAG:
			if(bSet)
			{
				sprite[iActor].lotag=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sprite[iActor].lotag,sActor,sPlayer);
			}
			break;
		case ACTOR_HITAG:
			if(bSet)
			{
				sprite[iActor].hitag=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sprite[iActor].hitag,sActor,sPlayer);
			}
			break;
		case ACTOR_EXTRA:
			if(bSet)
			{
				sprite[iActor].extra=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, sprite[iActor].extra,sActor,sPlayer);
			}
			break;

		case ACTOR_HTCGG:
			if(bSet)
			{
				hittype[iActor].cgg=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, hittype[iActor].cgg, sActor, sPlayer);
			}
			break;
		case ACTOR_HTPICNUM	:
			if(bSet)
			{
				hittype[iActor].picnum=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, hittype[iActor].picnum, sActor, sPlayer);
			}
			break;
		case ACTOR_HTANG:
			if(bSet)
			{
				hittype[iActor].ang=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2, hittype[iActor].ang, sActor, sPlayer);
			}
			break;
		case ACTOR_HTEXTRA:
			if(bSet)
			{
				hittype[iActor].extra=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2,hittype[iActor].extra, sActor, sPlayer);
			}
			break;
		case ACTOR_HTOWNER:
			if(bSet)
			{
				hittype[iActor].owner=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2,hittype[iActor].owner, sActor, sPlayer);
			}
			break;
		case ACTOR_HTMOVFLAG:
			if(bSet)
			{
				hittype[iActor].movflag=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2,hittype[iActor].movflag, sActor, sPlayer);
			}
			break;
		case ACTOR_HTTEMPANG:
			if(bSet)
			{
				hittype[iActor].tempang=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2,hittype[iActor].tempang, sActor, sPlayer);
			}
			break;
		case ACTOR_HTACTORSTAYPUT:
			if(bSet)
			{
				hittype[iActor].actorstayput=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2,hittype[iActor].actorstayput, sActor, sPlayer);
			}
			break;
		case ACTOR_HTDISPICNUM:
			if(bSet)
			{
				hittype[iActor].dispicnum=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2,hittype[iActor].dispicnum, sActor, sPlayer);
			}
			break;
		case ACTOR_HTTIMETOSLEEP:
			if(bSet)
			{
				hittype[iActor].timetosleep=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2,hittype[iActor].timetosleep, sActor, sPlayer);
			}
			break;
		case ACTOR_HTFLOORZ:
			if(bSet)
			{
				hittype[iActor].floorz=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2,hittype[iActor].floorz, sActor, sPlayer);
			}
			break;
		case ACTOR_HTCEILINGZ:
			if(bSet)
			{
				hittype[iActor].ceilingz=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2,hittype[iActor].ceilingz, sActor, sPlayer);
			}
			break;
		case ACTOR_HTLASTVX:
			if(bSet)
			{
				hittype[iActor].lastvx=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2,hittype[iActor].lastvx, sActor, sPlayer);
			}
			break;
		case ACTOR_HTLASTVY:
			if(bSet)
			{
				hittype[iActor].lastvy=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2,hittype[iActor].lastvy, sActor, sPlayer);
			}
			break;
		case ACTOR_HTBPOSX:
			if(bSet)
			{
				hittype[iActor].bposx=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2,hittype[iActor].bposx, sActor, sPlayer);
			}
			break;
		case ACTOR_HTBPOSY:
			if(bSet)
			{
				hittype[iActor].bposy=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2,hittype[iActor].bposy, sActor, sPlayer);
			}
			break;
		case ACTOR_HTBPOSZ:
			if(bSet)
			{
				hittype[iActor].bposz=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2,hittype[iActor].bposz, sActor, sPlayer);
			}
			break;
		case ACTOR_HTG_T0:
			if(bSet)
			{
				hittype[iActor].temp_data[0]=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2,hittype[iActor].temp_data[0], sActor, sPlayer);
			}
			break;
		case ACTOR_HTG_T1:
			if(bSet)
			{
				hittype[iActor].temp_data[1]=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2,hittype[iActor].temp_data[1], sActor, sPlayer);
			}
			break;
		case ACTOR_HTG_T2:
			if(bSet)
			{
				hittype[iActor].temp_data[2]=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2,hittype[iActor].temp_data[2], sActor, sPlayer);
			}
			break;
		case ACTOR_HTG_T3:
			if(bSet)
			{
				hittype[iActor].temp_data[3]=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2,hittype[iActor].temp_data[3], sActor, sPlayer);
			}
			break;
		case ACTOR_HTG_T4:
			if(bSet)
			{
				hittype[iActor].temp_data[4]=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2,hittype[iActor].temp_data[4], sActor, sPlayer);
			}
			break;
		case ACTOR_HTG_T5:
			if(bSet)
			{
				hittype[iActor].temp_data[5]=lValue;
			}
			else
			{
				SetGameVarID((int)lVar2,hittype[iActor].temp_data[5], sActor, sPlayer);
			}
			break;
			
		default:
			break;
	}
	return;
}
#endif // APPVER_DN3DREV >= AV_DR_EDK20021


void AddLog(char *psz)
{
	FILE *fp;
	fp=fopen("log.log","a");
	if(!fp)
		return;
	fputs(psz,fp);
	fputs("\n",fp);
	fclose(fp);
	return;
}

#define MAXGAMEEVENTS	128
long *apScriptGameEvent[MAXGAMEEVENTS];
long *parsing_event=NULL;

bDebugFunStuff=0;

void OnEvent(int iEventID, short i,short p,long x)
{
	short og_i,og_p;
	long og_x;
	long *og_t;
	spritetype *og_sp;
	char okillit_flag;
	long *oinsptr;

	char done;

	if( iEventID >= MAXGAMEEVENTS)
	{
		AddLog("Invalid Event ID");
		return;
	}
	if( apScriptGameEvent[iEventID] == 0 )
	{
//sprintf(g_szBuf,"No event found for %d",iEventID);		
//AddLog(g_szBuf);
		return;
	}

	// save current values...
	og_i=g_i;
	og_p=g_p;
	og_x=g_x;
	og_sp=g_sp;
	og_t=g_t;
	okillit_flag=killit_flag;
	oinsptr=insptr;
	
	g_i = i;	// current sprite ID
	g_p = p;	/// current player ID
	g_x = x;	// ?
	g_sp = &sprite[g_i];
	g_t = &hittype[g_i].temp_data[0];

	insptr = (apScriptGameEvent[iEventID]);
//sprintf(g_szBuf,"Executing event for %d at %lX",iEventID, insptr);		
//AddLog(g_szBuf);

bDebugFunStuff=0;

	killit_flag = 0;
	do
		done = parse();
	while( done == 0 );

	// restore old values...
	g_i=og_i;
	g_p=og_p;
	g_x=og_x;
	g_sp=og_sp;
	g_t=og_t;
	killit_flag=okillit_flag;
	insptr=oinsptr;

bDebugFunStuff=0;
//AddLog("End of Execution");

#if 0
	if(killit_flag == 1)
	{
		if(ps[g_p].actorsqu == g_i)
			ps[g_p].actorsqu = -1;
		deletesprite(g_i);
	}
	else
	{
		move();

		if( g_sp->statnum == 1)
		{
			if( badguy(g_sp) )
			{
				if( g_sp->xrepeat > 60 ) return;
				if( ud.respawn_monsters == 1 && g_sp->extra <= 0 ) return;
			}
			else if( ud.respawn_items == 1 && (g_sp->cstat&32768) ) return;

			if(hittype[g_i].timetosleep > 1)
				hittype[g_i].timetosleep--;
			else if(hittype[g_i].timetosleep == 1)
				 changespritestat(g_i,2);
		}

		else if(g_sp->statnum == 6)
			switch(g_sp->picnum)
			{
				case RUBBERCAN:
				case EXPLODINGBARREL:
				case WOODENHORSE:
				case HORSEONSIDE:
				case CANWITHSOMETHING:
				case FIREBARREL:
				case NUKEBARREL:
				case NUKEBARRELDENTED:
				case NUKEBARRELLEAKED:
				case TRIPBOMB:
				case EGG:
					if(hittype[g_i].timetosleep > 1)
						hittype[g_i].timetosleep--;
					else if(hittype[g_i].timetosleep == 1)
						changespritestat(g_i,2);
					break;
			}
	}
#endif
}



MATTGAMEVAR aGameVars[MAXGAMEVARS];
int iGameVarCount=0;

MATTGAMEVAR aDefaultGameVars[MAXGAMEVARS];	// the 'original' values
int iDefaultGameVarCount=0;

char AddGameVar(char *pszLabel, long lValue, unsigned long dwFlags);


void ReadGameVars(long fil)
{
	int i;
	long l;

#if (APPVER_DN3DREV == AV_DR_EDK20021)
AddLog("Reading Game Vars from File");
#endif

	 kdfread(&l,sizeof(l),1,fil);
	 kdfread(g_szBuf,l,1,fil);
	 g_szBuf[l]=0;
#if (APPVER_DN3DREV == AV_DR_EDK20021)
 AddLog(g_szBuf);
#endif

	 FreeGameVars();	// nuke 'em all...
#if (APPVER_DN3DREV == AV_DR_EDK20021)
sprintf(g_szBuf,"CP:%s %d",__FILE__,__LINE__);
AddLog(g_szBuf);
#endif
	 
	 kdfread(&iGameVarCount,sizeof(iGameVarCount),1,fil);
	 
	 for(i=0;i<iGameVarCount;i++)
	 {
		 kdfread(&(aGameVars[i]),sizeof(MATTGAMEVAR),1,fil);
	 }

#if (APPVER_DN3DREV == AV_DR_EDK20021)
sprintf(g_szBuf,"CP:%s %d",__FILE__,__LINE__);
AddLog(g_szBuf);
#endif
	 for(i=0;i<iGameVarCount;i++)
	 {
	 
		if(aGameVars[i].dwFlags & GAMEVAR_FLAG_PERPLAYER)
		{
			aGameVars[i].plValues=malloc(sizeof(long) * MAXPLAYERS);
		}
		else if( aGameVars[i].dwFlags & GAMEVAR_FLAG_PERACTOR)
		{
			aGameVars[i].plValues=malloc(sizeof(long) * MAXSPRITES);
		}
		else
		{
			// else nothing 'extra...'
			aGameVars[i].plValues=NULL;
		}
	 }
	 
#if (APPVER_DN3DREV == AV_DR_EDK20021)
sprintf(g_szBuf,"CP:%s %d",__FILE__,__LINE__);
AddLog(g_szBuf);
#endif
	 InitGameVarPointers();

#if (APPVER_DN3DREV == AV_DR_EDK20021)
sprintf(g_szBuf,"CP:%s %d",__FILE__,__LINE__);
AddLog(g_szBuf);
#endif
	 for(i=0;i<iGameVarCount;i++)
	 {
	 
		if(aGameVars[i].dwFlags & GAMEVAR_FLAG_PERPLAYER)
		{
//sprintf(g_szBuf,"Reading value array for %s (%d)",aGameVars[i].szLabel,sizeof(long) * MAXPLAYERS);
//AddLog(g_szBuf);
			kdfread(aGameVars[i].plValues,sizeof(long) * MAXPLAYERS, 1, fil);
		}
		else if( aGameVars[i].dwFlags & GAMEVAR_FLAG_PERACTOR)
		{
//sprintf(g_szBuf,"Reading value array for %s (%d)",aGameVars[i].szLabel,sizeof(long) * MAXSPRITES);
//AddLog(g_szBuf);
			kdfread(aGameVars[i].plValues,sizeof(long) * MAXSPRITES, 1, fil);
		}
		// else nothing 'extra...'
	 }

#if (APPVER_DN3DREV == AV_DR_EDK20021)
sprintf(g_szBuf,"CP:%s %d",__FILE__,__LINE__);
AddLog(g_szBuf);
#endif
	 kdfread(apScriptGameEvent,sizeof(apScriptGameEvent),1,fil);
	 for(i=0;i<MAXGAMEEVENTS;i++)
		 if(apScriptGameEvent[i])
	 {
		 l = (long)apScriptGameEvent[i]+(long)&script[0];
		 apScriptGameEvent[i] = (long *)l;
	 }
	 
#if (APPVER_DN3DREV >= AV_DR_EDK20021)
	 kdfread(&g_bEnhanced, sizeof(g_bEnhanced), 1, fil);
#endif
	 
#if (APPVER_DN3DREV == AV_DR_EDK20021)
sprintf(g_szBuf,"CP:%s %d",__FILE__,__LINE__);
AddLog(g_szBuf);
#endif
	 kdfread(&l,sizeof(l),1,fil);
	 kdfread(g_szBuf,l,1,fil);
	 g_szBuf[l]=0;
#if (APPVER_DN3DREV == AV_DR_EDK20021)
 AddLog(g_szBuf);
#endif
	 

#if 0 
	 {
		 FILE *fp;
AddLog("Dumping Vars...");		 
		 fp=fopen("xxx.txt","w");
		 if(fp)
		 {
			 DumpGameVars(fp);
			 fclose(fp);
		 }
AddLog("Done Dumping...");		 
	 }
#endif
	 
}

void SaveGameVars(FILE *fil)
{
	int i;
	long l;
	
//	 AddLog("Saving Game Vars to File");
	 sprintf(g_szBuf,"Matt Saettler");
	 l=strlen(g_szBuf);
	 dfwrite(&l,sizeof(l),1,fil);
	 dfwrite(g_szBuf,l,1,fil);
	 
	 dfwrite(&iGameVarCount,sizeof(iGameVarCount),1,fil);

	 for(i=0;i<iGameVarCount;i++)
	 {
		 dfwrite(&(aGameVars[i]),sizeof(MATTGAMEVAR),1,fil);
	 }
	 
//	   dfwrite(&aGameVars,sizeof(aGameVars),1,fil);

	 for(i=0;i<iGameVarCount;i++)
	 {
		if(aGameVars[i].dwFlags & GAMEVAR_FLAG_PERPLAYER)
		{
//sprintf(g_szBuf,"Writing value array for %s (%d)",aGameVars[i].szLabel,sizeof(long) * MAXPLAYERS);
//AddLog(g_szBuf);
			dfwrite(aGameVars[i].plValues,sizeof(long) * MAXPLAYERS, 1, fil);
		}
		else if( aGameVars[i].dwFlags & GAMEVAR_FLAG_PERACTOR)
		{
//sprintf(g_szBuf,"Writing value array for %s (%d)",aGameVars[i].szLabel,sizeof(long) * MAXSPRITES);
//AddLog(g_szBuf);
			dfwrite(aGameVars[i].plValues,sizeof(long) * MAXSPRITES, 1, fil);
		}
		// else nothing 'extra...'
	 }

	 for(i=0;i<MAXGAMEEVENTS;i++)
		 if(apScriptGameEvent[i])
	 {
		l = (long)apScriptGameEvent[i]-(long)&script[0];
		apScriptGameEvent[i] = (long *)l;
	 }
	 dfwrite(apScriptGameEvent,sizeof(apScriptGameEvent),1,fil);
	 for(i=0;i<MAXGAMEEVENTS;i++)
		 if(apScriptGameEvent[i])
	 {
		 l = (long)apScriptGameEvent[i]+(long)&script[0];
		 apScriptGameEvent[i] = (long *)l;
	 }

#if (APPVER_DN3DREV >= AV_DR_EDK20021)
	 dfwrite(&g_bEnhanced, sizeof(g_bEnhanced), 1, fil);
#endif
	 
	 sprintf(g_szBuf,"EOF: Matt Saettler");
	 l=strlen(g_szBuf);
	 dfwrite(&l,sizeof(l),1,fil);
	 dfwrite(g_szBuf,l,1,fil);
 
}

void DumpGameVars(FILE *fp)
{
	int i;
	if(!fp)
	{
		return;
	}
	fprintf(fp,"// Current Game Definitions\n\n");
	fprintf(fp,"\ninclude enhance.con\n");
	
	fprintf(fp,"\n");
	for(i=0;i<iGameVarCount;i++)
	{
		if(aGameVars[i].dwFlags & (GAMEVAR_FLAG_SECRET) )
		{
			continue; // do nothing...
		}
		else
		{
			fprintf(fp,"gamedef %s ",aGameVars[i].szLabel);
					
			if(aGameVars[i].dwFlags & (GAMEVAR_FLAG_PLONG) )
			{
				fprintf(fp," 0");
			}
			else
			{
				fprintf(fp,"%d",aGameVars[i].lValue);
			}
			if(aGameVars[i].dwFlags & (GAMEVAR_FLAG_PERPLAYER) )
			{
				fprintf(fp," GAMEVAR_FLAG_PERPLAYER");
			}
			else if(aGameVars[i].dwFlags & (GAMEVAR_FLAG_PERACTOR) )
			{
				fprintf(fp," GAMEVAR_FLAG_PERACTOR");
			}
			else
			{
				fprintf(fp," %d",aGameVars[i].dwFlags & (GAMEVAR_FLAG_USER_MASK));
			}
			fprintf(fp," // ");
			if(aGameVars[i].dwFlags & (GAMEVAR_FLAG_PLONG)
			   || aGameVars[i].dwFlags & (GAMEVAR_FLAG_SYSTEM)
			  )
			{
				fprintf(fp," (system)");
			}
			if(aGameVars[i].dwFlags & (GAMEVAR_FLAG_READONLY) )
			{
				fprintf(fp," (read only)");
			}
			fprintf(fp,"\n");
		}
	}
	fprintf(fp,"\n// end of game definitions\n");	
}

void ResetGameVars(void)
{
	int i;

//AddLog("Reset Game Vars");	
	FreeGameVars();
	for(i=0;i<iDefaultGameVarCount;i++)
	{
//sprintf(g_szBuf,"Resetting %d: '%s' to %ld",i,aDefaultGameVars[i].szLabel,
//		aDefaultGameVars[i].lValue
//		);
//AddLog(g_szBuf);
		AddGameVar(aDefaultGameVars[i].szLabel,
				   aDefaultGameVars[i].lValue,
				   aDefaultGameVars[i].dwFlags | GAMEVAR_FLAG_NODEFAULT
				   );
	}

}

//BOOL
char AddGameVar(char *pszLabel, long lValue, unsigned long dwFlags)
{
	
	int i;
	int j;

	int b=0;

//sprintf(g_szBuf,"AddGameVar(%s, %d, %X)",pszLabel, lValue, dwFlags);
//AddLog(g_szBuf);

	if(strlen(pszLabel) > (MAXVARLABEL-1) )
	{
		warning++;
		printf("  * WARNING.(L%ld) Variable Name '%s' too long (max is %d)\n",line_number,pszLabel, MAXVARLABEL-1);
		return 0;
	}
	for(i=0;i<iGameVarCount;i++)
	{
		if( strcmp(pszLabel,aGameVars[i].szLabel) == 0 )
		{
			// found it...
			if(	  (aGameVars[i].dwFlags & GAMEVAR_FLAG_DEFAULT)
			   || (aGameVars[i].dwFlags & GAMEVAR_FLAG_SYSTEM)
			  )
			{
//sprintf(g_szBuf,"Replacing %s at %d",pszLabel,i);
//AddLog(g_szBuf);
//b=1;
				// it's OK to replace
				break;
			}
			else
			{
				// it's a duplicate in error
				error++;
				printf("  * ERROR.(L%ld) Duplicate Game definition '%s' ignored.\n",line_number,pszLabel);
				return 0;
			}
		}
	}
	if( i < MAXGAMEVARS)
	{
		// Set values
		if(aGameVars[i].dwFlags & GAMEVAR_FLAG_SYSTEM)
		{
//if(b)
//{
//sprintf(g_szBuf,"CP:%s %d",__FILE__,__LINE__);
//AddLog(g_szBuf);
//}
			// if existing is system, they only get to change default value....
			aGameVars[i].lValue=lValue;	
			if(!(dwFlags & GAMEVAR_FLAG_NODEFAULT))
			{
				aDefaultGameVars[i].lValue=lValue;
			}
		}
		else
		{
			strcpy(aGameVars[i].szLabel,pszLabel);
			aGameVars[i].dwFlags=dwFlags;
			aGameVars[i].lValue=lValue;
			if(!(dwFlags & GAMEVAR_FLAG_NODEFAULT))
			{
				strcpy(aDefaultGameVars[i].szLabel,pszLabel);
				aDefaultGameVars[i].dwFlags=dwFlags;
				aDefaultGameVars[i].lValue=lValue;
			}
		}
		
		if(i==iGameVarCount)
		{
			// we're adding a new one.
			iGameVarCount++;
			if(!(dwFlags & GAMEVAR_FLAG_NODEFAULT))
			{
				iDefaultGameVarCount++;
			}
		}
		if(aGameVars[i].plValues && !(aGameVars[i].dwFlags & GAMEVAR_FLAG_SYSTEM))
		{
			// only free if not system
			free(aGameVars[i].plValues);
			aGameVars[i].plValues=NULL;
		}
		if(aGameVars[i].dwFlags & GAMEVAR_FLAG_PERPLAYER)
		{
			if(!aGameVars[i].plValues)
			{
				aGameVars[i].plValues=malloc(sizeof(long) * MAXPLAYERS);
			}
			for(j=0;j<MAXPLAYERS;j++)
			{
				aGameVars[i].plValues[j]=lValue;
			}
		}
		else if( aGameVars[i].dwFlags & GAMEVAR_FLAG_PERACTOR)
		{
			if(!aGameVars[i].plValues)
			{
				aGameVars[i].plValues=malloc(sizeof(long) * MAXSPRITES);
			}
			for(j=0;j<MAXSPRITES;j++)
			{
				aGameVars[i].plValues[j]=lValue;
			}
		}
		return 1;

	}
	else
	{
		// no room to add...
		return 0;
	}
 
}

int GetGameID(char *szGameLabel)
{
	int i;
	for(i=0;i<iGameVarCount;i++)
	{
		if( strcmp(szGameLabel, aGameVars[i].szLabel) == 0 )
		{
			return i;
		}
	}
	return -1;	
}

long GetGameVarID(int id, short sActor, short sPlayer)
{
	if(id<0 || id >= iGameVarCount)
	{
		AddLog("GetGameVarID: Invalid Game ID");
		return -1;
	}
#if (APPVER_DN3DREV >= AV_DR_EDK20021)
	if( id == g_iThisActorID )
	{
		return sActor;
	}
#endif
	if( aGameVars[id].dwFlags & GAMEVAR_FLAG_PERPLAYER )
	{
		// for the current player
		if(sPlayer >=0 && sPlayer < MAXPLAYERS)
		{
//sprintf(g_szBuf,"GetGameVarID( %d, %d, %d) returns %ld\n",id,sActor,sPlayer, aGameVars[id].plValues[sPlayer]);
//AddLog(g_szBuf);
			return aGameVars[id].plValues[sPlayer];
		}
		else
		{
			return aGameVars[id].lValue;
		}
	}
	else if( aGameVars[id].dwFlags & GAMEVAR_FLAG_PERACTOR )
	{
		// for the current actor
		if(sActor >= 0 && sActor <=MAXSPRITES)
		{
			return aGameVars[id].plValues[sActor];
		}
		else
		{
			return aGameVars[id].lValue;
		}
	}
	else if( aGameVars[id].dwFlags & GAMEVAR_FLAG_PLONG )
	{
		return	*((long*)aGameVars[id].lValue);
	}
	else
	{
		return aGameVars[id].lValue;
	}
	
}

void SetGameVarID(int id, long lValue, short sActor, short sPlayer)
{
	if(id<0 || id >= iGameVarCount)
	{
		AddLog("Invalid Game ID");
		return;
	}
//sprintf(g_szBuf,"SGVI: %d ('%s') to %ld for %d %d",id,aGameVars[id].szLabel,lValue,sActor,sPlayer);
//AddLog(g_szBuf);
	if( aGameVars[id].dwFlags & GAMEVAR_FLAG_PERPLAYER )
	{
		// for the current player
		aGameVars[id].plValues[sPlayer]=lValue;
	}
	else if( aGameVars[id].dwFlags & GAMEVAR_FLAG_PERACTOR )
	{
		// for the current actor
		aGameVars[id].plValues[sActor]=lValue;
	}
	else if( aGameVars[id].dwFlags & GAMEVAR_FLAG_PLONG )
	{
		// set the value at pointer
		*((long*)aGameVars[id].lValue)=lValue;
	}
	else
	{
		aGameVars[id].lValue=lValue;
	}
	
}

long GetGameVar(char *szGameLabel, long lDefault, short sActor, short sPlayer)
{
	int i;
	for(i=0;i<iGameVarCount;i++)
	{
		if( strcmp(szGameLabel, aGameVars[i].szLabel) == 0 )
		{
			return GetGameVarID(i, sActor, sPlayer);
		}
	}
	return lDefault;
	
}

long *GetGameValuePtr(char *szGameLabel)
{
	int i;
	for(i=0;i<iGameVarCount;i++)
	{
		if( strcmp(szGameLabel, aGameVars[i].szLabel) == 0 )
		{
			if(aGameVars[i].dwFlags & (GAMEVAR_FLAG_PERACTOR | GAMEVAR_FLAG_PERPLAYER))
			{
				if(!aGameVars[i].plValues)
				{
					AddLog("INTERNAL ERROR: NULL array !!!");
				}
				return aGameVars[i].plValues;
			}
			return &(aGameVars[i].lValue);
		}
	}
//sprintf(g_szBuf,"Could not find value '%s'\n",szGameLabel);
//AddLog(g_szBuf);
	return NULL;
	
}

long GetDefID(char *szGameLabel)
{
	int i;
	for(i=0;i<iGameVarCount;i++)
	{
		if( strcmp(szGameLabel, aGameVars[i].szLabel) == 0 )
		{
			return i;
		}
	}
	return -1;
	
}

#if 0
#define MAXLABELSIZE	32
static aszLabel[MAXLABELSIZE];

void GetGameVarLabel(void)
{
	long i;

	while( isalnum(*textptr) == 0 )
	{
		if(*textptr == 0x0a) line_number++;
		textptr++;
		if( *textptr == 0)
			return;
	}

	i = 0;
	while( ispecial(*textptr) == 0	&& i < (MAXLABELSIZE-1))
		aszLabel[i++] = *(textptr++);

	aszLabel[i]= 0;
}
#endif
#endif

short getincangle(short a,short na)
{
	a &= 2047;
	na &= 2047;

	if(klabs(a-na) < 1024)
		return (na-a);
	else
	{
		if(na > 1024) na -= 2048;
		if(a > 1024) a -= 2048;

		na -= 2048;
		a -= 2048;
		return (na-a);
	}
}

char ispecial(char c)
{
	if(c == 0x0a)
	{
		line_number++;
		return 1;
	}

	if(c == ' ' || c == 0x0d)
		return 1;

	return 0;
}

char isaltok(char c)
{
	return ( isalnum(c) || c == '{' || c == '}' || c == '/' || c == '*' || c == '-' || c == '_' || c == '.');
}

void getglobalz(short i)
{
	long hz,lz,zr;

	spritetype *s = &sprite[i];

	if( s->statnum == 10 || s->statnum == 6 || s->statnum == 2 || s->statnum == 1 || s->statnum == 4)
	{
		if(s->statnum == 4)
			zr = 4L;
		else zr = 127L;

		getzrange(s->x,s->y,s->z-(FOURSLEIGHT),s->sectnum,&hittype[i].ceilingz,&hz,&hittype[i].floorz,&lz,zr,CLIPMASK0);

		if( (lz&49152) == 49152 && (sprite[lz&(MAXSPRITES-1)].cstat&48) == 0 )
		{
			lz &= (MAXSPRITES-1);
			if( badguy(&sprite[lz]) && sprite[lz].pal != 1)
			{
				if( s->statnum != 4 )
				{
					hittype[i].dispicnum = -4; // No shadows on actors
					s->xvel = -256;
					ssp(i,CLIPMASK0);
				}
			}
			else if(sprite[lz].picnum == APLAYER && badguy(s) )
			{
				hittype[i].dispicnum = -4; // No shadows on actors
				s->xvel = -256;
				ssp(i,CLIPMASK0);
			}
			else if(s->statnum == 4 && sprite[lz].picnum == APLAYER)
				if(s->owner == lz)
			{
				hittype[i].ceilingz = sector[s->sectnum].ceilingz;
				hittype[i].floorz	= sector[s->sectnum].floorz;
			}
		}
	}
	else
	{
		hittype[i].ceilingz = sector[s->sectnum].ceilingz;
		hittype[i].floorz	= sector[s->sectnum].floorz;
	}
}


void makeitfall(short i)
{
	spritetype *s = &sprite[i];
	long hz,lz,c;

	if( floorspace(s->sectnum) )
		c = 0;
	else
	{
		if( ceilingspace(s->sectnum) || sector[s->sectnum].lotag == 2)
			c = gc/6;
		else c = gc;
	}

	if( ( s->statnum == 1 || s->statnum == 10 || s->statnum == 2 || s->statnum == 6 ) )
		getzrange(s->x,s->y,s->z-(FOURSLEIGHT),s->sectnum,&hittype[i].ceilingz,&hz,&hittype[i].floorz,&lz,127L,CLIPMASK0);
	else
	{
		hittype[i].ceilingz = sector[s->sectnum].ceilingz;
		hittype[i].floorz	= sector[s->sectnum].floorz;
	}

	if( s->z < hittype[i].floorz-(FOURSLEIGHT) )
	{
		if( sector[s->sectnum].lotag == 2 && s->zvel > 3122 )
			s->zvel = 3144;
		if(s->zvel < 6144)
			s->zvel += c;
		else s->zvel = 6144;
		s->z += s->zvel;
	}
	if( s->z >= hittype[i].floorz-(FOURSLEIGHT) )
	{
		s->z = hittype[i].floorz - FOURSLEIGHT;
		s->zvel = 0;
	}
}

#if (APPVER_DN3DREV >= AV_DR_EDK20021)
long getlabelid(LABELS *pLabel, char *psz)
{
	// find the label psz in the table pLabel.
	// returns the ID for the label, or -1
	
	long l=-1;
	int i;

	for(i=0;pLabel[i].lId >=0 ; i++)
	{
		if(!stricmp(pLabel[i].name,psz))
		{
			l= pLabel[i].lId;
			break;	// stop for loop
		}
	}
	return l;
}
#endif


void getlabel(void)
{
	long i;

	while( isalnum(*textptr) == 0 )
	{
		if(*textptr == 0x0a) line_number++;
		textptr++;
		if( *textptr == 0)
			return;
	}

	i = 0;
#ifdef EDUKE
	while( ispecial(*textptr) == 0 && *textptr!=']' )
#else
	while( ispecial(*textptr) == 0 )
#endif
		label[(labelcnt<<6)+i++] = *(textptr++);

	label[(labelcnt<<6)+i] = 0;
}

long keyword(void)
{
	long i;
	char *temptextptr;

	temptextptr = textptr;

	while( isaltok(*temptextptr) == 0 )
	{
		temptextptr++;
		if( *temptextptr == 0 )
			return 0;
	}

	i = 0;
	while( isaltok(*temptextptr) )
	{
		tempbuf[i] = *(temptextptr++);
		i++;
	}
	tempbuf[i] = 0;

	for(i=0;i<NUMKEYWORDS;i++)
		if( strcmp( tempbuf,keyw[i]) == 0 )
			return i;

	return -1;
}

long transword(void) //Returns its code #
{
	long i, l;

	while( isaltok(*textptr) == 0 )
	{
		if(*textptr == 0x0a) line_number++;
		if( *textptr == 0 )
			return -1;
		textptr++;
	}

	l = 0;
	while( isaltok(*(textptr+l)) )
	{
		tempbuf[l] = textptr[l];
		l++;
	}
	tempbuf[l] = 0;

	for(i=0;i<NUMKEYWORDS;i++)
	{
		if( strcmp( tempbuf,keyw[i]) == 0 )
		{
			*scriptptr = i;
			textptr += l;
			scriptptr++;
			return i;
		}
	}

	textptr += l;

	if( tempbuf[0] == '{' && tempbuf[1] != 0)
		printf("  * ERROR!(L%ld) Expecting a SPACE or CR between '{' and '%s'.\n",line_number,tempbuf+1);
	else if( tempbuf[0] == '}' && tempbuf[1] != 0)
		printf("  * ERROR!(L%ld) Expecting a SPACE or CR between '}' and '%s'.\n",line_number,tempbuf+1);
	else if( tempbuf[0] == '/' && tempbuf[1] == '/' && tempbuf[2] != 0 )
		printf("  * ERROR!(L%ld) Expecting a SPACE between '//' and '%s'.\n",line_number,tempbuf+2);
	else if( tempbuf[0] == '/' && tempbuf[1] == '*' && tempbuf[2] != 0 )
		printf("  * ERROR!(L%ld) Expecting a SPACE between '/*' and '%s'.\n",line_number,tempbuf+2);
	else if( tempbuf[0] == '*' && tempbuf[1] == '/' && tempbuf[2] != 0 )
		printf("  * ERROR!(L%ld) Expecting a SPACE between '*/' and '%s'.\n",line_number,tempbuf+2);
	else printf("  * ERROR!(L%ld) Expecting key word, but found '%s'.\n",line_number,tempbuf);

	error++;
	return -1;
}

void transnum(void)
{
	long i, l;

	while( isaltok(*textptr) == 0 )
	{
		if(*textptr == 0x0a) line_number++;
		textptr++;
		if( *textptr == 0 )
			return;
	}


	l = 0;
	while( isaltok(*(textptr+l)) )
	{
		tempbuf[l] = textptr[l];
		l++;
	}
	tempbuf[l] = 0;

	for(i=0;i<NUMKEYWORDS;i++)
		if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
	{
		error++;
		printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
		textptr+=l;
	}


	for(i=0;i<labelcnt;i++)
	{
		if( strcmp(tempbuf,label+(i<<6)) == 0 )
		{
			*scriptptr = labelcode[i];
			scriptptr++;
			textptr += l;
			return;
		}
	}

	if( isdigit(*textptr) == 0 && *textptr != '-')
	{
		printf("  * ERROR!(L%ld) Parameter '%s' is undefined.\n",line_number,tempbuf);
		error++;
		textptr+=l;
		return;
	}

	*scriptptr = atol(textptr);
	scriptptr++;

	textptr += l;
}


char parsecommand(void)
{
	long i, j, k, *tempscrptr;
	char done, *origtptr, temp_ifelse_check, tw;
	short temp_line_number;
	int fp;

#ifdef WW2
	if( (error+warning) > 12 || ( *textptr == '\0' ) || ( *(textptr+1) == '\0' ) ) return 1;
#else
	if( error > 12 || ( *textptr == '\0' ) || ( *(textptr+1) == '\0' ) ) return 1;
#endif	

	tw = transword();

	switch(tw)
	{
		default:
		case -1:
			return 0; //End
		case 39:	  //Rem endrem
			scriptptr--;
			j = line_number;
			do
			{
				textptr++;
				if(*textptr == 0x0a) line_number++;
				if( *textptr == 0 )
				{
					printf("  * ERROR!(L%ld) Found '/*' with no '*/'.\n",j,label+(labelcnt<<6));
					error++;
					return 0;
				}
			}
			while( *textptr != '*' || *(textptr+1) != '/' );
			textptr+=2;
			return 0;
		case 17:
			if( parsing_actor == 0 && parsing_state == 0 )
			{
				getlabel();
				scriptptr--;
				labelcode[labelcnt] = (long) scriptptr;
				labelcnt++;

				parsing_state = 1;

				return 0;
			}

			getlabel();

			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			for(j=0;j<labelcnt;j++)
			{
				if( strcmp(label+(j<<6),label+(labelcnt<<6)) == 0 )
				{
					*scriptptr = labelcode[j];
					break;
				}
			}

			if(j==labelcnt)
			{
				printf("  * ERROR!(L%ld) State '%s' not found.\n",line_number,label+(labelcnt<<6));
				error++;
			}
			scriptptr++;
			return 0;

		case 15:
		case 92:
		case 87:
		case 89:
		case 93:
			transnum();
			return 0;
			
#if (APPVER_DN3DREV >= AV_DR_EDK20021)
		case CON_IFSOUND:
			transnum();
			tempscrptr = scriptptr;
			scriptptr++; //Leave a spot for the fail location
			return 0;

#endif
		case 18:
			if( parsing_state == 0 )
			{
				printf("  * ERROR!(L%ld) Found 'ends' with no 'state'.\n",line_number);
				error++;
			}
//			  else
			{
				if( num_squigilly_brackets > 0 )
				{
					printf("  * ERROR!(L%ld) Found more '{' than '}' before 'ends'.\n",line_number);
					error++;
				}
				if( num_squigilly_brackets < 0 )
				{
					printf("  * ERROR!(L%ld) Found more '}' than '{' before 'ends'.\n",line_number);
					error++;
				}
				parsing_state = 0;
			}
			return 0;
#ifdef WW2
		case CON_GAMEVAR:
			// syntax: gamevar <var1> <initial value> <flags>
			// defines var1 and sets initial value.
			// flags are used to define usage
			// (see top of this files for flags)
//printf("Got gamedef. Getting Label. '%.20s'\n",textptr);
			getlabel();	//GetGameVarLabel();
//printf("Got Label '%.20s'\n",textptr);
			// Check to see it's already defined

			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

#if 0			
			for(i=0;i<iGameVarCount;i++)
			{
				if( strcmp(label+(labelcnt<<6),apszGameVarLabel[i]) == 0 )
				{
					warning++;
					printf("  * WARNING.(L%ld) Duplicate Game definition '%s' ignored.\n",line_number,label+(labelcnt<<6));
					break;
				}
			}
#endif			

//printf("Translating number  '%.20s'\n",textptr);			
			transnum();	// get initial value
//printf("Done Translating number.	'%.20s'\n",textptr);

			transnum();	// get flags
//sprintf(g_szBuf,"Adding GameVar='%s', val=%l, flags=%lX",label+(labelcnt<<6),
//		*(scriptptr-2), *(scriptptr-1));
//AddLog(g_szBuf);
			
			AddGameVar(label+(labelcnt<<6),*(scriptptr-2),
#if (APPVER_DN3DREV < AV_DR_EDK20021)
					   (*(scriptptr-2))
#else
					   (*(scriptptr-1))
#endif
						// can't define default or secret
					   & (~( GAMEVAR_FLAG_DEFAULT | GAMEVAR_FLAG_SECRET))
					  );
//AddLog("Added gamevar");
			scriptptr -= 3;	// no need to save in script...
			return 0;
#endif			
		case 19:
//printf("Got definition. Getting Label. '%.20s'\n",textptr);
			getlabel();
//printf("Got label. '%.20s'\n",textptr);
			// Check to see it's already defined

			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			for(i=0;i<labelcnt;i++)
			{
				if( strcmp(label+(labelcnt<<6),label+(i<<6)) == 0 )
				{
					warning++;
					printf("  * WARNING.(L%ld) Duplicate definition '%s' ignored.\n",line_number,label+(labelcnt<<6));
					break;
				}
			}

//printf("Translating. '%.20s'\n",textptr);
			transnum();
//printf("Translated. '%.20s'\n",textptr);
			if(i == labelcnt)
			{
//				printf("Defining Definition '%s' to be '%d'\n",label+(labelcnt<<6),*(scriptptr-1));
				labelcode[labelcnt++] = *(scriptptr-1);
			}
			scriptptr -= 2;
			return 0;
		case 14:

			for(j = 0;j < 4;j++)
			{
				if( keyword() == -1 )
					transnum();
				else break;
			}

			while(j < 4)
			{
				*scriptptr = 0;
				scriptptr++;
				j++;
			}
			return 0;

		case 32:
			if( parsing_actor || parsing_state )
			{
				transnum();

				j = 0;
				while(keyword() == -1)
				{
					transnum();
					scriptptr--;
					j |= *scriptptr;
				}
				*scriptptr = j;
				scriptptr++;
			}
			else
			{
				scriptptr--;
				getlabel();
				// Check to see it's already defined

				for(i=0;i<NUMKEYWORDS;i++)
					if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

				for(i=0;i<labelcnt;i++)
					if( strcmp(label+(labelcnt<<6),label+(i<<6)) == 0 )
					{
						warning++;
						printf("  * WARNING.(L%ld) Duplicate move '%s' ignored.\n",line_number,label+(labelcnt<<6));
						break;
					}
				if(i == labelcnt)
					labelcode[labelcnt++] = (long) scriptptr;
				for(j=0;j<2;j++)
				{
					if(keyword() >= 0) break;
					transnum();
				}
				for(k=j;k<2;k++)
				{
					*scriptptr = 0;
					scriptptr++;
				}
			}
			return 0;

		case 54:
			{
				// NOTE: this doesn't get stored in the PCode...
				
// music 1 stalker.mid dethtoll.mid streets.mid watrwld1.mid snake1.mid
//	  thecall.mid ahgeez.mid dethtoll.mid streets.mid watrwld1.mid snake1.mid
				scriptptr--;
				transnum(); // Volume Number (0/4)
				scriptptr--;

				k = *scriptptr-1;

				if(k >= 0) // if it's background music
				{
					i = 0;
					// get the file name...
					while(keyword() == -1)
					{
						while( isaltok(*textptr) == 0 )
						{
							if(*textptr == 0x0a) line_number++;
							textptr++;
							if( *textptr == 0 ) break;
						}
						j = 0;
						while( isaltok(*(textptr+j)) )
						{
							music_fn[k][i][j] = textptr[j];
							j++;
						}
						music_fn[k][i][j] = '\0';
						textptr += j;
						if(i > 9) break;
						i++;
					}
				}
				else
				{
					i = 0;
					while(keyword() == -1)
					{
						while( isaltok(*textptr) == 0 )
						{
							if(*textptr == 0x0a) line_number++;
							textptr++;
							if( *textptr == 0 ) break;
						}
						j = 0;
						while( isaltok(*(textptr+j)) )
						{
							env_music_fn[i][j] = textptr[j];
							j++;
						}
						env_music_fn[i][j] = '\0';

						textptr += j;
						if(i > 9) break;
						i++;
					}
				}
			}
			return 0;
		case 55:
			scriptptr--;
			while( isaltok(*textptr) == 0 )
			{
				if(*textptr == 0x0a) line_number++;
				textptr++;
				if( *textptr == 0 ) break;
			}
			j = 0;
			while( isaltok(*textptr) )
			{
				tempbuf[j] = *(textptr++);
				j++;
			}
			tempbuf[j] = '\0';

			fp = kopen4load(tempbuf,loadfromgrouponly);
			if(fp == 0)
			{
				error++;
				printf("  * ERROR!(L%ld) Could not find '%s'.\n",line_number,label+(labelcnt<<6));
				return 0;
			}

			j = kfilelength(fp);

			printf("Including: '%s'.\n",tempbuf);

			temp_line_number = line_number;
			line_number = 1;
			temp_ifelse_check = checking_ifelse;
			checking_ifelse = 0;
			origtptr = textptr;
			textptr = last_used_text+last_used_size;

			*(textptr+j) = 0;

			kread(fp,(char *)textptr,j);
			kclose(fp);

//sprintf(g_szBuf,"CP:%s %d",__FILE__,__LINE__);
//AddLog(g_szBuf);
			do
				done = parsecommand();
			while( done == 0 );

			textptr = origtptr;
			total_lines += line_number;
			line_number = temp_line_number;
			checking_ifelse = temp_ifelse_check;
//sprintf(g_szBuf,"CP:%s %d",__FILE__,__LINE__);
//AddLog(g_szBuf);

			return 0;
		case 24:
			if( parsing_actor || parsing_state )
				transnum();
			else
			{
				scriptptr--;
				getlabel();

				for(i=0;i<NUMKEYWORDS;i++)
					if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
					{
						error++;
						printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
						return 0;
					}

				for(i=0;i<labelcnt;i++)
					if( strcmp(label+(labelcnt<<6),label+(i<<6)) == 0 )
					{
						warning++;
						printf("  * WARNING.(L%ld) Duplicate ai '%s' ignored.\n",line_number,label+(labelcnt<<6));
						break;
					}

				if(i == labelcnt)
					labelcode[labelcnt++] = (long) scriptptr;

				for(j=0;j<3;j++)
				{
					if(keyword() >= 0) break;
					if(j == 2)
					{
						k = 0;
						while(keyword() == -1)
						{
							transnum();
							scriptptr--;
							k |= *scriptptr;
						}
						*scriptptr = k;
						scriptptr++;
						return 0;
					}
					else transnum();
				}
				for(k=j;k<3;k++)
				{
					*scriptptr = 0;
					scriptptr++;
				}
			}
			return 0;

		case 7:
			if( parsing_actor || parsing_state )
				transnum();
			else
			{
				scriptptr--;
				getlabel();
				// Check to see it's already defined

				for(i=0;i<NUMKEYWORDS;i++)
					if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
					{
						error++;
						printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
						return 0;
					}

				for(i=0;i<labelcnt;i++)
					if( strcmp(label+(labelcnt<<6),label+(i<<6)) == 0 )
					{
						warning++;
#if (APPVER_DN3DREV < AV_DR_WW2GI10)
						printf("  * WARNING.(L%ld) Duplicate action '%s' ignored.\n",line_number,label+(labelcnt<<6));
#else
						printf("  * WARNING.(L%ld) Duplicate event '%s' ignored.\n",line_number,label+(labelcnt<<6));
#endif
						break;
					}

				if(i == labelcnt)
					labelcode[labelcnt++] = (long) scriptptr;

				for(j=0;j<5;j++)
				{
					if(keyword() >= 0) break;
					transnum();
				}
				for(k=j;k<5;k++)
				{
					*scriptptr = 0;
					scriptptr++;
				}
			}
			return 0;

		case 1:
			if( parsing_state )
			{
				printf("  * ERROR!(L%ld) Found 'actor' within 'state'.\n",line_number);
				error++;
			}

			if( parsing_actor )
			{
				printf("  * ERROR!(L%ld) Found 'actor' within 'actor'.\n",line_number);
				error++;
			}

			num_squigilly_brackets = 0;
			scriptptr--;
			parsing_actor = scriptptr;

			transnum();
			scriptptr--;
			actorscrptr[*scriptptr] = parsing_actor;

			for(j=0;j<4;j++)
			{
				*(parsing_actor+j) = 0;
				if(j == 3)
				{
					j = 0;
					while(keyword() == -1)
					{
						transnum();
						scriptptr--;
						j |= *scriptptr;
					}
					*scriptptr = j;
					scriptptr++;
					break;
				}
				else
				{
					if(keyword() >= 0)
					{
						scriptptr += (4-j);
						break;
					}
					transnum();

					*(parsing_actor+j) = *(scriptptr-1);
				}
			}

			checking_ifelse = 0;

			return 0;

#ifdef WW2
		case CON_ONEVENT:
			if( parsing_state )
			{
#if (APPVER_DN3DREV < AV_DR_EDK20021)
				printf("  * ERROR!(L%ld) Found 'useritem' within 'state'.\n",line_number);
#else
				printf("  * ERROR!(L%ld) Found 'onevent' within 'state'.\n",line_number);
#endif
				error++;
			}

			if( parsing_actor )
			{
#if (APPVER_DN3DREV < AV_DR_EDK20021)
				printf("  * ERROR!(L%ld) Found 'useritem' within 'actor'.\n",line_number);
#else
				printf("  * ERROR!(L%ld) Found 'onevent' within 'actor'.\n",line_number);
#endif
				error++;
			}

			num_squigilly_brackets = 0;
			scriptptr--;
			parsing_event = scriptptr;
			parsing_actor = scriptptr;

			transnum();
			scriptptr--;
			j= *scriptptr;	// type of event
//sprintf(g_szBuf,"Adding Event for %d at %lX",j, parsing_event);
//AddLog(g_szBuf);
			if(j>=MAXGAMEEVENTS || j < 0)
			{
				printf("  * ERROR!(L%ld) Invalid Event ID.\n",line_number);
				error++;
				return 0;
			}
			apScriptGameEvent[j]=parsing_event;

			checking_ifelse = 0;

			return 0;
#ifdef EDUKE
		case CON_EVENTLOADACTOR:

			if( parsing_state )
			{
				printf("  * ERROR!(L%ld) Found '%s' within 'state'.\n",keyw[tw],line_number);
				error++;
			}

			if( parsing_actor )
			{
				printf("  * ERROR!(L%ld) Found '%s' within 'actor'.\n",keyw[tw],line_number);
				error++;
			}

			num_squigilly_brackets = 0;
			scriptptr--;
			parsing_actor = scriptptr;

			transnum();
			scriptptr--;
			actorLoadEventScrptr[*scriptptr] = parsing_actor;

			checking_ifelse = 0;

			return 0;
#endif // EDUKE			
#endif // WW2GI

		case 98:

			if( parsing_state )
			{
#if (APPVER_DN3DREV < AV_DR_EDK20021)
				printf("  * ERROR!(L%ld) Found 'useritem' within 'state'.\n",line_number);
#else
				printf("  * ERROR!(L%ld) Found 'useractor' within 'state'.\n",line_number);
#endif
				error++;
			}

			if( parsing_actor )
			{
#if (APPVER_DN3DREV < AV_DR_EDK20021)
				printf("  * ERROR!(L%ld) Found 'useritem' within 'actor'.\n",line_number);
#else
				printf("  * ERROR!(L%ld) Found 'useractor' within 'actor'.\n",line_number);
#endif
				error++;
			}

			num_squigilly_brackets = 0;
			scriptptr--;
			parsing_actor = scriptptr;

			transnum();
			scriptptr--;
			j = *scriptptr;

			transnum();
			scriptptr--;
			actorscrptr[*scriptptr] = parsing_actor;
			actortype[*scriptptr] = j;

			for(j=0;j<4;j++)
			{
				*(parsing_actor+j) = 0;
				if(j == 3)
				{
					j = 0;
					while(keyword() == -1)
					{
						transnum();
						scriptptr--;
						j |= *scriptptr;
					}
					*scriptptr = j;
					scriptptr++;
					break;
				}
				else
				{
					if(keyword() >= 0)
					{
						scriptptr += (4-j);
						break;
					}
					transnum();

					*(parsing_actor+j) = *(scriptptr-1);
				}
			}

			checking_ifelse = 0;

			return 0;

		case 11:
		case 13:
		case 25:
		case 31:
		case 40:
		case 52:
		case 69:
		case 74:
		case 77:
		case 80:
		case 86:
		case 88:
		case 68:
		case 100:
		case 101:
		case 102:
		case 103:
		case 105:
		case 110:
#ifdef EDUKE
		case CON_ESPAWN:
#endif
			transnum();
			return 0;

		case 2:
		case 23:
		case 28:
		case 99:
		case 37:
		case 48:
		case 58:
			transnum();
			transnum();
			break;
		case 50:
			transnum();
			transnum();
			transnum();
			transnum();
			transnum();
			break;
		case 10:
			if( checking_ifelse )
			{
				checking_ifelse--;
				tempscrptr = scriptptr;
				scriptptr++; //Leave a spot for the fail location
				parsecommand();
				*tempscrptr = (long) scriptptr;
			}
			else
			{
				scriptptr--;
				error++;
				printf("  * ERROR!(L%ld) Found 'else' with no 'if'.\n",line_number);
			}

			return 0;
#ifdef EDUKE
		case CON_SETSECTOR:
		case CON_GETSECTOR:
		{
			long lLabelID;
			// syntax getsector[<var>].x <VAR>
			// gets the value of sector[<var>].xxx into <VAR>
			
			// now get name of .xxx
			while((*textptr != '['))
			{
				textptr++;
			}
			if(*textptr == '[')
				textptr++;
		
			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
//printf("found label of '%s'\n",	label+(labelcnt<<6));

			// Check to see if it's a keyword
			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
//printf("Label '%s' ID is %d\n",label+(labelcnt<<6), i);
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
#if 0
			if(aGameVars[i].dwFlags & GAMEVAR_FLAG_READONLY)
			{
				error++;
				printf("  * ERROR!(L%ld) Variable '%s' is read-only.\n",line_number,label+(labelcnt<<6));
				return 0;
				
			}
#endif			
			*scriptptr++=i;	// the ID of the DEF (offset into array...)

			// now get name of .xxx
			while(*textptr != '.')
			{
				if(*textptr == 0xa)
					break;
				if(!*textptr)
					break;
				
				textptr++;
			}
			if(*textptr!='.')
			{
				error++;
				printf("  * ERROR!(L%ld) Syntax error\n",line_number);
				return 0;
			
			}
			textptr++;
			/// now pointing at 'xxx'
			getlabel();
//printf("found xxx label of '%s'\n",	label+(labelcnt<<6));

			lLabelID=getlabelid(sectorlabels,label+(labelcnt<<6));

			if(lLabelID == -1 )
			{
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not recognized.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
			*scriptptr++=lLabelID;

			// now at target VAR...
			
			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
//printf("found label of '%s'\n",	label+(labelcnt<<6));

			// Check to see if it's a keyword
			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
//printf("Label '%s' ID is %d\n",label+(labelcnt<<6), i);
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
#if 1
			if(tw == CON_GETSECTOR && aGameVars[i].dwFlags & GAMEVAR_FLAG_READONLY)
			{
				error++;
				printf("  * ERROR!(L%ld) Variable '%s' is read-only.\n",line_number,label+(labelcnt<<6));
				return 0;
				
			}
#endif			
			*scriptptr++=i;	// the ID of the DEF (offset into array...)

			break;
		}
		case CON_FINDNEARACTOR:
		{
			// syntax findnearactor <type> <maxdist> <getvar>
			// gets the sprite ID of the nearest actor within max dist
			// that is of <type> into <getvar>
			// -1 for none found

			transnum();	// get <type>

			transnum(); // get maxdist
			
			// target var
			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
//printf("found label of '%s'\n",	label+(labelcnt<<6));

			// Check to see if it's a keyword
			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
//printf("Label '%s' ID is %d\n",label+(labelcnt<<6), i);
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
#if 1
			if(aGameVars[i].dwFlags & GAMEVAR_FLAG_READONLY)
			{
				error++;
				printf("  * ERROR!(L%ld) Variable '%s' is read-only.\n",line_number,label+(labelcnt<<6));
				return 0;
				
			}
#endif			
			*scriptptr++=i;	// the ID of the DEF (offset into array...)
			
			break;
		}
		case CON_FINDNEARACTORVAR:
		{
			// syntax findnearactorvar <type> <maxdistvar> <getvar>
			// gets the sprite ID of the nearest actor within max dist
			// that is of <type> into <getvar>
			// -1 for none found

			transnum();	// get <type>
						
			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
//printf("found label of '%s'\n",	label+(labelcnt<<6));

			// Check to see if it's a keyword
			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
//printf("Label '%s' ID is %d\n",label+(labelcnt<<6), i);
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
#if 0
			if(aGameVars[i].dwFlags & GAMEVAR_FLAG_READONLY)
			{
				error++;
				printf("  * ERROR!(L%ld) Variable '%s' is read-only.\n",line_number,label+(labelcnt<<6));
				return 0;
				
			}
#endif			
			*scriptptr++=i;	// the ID of the DEF (offset into array...)
			
			// target var
			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
//printf("found label of '%s'\n",	label+(labelcnt<<6));

			// Check to see if it's a keyword
			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
//printf("Label '%s' ID is %d\n",label+(labelcnt<<6), i);
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
#if 1
			if(aGameVars[i].dwFlags & GAMEVAR_FLAG_READONLY)
			{
				error++;
				printf("  * ERROR!(L%ld) Variable '%s' is read-only.\n",line_number,label+(labelcnt<<6));
				return 0;
				
			}
#endif			
			*scriptptr++=i;	// the ID of the DEF (offset into array...)
			
			break;
		}
		case CON_SQRT:
		{
			// syntax sqrt <invar> <outvar>
			// gets the sqrt of invar into outvar
						
			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
//printf("found label of '%s'\n",	label+(labelcnt<<6));

			// Check to see if it's a keyword
			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
//printf("Label '%s' ID is %d\n",label+(labelcnt<<6), i);
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
#if 0
			if(aGameVars[i].dwFlags & GAMEVAR_FLAG_READONLY)
			{
				error++;
				printf("  * ERROR!(L%ld) Variable '%s' is read-only.\n",line_number,label+(labelcnt<<6));
				return 0;
				
			}
#endif			
			*scriptptr++=i;	// the ID of the DEF (offset into array...)
			
			// target var
			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
//printf("found label of '%s'\n",	label+(labelcnt<<6));

			// Check to see if it's a keyword
			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
//printf("Label '%s' ID is %d\n",label+(labelcnt<<6), i);
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
#if 1
			if(aGameVars[i].dwFlags & GAMEVAR_FLAG_READONLY)
			{
				error++;
				printf("  * ERROR!(L%ld) Variable '%s' is read-only.\n",line_number,label+(labelcnt<<6));
				return 0;
				
			}
#endif			
			*scriptptr++=i;	// the ID of the DEF (offset into array...)
			
			break;
		}
		case CON_SETWALL:
		case CON_GETWALL:
		{
			long lLabelID;
			// syntax getwall[<var>].x <VAR>
			// gets the value of wall[<var>].xxx into <VAR>
			
			// now get name of .xxx
			while((*textptr != '['))
			{
				textptr++;
			}
			if(*textptr == '[')
				textptr++;
		
			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
//printf("found label of '%s'\n",	label+(labelcnt<<6));

			// Check to see if it's a keyword
			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
//printf("Label '%s' ID is %d\n",label+(labelcnt<<6), i);
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
#if 0
			if(aGameVars[i].dwFlags & GAMEVAR_FLAG_READONLY)
			{
				error++;
				printf("  * ERROR!(L%ld) Variable '%s' is read-only.\n",line_number,label+(labelcnt<<6));
				return 0;
				
			}
#endif			
			*scriptptr++=i;	// the ID of the DEF (offset into array...)

			// now get name of .xxx
			while(*textptr != '.')
			{
				if(*textptr == 0xa)
					break;
				if(!*textptr)
					break;
				
				textptr++;
			}
			if(*textptr!='.')
			{
				error++;
				printf("  * ERROR!(L%ld) Syntax error\n",line_number);
				return 0;
			
			}
			textptr++;
			/// now pointing at 'xxx'
			getlabel();
//printf("found xxx label of '%s'\n",	label+(labelcnt<<6));

			lLabelID=getlabelid(walllabels,label+(labelcnt<<6));

			if(lLabelID == -1 )
			{
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not recognized.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
			*scriptptr++=lLabelID;

			// now at target VAR...
			
			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
//printf("found label of '%s'\n",	label+(labelcnt<<6));

			// Check to see if it's a keyword
			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
//printf("Label '%s' ID is %d\n",label+(labelcnt<<6), i);
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
#if 1
			if(tw == CON_GETWALL && aGameVars[i].dwFlags & GAMEVAR_FLAG_READONLY)
			{
				error++;
				printf("  * ERROR!(L%ld) Variable '%s' is read-only.\n",line_number,label+(labelcnt<<6));
				return 0;
				
			}
#endif			
			*scriptptr++=i;	// the ID of the DEF (offset into array...)

			break;
		}
		case CON_SETPLAYER:
		case CON_GETPLAYER:
		{
			long lLabelID;
			// syntax getwall[<var>].x <VAR>
			// gets the value of wall[<var>].xxx into <VAR>
			
			// now get name of .xxx
			while((*textptr != '['))
			{
				textptr++;
			}
			if(*textptr == '[')
				textptr++;
		
			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
//printf("found label of '%s'\n",	label+(labelcnt<<6));

			// Check to see if it's a keyword
			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
//printf("Label '%s' ID is %d\n",label+(labelcnt<<6), i);
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
#if 0
			if(aGameVars[i].dwFlags & GAMEVAR_FLAG_READONLY)
			{
				error++;
				printf("  * ERROR!(L%ld) Variable '%s' is read-only.\n",line_number,label+(labelcnt<<6));
				return 0;
				
			}
#endif			
			*scriptptr++=i;	// the ID of the DEF (offset into array...)

			// now get name of .xxx
			while(*textptr != '.')
			{
				if(*textptr == 0xa)
					break;
				if(!*textptr)
					break;
				
				textptr++;
			}
			if(*textptr!='.')
			{
				error++;
				printf("  * ERROR!(L%ld) Syntax error\n",line_number);
				return 0;
			
			}
			textptr++;
			/// now pointing at 'xxx'
			getlabel();
//printf("found xxx label of '%s'\n",	label+(labelcnt<<6));

			lLabelID=getlabelid(playerlabels,label+(labelcnt<<6));

			if(lLabelID == -1 )
			{
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not recognized.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
			*scriptptr++=lLabelID;

			// now at target VAR...
			
			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
//printf("found label of '%s'\n",	label+(labelcnt<<6));

			// Check to see if it's a keyword
			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
//printf("Label '%s' ID is %d\n",label+(labelcnt<<6), i);
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
#if 1
			if(tw == CON_GETPLAYER && aGameVars[i].dwFlags & GAMEVAR_FLAG_READONLY)
			{
				error++;
				printf("  * ERROR!(L%ld) Variable '%s' is read-only.\n",line_number,label+(labelcnt<<6));
				return 0;
				
			}
#endif			
			*scriptptr++=i;	// the ID of the DEF (offset into array...)

			break;
		}
		case CON_SETUSERDEF:
		case CON_GETUSERDEF:
		{
			long lLabelID;
			// syntax [gs]etuserdef.x <VAR>
			// gets the value of ud.xxx into <VAR>
			
			// now get name of .xxx
			while(*textptr != '.')
			{
				if(*textptr == 0xa)
					break;
				if(!*textptr)
					break;
				
				textptr++;
			}
			if(*textptr!='.')
			{
				error++;
				printf("  * ERROR!(L%ld) Syntax error\n",line_number);
				return 0;
			
			}
			textptr++;
			/// now pointing at 'xxx'
			getlabel();
//printf("found xxx label of '%s'\n",	label+(labelcnt<<6));

			lLabelID=getlabelid(userdefslabels,label+(labelcnt<<6));

			if(lLabelID == -1 )
			{
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not recognized.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
			*scriptptr++=lLabelID;

			// now at target VAR...
			
			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
//printf("found label of '%s'\n",	label+(labelcnt<<6));

			// Check to see if it's a keyword
			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
//printf("Label '%s' ID is %d\n",label+(labelcnt<<6), i);
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
#if 1
			if(tw == CON_GETPLAYER && aGameVars[i].dwFlags & GAMEVAR_FLAG_READONLY)
			{
				error++;
				printf("  * ERROR!(L%ld) Variable '%s' is read-only.\n",line_number,label+(labelcnt<<6));
				return 0;
				
			}
#endif			
			*scriptptr++=i;	// the ID of the DEF (offset into array...)

			break;
		}
		case CON_SETACTORVAR:
		case CON_GETACTORVAR:
		{
			// syntax [gs]etactorvar[<var>].<varx> <VAR>
			// gets the value of the per-actor variable varx into VAR
			
			// now get name of <var>
			while((*textptr != '['))
			{
				textptr++;
			}
			if(*textptr == '[')
				textptr++;
		
			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
//printf("found label of '%s'\n",	label+(labelcnt<<6));

			// Check to see if it's a keyword
			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
//printf("Label '%s' ID is %d\n",label+(labelcnt<<6), i);
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
#if 0
			if(aGameVars[i].dwFlags & GAMEVAR_FLAG_READONLY)
			{
				error++;
				printf("  * ERROR!(L%ld) Variable '%s' is read-only.\n",line_number,label+(labelcnt<<6));
				return 0;
				
			}
#endif			
			*scriptptr++=i;	// the ID of the DEF (offset into array...)

			// now get name of .<varx>
			while(*textptr != '.')
			{
				if(*textptr == 0xa)
					break;
				if(!*textptr)
					break;
				
				textptr++;
			}
			if(*textptr!='.')
			{
				error++;
				printf("  * ERROR!(L%ld) Syntax error\n",line_number);
				return 0;
			
			}
			textptr++;
			/// now pointing at 'xxx'

			
			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
//printf("found label of '%s'\n",	label+(labelcnt<<6));

			// Check to see if it's a keyword
			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
//printf("Label '%s' ID is %d\n",label+(labelcnt<<6), i);
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
#if 1
			if(tw == CON_SETACTORVAR && aGameVars[i].dwFlags & GAMEVAR_FLAG_READONLY)
			{
				error++;
				printf("  * ERROR!(L%ld) Variable '%s' is read-only.\n",line_number,label+(labelcnt<<6));
				return 0;
				
			}
			if(tw == CON_SETACTORVAR && !(aGameVars[i].dwFlags & GAMEVAR_FLAG_PERACTOR))
			{
				error++;
				printf("  * ERROR!(L%ld) Variable '%s' is not per-actor.\n",line_number,label+(labelcnt<<6));
				return 0;
				
			}
#endif			
			*scriptptr++=i;	// the ID of the DEF (offset into array...)

			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
//printf("found label of '%s'\n",	label+(labelcnt<<6));

			// Check to see if it's a keyword
			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
//printf("Label '%s' ID is %d\n",label+(labelcnt<<6), i);
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
#if 1
			if(tw == CON_GETACTORVAR && aGameVars[i].dwFlags & GAMEVAR_FLAG_READONLY)
			{
				error++;
				printf("  * ERROR!(L%ld) Variable '%s' is read-only.\n",line_number,label+(labelcnt<<6));
				return 0;
				
			}
#endif			
			*scriptptr++=i;	// the ID of the DEF (offset into array...)

			break;
		}
		case CON_SETACTOR:
		case CON_GETACTOR:
		{
			long lLabelID;
			// syntax getsector[<var>].x <VAR>
			// gets the value of sector[<var>].xxx into <VAR>
			
			// now get name of .xxx
			while((*textptr != '['))
			{
				textptr++;
			}
			if(*textptr == '[')
				textptr++;
		
			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
//printf("found label of '%s'\n",	label+(labelcnt<<6));

			// Check to see if it's a keyword
			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
//printf("Label '%s' ID is %d\n",label+(labelcnt<<6), i);
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
#if 0
			if(aGameVars[i].dwFlags & GAMEVAR_FLAG_READONLY)
			{
				error++;
				printf("  * ERROR!(L%ld) Variable '%s' is read-only.\n",line_number,label+(labelcnt<<6));
				return 0;
				
			}
#endif			
			*scriptptr++=i;	// the ID of the DEF (offset into array...)

			// now get name of .xxx
			while(*textptr != '.')
			{
				if(*textptr == 0xa)
					break;
				if(!*textptr)
					break;
				
				textptr++;
			}
			if(*textptr!='.')
			{
				error++;
				printf("  * ERROR!(L%ld) Syntax error\n",line_number);
				return 0;
			
			}
			textptr++;
			/// now pointing at 'xxx'
			getlabel();
//printf("found xxx label of '%s'\n",	label+(labelcnt<<6));

			lLabelID=getlabelid(actorlabels,label+(labelcnt<<6));

			if(lLabelID == -1 )
			{
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not recognized.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
			*scriptptr++=lLabelID;

			// now at target VAR...
			
			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
//printf("found label of '%s'\n",	label+(labelcnt<<6));

			// Check to see if it's a keyword
			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
//printf("Label '%s' ID is %d\n",label+(labelcnt<<6), i);
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
#if 1
			if(tw == CON_GETACTOR && aGameVars[i].dwFlags & GAMEVAR_FLAG_READONLY)
			{
				error++;
				printf("  * ERROR!(L%ld) Variable '%s' is read-only.\n",line_number,label+(labelcnt<<6));
				return 0;
				
			}
#endif			
			*scriptptr++=i;	// the ID of the DEF (offset into array...)

			break;
		}
		case CON_ESPAWNVAR:
			// syntax: espawnvar <Var1>
			// spawns the sprite of type ID and sets RETURN to spawned sprite ID
			// FALL THROUGH:
		case CON_LOCKPLAYER:
			// syntax: lockplayer	<var1>
			// sets locks the player controls for <var1> ticks
			
//printf("Found lockplayer at line= %ld\n",line_number);

			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
//printf("found label of '%s'\n",	label+(labelcnt<<6));

			// Check to see if it's a keyword
			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
//printf("Label '%s' ID is %d\n",label+(labelcnt<<6), i);
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
			if(aGameVars[i].dwFlags & GAMEVAR_FLAG_READONLY)
			{
				error++;
				printf("  * ERROR!(L%ld) Variable '%s' is read-only.\n",line_number,label+(labelcnt<<6));
				return 0;
				
			}
			*scriptptr++=i;	// the ID of the DEF (offset into array...)
	
			return 0;
#endif
#ifdef EDUKE
		case CON_ENHANCED:
		{
			long k;
			// we are enhanced, baby...
			if(g_bEnhanced)
			{
				printf("  * ERROR!(L%ld) Multiple 'enhanced' commands.	There can be only one..\n",line_number);
				error++;
			}
			g_bEnhanced=1;

			// don't store in pCode...
			scriptptr--;
//printf("We are enhanced, baby...\n");			
			transnum();
			k = *(scriptptr-1);
			scriptptr--;
			if(k > VERSIONCHECK)
			{
				printf("  * ERROR:	This CON Code requires at least Build %ld, but we are only Build %ld\n",k,(long)VERSIONCHECK);
				error++;
			}
			break;
		}
#endif			
#ifdef WW2
		case CON_SETVAR:
		case CON_ADDVAR:
#ifdef EDUKE
		case CON_SUBVAR:
		case CON_RANDVAR:
		case CON_MULVAR:
		case CON_DIVVAR:
		case CON_MODVAR:
		case CON_ANDVAR:
		case CON_ORVAR:
#endif
			// syntax: [rand|add|set]var	<var1> <const1>
			// sets var1 to const1
			// adds const1 to var1 (const1 can be negative...)
//printf("Found [add|set]var at line= %ld\n",line_number);

			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
//printf("found label of '%s'\n",	label+(labelcnt<<6));

			// Check to see if it's a keyword
			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
//printf("Label '%s' ID is %d\n",label+(labelcnt<<6), i);
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
			if(aGameVars[i].dwFlags & GAMEVAR_FLAG_READONLY)
			{
				error++;
				printf("  * ERROR!(L%ld) Variable '%s' is read-only.\n",line_number,label+(labelcnt<<6));
				return 0;
				
			}
			*scriptptr++=i;	// the ID of the DEF (offset into array...)
			
			transnum();	// the number to check against...
			return 0;

		case CON_SETVARVAR:
		case CON_ADDVARVAR:
#ifdef EDUKE
		case CON_SUBVARVAR:
		case CON_MULVARVAR:
		case CON_DIVVARVAR:
		case CON_MODVARVAR:
		case CON_ANDVARVAR:
		case CON_ORVARVAR:
#endif
			// syntax: [add|set]varvar <var1> <var2>
			// sets var1 = var2
			// adds var1 and var2 with result in var1
//printf("Found [set|addd]varvar at line= %ld\n",line_number);

			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
//printf("found label1 of '%s'\n",	label+(labelcnt<<6));

			// Check to see if it's a keyword
			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
//printf("Label '%s' ID is %d\n",label+(labelcnt<<6), i);
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
			if(aGameVars[i].dwFlags & GAMEVAR_FLAG_READONLY)
			{
				error++;
				printf("  * ERROR!(L%ld) Variable '%s' is read-only.\n",line_number,label+(labelcnt<<6));
				return 0;
				
			}
			*scriptptr++=i;	// the ID of the DEF (offset into array...)
			
			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
//printf("found label2 of '%s'\n",	label+(labelcnt<<6));

			// Check to see if it's a keyword
			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
//printf("Label '%s' ID is %d\n",label+(labelcnt<<6), i);
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
#ifndef EDUKE
// this was a bug:	second var can be RO because it is source
			if(aGameVars[i].dwFlags & GAMEVAR_FLAG_READONLY)
			{
				error++;
				printf("  * ERROR!(L%ld) Variable '%s' is read-only.\n",line_number,label+(labelcnt<<6));
				return 0;
				
			}
#endif			
			*scriptptr++=i;	// the ID of the DEF (offset into array...)
			return 0;
			
		case CON_IFVARVARG:
		case CON_IFVARVARL:
		case CON_IFVARVARE:
#if (APPVER_DN3DREV >= AV_DR_EDK20021)
		case CON_IFVARVARN:
		case CON_IFVARVARAND:
#endif

			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
			// Check to see it's a keyword

			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
			*scriptptr++=i;	// the ID of the DEF (offset into array...)
			
			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
			// Check to see it's a keyword

			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}
			
			i=GetDefID(label+(labelcnt<<6));
//printf("Label '%s' ID is %d\n",label+(labelcnt<<6), i);
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
			*scriptptr++=i;	// the ID of the DEF (offset into array...)
		
			tempscrptr = scriptptr;
			scriptptr++; //Leave a spot for the fail location

			// eat comments
			do
			{
				j = keyword();
				if(j == 20 || j == 39)
					parsecommand();
			} while(j == 20 || j == 39);

			parsecommand();

			*tempscrptr = (long) scriptptr;

			checking_ifelse++;
			return 0;
#if (APPVER_DN3DREV >= AV_DR_EDK20021)
		case CON_SPGETLOTAG:
		case CON_SPGETHITAG:
		case CON_SECTGETLOTAG:
		case CON_SECTGETHITAG:
		case CON_GETTEXTUREFLOOR:
		case CON_GETTEXTURECEILING:
			// no paramaters...
			return 0;
		case CON_STARTTRACK:
			// one parameter (track#)
			transnum();
			return 0;
		case CON_GETTEXTUREWALL:
			error++;
			printf("  * ERROR!(L%ld) Command  '%s' is not yet implemented.\n",line_number,tempbuf);
			return 0;
#endif
		case CON_IFVARL:
		case CON_IFVARG:
		case CON_IFVARE:
#if (APPVER_DN3DREV >= AV_DR_EDK20021)
		case CON_IFVARN:
		case CON_IFVARAND:
#endif

			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
			// Check to see it's a keyword

			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Var.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
			*scriptptr++=i;	// the ID of the DEF (offset into array...)
			
			transnum();	// the number to check against...
			
			tempscrptr = scriptptr;
			scriptptr++; //Leave a spot for the fail location

			do
			{
				j = keyword();
				if(j == 20 || j == 39)
					parsecommand();
			} while(j == 20 || j == 39);

			parsecommand();

			*tempscrptr = (long) scriptptr;

			checking_ifelse++;
			return 0;
		
		case CON_ADDLOGVAR:
			// syntax: addlogvar <var>
			
			// prints the line number in the log file.
			*scriptptr=line_number;
			scriptptr++;
			
			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
//printf("found label of '%s'\n",	label+(labelcnt<<6));

			// Check to see if it's a keyword
			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
//printf("Label '%s' ID is %d\n",label+(labelcnt<<6), i);
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
			*scriptptr++=i;	// the ID of the DEF (offset into array...)
			
			return 0;
#if (APPVER_DN3DREV >= AV_DR_EDK20021)
		case CON_GETANGLETOTARGET:
		case CON_GETACTORANGLE:
		case CON_SETACTORANGLE:
		case CON_GETPLAYERANGLE:
		case CON_SETPLAYERANGLE:
			// Syntax:	 <command> <var>
			
			// get the ID of the DEF
			getlabel();	//GetGameVarLabel();
//printf("found label of '%s'\n",	label+(labelcnt<<6));

			// Check to see if it's a keyword
			for(i=0;i<NUMKEYWORDS;i++)
				if( strcmp( label+(labelcnt<<6),keyw[i]) == 0 )
				{
					error++;
					printf("  * ERROR!(L%ld) Symbol '%s' is a key word.\n",line_number,label+(labelcnt<<6));
					return 0;
				}

			i=GetDefID(label+(labelcnt<<6));
//printf("Label '%s' ID is %d\n",label+(labelcnt<<6), i);
			if(i<0)
			{	// not a defined DEF
				error++;
				printf("  * ERROR!(L%ld) Symbol '%s' is not a Game Definition.\n",line_number,label+(labelcnt<<6));
				return 0;
			}
			*scriptptr++=i;	// the ID of the DEF (offset into array...)
			
			return 0;
			
#endif
		case CON_ADDLOG:
			// syntax: addlog
			
			// prints the line number in the log file.
			*scriptptr=line_number;
			scriptptr++;
			return 0;
			
#endif

		case 75:
			transnum();
		case 3:
		case 8:
		case 9:
		case 21:
		case 33:
		case 34:
		case 35:
		case 41:
		case 46:
		case 53:
		case 56:
		case 59:
		case 62:
		case 72:
		case 73:
//		  case 74:
		case 78:
		case 85:
		case 94:
		case 111:
			transnum();
		case 43:
		case 44:
		case 49:
		case 5:
		case 6:
		case 27:
		case 26:
		case 45:
		case 51:
		case 63:
		case 64:
		case 65:
		case 67:
		case 70:
		case 71:
		case 81:
		case 82:
		case 90:
		case 91:
		case 109:

			if(tw == 51)
			{
				j = 0;
				do
				{
					transnum();
					scriptptr--;
					j |= *scriptptr;
				}
				while(keyword() == -1);
				*scriptptr = j;
				scriptptr++;
			}

			tempscrptr = scriptptr;
			scriptptr++; //Leave a spot for the fail location

			do
			{
				j = keyword();
				if(j == 20 || j == 39)
					parsecommand();
			} while(j == 20 || j == 39);

			parsecommand();

			*tempscrptr = (long) scriptptr;

			checking_ifelse++;
			return 0;
		case 29:
			num_squigilly_brackets++;
			do
				done = parsecommand();
			while( done == 0 );
			return 0;
		case 30:
			num_squigilly_brackets--;
			if( num_squigilly_brackets < 0 )
			{
				printf("  * ERROR!(L%ld) Found more '}' than '{'.\n",line_number);
				error++;
			}
			return 1;
		case 76:
			scriptptr--;
			j = 0;
			while( *textptr != 0x0a )
			{
				betaname[j] = *textptr;
				j++; textptr++;
			}
			betaname[j] = 0;
			return 0;
		case 20:
			scriptptr--; //Negate the rem
			while( *textptr != 0x0a )
				textptr++;

			// line_number++;
			return 0;

		case 107:
			scriptptr--;
			transnum();
			scriptptr--;
			j = *scriptptr;
			while( *textptr == ' ' ) textptr++;

			i = 0;

			while( *textptr != 0x0a )
			{
				volume_names[j][i] = toupper(*textptr);
				textptr++,i++;
				if(i >= 32)
				{
					printf("  * ERROR!(L%ld) Volume name exceeds character size limit of 32.\n",line_number);
					error++;
					while( *textptr != 0x0a ) textptr++;
					break;
				}
			}
			volume_names[j][i-1] = '\0';
			return 0;
		case 108:
			scriptptr--;
			transnum();
			scriptptr--;
			j = *scriptptr;
			while( *textptr == ' ' ) textptr++;

			i = 0;

			while( *textptr != 0x0a )
			{
				skill_names[j][i] = toupper(*textptr);
				textptr++,i++;
				if(i >= 32)
				{
					printf("  * ERROR!(L%ld) Skill name exceeds character size limit of 32.\n",line_number);
					error++;
					while( *textptr != 0x0a ) textptr++;
					break;
				}
			}
			skill_names[j][i-1] = '\0';
			return 0;

		case 0:
			scriptptr--;
			transnum();
			scriptptr--;
			j = *scriptptr;
			transnum();
			scriptptr--;
			k = *scriptptr;
			while( *textptr == ' ' ) textptr++;

			i = 0;
			while( *textptr != ' ' && *textptr != 0x0a )
			{
				level_file_names[j*11+k][i] = *textptr;
				textptr++,i++;
				if(i > 127)
				{
					printf("  * ERROR!(L%ld) Level file name exceeds character size limit of 128.\n",line_number);
					error++;
					while( *textptr != ' ') textptr++;
					break;
				}
			}
			level_names[j*11+k][i-1] = '\0';

			while( *textptr == ' ' ) textptr++;

			partime[j*11+k] =
				(((*(textptr+0)-'0')*10+(*(textptr+1)-'0'))*26*60)+
				(((*(textptr+3)-'0')*10+(*(textptr+4)-'0'))*26);

			textptr += 5;
			while( *textptr == ' ' ) textptr++;

			designertime[j*11+k] =
				(((*(textptr+0)-'0')*10+(*(textptr+1)-'0'))*26*60)+
				(((*(textptr+3)-'0')*10+(*(textptr+4)-'0'))*26);

			textptr += 5;
			while( *textptr == ' ' ) textptr++;

			i = 0;

			while( *textptr != 0x0a )
			{
				level_names[j*11+k][i] = toupper(*textptr);
				textptr++,i++;
				if(i >= 32)
				{
					printf("  * ERROR!(L%ld) Level name exceeds character size limit of 32.\n",line_number);
					error++;
					while( *textptr != 0x0a ) textptr++;
					break;
				}
			}
			level_names[j*11+k][i-1] = '\0';
			return 0;

		case 79:
			scriptptr--;
			transnum();
			k = *(scriptptr-1);
			if(k >= NUMOFFIRSTTIMEACTIVE)
			{
				printf("  * ERROR!(L%ld) Quote amount exceeds limit of %ld characters.\n",line_number,NUMOFFIRSTTIMEACTIVE);
				error++;
			}
			scriptptr--;
			i = 0;
			while( *textptr == ' ' )
				textptr++;

			while( *textptr != 0x0a )
			{
				fta_quotes[k][i] = *textptr;
				textptr++,i++;
				if(i >= 64)
				{
					printf("  * ERROR!(L%ld) Quote exceeds character size limit of 64.\n",line_number);
					error++;
					while( *textptr != 0x0a ) textptr++;
					break;
				}
			}
			fta_quotes[k][i] = '\0';
			return 0;
		case 57:
			scriptptr--;
			transnum();
			k = *(scriptptr-1);
			if(k >= NUM_SOUNDS)
			{
				printf("  * ERROR!(L%ld) Exceeded sound limit of %ld.\n",line_number,NUM_SOUNDS);
				error++;
			}
			scriptptr--;
			i = 0;
			while( *textptr == ' ')
				textptr++;

			while( *textptr != ' ' )
			{
				sounds[k][i] = *textptr;
				textptr++,i++;
				if(i >= 13)
				{
					puts(sounds[k]);
					printf("  * ERROR!(L%ld) Sound filename exceeded limit of 13 characters.\n",line_number);
					error++;
					while( *textptr != ' ' ) textptr++;
					break;
				}
			}
			sounds[k][i] = '\0';

			transnum();
			soundps[k] = *(scriptptr-1);
			scriptptr--;
			transnum();
			soundpe[k] = *(scriptptr-1);
			scriptptr--;
			transnum();
			soundpr[k] = *(scriptptr-1);
			scriptptr--;
			transnum();
			soundm[k] = *(scriptptr-1);
			scriptptr--;
			transnum();
			soundvo[k] = *(scriptptr-1);
			scriptptr--;
			return 0;
		
#ifdef WW2
			case CON_ENDEVENT:
			if( parsing_event == 0)
			{
				printf("  * ERROR!(L%ld) Found 'endevent' without defining 'onevent'.\n",line_number);
				error++;
			}
//			  else
			{
				if( num_squigilly_brackets > 0 )
				{
					printf("  * ERROR!(L%ld) Found more '{' than '}' before 'endevent'.\n",line_number);
					error++;
				}
				parsing_event = 0;
				parsing_actor = 0;
			}

			return 0;
#endif			
			case 4:
			if( parsing_actor == 0 )
			{
				printf("  * ERROR!(L%ld) Found 'enda' without defining 'actor'.\n",line_number);
				error++;
			}
//			  else
			{
				if( num_squigilly_brackets > 0 )
				{
					printf("  * ERROR!(L%ld) Found more '{' than '}' before 'enda'.\n",line_number);
					error++;
				}
				parsing_actor = 0;
			}

			return 0;
		case 12:
		case 16:
		case 84:
//		  case 21:
		case 22:	//KILLIT
		case 36:
		case 38:
		case 42:
		case 47:
		case 61:
		case 66:
		case 83:
		case 95:
		case 96:
		case 97:
		case 104:
		case 106:
			return 0;
		case 60:
			j = 0;
			while(j < 30)
			{
				transnum();
				scriptptr--;

				switch(j)
				{
					case 0:
						ud.const_visibility = *scriptptr;
						break;
					case 1:
						impact_damage = *scriptptr;
						break;
					case 2:
						max_player_health = *scriptptr;
						break;
					case 3:
						max_armour_amount = *scriptptr;
						break;
					case 4:
						respawnactortime = *scriptptr;break;
					case 5:
						respawnitemtime = *scriptptr;break;
					case 6:
						dukefriction = *scriptptr;break;
					case 7:
						gc = *scriptptr;break;
					case 8:rpgblastradius = *scriptptr;break;
					case 9:pipebombblastradius = *scriptptr;break;
					case 10:shrinkerblastradius = *scriptptr; break;
					case 11:tripbombblastradius = *scriptptr; break;
					case 12:morterblastradius = *scriptptr;break;
					case 13:bouncemineblastradius = *scriptptr;break;
					case 14:seenineblastradius = *scriptptr;break;

					case 15:
					case 16:
					case 17:
					case 18:
					case 19:
					case 20:
					case 21:
					case 22:
					case 23:
					case 24:
						if(j == 24)
							max_ammo_amount[11] = *scriptptr;
						else max_ammo_amount[j-14] = *scriptptr;
						break;
					case 25:
						camerashitable = *scriptptr;
						break;
					case 26:
						numfreezebounces = *scriptptr;
						break;
					case 27:
						freezerhurtowner = *scriptptr;
						break;
					case 28:
						spriteqamount = *scriptptr;
						if(spriteqamount > 1024) spriteqamount = 1024;
						else if(spriteqamount < 0) spriteqamount = 0;
						break;
					case 29:
						lasermode = *scriptptr;
						break;
				}
				j++;
			}
			scriptptr++;
			return 0;
	}
	return 0;
}


void passone(void)
{
#ifdef WW2
#ifdef DEBUG	
	int i;
#endif
#endif

	while( parsecommand() == 0 );

	if( (error+warning) > 12)
		puts(  "  * ERROR! Too many warnings or errors.");

#ifdef WW2
#ifdef DEBUG
	printf("Game Definitions\n");
	for(i=0;i<iGameVarCount;i++)
	{
		printf("%20s\t%d\n",apszGameVarLabel[i],lGameVarValue[i]);
	}
#endif
#endif
}


#ifdef WW2
#define NUM_DEFAULT_CONS	4
char *defaultcons[NUM_DEFAULT_CONS] =
{
	 {"GAME.CON"},
	 {"XUSER.CON"},
	 {"XDEFS.CON"},
	 {"ENHANCE.CON"}
};

#else
#define NUM_DEFAULT_CONS	3
char *defaultcons[NUM_DEFAULT_CONS] =
{
	 {"GAME.CON"},
	 {"USER.CON"},
	 {"DEFS.CON"}
};

#endif

void copydefaultcons(void)
{
	long i, fs, fpi;
	FILE *fpo;

	for(i=0;i<NUM_DEFAULT_CONS;i++)
	{
		fpi = kopen4load( defaultcons[i] , 1 );
		fpo = fopen( defaultcons[i],"wb");

		if(fpi == 0)
		{
			if(fpo == -1) fclose(fpo);
			continue;
		}
		if(fpo == -1)
		{
			if(fpi == 0) kclose(fpi);
			continue;
		}

		fs = kfilelength(fpi);

		kread(fpi,&hittype[0],fs);
		fwrite(&hittype[0],fs,1,fpo);

		kclose(fpi);
		fclose(fpo);
	}
}

#if (defined NAM) && (APPVER_DN3DREV >= AV_DR_WW2GI10)
//#ifdef NAM
void FreeGameVars(void)
{
	// call this function as many times as needed.
	int i;
#if (APPVER_DN3DREV == AV_DR_EDK20021)
AddLog("FreeGameVars");	
#endif
	for(i=0;i<MAXGAMEVARS;i++)
	{
		aGameVars[i].lValue=0;
		aGameVars[i].szLabel[0]=0;
		aGameVars[i].dwFlags=0;
		if(aGameVars[i].plValues)
		{
			free(aGameVars[i].plValues);
		}
		aGameVars[i].plValues=NULL;
	}
	iGameVarCount=0;
	return;
}

void ClearGameVars(void)
{
	// only call this function ONCE...
	int i;

//AddLog("ClearGameVars");

	for(i=0;i<MAXGAMEVARS;i++)
	{
		aGameVars[i].lValue=0;
		aGameVars[i].szLabel[0]=0;
		aGameVars[i].dwFlags=0;
		aGameVars[i].plValues=NULL;
	}
	iGameVarCount=0;
	iDefaultGameVarCount=0;
	return;
}

void InitGameVarPointers(void)
{
	int i,j;
	char aszBuf[64];
	// called from game Init AND when level is loaded...

//AddLog("InitGameVarPointers");

	for(i=0;i<MAX_WEAPONS;i++)
	{
		sprintf(aszBuf,"WEAPON%d_CLIP",i);
		aplWeaponClip[i]=GetGameValuePtr(aszBuf);
		if(!aplWeaponClip[i])
		{
			printf("ERROR: NULL Weapon\n");
			exit(0);
		}
		sprintf(aszBuf,"WEAPON%d_RELOAD",i);
		aplWeaponReload[i]=GetGameValuePtr(aszBuf);

		sprintf(aszBuf,"WEAPON%d_FIREDELAY",i);
		aplWeaponFireDelay[i]=GetGameValuePtr(aszBuf);

		sprintf(aszBuf,"WEAPON%d_TOTALTIME",i);
		aplWeaponTotalTime[i]=GetGameValuePtr(aszBuf);
		
		sprintf(aszBuf,"WEAPON%d_HOLDDELAY",i);
		aplWeaponHoldDelay[i]=GetGameValuePtr(aszBuf);

		sprintf(aszBuf,"WEAPON%d_FLAGS",i);
		aplWeaponFlags[i]=GetGameValuePtr(aszBuf);
		
		sprintf(aszBuf,"WEAPON%d_SHOOTS",i);
		aplWeaponShoots[i]=GetGameValuePtr(aszBuf);
		
		sprintf(aszBuf,"WEAPON%d_SPAWNTIME",i);
		aplWeaponSpawnTime[i]=GetGameValuePtr(aszBuf);
		
		sprintf(aszBuf,"WEAPON%d_SPAWN",i);
		aplWeaponSpawn[i]=GetGameValuePtr(aszBuf);
		
		sprintf(aszBuf,"WEAPON%d_SHOTSPERBURST",i);
		aplWeaponShotsPerBurst[i]=GetGameValuePtr(aszBuf);
		
		sprintf(aszBuf,"WEAPON%d_WORKSLIKE",i);
		aplWeaponWorksLike[i]=GetGameValuePtr(aszBuf);
		
		sprintf(aszBuf,"WEAPON%d_INITIALSOUND",i);
		aplWeaponInitialSound[i]=GetGameValuePtr(aszBuf);
		
		sprintf(aszBuf,"WEAPON%d_FIRESOUND",i);
		aplWeaponFireSound[i]=GetGameValuePtr(aszBuf);

		sprintf(aszBuf,"WEAPON%d_SOUND2TIME",i);
		aplWeaponSound2Time[i]=GetGameValuePtr(aszBuf);

		sprintf(aszBuf,"WEAPON%d_SOUND2SOUND",i);
		aplWeaponSound2Sound[i]=GetGameValuePtr(aszBuf);
	
	}
}

void AddSystemVars()
{
	// only call ONCE
	int i;
	char aszBuf[64];

//AddLog("AddSystemVars");

/*

// KICK
gamevar WEAPON0_WORKSLIKE 0 GAMEVAR_FLAG_PERPLAYER
gamevar WEAPON0_CLIP 0 GAMEVAR_FLAG_PERPLAYER
gamevar WEAPON0_RELOAD 30 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON0_FIREDELAY 7 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON0_TOTALTIME 14 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON0_HOLDDELAY 14 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON0_FLAGS WEAPON_FLAG_NOVISIBLE GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON0_SHOOTS KNEE GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON0_SPAWNTIME 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON0_SPAWN 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON0_SHOTSPERBURST 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON0_INITIALSOUND 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON0_FIRESOUND 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON0_SOUND2TIME 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON0_SOUND2SOUND 0 GAMEVAR_FLAG_PERPLAYER 

// Pistol
gamevar WEAPON1_WORKSLIKE 1 GAMEVAR_FLAG_PERPLAYER
gamevar WEAPON1_CLIP 12 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON1_RELOAD 50 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON1_FIREDELAY 2 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON1_TOTALTIME 6 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON1_HOLDDELAY 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON1_FLAGS WEAPON_FLAG_AUTOMATIC GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON1_SHOOTS SHOTSPARK1 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON1_SPAWNTIME 2 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON1_SPAWN SHELL GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON1_SHOTSPERBURST 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON1_INITIALSOUND 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON1_FIRESOUND 3 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON1_SOUND2TIME 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON1_SOUND2SOUND 0 GAMEVAR_FLAG_PERPLAYER 

// Shotgun
gamevar WEAPON2_WORKSLIKE 2 GAMEVAR_FLAG_PERPLAYER
gamevar WEAPON2_CLIP 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON2_RELOAD 13 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON2_FIREDELAY 4 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON2_TOTALTIME 31 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON2_HOLDDELAY 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON2_FLAGS WEAPON_FLAG_CHECKATRELOAD GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON2_SHOOTS SHOTGUN GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON2_SPAWNTIME 24 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON2_SPAWN SHOTGUNSHELL GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON2_SHOTSPERBURST 7 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON2_INITIALSOUND 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON2_FIRESOUND 109 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON2_SOUND2TIME 15 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON2_SOUND2SOUND 169 GAMEVAR_FLAG_PERPLAYER 

// Chaingun
gamevar WEAPON3_WORKSLIKE 3 GAMEVAR_FLAG_PERPLAYER
gamevar WEAPON3_CLIP 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON3_RELOAD 30 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON3_FIREDELAY 1 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON3_TOTALTIME 10 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON3_HOLDDELAY 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON3_FLAGS 84 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON3_SHOOTS CHAINGUN GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON3_SPAWNTIME 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON3_SPAWN SHELL GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON3_SHOTSPERBURST 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON3_INITIALSOUND 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON3_FIRESOUND 6 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON3_SOUND2TIME 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON3_SOUND2SOUND 0 GAMEVAR_FLAG_PERPLAYER 

// RPG
gamevar WEAPON4_WORKSLIKE 4 GAMEVAR_FLAG_PERPLAYER
gamevar WEAPON4_CLIP 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON4_RELOAD 30 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON4_FIREDELAY 4 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON4_TOTALTIME 20 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON4_HOLDDELAY 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON4_FLAGS 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON4_SHOOTS RPG GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON4_SPAWNTIME 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON4_SPAWN 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON4_SHOTSPERBURST 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON4_INITIALSOUND 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON4_FIRESOUND 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON4_SOUND2TIME 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON4_SOUND2SOUND 0 GAMEVAR_FLAG_PERPLAYER 

// PipeBomb
gamevar WEAPON5_WORKSLIKE 5 GAMEVAR_FLAG_PERPLAYER
gamevar WEAPON5_CLIP 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON5_RELOAD 30 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON5_FIREDELAY 6 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON5_TOTALTIME 19 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON5_HOLDDELAY 12 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON5_FLAGS WEAPON_FLAG_THROWIT GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON5_SHOOTS HEAVYHBOMB GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON5_SPAWNTIME 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON5_SPAWN 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON5_SHOTSPERBURST 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON5_INITIALSOUND 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON5_FIRESOUND 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON5_SOUND2TIME 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON5_SOUND2SOUND 0 GAMEVAR_FLAG_PERPLAYER 

// Shrinker
gamevar WEAPON6_WORKSLIKE 6 GAMEVAR_FLAG_PERPLAYER
gamevar WEAPON6_CLIP 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON6_RELOAD 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON6_FIREDELAY 3 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON6_TOTALTIME 12 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON6_HOLDDELAY 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON6_FLAGS WEAPON_FLAG_GLOWS GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON6_SHOOTS SHRINKER GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON6_SPAWNTIME 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON6_SPAWN 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON6_SHOTSPERBURST 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON6_INITIALSOUND 11 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON6_FIRESOUND 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON6_SOUND2TIME 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON6_SOUND2SOUND 0 GAMEVAR_FLAG_PERPLAYER 

// Devastator
gamevar WEAPON7_WORKSLIKE 7 GAMEVAR_FLAG_PERPLAYER
gamevar WEAPON7_CLIP 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON7_RELOAD 30 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON7_FIREDELAY 2 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON7_TOTALTIME 5 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON7_HOLDDELAY 5 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON7_FLAGS WEAPON_FLAG_FIREEVERYOTHER GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON7_SHOOTS RPG GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON7_SPAWNTIME 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON7_SPAWN 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON7_SHOTSPERBURST 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON7_INITIALSOUND 10 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON7_FIRESOUND 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON7_SOUND2TIME 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON7_SOUND2SOUND 0 GAMEVAR_FLAG_PERPLAYER 

// Tripbomb
gamevar WEAPON8_WORKSLIKE 8 GAMEVAR_FLAG_PERPLAYER
gamevar WEAPON8_CLIP 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON8_RELOAD 30 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON8_FIREDELAY 3 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON8_TOTALTIME 16 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON8_HOLDDELAY 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON8_FLAGS WEAPON_FLAG_STANDSTILL GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON8_SHOOTS HANDHOLDINGLASER GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON8_SPAWNTIME 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON8_SPAWN 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON8_SHOTSPERBURST 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON8_INITIALSOUND 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON8_FIRESOUND 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON8_SOUND2TIME 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON8_SOUND2SOUND 0 GAMEVAR_FLAG_PERPLAYER 

// Freezethrower
gamevar WEAPON9_WORKSLIKE 9 GAMEVAR_FLAG_PERPLAYER
gamevar WEAPON9_CLIP 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON9_RELOAD 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON9_FIREDELAY 3 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON9_TOTALTIME 5 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON9_HOLDDELAY 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON9_FLAGS WEAPON_FLAG_FIREEVERYOTHER GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON9_SHOOTS FREEZEBLAST GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON9_SPAWNTIME 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON9_SPAWN 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON9_SHOTSPERBURST 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON9_INITIALSOUND 10 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON9_FIRESOUND 10 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON9_SOUND2TIME 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON9_SOUND2SOUND 0 GAMEVAR_FLAG_PERPLAYER 

// ?
gamevar WEAPON10_WORKSLIKE 10 GAMEVAR_FLAG_PERPLAYER
gamevar WEAPON10_CLIP 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON10_RELOAD 10 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON10_FIREDELAY 2 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON10_TOTALTIME 10 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON10_HOLDDELAY 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON10_FLAGS 384 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON10_SHOOTS 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON10_SPAWNTIME 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON10_SPAWN 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON10_SHOTSPERBURST 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON10_INITIALSOUND 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON10_FIRESOUND 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON10_SOUND2TIME 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON10_SOUND2SOUND 0 GAMEVAR_FLAG_PERPLAYER 

// Expander
gamevar WEAPON11_WORKSLIKE 11 GAMEVAR_FLAG_PERPLAYER
gamevar WEAPON11_CLIP 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON11_RELOAD 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON11_FIREDELAY 2 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON11_TOTALTIME 5 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON11_HOLDDELAY 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON11_FLAGS WEAPON_FLAG_GLOWS GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON11_SHOOTS GROWSPARK GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON11_SPAWNTIME 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON11_SPAWN 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON11_SHOTSPERBURST 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON11_INITIALSOUND 388 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON11_FIRESOUND 388 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON11_SOUND2TIME 0 GAMEVAR_FLAG_PERPLAYER 
gamevar WEAPON11_SOUND2SOUND 0 GAMEVAR_FLAG_PERPLAYER
*/	
/////////////////////////////		
		sprintf(aszBuf,"WEAPON%d_WORKSLIKE",KNEE_WEAPON);
		AddGameVar(aszBuf, KNEE_WEAPON, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_CLIP",KNEE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_RELOAD",KNEE_WEAPON);
		AddGameVar(aszBuf, 30, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_FIREDELAY",KNEE_WEAPON);
		AddGameVar(aszBuf, 7, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_TOTALTIME",KNEE_WEAPON);
		AddGameVar(aszBuf, 14, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_HOLDDELAY",KNEE_WEAPON);
		AddGameVar(aszBuf, 14, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_FLAGS",KNEE_WEAPON);
#if (APPVER_DN3DREV < AV_DR_EDK20021)
		AddGameVar(aszBuf, WEAPON_FLAG_AUTOMATIC | WEAPON_FLAG_RANDOMRESTART, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
#else
		AddGameVar(aszBuf, WEAPON_FLAG_NOVISIBLE | WEAPON_FLAG_AUTOMATIC | WEAPON_FLAG_RANDOMRESTART, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
#endif
		
		sprintf(aszBuf,"WEAPON%d_SHOOTS",KNEE_WEAPON);
		AddGameVar(aszBuf, KNEE, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SPAWNTIME",KNEE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SPAWN",KNEE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SHOTSPERBURST",KNEE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_INITIALSOUND",KNEE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_FIRESOUND",KNEE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_SOUND2TIME",KNEE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_SOUND2SOUND",KNEE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

/////////////////////////////
		sprintf(aszBuf,"WEAPON%d_WORKSLIKE",PISTOL_WEAPON);
		AddGameVar(aszBuf, PISTOL_WEAPON, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_CLIP",PISTOL_WEAPON);
#ifdef EDUKE
		AddGameVar(aszBuf, 12, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
#else
		AddGameVar(aszBuf, 20, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
#endif

		sprintf(aszBuf,"WEAPON%d_RELOAD",PISTOL_WEAPON);
#ifdef EDUKE
		AddGameVar(aszBuf, 30, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
#else
		AddGameVar(aszBuf, 50, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
#endif		
		sprintf(aszBuf,"WEAPON%d_FIREDELAY",PISTOL_WEAPON);
		AddGameVar(aszBuf, 2, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_TOTALTIME",PISTOL_WEAPON);
#ifdef EDUKE
		AddGameVar(aszBuf, 6, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
#else
		AddGameVar(aszBuf, 5, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
#endif
		
		sprintf(aszBuf,"WEAPON%d_HOLDDELAY",PISTOL_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_FLAGS",PISTOL_WEAPON);
		AddGameVar(aszBuf, WEAPON_FLAG_AUTOMATIC | WEAPON_FLAG_HOLSTER_CLEARS_CLIP, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SHOOTS",PISTOL_WEAPON);
		AddGameVar(aszBuf, SHOTSPARK1, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SPAWNTIME",PISTOL_WEAPON);
		AddGameVar(aszBuf, 2, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SPAWN",PISTOL_WEAPON);
		AddGameVar(aszBuf, SHELL, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SHOTSPERBURST",PISTOL_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_INITIALSOUND",PISTOL_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_FIRESOUND",PISTOL_WEAPON);
		AddGameVar(aszBuf, PISTOL_FIRE, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_SOUND2TIME",PISTOL_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_SOUND2SOUND",PISTOL_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

/////////////////////////////
		sprintf(aszBuf,"WEAPON%d_WORKSLIKE",SHOTGUN_WEAPON);
		AddGameVar(aszBuf, SHOTGUN_WEAPON, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_CLIP",SHOTGUN_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_RELOAD",SHOTGUN_WEAPON);
		AddGameVar(aszBuf, 13, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_FIREDELAY",SHOTGUN_WEAPON);
		AddGameVar(aszBuf, 4, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_TOTALTIME",SHOTGUN_WEAPON);
		AddGameVar(aszBuf, 31, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_HOLDDELAY",SHOTGUN_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_FLAGS",SHOTGUN_WEAPON);
		AddGameVar(aszBuf, WEAPON_FLAG_CHECKATRELOAD, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SHOOTS",SHOTGUN_WEAPON);
		AddGameVar(aszBuf, SHOTGUN, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SPAWNTIME",SHOTGUN_WEAPON);
		AddGameVar(aszBuf, 24, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SPAWN",SHOTGUN_WEAPON);
		AddGameVar(aszBuf, SHOTGUNSHELL, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SHOTSPERBURST",SHOTGUN_WEAPON);
		AddGameVar(aszBuf, 7, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_INITIALSOUND",SHOTGUN_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_FIRESOUND",SHOTGUN_WEAPON);
		AddGameVar(aszBuf, SHOTGUN_FIRE, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_SOUND2TIME",SHOTGUN_WEAPON);
		AddGameVar(aszBuf, 15, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_SOUND2SOUND",SHOTGUN_WEAPON);
		AddGameVar(aszBuf, SHOTGUN_COCK, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

/////////////////////////////
		sprintf(aszBuf,"WEAPON%d_WORKSLIKE",CHAINGUN_WEAPON);
		AddGameVar(aszBuf, CHAINGUN_WEAPON, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_CLIP",CHAINGUN_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_RELOAD",CHAINGUN_WEAPON);
		AddGameVar(aszBuf, 30, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_FIREDELAY",CHAINGUN_WEAPON);
		AddGameVar(aszBuf, 1, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_TOTALTIME",CHAINGUN_WEAPON);
#ifdef EDUKE
		AddGameVar(aszBuf, 10, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
#else
		AddGameVar(aszBuf, 12, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
#endif
		
		sprintf(aszBuf,"WEAPON%d_HOLDDELAY",CHAINGUN_WEAPON);
#ifdef EDUKE
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
#else
		AddGameVar(aszBuf, 10, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
#endif
		sprintf(aszBuf,"WEAPON%d_FLAGS",CHAINGUN_WEAPON);
#ifdef EDUKE
		AddGameVar(aszBuf, WEAPON_FLAG_AUTOMATIC | WEAPON_FLAG_FIREEVERYTHIRD | WEAPON_FLAG_AMMOPERSHOT, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
#else
		AddGameVar(aszBuf, WEAPON_FLAG_AUTOMATIC | WEAPON_FLAG_FIREEVERYTHIRD | WEAPON_FLAG_AMMOPERSHOT, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
#endif

		sprintf(aszBuf,"WEAPON%d_SHOOTS",CHAINGUN_WEAPON);
		AddGameVar(aszBuf, CHAINGUN, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SPAWNTIME",CHAINGUN_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SPAWN",CHAINGUN_WEAPON);
		AddGameVar(aszBuf, SHELL, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SHOTSPERBURST",CHAINGUN_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_INITIALSOUND",CHAINGUN_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_FIRESOUND",CHAINGUN_WEAPON);
		AddGameVar(aszBuf, CHAINGUN_FIRE, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_SOUND2TIME",CHAINGUN_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_SOUND2SOUND",CHAINGUN_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

/////////////////////////////
		sprintf(aszBuf,"WEAPON%d_WORKSLIKE",RPG_WEAPON);
		AddGameVar(aszBuf, RPG_WEAPON, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_CLIP",RPG_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_RELOAD",RPG_WEAPON);
		AddGameVar(aszBuf, 30, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_FIREDELAY",RPG_WEAPON);
		AddGameVar(aszBuf, 4, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_TOTALTIME",RPG_WEAPON);
		AddGameVar(aszBuf, 20, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_HOLDDELAY",RPG_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_FLAGS",RPG_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SHOOTS",RPG_WEAPON);
		AddGameVar(aszBuf, RPG, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SPAWNTIME",RPG_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SPAWN",RPG_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SHOTSPERBURST",RPG_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_INITIALSOUND",RPG_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_FIRESOUND",RPG_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_SOUND2TIME",RPG_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_SOUND2SOUND",RPG_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

/////////////////////////////
		sprintf(aszBuf,"WEAPON%d_WORKSLIKE",HANDBOMB_WEAPON);
		AddGameVar(aszBuf, HANDBOMB_WEAPON, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_CLIP",HANDBOMB_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_RELOAD",HANDBOMB_WEAPON);
		AddGameVar(aszBuf, 30, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_FIREDELAY",HANDBOMB_WEAPON);
		AddGameVar(aszBuf, 6, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_TOTALTIME",HANDBOMB_WEAPON);
		AddGameVar(aszBuf, 19, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_HOLDDELAY",HANDBOMB_WEAPON);
		AddGameVar(aszBuf, 12, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_FLAGS",HANDBOMB_WEAPON);
		AddGameVar(aszBuf, WEAPON_FLAG_THROWIT, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SHOOTS",HANDBOMB_WEAPON);
		AddGameVar(aszBuf, HEAVYHBOMB, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SPAWNTIME",HANDBOMB_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SPAWN",HANDBOMB_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SHOTSPERBURST",HANDBOMB_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_INITIALSOUND",HANDBOMB_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_FIRESOUND",HANDBOMB_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_SOUND2TIME",HANDBOMB_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_SOUND2SOUND",HANDBOMB_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

/////////////////////////////
		sprintf(aszBuf,"WEAPON%d_WORKSLIKE",SHRINKER_WEAPON);
		AddGameVar(aszBuf, SHRINKER_WEAPON, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_CLIP",SHRINKER_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_RELOAD",SHRINKER_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_FIREDELAY",SHRINKER_WEAPON);
#ifdef EDUKE
		AddGameVar(aszBuf, 3, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
#else
		AddGameVar(aszBuf, 10, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
#endif

		sprintf(aszBuf,"WEAPON%d_TOTALTIME",SHRINKER_WEAPON);
#ifdef EDUKE
		AddGameVar(aszBuf, 12, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
#else
		AddGameVar(aszBuf, 30, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
#endif

		sprintf(aszBuf,"WEAPON%d_HOLDDELAY",SHRINKER_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_FLAGS",SHRINKER_WEAPON);
		AddGameVar(aszBuf, WEAPON_FLAG_GLOWS, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SHOOTS",SHRINKER_WEAPON);
		AddGameVar(aszBuf, SHRINKER, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SPAWNTIME",SHRINKER_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SPAWN",SHRINKER_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SHOTSPERBURST",SHRINKER_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_INITIALSOUND",SHRINKER_WEAPON);
		AddGameVar(aszBuf, SHRINKER_FIRE, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_FIRESOUND",SHRINKER_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_SOUND2TIME",SHRINKER_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_SOUND2SOUND",SHRINKER_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

/////////////////////////////
		sprintf(aszBuf,"WEAPON%d_WORKSLIKE",DEVISTATOR_WEAPON);
		AddGameVar(aszBuf, DEVISTATOR_WEAPON, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_CLIP",DEVISTATOR_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_RELOAD",DEVISTATOR_WEAPON);
		AddGameVar(aszBuf, 30, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_FIREDELAY",DEVISTATOR_WEAPON);
		AddGameVar(aszBuf, 2, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_TOTALTIME",DEVISTATOR_WEAPON);
		AddGameVar(aszBuf, 5, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_HOLDDELAY",DEVISTATOR_WEAPON);
		AddGameVar(aszBuf, 5, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_FLAGS",DEVISTATOR_WEAPON);
		AddGameVar(aszBuf, WEAPON_FLAG_FIREEVERYOTHER, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SHOOTS",DEVISTATOR_WEAPON);
		AddGameVar(aszBuf, RPG, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SPAWNTIME",DEVISTATOR_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SPAWN",DEVISTATOR_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SHOTSPERBURST",DEVISTATOR_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_INITIALSOUND",DEVISTATOR_WEAPON);
		AddGameVar(aszBuf, CAT_FIRE, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_FIRESOUND",DEVISTATOR_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_SOUND2TIME",DEVISTATOR_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_SOUND2SOUND",DEVISTATOR_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

/////////////////////////////
		sprintf(aszBuf,"WEAPON%d_WORKSLIKE",TRIPBOMB_WEAPON);
		AddGameVar(aszBuf, TRIPBOMB_WEAPON, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_CLIP",TRIPBOMB_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_RELOAD",TRIPBOMB_WEAPON);
		AddGameVar(aszBuf, 30, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_FIREDELAY",TRIPBOMB_WEAPON);
		AddGameVar(aszBuf, 3, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_TOTALTIME",TRIPBOMB_WEAPON);
		AddGameVar(aszBuf, 16, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_HOLDDELAY",TRIPBOMB_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_FLAGS",TRIPBOMB_WEAPON);
		AddGameVar(aszBuf, WEAPON_FLAG_STANDSTILL, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SHOOTS",TRIPBOMB_WEAPON);
		AddGameVar(aszBuf, HANDHOLDINGLASER, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SPAWNTIME",TRIPBOMB_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SPAWN",TRIPBOMB_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SHOTSPERBURST",TRIPBOMB_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_INITIALSOUND",TRIPBOMB_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_FIRESOUND",TRIPBOMB_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_SOUND2TIME",TRIPBOMB_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_SOUND2SOUND",TRIPBOMB_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

/////////////////////////////
		sprintf(aszBuf,"WEAPON%d_WORKSLIKE",FREEZE_WEAPON);
		AddGameVar(aszBuf, FREEZE_WEAPON, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_CLIP",FREEZE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_RELOAD",FREEZE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_FIREDELAY",FREEZE_WEAPON);
		AddGameVar(aszBuf, 3, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_TOTALTIME",FREEZE_WEAPON);
		AddGameVar(aszBuf, 5, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_HOLDDELAY",FREEZE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_FLAGS",FREEZE_WEAPON);
		AddGameVar(aszBuf, WEAPON_FLAG_FIREEVERYOTHER, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SHOOTS",FREEZE_WEAPON);
		AddGameVar(aszBuf, FREEZEBLAST, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SPAWNTIME",FREEZE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SPAWN",FREEZE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SHOTSPERBURST",FREEZE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_INITIALSOUND",FREEZE_WEAPON);
		AddGameVar(aszBuf, CAT_FIRE, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_FIRESOUND",FREEZE_WEAPON);
		AddGameVar(aszBuf, CAT_FIRE, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_SOUND2TIME",FREEZE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_SOUND2SOUND",FREEZE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
/////////////////////////////
		sprintf(aszBuf,"WEAPON%d_WORKSLIKE",HANDREMOTE_WEAPON);
		AddGameVar(aszBuf, HANDREMOTE_WEAPON, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_CLIP",HANDREMOTE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_RELOAD",HANDREMOTE_WEAPON);
#ifdef EDUKE
		AddGameVar(aszBuf, 10, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
#else
		AddGameVar(aszBuf, 30, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
#endif

		sprintf(aszBuf,"WEAPON%d_FIREDELAY",HANDREMOTE_WEAPON);
		AddGameVar(aszBuf, 2, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_TOTALTIME",HANDREMOTE_WEAPON);
		AddGameVar(aszBuf, 10, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_HOLDDELAY",HANDREMOTE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_FLAGS",HANDREMOTE_WEAPON);
		AddGameVar(aszBuf, WEAPON_FLAG_BOMB_TRIGGER | WEAPON_FLAG_NOVISIBLE, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SHOOTS",HANDREMOTE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SPAWNTIME",HANDREMOTE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SPAWN",HANDREMOTE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SHOTSPERBURST",HANDREMOTE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_INITIALSOUND",HANDREMOTE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_FIRESOUND",HANDREMOTE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_SOUND2TIME",HANDREMOTE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_SOUND2SOUND",HANDREMOTE_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

///////////////////////////////////////////////////////		
		sprintf(aszBuf,"WEAPON%d_WORKSLIKE",GROW_WEAPON);
		AddGameVar(aszBuf, GROW_WEAPON, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_CLIP",GROW_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_RELOAD",GROW_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_FIREDELAY",GROW_WEAPON);
#ifdef EDUKE
		AddGameVar(aszBuf, 2, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
#else
		AddGameVar(aszBuf, 3, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
#endif

		sprintf(aszBuf,"WEAPON%d_TOTALTIME",GROW_WEAPON);
#ifdef EDUKE
		AddGameVar(aszBuf, 5, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
#else
		AddGameVar(aszBuf, 30, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
#endif

		sprintf(aszBuf,"WEAPON%d_HOLDDELAY",GROW_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_FLAGS",GROW_WEAPON);
		AddGameVar(aszBuf, WEAPON_FLAG_GLOWS, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SHOOTS",GROW_WEAPON);
		AddGameVar(aszBuf, GROWSPARK, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SPAWNTIME",GROW_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SPAWN",GROW_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_SHOTSPERBURST",GROW_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_INITIALSOUND",GROW_WEAPON);
		AddGameVar(aszBuf, EXPANDERSHOOT, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
		
		sprintf(aszBuf,"WEAPON%d_FIRESOUND",GROW_WEAPON);
		AddGameVar(aszBuf, EXPANDERSHOOT, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_SOUND2TIME",GROW_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

		sprintf(aszBuf,"WEAPON%d_SOUND2SOUND",GROW_WEAPON);
		AddGameVar(aszBuf, 0, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

	AddGameVar("GRENADE_LIFETIME", NAM_GRENADE_LIFETIME, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
	AddGameVar("GRENADE_LIFETIME_VAR", NAM_GRENADE_LIFETIME_VAR, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

	AddGameVar("STICKYBOMB_LIFETIME", NAM_GRENADE_LIFETIME, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);
	AddGameVar("STICKYBOMB_LIFETIME_VAR", NAM_GRENADE_LIFETIME_VAR, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

	AddGameVar("TRIPBOMB_CONTROL", TRIPBOMB_TRIPWIRE, GAMEVAR_FLAG_PERPLAYER | GAMEVAR_FLAG_SYSTEM);

	AddGameVar("RESPAWN_MONSTERS", (long)&ud.respawn_monsters,GAMEVAR_FLAG_SYSTEM | GAMEVAR_FLAG_PLONG);
	AddGameVar("RESPAWN_ITEMS",(long)&ud.respawn_items, GAMEVAR_FLAG_SYSTEM | GAMEVAR_FLAG_PLONG);
	AddGameVar("RESPAWN_INVENTORY",(long)&ud.respawn_inventory, GAMEVAR_FLAG_SYSTEM | GAMEVAR_FLAG_PLONG);
	AddGameVar("MONSTERS_OFF",(long)&ud.monsters_off, GAMEVAR_FLAG_SYSTEM | GAMEVAR_FLAG_PLONG);
	AddGameVar("MARKER",(long)&ud.marker, GAMEVAR_FLAG_SYSTEM | GAMEVAR_FLAG_PLONG);
	AddGameVar("FFIRE",(long)&ud.ffire, GAMEVAR_FLAG_SYSTEM | GAMEVAR_FLAG_PLONG);
	AddGameVar("LEVEL",(long)&ud.level_number, GAMEVAR_FLAG_SYSTEM | GAMEVAR_FLAG_PLONG | GAMEVAR_FLAG_READONLY);
	AddGameVar("VOLUME",(long)&ud.volume_number, GAMEVAR_FLAG_SYSTEM | GAMEVAR_FLAG_PLONG | GAMEVAR_FLAG_READONLY);

	AddGameVar("COOP",(long)&ud.coop, GAMEVAR_FLAG_SYSTEM | GAMEVAR_FLAG_PLONG);
	AddGameVar("MULTIMODE",(long)&ud.multimode, GAMEVAR_FLAG_SYSTEM | GAMEVAR_FLAG_PLONG);
	
	AddGameVar("WEAPON", 0, GAMEVAR_FLAG_READONLY | GAMEVAR_FLAG_SYSTEM);
	AddGameVar("WORKSLIKE", 0, GAMEVAR_FLAG_READONLY | GAMEVAR_FLAG_SYSTEM);
	AddGameVar("RETURN", 0, GAMEVAR_FLAG_SYSTEM);
	AddGameVar("ZRANGE", 0, GAMEVAR_FLAG_SYSTEM);
	AddGameVar("ANGRANGE", 0, GAMEVAR_FLAG_SYSTEM);
	AddGameVar("AUTOAIMANGLE", 0, GAMEVAR_FLAG_SYSTEM);
#if (APPVER_DN3DREV >= AV_DR_EDK20021)
	AddGameVar("LOTAG", 0, GAMEVAR_FLAG_READONLY | GAMEVAR_FLAG_SYSTEM);
	AddGameVar("HITAG", 0, GAMEVAR_FLAG_READONLY | GAMEVAR_FLAG_SYSTEM);
	AddGameVar("TEXTURE", 0, GAMEVAR_FLAG_READONLY | GAMEVAR_FLAG_SYSTEM);
	AddGameVar("THISACTOR", 0, GAMEVAR_FLAG_READONLY | GAMEVAR_FLAG_SYSTEM);
	AddGameVar("myconnectindex", (long)&myconnectindex, GAMEVAR_FLAG_READONLY | GAMEVAR_FLAG_PLONG | GAMEVAR_FLAG_SYSTEM);
	AddGameVar("screenpeek", (long)&screenpeek, GAMEVAR_FLAG_READONLY | GAMEVAR_FLAG_PLONG | GAMEVAR_FLAG_SYSTEM);
#endif
}

void ResetSystemDefaults(void)
{
	// call many times...
	
	int i,j;
	char aszBuf[64];

//AddLog("ResetWeaponDefaults");

	for(j=0;j<MAXPLAYERS;j++)
	{
		for(i=0;i<MAX_WEAPONS;i++)
		{
			sprintf(aszBuf,"WEAPON%d_CLIP",i);
			aplWeaponClip[i][j]=GetGameVar(aszBuf,0, -1, j);
		
			sprintf(aszBuf,"WEAPON%d_RELOAD",i);
			aplWeaponReload[i][j]=GetGameVar(aszBuf,0, -1, j);

			sprintf(aszBuf,"WEAPON%d_FIREDELAY",i);
			aplWeaponFireDelay[i][j]=GetGameVar(aszBuf,0, -1, j);

			sprintf(aszBuf,"WEAPON%d_TOTALTIME",i);
			aplWeaponTotalTime[i][j]=GetGameVar(aszBuf,0, -1, j);
		
			sprintf(aszBuf,"WEAPON%d_HOLDDELAY",i);
			aplWeaponHoldDelay[i][j]=GetGameVar(aszBuf,0, -1, j);

			sprintf(aszBuf,"WEAPON%d_FLAGS",i);
			aplWeaponFlags[i][j]=GetGameVar(aszBuf,0, -1, j);
		
			sprintf(aszBuf,"WEAPON%d_SHOOTS",i);
			aplWeaponShoots[i][j]=GetGameVar(aszBuf,0, -1, j);
		
			sprintf(aszBuf,"WEAPON%d_SPAWNTIME",i);
			aplWeaponSpawnTime[i][j]=GetGameVar(aszBuf,0, -1, j);
		
			sprintf(aszBuf,"WEAPON%d_SPAWN",i);
			aplWeaponSpawn[i][j]=GetGameVar(aszBuf,0, -1, j);
		
			sprintf(aszBuf,"WEAPON%d_SHOTSPERBURST",i);
			aplWeaponShotsPerBurst[i][j]=GetGameVar(aszBuf,0, -1, j);
		
			sprintf(aszBuf,"WEAPON%d_WORKSLIKE",i);
			aplWeaponWorksLike[i][j]=GetGameVar(aszBuf,0, -1, j);
		
			sprintf(aszBuf,"WEAPON%d_INITIALSOUND",i);
			aplWeaponInitialSound[i][j]=GetGameVar(aszBuf,0, -1, j);
		
			sprintf(aszBuf,"WEAPON%d_FIRESOUND",i);
			aplWeaponFireSound[i][j]=GetGameVar(aszBuf,0, -1, j);

			sprintf(aszBuf,"WEAPON%d_SOUND2TIME",i);
			aplWeaponSound2Time[i][j]=GetGameVar(aszBuf,0, -1, j);

			sprintf(aszBuf,"WEAPON%d_SOUND2SOUND",i);
			aplWeaponSound2Sound[i][j]=GetGameVar(aszBuf,0, -1, j);
	
		}
	}

	g_iReturnVarID=GetGameID("RETURN");
	g_iWeaponVarID=GetGameID("WEAPON");
	g_iWorksLikeVarID=GetGameID("WORKSLIKE");
	g_iZRangeVarID=GetGameID("ZRANGE");
	g_iAngRangeVarID=GetGameID("ANGRANGE");
	g_iAimAngleVarID=GetGameID("AUTOAIMANGLE");
#ifdef EDUKE	
	g_iLoTagID=GetGameID("LOTAG");
	g_iHiTagID=GetGameID("HITAG");
	g_iTextureID=GetGameID("TEXTURE");
	g_iThisActorID=GetGameID("THISACTOR");
#endif

	//AddLog("EOF:ResetWeaponDefaults");

}
	
	
void InitGameVars(void)
{
	// only call ONCE

printf("Initializing Game Variables\n");
//AddLog("InitGameVars");

	ClearGameVars();

	AddSystemVars();

	InitGameVarPointers();

	ResetSystemDefaults();
	
}

void ClearGameEvents()
{
	int i;
	for (i=0;i<MAXGAMEEVENTS;i++)
	{
		apScriptGameEvent[i]=NULL;
	}
}

#endif


void loadefs(char *filenam,char *mptr)
{
	int i;
	long fs,fp;

#ifdef WW2	
	ClearGameEvents();
	
	InitGameVars();
#endif

	if(!SafeFileExists(filenam) && loadfromgrouponly == 0)
	{
		puts("Missing external con file(s).");
		puts("COPY INTERNAL DEFAULTS TO DIRECTORY(Y/n)?");

		KB_FlushKeyboardQueue();
		while( KB_KeyWaiting() );

		i = KB_Getch();
		if(i == 'y' || i == 'Y' )
		{
			puts(" Yes");
			copydefaultcons();
		}
	}

//sprintf(g_szBuf,"CP:%s %d",__FILE__,__LINE__);
//AddLog(g_szBuf);
	fp = kopen4load(filenam,loadfromgrouponly);
	if( fp == 0 )
	{
//sprintf(g_szBuf,"CP:%s %d",__FILE__,__LINE__);
//AddLog(g_szBuf);
		if( loadfromgrouponly == 1 )
		{
//sprintf(g_szBuf,"CP:%s %d",__FILE__,__LINE__);
//AddLog(g_szBuf);
			gameexit("\nMissing con file(s).");
		}

		loadfromgrouponly = 1;
		return; //Not there
	}
	else
	{
//sprintf(g_szBuf,"CP:%s %d",__FILE__,__LINE__);
//AddLog(g_szBuf);
		printf("Compiling: '%s'.\n",filenam);

		fs = kfilelength(fp);

		last_used_text = textptr = (char *) mptr;
		last_used_size = fs;

//sprintf(g_szBuf,"CP:%s %d (%ld)",__FILE__,__LINE__,fs);
//AddLog(g_szBuf);
		kread(fp,(char *)textptr,fs);
//sprintf(g_szBuf,"CP:%s %d",__FILE__,__LINE__);
//AddLog(g_szBuf);
		kclose(fp);
//sprintf(g_szBuf,"CP:%s %d",__FILE__,__LINE__);
//AddLog(g_szBuf);
	}

//sprintf(g_szBuf,"CP:%s %d",__FILE__,__LINE__);
//AddLog(g_szBuf);
	textptr[fs - 2] = 0;

	clearbuf(actorscrptr,MAXSPRITES,0L);
	clearbufbyte(actortype,MAXSPRITES,0L);

	labelcnt = 0;
	scriptptr = script+1;
	warning = 0;
	error = 0;
	line_number = 1;
	total_lines = 0;

//sprintf(g_szBuf,"CP:%s %d",__FILE__,__LINE__);
//AddLog(g_szBuf);
	passone(); //Tokenize
	*script = (long) scriptptr;
//sprintf(g_szBuf,"CP:%s %d",__FILE__,__LINE__);
//AddLog(g_szBuf);

	if(warning|error)
		printf("Found %ld warning(s), %ld error(s).\n",warning,error);

	if( error == 0 && warning != 0)
	{
		if( groupfile != -1 && loadfromgrouponly == 0 )
		{
			printf("\nWarnings found in %s file.  You should backup the original copies before\n",filenam);
#if (APPVER_DN3DREV < AV_DR_EDK20021)
			puts("before attempting to modify them.  Do you want to use the");
#else
			puts("before attempting to modify them.	 Do you want to use the");
#endif
			puts("INTERNAL DEFAULTS (y/N)?");

			KB_FlushKeyboardQueue();
			while( KB_KeyWaiting() );
			i = KB_Getch();
			if(i == 'y' || i == 'Y' )
			{
				loadfromgrouponly = 1;
				puts(" Yes");
				return;
			}
		}
	}

	if(error)
	{
		if( loadfromgrouponly )
		{
			sprintf(buf,"\nError in %s.",filenam);
			gameexit(buf);
		}
		else
		{
			if( groupfile != -1 && loadfromgrouponly == 0 )
			{
#if (APPVER_DN3DREV < AV_DR_EDK20021)
				printf("\nErrors found in %s file.  You should backup the original copies\n",filenam);
				puts("before attempting to modify them.  Do you want to use the");
#else
				printf("\nErrors found in %s file.	You should backup the original copies\n",filenam);
				puts("before attempting to modify them.	 Do you want to use the");
#endif
				puts("internal defaults (Y/N)?");

				KB_FlushKeyboardQueue();
				while( !KB_KeyWaiting() );

				i = KB_Getch();
				if( i == 'y' || i == 'Y' )
				{
					puts(" Yes");
					loadfromgrouponly = 1;
					return;
				}
				else gameexit("");
			}
		}
	}
	else
	{
		total_lines += line_number;
#ifdef WW2
		printf("Code Size:%ld bytes. %ld labels. %d/%d Variables.\n",
			   (long)((scriptptr-script)<<2)-4,
			   labelcnt,
			   iGameVarCount,
			   MAXGAMEVARS
			  );
#else
		printf("Code Size:%ld bytes(%ld labels).\n",(long)((scriptptr-script)<<2)-4,labelcnt);
#endif
	}
}

char dodge(spritetype *s)
{
	short i;
	long bx,by,mx,my,bxvect,byvect,mxvect,myvect,d;

	mx = s->x;
	my = s->y;
	mxvect = sintable[(s->ang+512)&2047]; myvect = sintable[s->ang&2047];

	for(i=headspritestat[4];i>=0;i=nextspritestat[i]) //weapons list
	{
		if( OW == i || SECT != s->sectnum)
			continue;

		bx = SX-mx;
		by = SY-my;
		bxvect = sintable[(SA+512)&2047]; byvect = sintable[SA&2047];

		if (mxvect*bx + myvect*by >= 0)
			if (bxvect*bx + byvect*by < 0)
		{
			d = bxvect*by - byvect*bx;
			if (klabs(d) < 65536*64)
			{
				s->ang -= 512+(TRAND&1024);
				return 1;
			}
		}
	}
	return 0;
}

short furthestangle(short i,short angs)
{
	short j, hitsect,hitwall,hitspr,furthest_angle, angincs;
	long hx, hy, hz, d, greatestd;
	spritetype *s = &sprite[i];

	greatestd = -(1<<30);
	angincs = 2048/angs;

	if(s->picnum != APLAYER)
		if( (g_t[0]&63) > 2 ) return( s->ang + 1024 );

	for(j=s->ang;j<(2048+s->ang);j+=angincs)
	{
		hitscan(s->x, s->y, s->z-(8<<8), s->sectnum,
			sintable[(j+512)&2047],
			sintable[j&2047],0,
			&hitsect,&hitwall,&hitspr,&hx,&hy,&hz,CLIPMASK1);

		d = klabs(hx-s->x) + klabs(hy-s->y);

		if(d > greatestd)
		{
			greatestd = d;
			furthest_angle = j;
		}
	}
	return (furthest_angle&2047);
}

short furthestcanseepoint(short i,spritetype *ts,long *dax,long *day)
{
	short j, hitsect,hitwall,hitspr, angincs, tempang;
	long hx, hy, hz, d, da;//, d, cd, ca,tempx,tempy,cx,cy;
	spritetype *s = &sprite[i];

	if( (g_t[0]&63) ) return -1;

	if(ud.multimode < 2 && ud.player_skill < 3)
		angincs = 2048/2;
	else angincs = 2048/(1+(TRAND&1));

	for(j=ts->ang;j<(2048+ts->ang);j+=(angincs-(TRAND&511)))
	{
		hitscan(ts->x, ts->y, ts->z-(16<<8), ts->sectnum,
			sintable[(j+512)&2047],
			sintable[j&2047],16384-(TRAND&32767),
			&hitsect,&hitwall,&hitspr,&hx,&hy,&hz,CLIPMASK1);

		d = klabs(hx-ts->x)+klabs(hy-ts->y);
		da = klabs(hx-s->x)+klabs(hy-s->y);

		if( d < da )
			if(cansee(hx,hy,hz,hitsect,s->x,s->y,s->z-(16<<8),s->sectnum))
		{
			*dax = hx;
			*day = hy;
			return hitsect;
		}
	}
	return -1;
}




void alterang(short a)
{
	short aang, angdif, goalang,j;
	long ticselapsed, *moveptr;

	moveptr = (long *)g_t[1];

	ticselapsed = (g_t[0])&31;

	aang = g_sp->ang;

	g_sp->xvel += (*moveptr-g_sp->xvel)/5;
	if(g_sp->zvel < 648) g_sp->zvel += ((*(moveptr+1)<<4)-g_sp->zvel)/5;

	if(a&seekplayer)
	{
		j = ps[g_p].holoduke_on;

// NOTE: looks like 'owner' is set to target sprite ID...
		
		if(j >= 0 && cansee(sprite[j].x,sprite[j].y,sprite[j].z,sprite[j].sectnum,g_sp->x,g_sp->y,g_sp->z,g_sp->sectnum) )
			g_sp->owner = j;
		else g_sp->owner = ps[g_p].i;

		if(sprite[g_sp->owner].picnum == APLAYER)
			goalang = getangle(hittype[g_i].lastvx-g_sp->x,hittype[g_i].lastvy-g_sp->y);
		else
			goalang = getangle(sprite[g_sp->owner].x-g_sp->x,sprite[g_sp->owner].y-g_sp->y);

		if(g_sp->xvel && g_sp->picnum != DRONE)
		{
			angdif = getincangle(aang,goalang);

			if(ticselapsed < 2)
			{
				if( klabs(angdif) < 256)
				{
					j = 128-(TRAND&256);
					g_sp->ang += j;
					if( hits(g_i) < 844 )
						g_sp->ang -= j;
				}
			}
			else if(ticselapsed > 18 && ticselapsed < 26) // choose
			{
				if(klabs(angdif>>2) < 128) g_sp->ang = goalang;
				else g_sp->ang += angdif>>2;
			}
		}
		else g_sp->ang = goalang;
	}

	if(ticselapsed < 1)
	{
		j = 2;
		if(a&furthestdir)
		{
			goalang = furthestangle(g_i,j);
			g_sp->ang = goalang;
			g_sp->owner = ps[g_p].i;
		}

		if(a&fleeenemy)
		{
			goalang = furthestangle(g_i,j);
			g_sp->ang = goalang; // += angdif; //  = getincangle(aang,goalang)>>1;
		}
	}
}

void move()
{
	long l, *moveptr;
	short j, a, goalang, angdif;
	long daxvel;

	a = g_sp->hitag;

	if(a == -1) a = 0;

	g_t[0]++;

	if(a&face_player)
	{
		if(ps[g_p].newowner >= 0)
			goalang = getangle(ps[g_p].oposx-g_sp->x,ps[g_p].oposy-g_sp->y);
		else goalang = getangle(ps[g_p].posx-g_sp->x,ps[g_p].posy-g_sp->y);
		angdif = getincangle(g_sp->ang,goalang)>>2;
		if(angdif > -8 && angdif < 0) angdif = 0;
		g_sp->ang += angdif;
	}

	if(a&spin)
		g_sp->ang += sintable[ ((g_t[0]<<3)&2047) ]>>6;

	if(a&face_player_slow)
	{
		if(ps[g_p].newowner >= 0)
			goalang = getangle(ps[g_p].oposx-g_sp->x,ps[g_p].oposy-g_sp->y);
		else goalang = getangle(ps[g_p].posx-g_sp->x,ps[g_p].posy-g_sp->y);
		angdif = ksgn(getincangle(g_sp->ang,goalang))<<5;
		if(angdif > -32 && angdif < 0)
		{
			angdif = 0;
			g_sp->ang = goalang;
		}
		g_sp->ang += angdif;
	}


	if((a&jumptoplayer) == jumptoplayer)
	{
		if(g_t[0] < 16)
			g_sp->zvel -= (sintable[(512+(g_t[0]<<4))&2047]>>5);
	}

	if(a&face_player_smart)
	{
		long newx,newy;

		newx = ps[g_p].posx+(ps[g_p].posxv/768);
		newy = ps[g_p].posy+(ps[g_p].posyv/768);
		goalang = getangle(newx-g_sp->x,newy-g_sp->y);
		angdif = getincangle(g_sp->ang,goalang)>>2;
		if(angdif > -8 && angdif < 0) angdif = 0;
		g_sp->ang += angdif;
	}

	if( g_t[1] == 0 || a == 0 )
	{
		if( ( badguy(g_sp) && g_sp->extra <= 0 ) || (hittype[g_i].bposx != g_sp->x) || (hittype[g_i].bposy != g_sp->y) )
		{
			hittype[g_i].bposx = g_sp->x;
			hittype[g_i].bposy = g_sp->y;
			setsprite(g_i,g_sp->x,g_sp->y,g_sp->z);
		}
		return;
	}

	moveptr = (long *)g_t[1];

	if(a&geth) g_sp->xvel += (*moveptr-g_sp->xvel)>>1;
	if(a&getv) g_sp->zvel += ((*(moveptr+1)<<4)-g_sp->zvel)>>1;

	if(a&dodgebullet)
		dodge(g_sp);

	if(g_sp->picnum != APLAYER)
		alterang(a);

	if(g_sp->xvel > -6 && g_sp->xvel < 6 ) g_sp->xvel = 0;

	a = badguy(g_sp);

	if(g_sp->xvel || g_sp->zvel)
	{
		if(a && g_sp->picnum != ROTATEGUN)
		{
			if( (g_sp->picnum == DRONE || g_sp->picnum == COMMANDER) && g_sp->extra > 0)
			{
				if(g_sp->picnum == COMMANDER)
				{
					hittype[g_i].floorz = l = getflorzofslope(g_sp->sectnum,g_sp->x,g_sp->y);
					if( g_sp->z > (l-(8<<8)) )
					{
						if( g_sp->z > (l-(8<<8)) ) g_sp->z = l-(8<<8);
						g_sp->zvel = 0;
					}

					hittype[g_i].ceilingz = l = getceilzofslope(g_sp->sectnum,g_sp->x,g_sp->y);
					if( (g_sp->z-l) < (80<<8) )
					{
						g_sp->z = l+(80<<8);
						g_sp->zvel = 0;
					}
				}
				else
				{
					if( g_sp->zvel > 0 )
					{
						hittype[g_i].floorz = l = getflorzofslope(g_sp->sectnum,g_sp->x,g_sp->y);
						if( g_sp->z > (l-(30<<8)) )
							g_sp->z = l-(30<<8);
					}
					else
					{
						hittype[g_i].ceilingz = l = getceilzofslope(g_sp->sectnum,g_sp->x,g_sp->y);
						if( (g_sp->z-l) < (50<<8) )
						{
							g_sp->z = l+(50<<8);
							g_sp->zvel = 0;
						}
					}
				}
			}
			else if(g_sp->picnum != ORGANTIC)
			{
				if(g_sp->zvel > 0 && hittype[g_i].floorz < g_sp->z)
					g_sp->z = hittype[g_i].floorz;
				if( g_sp->zvel < 0)
				{
					l = getceilzofslope(g_sp->sectnum,g_sp->x,g_sp->y);
					if( (g_sp->z-l) < (66<<8) )
					{
						g_sp->z = l+(66<<8);
						g_sp->zvel >>= 1;
					}
				}
			}
		}
		else if(g_sp->picnum == APLAYER)
			if( (g_sp->z-hittype[g_i].ceilingz) < (32<<8) )
				g_sp->z = hittype[g_i].ceilingz+(32<<8);

		daxvel = g_sp->xvel;
		angdif = g_sp->ang;

		if( a && g_sp->picnum != ROTATEGUN )
		{
			if( g_x < 960 && g_sp->xrepeat > 16 )
			{

				daxvel = -(1024-g_x);
				angdif = getangle(ps[g_p].posx-g_sp->x,ps[g_p].posy-g_sp->y);

				if(g_x < 512)
				{
					ps[g_p].posxv = 0;
					ps[g_p].posyv = 0;
				}
				else
				{
					ps[g_p].posxv = mulscale(ps[g_p].posxv,dukefriction-0x2000,16);
					ps[g_p].posyv = mulscale(ps[g_p].posyv,dukefriction-0x2000,16);
				}
			}
			else if(g_sp->picnum != DRONE && g_sp->picnum != SHARK && g_sp->picnum != COMMANDER)
			{
				if( hittype[g_i].bposz != g_sp->z || ( ud.multimode < 2 && ud.player_skill < 2 ) )
				{
					if( (g_t[0]&1) || ps[g_p].actorsqu == g_i ) return;
					else daxvel <<= 1;
				}
				else
				{
					if( (g_t[0]&3) || ps[g_p].actorsqu == g_i ) return;
					else daxvel <<= 2;
				}
			}
		}

		hittype[g_i].movflag = movesprite(g_i,
			(daxvel*(sintable[(angdif+512)&2047]))>>14,
			(daxvel*(sintable[angdif&2047]))>>14,g_sp->zvel,CLIPMASK0);
   }

   if( a )
   {
	   if (sector[g_sp->sectnum].ceilingstat&1)
		   g_sp->shade += (sector[g_sp->sectnum].ceilingshade-g_sp->shade)>>1;
	   else g_sp->shade += (sector[g_sp->sectnum].floorshade-g_sp->shade)>>1;

	   if( sector[g_sp->sectnum].floorpicnum == MIRROR )
		   deletesprite(g_i);
   }
}

char parse(void);

void parseifelse(long condition)
{
	if( condition )
	{
		// skip 'else' pointer.. and...
		insptr+=2;
		parse();
	}
	else
	{
		insptr = (long *) *(insptr+1);
		if(*insptr == 10)
		{
			// else...

			// skip 'else' and...
			insptr+=2;
			
			parse();
		}
	}
}

// long *it = 0x00589a04;

char parse(void)
{
	long j, l, s;

#ifdef WW2
	if(bDebugFunStuff)
	{
		sprintf(g_szBuf,"Parse() : %ld",*insptr);
		AddLog(g_szBuf);
	}
#endif

	if(killit_flag) return 1;

//	  if(*it == 1668249134L) gameexit("\nERR");
#ifdef WW2
//	sprintf(g_szBuf,"Parsing: %d",*insptr);
//	AddLog(g_szBuf);
#endif

	switch(*insptr)
	{
		case 3:
			insptr++;
			parseifelse( rnd(*insptr));
			break;
		case 45:

			if(g_x > 1024)
			{
				short temphit, sclip, angdif;

				if( badguy(g_sp) && g_sp->xrepeat > 56 )
				{
					sclip = 3084;
					angdif = 48;
				}
				else
				{
					sclip = 768;
					angdif = 16;
				}

				j = hitasprite(g_i,&temphit);
				if(j == (1<<30))
				{
					parseifelse(1);
					break;
				}
				if(j > sclip)
				{
					if(temphit >= 0 && sprite[temphit].picnum == g_sp->picnum)
						j = 0;
					else
					{
						g_sp->ang += angdif;j = hitasprite(g_i,&temphit);g_sp->ang -= angdif;
						if(j > sclip)
						{
							if(temphit >= 0 && sprite[temphit].picnum == g_sp->picnum)
								j = 0;
							else
							{
								g_sp->ang -= angdif;j = hitasprite(g_i,&temphit);g_sp->ang += angdif;
								if( j > 768 )
								{
									if(temphit >= 0 && sprite[temphit].picnum == g_sp->picnum)
										j = 0;
									else j = 1;
								}
								else j = 0;
							}
						}
						else j = 0;
					}
				}
				else j =  0;
			}
			else j = 1;

			parseifelse(j);
			break;
		case 91:
			j = cansee(g_sp->x,g_sp->y,g_sp->z-((TRAND&41)<<8),g_sp->sectnum,ps[g_p].posx,ps[g_p].posy,ps[g_p].posz/*-((TRAND&41)<<8)*/,sprite[ps[g_p].i].sectnum);
			parseifelse(j);
			if( j ) hittype[g_i].timetosleep = SLEEPTIME;
			break;

		case 49:
			parseifelse(hittype[g_i].actorstayput == -1);
			break;
		case 5:
		{
			spritetype *s;
			short sect;

			// select sprite for monster to target
			// if holoduke is on, let them target holoduke first.
			// 
			if(ps[g_p].holoduke_on >= 0)
			{
				s = &sprite[ps[g_p].holoduke_on];
				j = cansee(g_sp->x,g_sp->y,g_sp->z-(TRAND&((32<<8)-1)),g_sp->sectnum,
					   s->x,s->y,s->z,s->sectnum);
				
				if(j == 0)
				{
					// they can't see player's holoduke
					// check for player...
					s = &sprite[ps[g_p].i];
				}
			}
			else s = &sprite[ps[g_p].i];	// holoduke not on. look for player

			// can they see player, (or player's holoduke)
			j = cansee(g_sp->x,g_sp->y,g_sp->z-(TRAND&((47<<8))),g_sp->sectnum,
				s->x,s->y,s->z-(24<<8),s->sectnum);

			if(j == 0)
			{
				// they can't see it.

				// Huh?.  This does nothing....
				// (the result is always j==0....)
				if( ( klabs(hittype[g_i].lastvx-g_sp->x)+klabs(hittype[g_i].lastvy-g_sp->y) ) <
					( klabs(hittype[g_i].lastvx-s->x)+klabs(hittype[g_i].lastvy-s->y) ) )
						j = 0;

				// um yeah, this if() will always fire....
				if( j == 0 )
				{
					// search around for target player
					
					// also modifies 'target' x&y if found..
					
					j = furthestcanseepoint(g_i,s,&hittype[g_i].lastvx,&hittype[g_i].lastvy);

					if(j == -1) j = 0;
					else j = 1;
				}
			}
			else
			{
				// else, they did see it.
				// save where we were looking...
				hittype[g_i].lastvx = s->x;
				hittype[g_i].lastvy = s->y;
			}

			if( j == 1 && ( g_sp->statnum == 1 || g_sp->statnum == 6 ) )
				hittype[g_i].timetosleep = SLEEPTIME;

			parseifelse(j == 1);
			break;
		}

		case 6:
			parseifelse(ifhitbyweapon(g_i) >= 0);
			break;
		case 27:
			parseifelse( ifsquished(g_i, g_p) == 1);
			break;
		case 26:
			{
				j = g_sp->extra;
				if(g_sp->picnum == APLAYER)
					j--;
				parseifelse(j < 0);
			}
			break;
		case 24:
			insptr++;
			g_t[5] = *insptr;
			g_t[4] = *(long *)(g_t[5]);		  // Action
			g_t[1] = *(long *)(g_t[5]+4);		// move
			g_sp->hitag = *(long *)(g_t[5]+8);	  // Ai
			g_t[0] = g_t[2] = g_t[3] = 0;
			if(g_sp->hitag&random_angle)
				g_sp->ang = TRAND&2047;
			insptr++;
			break;
		case 7:
			insptr++;
			g_t[2] = 0;
			g_t[3] = 0;
			g_t[4] = *insptr;
			insptr++;
			break;

		case 8:
			insptr++;
			parseifelse(g_x < *insptr);
			if(g_x > MAXSLEEPDIST && hittype[g_i].timetosleep == 0)
				hittype[g_i].timetosleep = SLEEPTIME;
			break;
		case 9:
			insptr++;
			parseifelse(g_x > *insptr);
			if(g_x > MAXSLEEPDIST && hittype[g_i].timetosleep == 0)
				hittype[g_i].timetosleep = SLEEPTIME;
			break;
		case 10:
			insptr = (long *) *(insptr+1);
			break;
		case 100:
			insptr++;
			g_sp->extra += *insptr;
			insptr++;
			break;
		case 11:
			insptr++;
			g_sp->extra = *insptr;
			insptr++;
			break;
		case 94:
			insptr++;

			if(ud.coop >= 1 && ud.multimode > 1)
			{
				if(*insptr == 0)
				{
					for(j=0;j < ps[g_p].weapreccnt;j++)
						if( ps[g_p].weaprecs[j] == g_sp->picnum )
							break;

					parseifelse(j < ps[g_p].weapreccnt && g_sp->owner == g_i);
				}
				else if(ps[g_p].weapreccnt < 16)
				{
					ps[g_p].weaprecs[ps[g_p].weapreccnt++] = g_sp->picnum;
					parseifelse(g_sp->owner == g_i);
				}
			}
			else parseifelse(0);
			break;
		case 95:
			insptr++;
			if(g_sp->picnum == APLAYER)
				g_sp->pal = ps[g_sp->yvel].palookup;
			else g_sp->pal = hittype[g_i].tempang;
			hittype[g_i].tempang = 0;
			break;
		case 104:
			insptr++;
			checkweapons(&ps[g_sp->yvel]);
			break;
		case 106:
			insptr++;
			break;
		case 97:
			insptr++;
			if(Sound[g_sp->yvel].num == 0)
				spritesound(g_sp->yvel,g_i);
			break;
		case 96:
			insptr++;

			if( ud.multimode > 1 && g_sp->picnum == APLAYER )
			{
				if(ps[otherp].quick_kick == 0)
					ps[otherp].quick_kick = 14;
			}
			else if(g_sp->picnum != APLAYER && ps[g_p].quick_kick == 0)
				ps[g_p].quick_kick = 14;
			break;
		case 28:
			insptr++;

			j = ((*insptr)-g_sp->xrepeat)<<1;
			g_sp->xrepeat += ksgn(j);

			insptr++;

			if( ( g_sp->picnum == APLAYER && g_sp->yrepeat < 36 ) || *insptr < g_sp->yrepeat || ((g_sp->yrepeat*(tilesizy[g_sp->picnum]+8))<<2) < (hittype[g_i].floorz - hittype[g_i].ceilingz) )
			{
				j = ((*insptr)-g_sp->yrepeat)<<1;
				if( klabs(j) ) g_sp->yrepeat += ksgn(j);
			}

			insptr++;

			break;
		case 99:
			insptr++;
			g_sp->xrepeat = (char) *insptr;
			insptr++;
			g_sp->yrepeat = (char) *insptr;
			insptr++;
			break;
		case 13:
			insptr++;
			shoot(g_i,(short)*insptr);
			insptr++;
			break;
		case 87:
			insptr++;
			if( Sound[*insptr].num == 0 )
				spritesound((short) *insptr,g_i);
			insptr++;
			break;
#if (APPVER_DN3DREV >= AV_DR_EDK20021)
		case CON_IFSOUND:
			insptr++;
			parseifelse( Sound[*insptr].num == 0 );
			break;
#endif
		case 89:
			insptr++;
			if( Sound[*insptr].num > 0 )
				stopsound((short)*insptr);
			insptr++;
			break;
		case 92:
			insptr++;
			if(g_p == screenpeek || ud.coop==1)
				spritesound((short) *insptr,ps[screenpeek].i);
			insptr++;
			break;
		case 15:
			insptr++;
			spritesound((short) *insptr,g_i);
			insptr++;
			break;
		case 84:
			insptr++;
			ps[g_p].tipincs = 26;
			break;
		case 16:
			insptr++;
			g_sp->xoffset = 0;
			g_sp->yoffset = 0;
//			  if(!gotz)
			{
				long c;

				if( floorspace(g_sp->sectnum) )
					c = 0;
				else
				{
					if( ceilingspace(g_sp->sectnum) || sector[g_sp->sectnum].lotag == 2)
						c = gc/6;
					else c = gc;
				}

				if( hittype[g_i].cgg <= 0 || (sector[g_sp->sectnum].floorstat&2) )
				{
					getglobalz(g_i);
					hittype[g_i].cgg = 6;
				}
				else hittype[g_i].cgg --;

				if( g_sp->z < (hittype[g_i].floorz-FOURSLEIGHT) )
				{
					g_sp->zvel += c;
					g_sp->z+=g_sp->zvel;

					if(g_sp->zvel > 6144) g_sp->zvel = 6144;
				}
				else
				{
					g_sp->z = hittype[g_i].floorz - FOURSLEIGHT;

					if( badguy(g_sp) || ( g_sp->picnum == APLAYER && g_sp->owner >= 0) )
					{

						if( g_sp->zvel > 3084 && g_sp->extra <= 1)
						{
							if(g_sp->pal != 1 && g_sp->picnum != DRONE)
							{
								if(g_sp->picnum == APLAYER && g_sp->extra > 0)
									goto SKIPJIBS;
								guts(g_sp,JIBS6,15,g_p);
								spritesound(SQUISHED,g_i);
								spawn(g_i,BLOODPOOL);
							}

							SKIPJIBS:

							hittype[g_i].picnum = SHOTSPARK1;
							hittype[g_i].extra = 1;
							g_sp->zvel = 0;
						}
						else if(g_sp->zvel > 2048 && sector[g_sp->sectnum].lotag != 1)
						{

							j = g_sp->sectnum;
							pushmove(&g_sp->x,&g_sp->y,&g_sp->z,&j,128L,(4L<<8),(4L<<8),CLIPMASK0);
							if(j != g_sp->sectnum && j >= 0 && j < MAXSECTORS)
								changespritesect(g_i,j);

							spritesound(THUD,g_i);
						}
					}
					if(sector[g_sp->sectnum].lotag == 1)
						switch (g_sp->picnum)
						{
							case OCTABRAIN:
							case COMMANDER:
							case DRONE:
								break;
							default:
								g_sp->z += (24<<8);
								break;
						}
					else g_sp->zvel = 0;
				}
			}

			break;
		case 4:
		case 12:
		case 18:
			return 1;
		case 30:
			insptr++;
			return 1;
		case 2:
			insptr++;
			if( ps[g_p].ammo_amount[*insptr] >= max_ammo_amount[*insptr] )
			{
				killit_flag = 2;
				break;
			}
			addammo( *insptr, &ps[g_p], *(insptr+1) );
			if(ps[g_p].curr_weapon == KNEE_WEAPON)
				if( ps[g_p].gotweapon[*insptr] )
					addweapon( &ps[g_p], *insptr );
			insptr += 2;
			break;
		case 86:
			insptr++;
			lotsofmoney(g_sp,*insptr);
			insptr++;
			break;
		case 102:
			insptr++;
			lotsofmail(g_sp,*insptr);
			insptr++;
			break;
		case 105:
			insptr++;
			hittype[g_i].timetosleep = (short)*insptr;
			insptr++;
			break;
		case 103:
			insptr++;
			lotsofpaper(g_sp,*insptr);
			insptr++;
			break;
		case 88:
			insptr++;
			ps[g_p].actors_killed += *insptr;
			hittype[g_i].actorstayput = -1;
			insptr++;
			break;
		case 93:
			insptr++;
			spriteglass(g_i,*insptr);
			insptr++;
			break;
		case 22:
			insptr++;
			killit_flag = 1;
			break;
		case 23:
			insptr++;
			if( ps[g_p].gotweapon[*insptr] == 0 ) addweapon( &ps[g_p], *insptr );
			else if( ps[g_p].ammo_amount[*insptr] >= max_ammo_amount[*insptr] )
			{
				 killit_flag = 2;
				 break;
			}
			addammo( *insptr, &ps[g_p], *(insptr+1) );
			if(ps[g_p].curr_weapon == KNEE_WEAPON)
				if( ps[g_p].gotweapon[*insptr] )
					addweapon( &ps[g_p], *insptr );
			insptr+=2;
			break;
		case 68:
			insptr++;
			printf("%ld\n",*insptr);
			insptr++;
			break;
		case 69:
			insptr++;
			ps[g_p].timebeforeexit = *insptr;
			ps[g_p].customexitsound = -1;
			ud.eog = 1;
			insptr++;
			break;
		case 25:
			insptr++;

			if(ps[g_p].newowner >= 0)
			{
				ps[g_p].newowner = -1;
				ps[g_p].posx = ps[g_p].oposx;
				ps[g_p].posy = ps[g_p].oposy;
				ps[g_p].posz = ps[g_p].oposz;
				ps[g_p].ang = ps[g_p].oang;
				updatesector(ps[g_p].posx,ps[g_p].posy,&ps[g_p].cursectnum);
				setpal(&ps[g_p]);

				j = headspritestat[1];
				while(j >= 0)
				{
					if(sprite[j].picnum==CAMERA1)
						sprite[j].yvel = 0;
					j = nextspritestat[j];
				}
			}

			j = sprite[ps[g_p].i].extra;

			if(g_sp->picnum != ATOMICHEALTH)
			{
				if( j > max_player_health && *insptr > 0 )
				{
					insptr++;
					break;
				}
				else
				{
					if(j > 0)
						j += *insptr;
					if ( j > max_player_health && *insptr > 0 )
						j = max_player_health;
				}
			}
			else
			{
				if( j > 0 )
					j += *insptr;
				if ( j > (max_player_health<<1) )
					j = (max_player_health<<1);
			}

			if(j < 0) j = 0;

			if(ud.god == 0)
			{
				if(*insptr > 0)
				{
					if( ( j - *insptr ) < (max_player_health>>2) &&
						j >= (max_player_health>>2) )
							spritesound(DUKE_GOTHEALTHATLOW,ps[g_p].i);

					ps[g_p].last_extra = j;
				}

				sprite[ps[g_p].i].extra = j;
			}

			insptr++;
			break;
		case 17:
			{
				long *tempscrptr;

				tempscrptr = insptr+2;

				insptr = (long *) *(insptr+1);
				while(1) if(parse()) break;
				insptr = tempscrptr;
			}
			break;
		case 29:
			insptr++;
			while(1) if(parse()) break;
			break;
		case 32:
			g_t[0]=0;
			insptr++;
			g_t[1] = *insptr;
			insptr++;
			g_sp->hitag = *insptr;
			insptr++;
			if(g_sp->hitag&random_angle)
				g_sp->ang = TRAND&2047;
			break;
#ifdef EDUKE
		case CON_ESPAWNVAR:
		{
			long lReturn;
			long lIn;
			lReturn=-1;
			insptr++;

			lIn=*insptr++;
			lIn=GetGameVarID(lIn, g_i, g_p);
			if(g_sp->sectnum >= 0 && g_sp->sectnum < MAXSECTORS)
				lReturn = spawn(g_i, lIn);

			SetGameVarID(g_iReturnVarID, lReturn, g_i, g_p);
			break;
		}
		case CON_ESPAWN:
		{
			long lReturn;
			lReturn=-1;
			insptr++;
			if(g_sp->sectnum >= 0 && g_sp->sectnum < MAXSECTORS)
				lReturn = spawn(g_i,*insptr);
			insptr++;
			SetGameVarID(g_iReturnVarID, lReturn, g_i, g_p);
			break;
		}
#endif
		case 31:
			insptr++;
			if(g_sp->sectnum >= 0 && g_sp->sectnum < MAXSECTORS)
				spawn(g_i,*insptr);
			insptr++;
			break;
		case 33:
			insptr++;
			parseifelse( hittype[g_i].picnum == *insptr);
			break;
		case 21:
			insptr++;
			parseifelse(g_t[5] == *insptr);
			break;
		case 34:
			insptr++;
			parseifelse(g_t[4] == *insptr);
			break;
		case 35:
			insptr++;
			parseifelse(g_t[2] >= *insptr);
			break;
		case 36:
			insptr++;
			g_t[2] = 0;
			break;
		case 37:
			{
				short dnum;

				insptr++;
				dnum = *insptr;
				insptr++;

				if(g_sp->sectnum >= 0 && g_sp->sectnum < MAXSECTORS)
					for(j=(*insptr)-1;j>=0;j--)
				{
					if(g_sp->picnum == BLIMP && dnum == SCRAP1)
						s = 0;
					else s = (TRAND%3);

					l = EGS(g_sp->sectnum,
							g_sp->x+(TRAND&255)-128,g_sp->y+(TRAND&255)-128,g_sp->z-(8<<8)-(TRAND&8191),
							dnum+s,g_sp->shade,32+(TRAND&15),32+(TRAND&15),
							TRAND&2047,(TRAND&127)+32,
							-(TRAND&2047),g_i,5);
					if(g_sp->picnum == BLIMP && dnum == SCRAP1)
						sprite[l].yvel = weaponsandammosprites[j%14];
					else sprite[l].yvel = -1;
					sprite[l].pal = g_sp->pal;
				}
				insptr++;
			}
			break;
		case 52:
			insptr++;
			g_t[0] = (short) *insptr;
			insptr++;
			break;
		case 101:
			insptr++;
			g_sp->cstat |= (short)*insptr;
			insptr++;
			break;
		case 110:
			insptr++;
			g_sp->clipdist = (short) *insptr;
			insptr++;
			break;
		case 40:
			insptr++;
			g_sp->cstat = (short) *insptr;
			insptr++;
			break;
		case 41:
			insptr++;
			parseifelse(g_t[1] == *insptr);
			break;
		case 42:
			insptr++;

//AddLog("resetplayer");				
			if(ud.multimode < 2)
			{
				if( lastsavedpos >= 0 && ud.recstat != 2 )
				{
					ps[g_p].gm = MODE_MENU;
					KB_ClearKeyDown(sc_Space);
					cmenu(15000);
				}
				else ps[g_p].gm = MODE_RESTART;
				killit_flag = 2;
			}
			else
			{
				pickrandomspot(g_p);
				g_sp->x = hittype[g_i].bposx = ps[g_p].bobposx = ps[g_p].oposx = ps[g_p].posx;
				g_sp->y = hittype[g_i].bposy = ps[g_p].bobposy = ps[g_p].oposy =ps[g_p].posy;
				g_sp->z = hittype[g_i].bposy = ps[g_p].oposz =ps[g_p].posz;
				updatesector(ps[g_p].posx,ps[g_p].posy,&ps[g_p].cursectnum);
				setsprite(ps[g_p].i,ps[g_p].posx,ps[g_p].posy,ps[g_p].posz+PHEIGHT);
				g_sp->cstat = 257;

				g_sp->shade = -12;
				g_sp->clipdist = 64;
				g_sp->xrepeat = 42;
				g_sp->yrepeat = 36;
				g_sp->owner = g_i;
				g_sp->xoffset = 0;
				g_sp->pal = ps[g_p].palookup;

				ps[g_p].last_extra = g_sp->extra = max_player_health;
				ps[g_p].wantweaponfire = -1;
				ps[g_p].horiz = 100;
				ps[g_p].on_crane = -1;
				ps[g_p].frag_ps = g_p;
				ps[g_p].horizoff = 0;
				ps[g_p].opyoff = 0;
				ps[g_p].wackedbyactor = -1;
				ps[g_p].shield_amount = max_armour_amount;
				ps[g_p].dead_flag = 0;
				ps[g_p].pals_time = 0;
				ps[g_p].footprintcount = 0;
				ps[g_p].weapreccnt = 0;
				ps[g_p].fta = 0;
				ps[g_p].ftq = 0;
				ps[g_p].posxv = ps[g_p].posyv = 0;
				ps[g_p].rotscrnang = 0;

				ps[g_p].falling_counter = 0;

				hittype[g_i].extra = -1;
				hittype[g_i].owner = g_i;

				hittype[g_i].cgg = 0;
				hittype[g_i].movflag = 0;
				hittype[g_i].tempang = 0;
				hittype[g_i].actorstayput = -1;
				hittype[g_i].dispicnum = 0;
				hittype[g_i].owner = ps[g_p].i;

				resetinventory(g_p);
				resetweapons(g_p);

				cameradist = 0;
				cameraclock = totalclock;
			}
			setpal(&ps[g_p]);
//AddLog("EOF: resetplayer");

			break;
		case 43:
			parseifelse( klabs(g_sp->z-sector[g_sp->sectnum].floorz) < (32<<8) && sector[g_sp->sectnum].lotag == 1);
			break;
		case 44:
			parseifelse( sector[g_sp->sectnum].lotag == 2);
			break;
		case 46:
			insptr++;
			parseifelse(g_t[0] >= *insptr);
			break;
		case 53:
			insptr++;
			parseifelse(g_sp->picnum == *insptr);
			break;
		case 47:
			insptr++;
			g_t[0] = 0;
			break;
		case 48:
			insptr+=2;
			switch(*(insptr-1))
			{
				case 0:
					ps[g_p].steroids_amount = *insptr;
					ps[g_p].inven_icon = 2;
					break;
				case 1:
					ps[g_p].shield_amount +=		  *insptr;// 100;
					if(ps[g_p].shield_amount > max_player_health)
						ps[g_p].shield_amount = max_player_health;
					break;
				case 2:
					ps[g_p].scuba_amount =			   *insptr;// 1600;
					ps[g_p].inven_icon = 6;
					break;
				case 3:
					ps[g_p].holoduke_amount =		   *insptr;// 1600;
					ps[g_p].inven_icon = 3;
					break;
				case 4:
					ps[g_p].jetpack_amount =		   *insptr;// 1600;
					ps[g_p].inven_icon = 4;
					break;
				case 6:
					switch(g_sp->pal)
					{
						case  0: ps[g_p].got_access |= 1;break;
						case 21: ps[g_p].got_access |= 2;break;
						case 23: ps[g_p].got_access |= 4;break;
					}
					break;
				case 7:
					ps[g_p].heat_amount = *insptr;
					ps[g_p].inven_icon = 5;
					break;
				case 9:
					ps[g_p].inven_icon = 1;
					ps[g_p].firstaid_amount = *insptr;
					break;
				case 10:
					ps[g_p].inven_icon = 7;
					ps[g_p].boot_amount = *insptr;
					break;
			}
			insptr++;
			break;
		case 50:
			hitradius(g_i,*(insptr+1),*(insptr+2),*(insptr+3),*(insptr+4),*(insptr+5));
			insptr+=6;
			break;
		case 51:
			{
				insptr++;

				l = *insptr;
				j = 0;

				s = g_sp->xvel;

				if( (l&8) && ps[g_p].on_ground && (sync[g_p].bits&2) )
					   j = 1;
				else if( (l&16) && ps[g_p].jumping_counter == 0 && !ps[g_p].on_ground &&
					ps[g_p].poszv > 2048 )
						j = 1;
				else if( (l&32) && ps[g_p].jumping_counter > 348 )
					   j = 1;
				else if( (l&1) && s >= 0 && s < 8)
					   j = 1;
				else if( (l&2) && s >= 8 && !(sync[g_p].bits&(1<<5)) )
					   j = 1;
				else if( (l&4) && s >= 8 && sync[g_p].bits&(1<<5) )
					   j = 1;
				else if( (l&64) && ps[g_p].posz < (g_sp->z-(48<<8)) )
					   j = 1;
				else if( (l&128) && s <= -8 && !(sync[g_p].bits&(1<<5)) )
					   j = 1;
				else if( (l&256) && s <= -8 && (sync[g_p].bits&(1<<5)) )
					   j = 1;
				else if( (l&512) && ( ps[g_p].quick_kick > 0 || ( ps[g_p].curr_weapon == KNEE_WEAPON && ps[g_p].kickback_pic > 0 ) ) )
					   j = 1;
				else if( (l&1024) && sprite[ps[g_p].i].xrepeat < 32 )
					   j = 1;
				else if( (l&2048) && ps[g_p].jetpack_on )
					   j = 1;
				else if( (l&4096) && ps[g_p].steroids_amount > 0 && ps[g_p].steroids_amount < 400 )
					   j = 1;
				else if( (l&8192) && ps[g_p].on_ground)
					   j = 1;
				else if( (l&16384) && sprite[ps[g_p].i].xrepeat > 32 && sprite[ps[g_p].i].extra > 0 && ps[g_p].timebeforeexit == 0 )
					   j = 1;
				else if( (l&32768) && sprite[ps[g_p].i].extra <= 0)
					   j = 1;
				else if( (l&65536L) )
				{
					if(g_sp->picnum == APLAYER && ud.multimode > 1)
						j = getincangle(ps[otherp].ang,getangle(ps[g_p].posx-ps[otherp].posx,ps[g_p].posy-ps[otherp].posy));
					else
						j = getincangle(ps[g_p].ang,getangle(g_sp->x-ps[g_p].posx,g_sp->y-ps[g_p].posy));

					if( j > -128 && j < 128 )
						j = 1;
					else
						j = 0;
				}

				parseifelse((long) j);

			}
			break;
		case 56:
			insptr++;
			parseifelse(g_sp->extra <= *insptr);
			break;
		case 58:
			insptr += 2;
			guts(g_sp,*(insptr-1),*insptr,g_p);
			insptr++;
			break;
		case 59:
			insptr++;
//			  if(g_sp->owner >= 0 && sprite[g_sp->owner].picnum == *insptr)
  //			  parseifelse(1);
//			  else
			parseifelse( hittype[g_i].picnum == *insptr);
			break;
		case 61:
			insptr++;
			forceplayerangle(&ps[g_p]);
			return 0;
		case 62:
			insptr++;
			parseifelse( (( hittype[g_i].floorz - hittype[g_i].ceilingz ) >> 8 ) < *insptr);
			break;
		case 63:
			parseifelse( sync[g_p].bits&(1<<29));
			break;
		case 64:
			parseifelse(sector[g_sp->sectnum].ceilingstat&1);
			break;
		case 65:
			parseifelse(ud.multimode > 1);
			break;
		case 66:
			insptr++;
			if( sector[g_sp->sectnum].lotag == 0 )
			{
				neartag(g_sp->x,g_sp->y,g_sp->z-(32<<8),g_sp->sectnum,g_sp->ang,&neartagsector,&neartagwall,&neartagsprite,&neartaghitdist,768L,1);
				if( neartagsector >= 0 && isanearoperator(sector[neartagsector].lotag) )
					if( (sector[neartagsector].lotag&0xff) == 23 || sector[neartagsector].floorz == sector[neartagsector].ceilingz )
						if( (sector[neartagsector].lotag&16384) == 0 )
							if( (sector[neartagsector].lotag&32768) == 0 )
						{
							j = headspritesect[neartagsector];
							while(j >= 0)
							{
								if(sprite[j].picnum == ACTIVATOR)
									break;
								j = nextspritesect[j];
							}
							if(j == -1)
								operatesectors(neartagsector,g_i);
						}
			}
			break;
		case 67:
			parseifelse(ceilingspace(g_sp->sectnum));
			break;

		case 74:
			insptr++;
			if(g_sp->picnum != APLAYER)
				hittype[g_i].tempang = g_sp->pal;
			g_sp->pal = *insptr;
			insptr++;
			break;

		case 77:
			insptr++;
			g_sp->picnum = *insptr;
			insptr++;
			break;

		case 70:
			parseifelse( dodge(g_sp) == 1);
			break;
		case 71:
			if( badguy(g_sp) )
				parseifelse( ud.respawn_monsters );
			else if( inventory(g_sp) )
				parseifelse( ud.respawn_inventory );
			else
				parseifelse( ud.respawn_items );
			break;
		case 72:
			insptr++;
//			  getglobalz(g_i);
			parseifelse( (hittype[g_i].floorz - g_sp->z) <= ((*insptr)<<8));
			break;
		case 73:
			insptr++;
//			  getglobalz(g_i);
			parseifelse( ( g_sp->z - hittype[g_i].ceilingz ) <= ((*insptr)<<8));
			break;
		case 14:

			insptr++;
			ps[g_p].pals_time = *insptr;
			insptr++;
			for(j=0;j<3;j++)
			{
				ps[g_p].pals[j] = *insptr;
				insptr++;
			}
			break;

/*		  case 74:
			insptr++;
			getglobalz(g_i);
			parseifelse( (( hittype[g_i].floorz - hittype[g_i].ceilingz ) >> 8 ) >= *insptr);
			break;
*/
#ifdef WW2
		case CON_ADDLOG:
		{	long l;
			insptr++;
			l=*(insptr++);	// var
			sprintf(g_szBuf,"CONLOG: L=%ld",l);
			AddLog(g_szBuf);
			break;
		}
		case CON_ADDLOGVAR:
		{	long l;
			char szBuf[256];
			insptr++;
			l=*(insptr++);	// l=Line number, *instpr=varID
			if( (*insptr >= iGameVarCount)
				|| *insptr < 0
			  )
			{
				// invalid varID
				insptr++;
				sprintf(g_szBuf,"CONLOGVAR: L=%ld INVALID VARIABLE",l);
				AddLog(g_szBuf);
				break;	// out of switch
			}
			sprintf(szBuf,"CONLOGVAR: L=%ld %s ",l, aGameVars[*insptr].szLabel);
			strcpy(g_szBuf,szBuf);
			
			if( aGameVars[*insptr].dwFlags & GAMEVAR_FLAG_READONLY)
			{
				sprintf(szBuf," (read-only)");
				strcat(g_szBuf,szBuf);
			}
			if( aGameVars[*insptr].dwFlags & GAMEVAR_FLAG_PERPLAYER)
			{
				sprintf(szBuf," (Per Player. Player=%d)",g_p);
			}
			else if( aGameVars[*insptr].dwFlags & GAMEVAR_FLAG_PERACTOR)
			{
				sprintf(szBuf," (Per Actor. Actor=%d)",g_i);
			}
			else
			{
				sprintf(szBuf," (Global)");
			}
			strcat(g_szBuf,szBuf);
			sprintf(szBuf," =%ld",	GetGameVarID(*insptr, g_i, g_p));
			strcat(g_szBuf,szBuf);
			AddLog(g_szBuf);
			insptr++;
			break;
		}
#ifdef EDUKE			
		case CON_SETSECTOR:
		case CON_GETSECTOR:
		{
			// syntax [gs]etsector[<var>].x <VAR>
			// <varid> <xxxid> <varid>
			long lLabelID;
			long lVar1, lVar2;
			long lWhat;
			
			lWhat=*(insptr++);
			lVar1=*(insptr++);
			lLabelID=*(insptr++);
			lVar2=*(insptr++);
			DoSector(lWhat==CON_SETSECTOR, lVar1, lLabelID, lVar2, g_i, g_p);
			break;
		}
		case CON_SQRT:
		{
			// syntax sqrt <invar> <outvar>

			long lInVarID;
			long lOutVarID;
			long lIn;

			insptr++;
			lInVarID=*(insptr++);
			lOutVarID=*(insptr++);
			lIn=GetGameVarID(lInVarID, g_i, g_p);
			SetGameVarID(lOutVarID, ksqrt(lIn), g_i, g_p);
			break;
		}
		case CON_FINDNEARACTOR:
		{
			// syntax findnearactorvar <type> <maxdist> <getvar>
			// gets the sprite ID of the nearest actor within max dist
			// that is of <type> into <getvar>
			// -1 for none found
			// <type> <maxdist> <varid>
			long lType;
			long lMaxDist;
			long lVarID;
			long lTemp;
			long lFound;
			long lDist;
			short j;

			insptr++;

			lType=*(insptr++);
			lMaxDist=*(insptr++);
			lVarID=*(insptr++);

			lFound=-1;
			lDist=32767;	// big number
			
			j=headspritestat[1];	// all sprites
			while(j>=0)
			{
				if(sprite[j].picnum == lType)
				{
					lTemp=ldist(&sprite[g_i], &sprite[j]);
					if( lTemp < lMaxDist )
					{
						if (lTemp < lDist)
						{
							lFound=j;
						}
					}
					
				}
				j = nextspritestat[j];
			}
			SetGameVarID(lVarID, lFound, g_i, g_p);
		
			break;
		}
		case CON_FINDNEARACTORVAR:
		{
			// syntax findnearactorvar <type> <maxdistvar> <getvar>
			// gets the sprite ID of the nearest actor within max dist
			// that is of <type> into <getvar>
			// -1 for none found
			// <type> <maxdistvarid> <varid>
			long lType;
			long lMaxDistVar;
			long lMaxDist;
			long lVarID;
			long lTemp;
			long lFound;
			long lDist;
			short j;

			insptr++;
			
			lType=*(insptr++);
			lMaxDistVar=*(insptr++);
			lVarID=*(insptr++);
			lMaxDist=GetGameVarID(lMaxDistVar, g_i, g_p);
			lFound=-1;
			lDist=32767;	// big number
			
			j=headspritestat[1];	// all sprites
			while(j>=0)
			{
				if(sprite[j].picnum == lType)
				{
					lTemp=ldist(&sprite[g_i], &sprite[j]);
					if( lTemp < lMaxDist )
					{
						if (lTemp < lDist)
						{
							lFound=j;
						}
					}
					
				}
				j = nextspritestat[j];
			}
			SetGameVarID(lVarID, lFound, g_i, g_p);
	
			break;
		}
		case CON_SETPLAYER:
		case CON_GETPLAYER:
		{
			// syntax [gs]etplayer[<var>].x <VAR>
			// <varid> <xxxid> <varid>
			long lLabelID;
			long lVar1, lVar2;
			long lWhat;
			
			lWhat=*(insptr++);
			lVar1=*(insptr++);
			lLabelID=*(insptr++);
			lVar2=*(insptr++);
			
			DoPlayer(lWhat==CON_SETPLAYER, lVar1, lLabelID, lVar2, g_i, g_p);
			break;
		}
		case CON_GETUSERDEF:
		case CON_SETUSERDEF:
		{
			// syntax [gs]etuserdef.xxx <VAR>
			//  <xxxid> <varid>
			long lLabelID;
			long lVar1, lVar2;
			long lWhat;
			
			lWhat=*(insptr++);
			lVar1=-1;
			lLabelID=*(insptr++);
			lVar2=*(insptr++);
			
			DoUserDef(lWhat==CON_SETPLAYER, lVar1, lLabelID, lVar2, g_i, g_p);
			break;
		}
		case CON_SETWALL:
		case CON_GETWALL:
		{
			// syntax [gs]etwall[<var>].x <VAR>
			// <varid> <xxxid> <varid>
			long lLabelID;
			long lVar1, lVar2;
			long lWhat;
			
			lWhat=*(insptr++);
			lVar1=*(insptr++);
			lLabelID=*(insptr++);
			lVar2=*(insptr++);
			
			DoWall(lWhat==CON_SETWALL, lVar1, lLabelID, lVar2, g_i, g_p);
			break;
		}
		case CON_SETACTORVAR:
		{
			// syntax [gs]etactorvar[<var>].<varx> <VAR>
			// gets the value of the per-actor variable varx into VAR
			// <var> <varx> <VAR>
			long lVar1, lVar2, lVar3;
			long lTemp,lSprite;

			insptr++;
			
			lVar1=*(insptr++);
			lVar2=*(insptr++);
			lVar3=*(insptr++);
			
			lSprite=GetGameVarId(lVar1, g_i, g_p);
			if(lSprite >= 0)
			{
				lTemp=GetGameVarID(lVar3, g_i, g_p);
				SetGameVarID(lVar2, lTemp, lSprite, g_p);
			}
			
			break;
		}
		case CON_GETACTORVAR:
		{
			// syntax [gs]etactorvar[<var>].<varx> <VAR>
			// gets the value of the per-actor variable varx into VAR
			// <var> <varx> <VAR>
			long lVar1, lVar2, lVar3;
			long lTemp,lSprite;

			insptr++;
			
			lVar1=*(insptr++);
			lVar2=*(insptr++);
			lVar3=*(insptr++);

			lSprite=GetGameVarId(lVar1, g_i, g_p);
			if(lSprite>=0)
			{
				lTemp=GetGameVarID(lVar2, lSprite, g_p);
				SetGameVarID(lVar3, lTemp, g_i, g_p);
			}
			
			break;
		}
		case CON_SETACTOR:
		case CON_GETACTOR:
		{
			// syntax [gs]etactor[<var>].x <VAR>
			// <varid> <xxxid> <varid>
			long lLabelID;
			long lVar1, lVar2;
			long lWhat;
			
			lWhat=*(insptr++);
			lVar1=*(insptr++);
			lLabelID=*(insptr++);
			lVar2=*(insptr++);
			
			DoActor(lWhat==CON_SETACTOR, lVar1, lLabelID, lVar2, g_i, g_p);
			break;
		}
		case CON_GETANGLETOTARGET:
		{
			int i;
			short ang;
			
			insptr++;
			i=*(insptr++);	// ID of def

// hittype[g_i].lastvx and lastvy are last known location of target.
			ang=getangle(hittype[g_i].lastvx-g_sp->x,hittype[g_i].lastvy-g_sp->y);
			SetGameVarID(i, ang, g_i, g_p );
			break;
		}
		case CON_LOCKPLAYER:
		{	int i;
			insptr++;
			i=*(insptr++);	// ID of def
			ps[g_p].transporter_hold=GetGameVarID(i, g_i, g_p);
			break;
		}
		case CON_GETPLAYERANGLE:
		{	int i;
			insptr++;
			i=*(insptr++);	// ID of def
			SetGameVarID(i, ps[g_p].ang, g_i, g_p );
			break;
		}
		case CON_SETPLAYERANGLE:
		{	int i;
			insptr++;
			i=*(insptr++);	// ID of def
			ps[g_p].ang=GetGameVarID(i, g_i, g_p);
			ps[g_p].ang &= 2047;
			break;
		}
		case CON_GETACTORANGLE:
		{	int i;
			insptr++;
			i=*(insptr++);	// ID of def
			SetGameVarID(i, g_sp->ang, g_i, g_p );
			break;
		}
		case CON_SETACTORANGLE:
		{	int i;
			insptr++;
			i=*(insptr++);	// ID of def
			g_sp->ang=GetGameVarID(i, g_i, g_p);
			g_sp->ang &= 2047;
			break;
		}
#endif		
		case CON_SETVAR:
		{	int i;
			insptr++;
			i=*(insptr++);	// ID of def
			SetGameVarID(i, *insptr, g_i, g_p );
			insptr++;
			break;
		}
		case CON_SETVARVAR:
		{	int i;
			insptr++;
			i=*(insptr++);	// ID of def
			SetGameVarID(i, GetGameVarID(*insptr, g_i, g_p), g_i, g_p );
//			aGameVars[i].lValue = aGameVars[*insptr].lValue;
			insptr++;
			break;
		}
#ifdef EDUKE
		case CON_RANDVAR:
		{	int i;
			insptr++;
			i=*(insptr++);	// ID of def
			SetGameVarID(i, mulscale(rand(), *insptr, 15), g_i, g_p );
			insptr++;
			break;
		}
		case CON_MULVAR:
		{	int i;
			insptr++;
			i=*(insptr++);	// ID of def
			SetGameVarID(i, GetGameVarID(i, g_i, g_p) * (*insptr), g_i, g_p );
			insptr++;
			break;
		}
		case CON_DIVVAR:
		{	int i;
			insptr++;
			i=*(insptr++);	// ID of def
			if( (*insptr) == 0 )
			{
				gameexit("Divide by Zero in CON.");
			}
			SetGameVarID(i, GetGameVarID(i, g_i, g_p) / (*insptr), g_i, g_p );
			insptr++;
			break;
		}
		case CON_MODVAR:
		{	int i;
			long l;
			long lResult;
			insptr++;
			i=*(insptr++);	// ID of def
			l=(*insptr);
			if( l == 0 )
			{
				gameexit("Divide by Zero in CON");
			}
			lResult=GetGameVarID(i, g_i, g_p) % l;
			SetGameVarID(i, lResult, g_i, g_p );
			insptr++;
			break;
		}
		case CON_ANDVAR:
		{	int i;
			long l;
			long lResult;
			insptr++;
			i=*(insptr++);	// ID of def
			l=(*insptr);
			lResult=GetGameVarID(i, g_i, g_p) & l;
			SetGameVarID(i, lResult, g_i, g_p );
			insptr++;
			break;
		}
		case CON_ORVAR:
		{	int i;
			long l;
			long lResult;
			insptr++;
			i=*(insptr++);	// ID of def
			l=(*insptr);
			lResult=GetGameVarID(i, g_i, g_p) | l;
			SetGameVarID(i, lResult, g_i, g_p );
			insptr++;
			break;
		}
		case CON_MULVARVAR:
		{	int i;
			long l1,l2;
			long lResult;
			insptr++;
			i=*(insptr++);	// ID of def
			l1=GetGameVarID(i, g_i, g_p);
			l2=GetGameVarID(*insptr, g_i, g_p);
			lResult=l1*l2;
			SetGameVarID(i, lResult , g_i, g_p );
			insptr++;
			break;
		}
		case CON_DIVVARVAR:
		{	int i;
			long l1,l2;
			long lResult;
			insptr++;
			i=*(insptr++);	// ID of def
			l1=GetGameVarID(i, g_i, g_p);
			l2=GetGameVarID(*insptr, g_i, g_p);
			if(l2==0)
			{
				gameexit("Divide by Zero in CON");
			}
			lResult=l1/l2;
			SetGameVarID(i, lResult , g_i, g_p );
			insptr++;
			break;
		}
		case CON_MODVARVAR:
		{	int i;
			long l1,l2;
			long lResult;
			insptr++;
			i=*(insptr++);	// ID of def
			l1=GetGameVarID(i, g_i, g_p);
			l2=GetGameVarID(*insptr, g_i, g_p);
			if(l2==0)
			{
				gameexit("Mod by Zero in CON");
			}
			lResult=l1 % l2;
			SetGameVarID(i, lResult , g_i, g_p );
			insptr++;
			break;
		}
		case CON_ANDVARVAR:
		{	int i;
			long l1,l2;
			long lResult;
			insptr++;
			i=*(insptr++);	// ID of def
			l1=GetGameVarID(i, g_i, g_p);
			l2=GetGameVarID(*insptr, g_i, g_p);
			lResult=l1 & l2;
			SetGameVarID(i, lResult , g_i, g_p );
			insptr++;
			break;
		}
		case CON_ORVARVAR:
		{	int i;
			long l1,l2;
			long lResult;
			insptr++;
			i=*(insptr++);	// ID of def
			l1=GetGameVarID(i, g_i, g_p);
			l2=GetGameVarID(*insptr, g_i, g_p);
			lResult=l1 | l2;
			SetGameVarID(i, lResult , g_i, g_p );
			insptr++;
			break;
		}
		case CON_SUBVAR:
		{	int i;		
			insptr++;
			i=*(insptr++);	// ID of def
			SetGameVarID(i, GetGameVarID(i, g_i, g_p) - *insptr, g_i, g_p );
			insptr++;
			break;
		}
		case CON_SUBVARVAR:
		{	int i;
			insptr++;
			i=*(insptr++);	// ID of def
			SetGameVarID(i, GetGameVarID(i, g_i, g_p) - GetGameVarID(*insptr, g_i, g_p), g_i, g_p );
			insptr++;
			break;
		}
#endif		
		case CON_ADDVAR:
		{	int i;		
			insptr++;
			i=*(insptr++);	// ID of def
//sprintf(g_szBuf,"AddVar %d to Var ID=%d, g_i=%d, g_p=%d\n",*insptr, i, g_i, g_p);
//AddLog(g_szBuf);
			SetGameVarID(i, GetGameVarID(i, g_i, g_p) + *insptr, g_i, g_p );
			insptr++;
			break;
		}
		case CON_ADDVARVAR:
		{	int i;
			insptr++;
			i=*(insptr++);	// ID of def
			SetGameVarID(i, GetGameVarID(i, g_i, g_p) + GetGameVarID(*insptr, g_i, g_p), g_i, g_p );
			insptr++;
			break;
		}
#if (APPVER_DN3DREV >= AV_DR_EDK20021)
		case CON_SPGETLOTAG:
		{	
			insptr++;
			SetGameVarID(g_iLoTagID, g_sp->lotag, g_i, g_p);
			break;
		}
		case CON_SPGETHITAG:
		{	
			insptr++;
			SetGameVarID(g_iHiTagID, g_sp->hitag, g_i, g_p);
			break;
		}
		case CON_SECTGETLOTAG:
		{	
			insptr++;
			SetGameVarID(g_iLoTagID, sector[g_sp->sectnum].lotag, g_i, g_p);
			break;
		}
		case CON_SECTGETHITAG:
		{	
			insptr++;
			SetGameVarID(g_iHiTagID, sector[g_sp->sectnum].hitag, g_i, g_p);
			break;
		}
		case CON_GETTEXTUREFLOOR:
		{	
			insptr++;
			SetGameVarID(g_iTextureID, sector[g_sp->sectnum].floorpicnum, g_i, g_p);
			break;
		}

#ifdef EDUKE
		case CON_STARTTRACK:
		{	
			insptr++;
			music_select=*insptr++;
			playmusic(&music_fn[ud.volume_number][music_select][0]);
			break;
		}
		case CON_GETTEXTURECEILING:
		{	
			insptr++;
			SetGameVarID(g_iTextureID, sector[g_sp->sectnum].ceilingpicnum, g_i, g_p);
			break;
		}
#endif		
		case CON_IFVARVARAND:
		{
			int i;
			insptr++;
			i=*(insptr++);	// ID of def
			j=0;
			if(GetGameVarID(i, g_i, g_p) & GetGameVarID(*(insptr), g_i, g_p) )
			{
				j=1;
			}
			parseifelse( j );
			break;
		}
		case CON_IFVARVARN:
		{
			int i;
			insptr++;
			i=*(insptr++);	// ID of def
			j=0;
			if(GetGameVarID(i, g_i, g_p) != GetGameVarID(*(insptr), g_i, g_p) )
			{
				j=1;
			}
			parseifelse( j );
			break;
		}
#endif // APPVER_DN3DREV >= AV_DR_EDK20021
		case CON_IFVARVARE:
		{
			int i;
			insptr++;
			i=*(insptr++);	// ID of def
			j=0;
#if (APPVER_DN3DREV < AV_DR_EDK20021)
			if(GetGameVarID(i, g_i, g_p) == GetGameVarID(*(insptr++), g_i, g_p) )
#else
			if(GetGameVarID(i, g_i, g_p) == GetGameVarID(*(insptr), g_i, g_p) )
#endif
			{
				j=1;
			}
			parseifelse( j );
			break;
		}
		case CON_IFVARVARG:
		{
			int i;
			insptr++;
			i=*(insptr++);	// ID of def
			j=0;
#if (APPVER_DN3DREV < AV_DR_EDK20021)
			if(GetGameVarID(i, g_i, g_p) > GetGameVarID(*(insptr++), g_i, g_p) )
#else
			if(GetGameVarID(i, g_i, g_p) > GetGameVarID(*(insptr), g_i, g_p) )
#endif
			{
				j=1;
			}
			parseifelse( j );
			break;
		}
		case CON_IFVARVARL:
		{
			int i;
			insptr++;
			i=*(insptr++);	// ID of def
			j=0;
#if (APPVER_DN3DREV < AV_DR_EDK20021)
			if(GetGameVarID(i, g_i, g_p) < GetGameVarID(*(insptr++), g_i, g_p) )
#else
			if(GetGameVarID(i, g_i, g_p) < GetGameVarID(*(insptr), g_i, g_p) )
#endif
			{
				j=1;
			}
			parseifelse( j );
			break;
		}
		case CON_IFVARE:
		{
			int i;
			insptr++;
			i=*(insptr++);	// ID of def
			j=0;
			if(GetGameVarID(i, g_i, g_p) == *insptr)
			{
				j=1;
			}
			parseifelse( j );
			break;
		}
#if (APPVER_DN3DREV >= AV_DR_EDK20021)
		case CON_IFVARN:
		{
			int i;
			insptr++;
			i=*(insptr++);	// ID of def
			j=0;
			if(GetGameVarID(i, g_i, g_p) != *insptr)
			{
				j=1;
			}
			parseifelse( j );
			break;
		}
		case CON_IFVARAND:
		{
			int i;
			insptr++;
			i=*(insptr++);	// ID of def
			j=0;
			if(GetGameVarID(i, g_i, g_p) & *insptr)
			{
				j=1;
			}
			parseifelse( j );
			break;
		}
#endif
		case CON_IFVARG:
		{
			int i;
			insptr++;
			i=*(insptr++);	// ID of def
			j=0;
			if(GetGameVarID(i, g_i, g_p) > *insptr)
			{
				j=1;
			}
			parseifelse( j );
			break;
		}
		case CON_IFVARL:
		{
			int i;
			insptr++;
			i=*(insptr++);	// ID of def
			j=0;
			if(GetGameVarID(i, g_i, g_p) < *insptr)
			{
				j=1;
			}
			parseifelse( j );
			break;
		}
#endif
		case 78:
			insptr++;
			parseifelse( sprite[ps[g_p].i].extra < *insptr);
			break;

		case 75:
			{
				insptr++;
				j = 0;
				switch(*(insptr++))
				{
					case 0:if( ps[g_p].steroids_amount != *insptr)
						   j = 1;
						break;
					case 1:if(ps[g_p].shield_amount != max_player_health )
							j = 1;
						break;
					case 2:if(ps[g_p].scuba_amount != *insptr) j = 1;break;
					case 3:if(ps[g_p].holoduke_amount != *insptr) j = 1;break;
					case 4:if(ps[g_p].jetpack_amount != *insptr) j = 1;break;
					case 6:
						switch(g_sp->pal)
						{
							case  0: if(ps[g_p].got_access&1) j = 1;break;
							case 21: if(ps[g_p].got_access&2) j = 1;break;
							case 23: if(ps[g_p].got_access&4) j = 1;break;
						}
						break;
					case 7:if(ps[g_p].heat_amount != *insptr) j = 1;break;
					case 9:
						if(ps[g_p].firstaid_amount != *insptr) j = 1;break;
					case 10:
						if(ps[g_p].boot_amount != *insptr) j = 1;break;
				}

				parseifelse(j);
				break;
			}
		case 38:
			insptr++;
			if( ps[g_p].knee_incs == 0 && sprite[ps[g_p].i].xrepeat >= 40 )
				if( cansee(g_sp->x,g_sp->y,g_sp->z-(4<<8),g_sp->sectnum,ps[g_p].posx,ps[g_p].posy,ps[g_p].posz+(16<<8),sprite[ps[g_p].i].sectnum) )
			{
				ps[g_p].knee_incs = 1;
				if(ps[g_p].weapon_pos == 0)
					ps[g_p].weapon_pos = -1;
				ps[g_p].actorsqu = g_i;
			}
			break;
		case 90:
			{
				short s1;

				s1 = g_sp->sectnum;

				j = 0;

					updatesector(g_sp->x+108,g_sp->y+108,&s1);
					if( s1 == g_sp->sectnum )
					{
						updatesector(g_sp->x-108,g_sp->y-108,&s1);
						if( s1 == g_sp->sectnum )
						{
							updatesector(g_sp->x+108,g_sp->y-108,&s1);
							if( s1 == g_sp->sectnum )
							{
								updatesector(g_sp->x-108,g_sp->y+108,&s1);
								if( s1 == g_sp->sectnum )
									j = 1;
							}
						}
					}
					parseifelse( j );
			}

			break;
		case 80:
			insptr++;
			FTA(*insptr,&ps[g_p]);
			insptr++;
			break;
		case 81:
			parseifelse( floorspace(g_sp->sectnum));
			break;
		case 82:
			parseifelse( (hittype[g_i].movflag&49152) > 16384 );
			break;
		case 83:
			insptr++;
			switch(g_sp->picnum)
			{
				case FEM1:
				case FEM2:
				case FEM3:
				case FEM4:
				case FEM5:
				case FEM6:
				case FEM7:
				case FEM8:
				case FEM9:
				case FEM10:
				case PODFEM1:
				case NAKED1:
				case STATUE:
					if(g_sp->yvel) operaterespawns(g_sp->yvel);
					break;
				default:
					if(g_sp->hitag >= 0) operaterespawns(g_sp->hitag);
					break;
			}
			break;
		case 85:
			insptr++;
			parseifelse( g_sp->pal == *insptr);
			break;

		case 111:
			insptr++;
			j = klabs(getincangle(ps[g_p].ang,g_sp->ang));
			parseifelse( j <= *insptr);
			break;

		case 109:

			for(j=1;j<NUM_SOUNDS;j++)
				if( SoundOwner[j][0].i == g_i )
					break;

			parseifelse( j == NUM_SOUNDS );
			break;
		default:
#ifdef WW2
//AddLog("Default Processing in parse");
#endif
			killit_flag = 1;
			break;
	}
	return 0;
}

#if (APPVER_DN3DREV >= AV_DR_EDK20021)
void LoadActor(short i,short p,long x)
{
	char done;

	g_i = i;	// Sprite ID
	g_p = p;	// Player ID
	g_x = x;	// ??
	g_sp = &sprite[g_i];	// Pointer to sprite structure
	g_t = &hittype[g_i].temp_data[0];	// Sprite's 'extra' data

	if( actorLoadEventScrptr[g_sp->picnum] == 0 ) return;

	insptr = 4 + (actorLoadEventScrptr[g_sp->picnum]);

	killit_flag = 0;

	if(g_sp->sectnum < 0 || g_sp->sectnum >= MAXSECTORS)
	{
//		if(badguy(g_sp))
//			ps[g_p].actors_killed++;
		deletesprite(g_i);
		return;
	}
	do
		done = parse();
	while( done == 0 );

	if(killit_flag == 1)
	{
		// if player was set to squish, first stop that...
		if (g_p >= 0 )
		{
			if(ps[g_p].actorsqu == g_i)
				ps[g_p].actorsqu = -1;
		}
		deletesprite(g_i);
	}
	else
	{
		move();

		if( g_sp->statnum == 1)
		{
			if( badguy(g_sp) )
			{
				if( g_sp->xrepeat > 60 ) return;
				if( ud.respawn_monsters == 1 && g_sp->extra <= 0 ) return;
			}
			else if( ud.respawn_items == 1 && (g_sp->cstat&32768) ) return;

			if(hittype[g_i].timetosleep > 1)
				hittype[g_i].timetosleep--;
			else if(hittype[g_i].timetosleep == 1)
				 changespritestat(g_i,2);
		}

		else if(g_sp->statnum == 6)
		{
			switch(g_sp->picnum)
			{
				case RUBBERCAN:
				case EXPLODINGBARREL:
				case WOODENHORSE:
				case HORSEONSIDE:
				case CANWITHSOMETHING:
				case FIREBARREL:
				case NUKEBARREL:
				case NUKEBARRELDENTED:
				case NUKEBARRELLEAKED:
				case TRIPBOMB:
				case EGG:
					if(hittype[g_i].timetosleep > 1)
						hittype[g_i].timetosleep--;
					else if(hittype[g_i].timetosleep == 1)
						changespritestat(g_i,2);
					break;
			}
		}
	}

}
#endif // APPVER_DN3DREV >= AV_DR_EDK20021

void execute(short i,short p,long x)
{
	char done;

	g_i = i;	// Sprite ID
	g_p = p;	// Player ID
	g_x = x;	// ??
	g_sp = &sprite[g_i];	// Pointer to sprite structure
	g_t = &hittype[g_i].temp_data[0];	// Sprite's 'extra' data

	if( actorscrptr[g_sp->picnum] == 0 ) return;

	insptr = 4 + (actorscrptr[g_sp->picnum]);

	killit_flag = 0;

	if(g_sp->sectnum < 0 || g_sp->sectnum >= MAXSECTORS)
	{
		if(badguy(g_sp))
			ps[g_p].actors_killed++;
		deletesprite(g_i);
		return;
	}

	if(g_t[4])
	{
		g_sp->lotag += TICSPERFRAME;
		if(g_sp->lotag > *(long *)(g_t[4]+16) )
		{
			g_t[2]++;
			g_sp->lotag = 0;
			g_t[3] +=  *(long *)( g_t[4]+12 );
		}
		if( klabs(g_t[3]) >= klabs( *(long *)(g_t[4]+4) * *(long *)(g_t[4]+12) ) )
			g_t[3] = 0;
	}

	do
		done = parse();
	while( done == 0 );

	if(killit_flag == 1)
	{
		// if player was set to squish, first stop that...
		if(ps[g_p].actorsqu == g_i)
			ps[g_p].actorsqu = -1;
		deletesprite(g_i);
	}
	else
	{
		move();

		if( g_sp->statnum == 1)
		{
			if( badguy(g_sp) )
			{
				if( g_sp->xrepeat > 60 ) return;
				if( ud.respawn_monsters == 1 && g_sp->extra <= 0 ) return;
			}
			else if( ud.respawn_items == 1 && (g_sp->cstat&32768) ) return;

			if(hittype[g_i].timetosleep > 1)
				hittype[g_i].timetosleep--;
			else if(hittype[g_i].timetosleep == 1)
				 changespritestat(g_i,2);
		}

		else if(g_sp->statnum == 6)
			switch(g_sp->picnum)
			{
				case RUBBERCAN:
				case EXPLODINGBARREL:
				case WOODENHORSE:
				case HORSEONSIDE:
				case CANWITHSOMETHING:
				case FIREBARREL:
				case NUKEBARREL:
				case NUKEBARRELDENTED:
				case NUKEBARRELLEAKED:
				case TRIPBOMB:
				case EGG:
					if(hittype[g_i].timetosleep > 1)
						hittype[g_i].timetosleep--;
					else if(hittype[g_i].timetosleep == 1)
						changespritestat(g_i,2);
					break;
			}
	}
}





// "Duke 2000"
// "Virchua Duke"
// "Son of Death
// "Cromium"
// "Potent"
// "Flotsom"

// Volume One
// "Duke is brain dead",
// "BOOT TO THE HEAD"
// Damage too duke
// Weapons are computer cont.  Only logical thinking
// is disappearing.
// " Flips! "
// Flash on screen, inst.
// "BUMS"
// "JAIL"/"MENTAL WARD (Cop code for looney?  T. asks Cop.)"
// "GUTS OR GLORY"

// ( Duke's Mission

// Duke:	"Looks like some kind of transporter...?"
// Byte:	"...YES"

// Duke:	"Waa, here goes nuthin'. "
// (Duke puts r. arm in device)

// Duke:	AAAAHHHHHHHHHHHHHHHHHHHHHHHHH!!!
// (Duke's arm is seved.)
// Byte:	NO.NO.NO.NO.NO.NO.NO...
// ( Byte directs duke to the nearest heat source)
// (Shut Up Mode)
// ( Duke Staggers, end of arm bleeding, usual oozing arm guts. )
// Byte: Left, Left, Left, Left, Right.
// ( Duke, loozing consc, trips on broken pipe, )
// ( hits temple on edge of step. )
// ( Rats everywhere, byte pushing them away with weapon,
// ( eventually covered, show usual groosums, Duke appears dead
// ( Duke wakes up, in hospital, vision less blurry
// ( Hospital doing brain scan, 1/3 cran. mass MISSING!
// Doc: Hummm?	( Grabbing upper lip to "appear" smart. )

// Stand back boys

// Schrapnel has busted my scull!
// Now I'm insane, Mental ward, got to escape.
// Search light everywhere.

// (M)Mendor, The Tree Dweller.
// (M)BashMan, The Destructor.
// (M)Lash, The Scavenger.
// (F)Mag, The Slut.
// (F)
// NRA OR SOMETHIN'

// Duke Nukem
// 5th Dimention
// Pentagon Man!


// I Hope your not stupid!
// The 70's meet the future.
// Dirty Harry style.  70's music with futuristic edge
// The Instant De-Welder(tm)
// I think I'm going to puke...
// Badge attitude.
// He's got a Badge(LA 3322), a Bulldog, a Bronco (beat up/bondoed).
// Gfx:
// Lite rail systems
// A church.  Large cross
// Sniper Scope,
// Really use the phone
// The Boiler Room
// The IRS, nuking other government buildings?
// You wouldn't have a belt of booz, would ya?
// Slow turning signes
// More persise shooting/descructions
// Faces, use phoneoms and its lookup.	Talking, getting in fights.
// Drug dealers, pimps, and all galore
// Weapons, Anything lying around.
// Trees to clime, burning trees.
// Sledge Hammer, Sledge hammer with Spike
// sancurary, get away from it all.
// Goodlife = ( War + Greed ) / Peace
// Monsterism			(ACTION)
// Global Hunter		(RPG)
// Slick a Wick			(PUZZLE)
// Roach Condo			(FUNNY)
// AntiProfit			(RPG)
// Pen Patrol			(TD SIM)
// 97.5 KPIG! - Wanker County
// "Fauna" - Native Indiginouns Animal Life
