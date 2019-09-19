#ifndef _config_public
#define _config_public

#define SETUPNAMEPARM "SETUPFILE"

extern int32 FXDevice;
extern int32 MusicDevice;
extern int32 FXVolume;
extern int32 MusicVolume;
extern fx_blaster_config BlasterConfig;
extern int32 NumVoices;
extern int32 NumChannels;
extern int32 NumBits;
extern int32 MixRate;
extern int32 MidiPort;
extern int32 ReverseStereo;

extern int32 ControllerType;
extern int32 MouseAiming;
extern int32 ScreenMode;
extern int32 ScreenWidth;
extern int32 ScreenHeight;

void CONFIG_ReadSetup( void );
void CONFIG_GetSetupFilename( void );
void CONFIG_WriteSetup( void );

#endif
