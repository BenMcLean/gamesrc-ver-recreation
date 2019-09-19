//****************************************************************************
//
// gamedefs.h
//
// common defines between the game and the setup program
//
//****************************************************************************

#ifndef _gamedefs_public_
#define _gamedefs_public_
#ifdef __cplusplus
extern "C" {
#endif

//****************************************************************************
//
// DEFINES
//
//****************************************************************************

//
// Setup program defines
//
#ifdef NAM
#ifdef WW2
#define SETUPFILENAME "WW2GI.CFG"
#else
#define SETUPFILENAME "NAM.CFG"
#endif
#else
#define SETUPFILENAME "DUKE3D.CFG"
#endif


// Max number of players

#define MAXPLAYERS 16

// Number of Mouse buttons

#define MAXMOUSEBUTTONS 3

// Number of JOY buttons

#define MAXJOYBUTTONS 8

// Number of EXTERNAL buttons

//#define MAXEXTERNALBUTTONS 6

//
// modem string defines
//

#define MAXMODEMSTRING 50

// MACRO defines

#define MAXMACROS      10
#define MAXMACROLENGTH 34

// Phone list defines

#define PHONENUMBERLENGTH 28
#define PHONENAMELENGTH   16
#define MAXPHONEENTRIES   10

// length of program functions

#define MAXFUNCTIONLENGTH 30

// length of axis functions

#define MAXAXISFUNCTIONLENGTH 30

// Max Player Name length

#define MAXPLAYERNAMELENGTH 11

// Max RTS Name length

#define MAXRTSNAMELENGTH 15

// Number of Mouse Axes

#define MAXMOUSEAXES 2

// Number of JOY axes

#define MAXJOYAXES 4

// Number of GAMEPAD axes

#define MAXGAMEPADAXES 2

// MIN/MAX scale value for controller scales

#define MAXCONTROLSCALEVALUE (1<<19)

// DEFAULT scale value for controller scales

#define DEFAULTCONTROLSCALEVALUE (1<<16)

// base value for controller scales

#define BASECONTROLSCALEVALUE (1<<16)

// MAX mouse sensitivity scale

#define MAXMOUSESENSITIVITY (1<<17)

// DEFAULT mouse sensitivity scale

#define DEFAULTMOUSESENSITIVITY (1<<15)

enum
   {
   gametype_network=3,
   gametype_serial=1,
   gametype_modem=2
   };

enum
   {
   connecttype_dialing=0,
   connecttype_answer=1,
   connecttype_alreadyconnected=2
   };

enum
   {
   screenbuffer_320x200,
   screenbuffer_640x400,
   screenbuffer_640x480,
   screenbuffer_800x600,
   screenbuffer_1024x768,
   screenbuffer_1280x1024,
   screenbuffer_1600x1200
   };

enum
   {
   vesa_320x200,
   vesa_360x200,
   vesa_320x240,
   vesa_360x240,
   vesa_320x400,
   vesa_360x400,
   vesa_640x350,
   vesa_640x400,
   vesa_640x480,
   vesa_800x600,
   vesa_1024x768,
   vesa_1280x1024,
   vesa_1600x1200
   };

enum
   {
   screenmode_chained,
   screenmode_vesa,
   screenmode_buffered,
   screenmode_tseng,
   screenmode_paradise,
   screenmode_s3,
   screenmode_crystal,
   screenmode_redblue,
   };


#ifdef __cplusplus
};
#endif
#endif

