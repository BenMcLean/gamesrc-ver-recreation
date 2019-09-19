// _functio.h

// file created by makehead.exe
// these headers contain default key assignments, as well as
// default button assignments and game function names
// axis defaults are also included


#ifndef _function_private_
#define _function_private_
#ifdef __cplusplus
extern "C" {
#endif
char * gamefunctions[NUMGAMEFUNCTIONS] =
   {
   "Move_Forward",
   "Move_Backward",
   "Turn_Left",
   "Turn_Right",
   "Strafe",
   "Fire",
   "Open",
   "Run",
   "AutoRun",
   "Jump",
   "Crouch",
   "Look_Up",
   "Look_Down",
   "Look_Left",
   "Look_Right",
   "Strafe_Left",
   "Strafe_Right",
   "Aim_Up",
   "Aim_Down",
   "Weapon_1",
   "Weapon_2",
   "Weapon_3",
   "Weapon_4",
   "Weapon_5",
   "Weapon_6",
   "Weapon_7",
   "Weapon_8",
   "Weapon_9",
   "Weapon_10",
   "Inventory",
   "Inventory_Left",
   "Inventory_Right",
#if defined(EDUKE) || (!defined(WW2GI) && (APPVER_DN3DREV >= AV_DR_EDK20021))
//#if defined(EDUKE) || !defined(WW2GI)
"Hologram",
"Jetpack",
"NightVision",
#elif (APPVER_DN3DREV >= AV_DR_WW2GI10)
//#else
"Special1", //   "Hologram",
"Special2", //   "Jetpack",
"Special3", //   "NightVision",
#else // APPVER_DN3DREV < AV_DR_WW2GI10
   "Holo_Duke",
   "Jetpack",
   "NightVision",
#endif
   "MedKit",
   "TurnAround",
   "SendMessage",
   "Map",
   "Shrink_Screen",
   "Enlarge_Screen",
   "Center_View",
   "Holster_Weapon",
   "Show_Opponents_Weapon",
   "Map_Follow_Mode",
   "See_Coop_View",
   "Mouse_Aiming",
   "Toggle_Crosshair",
#if (APPVER_DN3DREV >= AV_DR_WW2GI10)
#if defined(EDUKE) || (!defined(WW2GI) && (APPVER_DN3DREV >= AV_DR_EDK20021))
//#if defined(EDUKE) || !defined(WW2GI)
"Steroids",
#else
"Special4", //   "Steroids",
#endif
   "Quick_Stab",
#else // APPVER_DN3DREV < AV_DR_WW2GI10
   "Steroids",
   "Quick_Kick",
#endif
   "Next_Weapon",
   "Previous_Weapon",
   };
#ifdef __SETUP__

#define NUMKEYENTRIES 52

static char * keydefaults[NUMKEYENTRIES*3] =
   {
   "Move_Forward", "Up", "Kpad8", 
   "Move_Backward", "Down", "Kpad2", 
   "Turn_Left", "Left", "Kpad4", 
   "Turn_Right", "Right", "KPad6", 
   "Strafe", "LAlt", "RAlt", 
   "Fire", "LCtrl", "RCtrl", 
   "Open", "Space", "", 
   "Run", "LShift", "RShift", 
   "AutoRun", "CapLck", "", 
   "Jump", "A", "/", 
   "Crouch", "Z", "", 
   "Look_Up", "PgUp", "Kpad9", 
   "Look_Down", "PgDn", "Kpad3", 
   "Look_Left", "Insert", "Kpad0", 
   "Look_Right", "Delete", "Kpad.", 
   "Strafe_Left", ",", "", 
   "Strafe_Right", ".", "", 
   "Aim_Up", "Home", "KPad7", 
   "Aim_Down", "End", "Kpad1", 
   "Weapon_1", "1", "", 
   "Weapon_2", "2", "", 
   "Weapon_3", "3", "", 
   "Weapon_4", "4", "", 
   "Weapon_5", "5", "", 
   "Weapon_6", "6", "", 
   "Weapon_7", "7", "", 
   "Weapon_8", "8", "", 
   "Weapon_9", "9", "", 
   "Weapon_10", "0", "", 
   "Inventory", "Enter", "KpdEnt", 
   "Inventory_Left", "[", "", 
   "Inventory_Right", "]", "", 
#if defined(EDUKE) || (!defined(WW2GI) && (APPVER_DN3DREV >= AV_DR_EDK20021))
//#if defined(EDUKE) || !defined(WW2GI)
"Hologram", "H", "", 
"Jetpack", "J", "", 
"NightVision", "N", "",
#elif (APPVER_DN3DREV >= AV_DR_WW2GI10)
//#else
"Special1", "H", "", //   "Hologram", "H", "", 
"Special2", "J", "", //   "Jetpack", "J", "", 
"Special3", "N", "", //   "NightVision", "N", "",
#else // APPVER_DN3DREV < AV_DR_WW2GI10
   "Holo_Duke", "H", "",
   "Jetpack", "J", "",
   "NightVision", "N", "",
#endif
   "MedKit", "M", "", 
   "TurnAround", "BakSpc", "", 
   "SendMessage", "T", "", 
   "Map", "Tab", "", 
   "Shrink_Screen", "-", "Kpad-", 
   "Enlarge_Screen", "=", "Kpad+", 
   "Center_View", "KPad5", "", 
   "Holster_Weapon", "ScrLck", "", 
   "Show_Opponents_Weapon", "W", "", 
   "Map_Follow_Mode", "F", "", 
   "See_Coop_View", "K", "", 
   "Mouse_Aiming", "U", "", 
   "Toggle_Crosshair", "I", "", 
#if (APPVER_DN3DREV >= AV_DR_WW2GI10)
#if defined(EDUKE) || (!defined(WW2GI) && (APPVER_DN3DREV >= AV_DR_EDK20021))
//#if defined(EDUKE) || !defined(WW2GI)
"Steroids", "R", "",
#else
"Special4", "R", "", //   "Steroids", "R", "",
#endif
   "Quick_Stab", "`", "", 
#else // APPVER_DN3DREV < AV_DR_WW2GI10
   "Steroids", "R", "",
   "Quick_Kick", "`", "",
#endif
   "Next_Weapon", "'", "", 
   "Previous_Weapon", ";", ""
   };


static char * mousedefaults[] =
   {
   "Fire",
   "Strafe",
   "Move_Forward",
   };


static char * mouseclickeddefaults[] =
   {
   "",
   "Open",
   "",
   };


static char * joystickdefaults[] =
   {
   "Fire",
   "Strafe",
   "Run",
   "Open",
   "Aim_Down",
   "Look_Right",
   "Aim_Up",
   "Look_Left",
   };


static char * joystickclickeddefaults[] =
   {
   "",
   "Inventory",
   "Jump",
   "Crouch",
   "",
   "",
   "",
   "",
   };


static char * mouseanalogdefaults[] =
   {
   "analog_turning",
   "analog_moving",
   };


static char * mousedigitaldefaults[] =
   {
   "",
   "",
   "",
   "",
   };


static char * gamepaddigitaldefaults[] =
   {
   "Turn_Left",
   "Turn_Right",
   "Move_Forward",
   "Move_Backward",
   };


static char * joystickanalogdefaults[] =
   {
   "analog_turning",
   "analog_moving",
   "analog_strafing",
   "",
   };


static char * joystickdigitaldefaults[] =
   {
   "",
   "",
   "",
   "",
   "",
   "",
   "Run",
   "",
   };
#endif
#ifdef __cplusplus
};
#endif
#endif
