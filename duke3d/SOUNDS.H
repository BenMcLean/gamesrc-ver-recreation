//****************************************************************************
//
// sounds.h
//
//****************************************************************************

#ifndef _sounds_public_
#define _sounds_public_

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

void SoundStartup( void );
void SoundShutdown( void );
void MusicStartup( void );
void MusicShutdown( void );

#endif
