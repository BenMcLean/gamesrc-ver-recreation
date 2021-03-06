//////////////////////////////////////
//
// Graphics .H file for .BS1
// IGRAB-ed on Wed Mar 30 18:12:07 1994
//
//////////////////////////////////////

/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
// Originally based on offsets for AOG v3.0 from bstone port (aog3 branch)

// RESTORATION - Used for convenience, covering multiple versions
#ifdef GAMEVER_RESTORATION_BS6_300
//#define GAMEVER_RESTORATION_GFXV_EARLY_OFFSET 0
#define GAMEVER_RESTORATION_GFXV_MIDDLE_OFFSET 0
#define GAMEVER_RESTORATION_GFXV_LATE_OFFSET 0
//#define GAMEVER_RESTORATION_GFXV_LAST_OFFSET 0
#elif defined GAMEVER_RESTORATION_BS1_300
//#define GAMEVER_RESTORATION_GFXV_EARLY_OFFSET 1
#define GAMEVER_RESTORATION_GFXV_MIDDLE_OFFSET -1
#define GAMEVER_RESTORATION_GFXV_LATE_OFFSET 12
//#define GAMEVER_RESTORATION_GFXV_LAST_OFFSET 13
#elif (defined GAMEVER_RESTORATION_BS6_200) || (defined GAMEVER_RESTORATION_BS6_210)
//#define GAMEVER_RESTORATION_GFXV_EARLY_OFFSET 3
#define GAMEVER_RESTORATION_GFXV_MIDDLE_OFFSET 3
#define GAMEVER_RESTORATION_GFXV_LATE_OFFSET 2
//#define GAMEVER_RESTORATION_GFXV_LAST_OFFSET 2
#elif (defined GAMEVER_RESTORATION_BS1_200) || (defined GAMEVER_RESTORATION_BS1_210)
//#define GAMEVER_RESTORATION_GFXV_EARLY_OFFSET 4
#define GAMEVER_RESTORATION_GFXV_MIDDLE_OFFSET 2
#define GAMEVER_RESTORATION_GFXV_LATE_OFFSET 14
//#define GAMEVER_RESTORATION_GFXV_LAST_OFFSET 15
#elif (defined GAMEVER_RESTORATION_BS6_100)
#define GAMEVER_RESTORATION_GFXV_MIDDLE_OFFSET 5
#define GAMEVER_RESTORATION_GFXV_LATE_OFFSET 12
#elif (defined GAMEVER_RESTORATION_BS1_100)
#define GAMEVER_RESTORATION_GFXV_MIDDLE_OFFSET 4
#define GAMEVER_RESTORATION_GFXV_LATE_OFFSET 24
#endif

typedef enum {
		TELEPORTBACKPIC=6,
		// Lump Start
		TELEPORT1OFFPIC, // 7
		TELEPORT2OFFPIC, // 8
		TELEPORT3OFFPIC, // 9
		TELEPORT4OFFPIC, // 10
		TELEPORT5OFFPIC, // 11
		TELEPORT6OFFPIC, // 12
		TELEPORT7OFFPIC, // 13
		TELEPORT8OFFPIC, // 14
		TELEPORT9OFFPIC, // 15
		TELEPORT10OFFPIC, // 16
		TELEPORT1ONPIC, // 17
		TELEPORT2ONPIC, // 18
		TELEPORT3ONPIC, // 19
		TELEPORT4ONPIC, // 20
		TELEPORT5ONPIC, // 21
		TELEPORT6ONPIC, // 22
		TELEPORT7ONPIC, // 23
		TELEPORT8ONPIC, // 24
		TELEPORT9ONPIC, // 25
		TELEPORT10ONPIC, // 26
		TELEPORT_TEXT_BG, // 27
		BACKGROUND_SCREENPIC, // 28
		APOGEEPIC, // 29
#ifndef GAMEVER_RESTORATION_BS1
		PIRACYPIC, // 30
#endif
		PC13PIC, // 31
		LOSEPIC, // 32
#ifdef GAMEVER_RESTORATION_AOG_300
		PSPROMO1PIC, // 33
		PSPROMO2PIC, // 34
		PSPROMO3PIC, // 35
#endif

		AUTOMAPPIC, // 36
		// Lump Start
		H_ALTPIC, // 37
		H_CTRLPIC, // 38
		H_SPACEPIC, // 39
		H_PAUSEPIC, // 40
		H_ESCPIC, // 41
		H_LTARROWPIC, // 42
		H_UPARROWPIC, // 43
		H_DNARROWPIC, // 44
		H_RTARROWPIC, // 45
		H_ENTERPIC, // 46
		H_QPIC, // 47
		H_WPIC, // 48
		H_EPIC, // 49
		H_IPIC, // 50
		H_HPIC, // 51
		H_1PIC, // 52
		H_2PIC, // 53
		H_3PIC, // 54
		H_4PIC, // 55
		H_5PIC, // 56
		H_F1PIC, // 57
		H_F2PIC, // 58
		H_F3PIC, // 59
		H_F4PIC, // 60
		H_F5PIC, // 61
		H_F6PIC, // 62
		H_F7PIC, // 63
		H_F8PIC, // 64
		H_F9PIC, // 65
		H_F10PIC, // 66
		H_TABPIC, // 67
		H_CPIC, // 68
		H_FPIC, // 69
		H_PPIC, // 70
		H_MPIC, // 71
#ifndef GAMEVER_RESTORATION_AOG_100
		H_LPIC, // 72
		H_SHIFTPIC, // 73
#endif
		APOGEE_LOGOPIC, // 74
		VISAPIC, // 75
		MCPIC, // 76
		FAXPIC, // 77
		H_TOPWINDOWPIC, // 78
		H_LEFTWINDOWPIC, // 79
		H_RIGHTWINDOWPIC, // 80
		H_BOTTOMINFOPIC, // 81
		// Lump Start
		C_NOTSELECTEDPIC, // 82
		C_SELECTEDPIC, // 83
		C_NOTSELECTED_HIPIC, // 84
		C_SELECTED_HIPIC, // 85
		C_BABYMODEPIC, // 86
		C_EASYPIC, // 87
		C_NORMALPIC, // 88
		C_HARDPIC, // 89
		C_EPISODE1PIC, // 90
		C_EPISODE2PIC, // 91
		C_EPISODE3PIC, // 92
		C_EPISODE4PIC, // 93
		C_EPISODE5PIC, // 94
		C_EPISODE6PIC, // 95
		BIGGOLDSTERNPIC, // 96
		STARLOGOPIC, // 97
		BLAKEWITHGUNPIC, // 98
		STARINSTITUTEPIC, // 99
		MEDALOFHONORPIC, // 100
		SMALLGOLDSTERNPIC, // 101
		BLAKEWINPIC, // 102
		SHUTTLEEXPPIC, // 103
		PLANETSPIC, // 104
		MOUSEPIC, // 105
		JOYSTICKPIC, // 106
		GRAVISPADPIC, // 107
		TITLEPIC, // 108
#ifdef GAMEVER_RESTORATION_BS1
		PROMO1PIC,
		PROMO2PIC,
#endif
		// Lump Start
		WEAPON1PIC, // 109
		WEAPON2PIC, // 110
		WEAPON3PIC, // 111
		WEAPON4PIC, // 112
		WEAPON5PIC, // 113
		WAITPIC, // 114
		READYPIC, // 115
		N_BLANKPIC, // 116
		N_0PIC, // 117
		N_1PIC, // 118
		N_2PIC, // 119
		N_3PIC, // 120
		N_4PIC, // 121
		N_5PIC, // 122
		N_6PIC, // 123
		N_7PIC, // 124
		N_8PIC, // 125
		N_9PIC, // 126
		N_RPIC, // 127
		N_OPIC, // 128
		N_LPIC, // 129
		N_DASHPIC, // 130
		DIM_LIGHTPIC, // 131
		BRI_LIGHTPIC, // 132
		ECG_HEART_GOOD, // 133
		ECG_HEART_BAD, // 134
		ECG_GRID_PIECE, // 135
		AMMONUM_BACKGR, // 136
		ECG_HEARTBEAT_00, // 137
		ECG_HEARTBEAT_01, // 138
		ECG_HEARTBEAT_02, // 139
		ECG_HEARTBEAT_03, // 140
		ECG_HEARTBEAT_04, // 141
		ECG_HEARTBEAT_05, // 142
		ECG_HEARTBEAT_06, // 143
		ECG_HEARTBEAT_07, // 144
		ECG_HEARTBEAT_08, // 145
		ECG_HEARTBEAT_09, // 146
		ECG_HEARTBEAT_10, // 147
		ECG_HEARTBEAT_11, // 148
		ECG_HEARTBEAT_12, // 149
		ECG_HEARTBEAT_13, // 150
		ECG_HEARTBEAT_14, // 151
		ECG_HEARTBEAT_15, // 152
		ECG_HEARTBEAT_16, // 153
		ECG_HEARTBEAT_17, // 154
		ECG_HEARTBEAT_18, // 155
		ECG_HEARTBEAT_19, // 156
		ECG_HEARTBEAT_20, // 157
		ECG_HEARTBEAT_21, // 158
		ECG_HEARTBEAT_22, // 159
		ECG_HEARTBEAT_23, // 160
		ECG_HEARTBEAT_24, // 161
		ECG_HEARTBEAT_25, // 162
		ECG_HEARTBEAT_26, // 163
		ECG_HEARTBEAT_27, // 164
		INFOAREAPIC, // 165
		TOP_STATUSBARPIC, // 166
		STATUSBARPIC, // 167

#ifdef GAMEVER_RESTORATION_BS1
#ifdef GAMEVER_RESTORATION_AOG_100
		APOGEEPALETTE=169-GAMEVER_RESTORATION_GFXV_MIDDLE_OFFSET,
#else
		POWERBALLTEXT=169-GAMEVER_RESTORATION_GFXV_MIDDLE_OFFSET,
		APOGEEPALETTE, // 171
		MUSICTEXT, // 172
		RADARTEXT, // 173
		TICSTEXT, // 174
#endif
		TITLEPALETTE, // 175
		ORDERSCREEN, // 176
		ERRORSCREEN, // 177
#else // BS1/BS6
#ifdef GAMEVER_RESTORATION_AOG_100
		PIRACYPALETTE=169-GAMEVER_RESTORATION_GFXV_MIDDLE_OFFSET,
#else
		POWERBALLTEXT=169-GAMEVER_RESTORATION_GFXV_MIDDLE_OFFSET,
		PIRACYPALETTE, // 170
#endif
		APOGEEPALETTE, // 171
		TITLEPALETTE, // 172
		ORDERSCREEN, // 173
		ERRORSCREEN, // 174
#ifndef GAMEVER_RESTORATION_AOG_100
		MUSICTEXT, // 175
		RADARTEXT, // 176
		TICSTEXT, // 177
#endif
#endif // BS1/BS6
#ifndef GAMEVER_RESTORATION_AOG_300
		T_DEMO0,
#endif
		T_DEMO1, // 178
		T_DEMO2, // 179
		T_DEMO3, // 180
#ifndef GAMEVER_RESTORATION_BS1
		T_DEMO4, // 181
		T_DEMO5, // 182
#endif
 		INFORMANT_HINTS, // 183
		NICE_SCIE_HINTS, // 184
		MEAN_SCIE_HINTS, // 185
		BRIEF_W1, // 186
		BRIEF_I1, // 187
#ifndef GAMEVER_RESTORATION_BS1
		BRIEF_W2, // 188
		BRIEF_I2, // 189
		BRIEF_W3, // 190
		BRIEF_I3, // 191
		BRIEF_W4, // 192
		BRIEF_I4, // 193
		BRIEF_W5, // 194
		BRIEF_I5, // 195
		BRIEF_W6, // 196
		BRIEF_I6, // 197
#endif
		LEVEL_DESCS, // 198

		HELPTEXT=203-GAMEVER_RESTORATION_GFXV_LATE_OFFSET,
		SAGATEXT, // 204
		LOSETEXT, // 205
		ORDERTEXT, // 206
		CREDITSTEXT, // 207
		MUSTBE386TEXT, // 208
		QUICK_INFO1_TEXT, // 209
		QUICK_INFO2_TEXT, // 210
		BADINFO_TEXT, // 211
		CALJOY1_TEXT, // 212
		CALJOY2_TEXT, // 213
		READTHIS_TEXT, // 214
		ELEVMSG0_TEXT, // 215
		ELEVMSG1_TEXT, // 216
		ELEVMSG4_TEXT, // 217
		ELEVMSG5_TEXT, // 218
		FLOORMSG_TEXT, // 219
		YOUWIN_TEXT, // 220
		CHANGEVIEW_TEXT, // 221
#ifdef GAMEVER_RESTORATION_BS1
		BADCHECKSUMTEXT,
#else
		DIZ_ERR_TEXT, // 222
		BADLEVELSTEXT, // 223
#endif
#ifndef GAMEVER_RESTORATION_AOG_100
		BADSAVEGAME_TEXT, // 224
#endif

		ENUMEND
	     } graphicnums;

//
// Data LUMPs
//
#define TELEPORT_LUMP_START		7
#define TELEPORT_LUMP_END		27

#ifdef GAMEVER_RESTORATION_BS6_300

#define README_LUMP_START		37
#define README_LUMP_END			81

#define CONTROLS_LUMP_START		82
#define CONTROLS_LUMP_END		95

#define LATCHPICS_LUMP_START		109
#define LATCHPICS_LUMP_END		167

#elif defined GAMEVER_RESTORATION_BS1_300

#define README_LUMP_START		36
#define README_LUMP_END			80

#define CONTROLS_LUMP_START		81
#define CONTROLS_LUMP_END		94

#define LATCHPICS_LUMP_START		110
#define LATCHPICS_LUMP_END		168

#elif (defined GAMEVER_RESTORATION_BS6_200) || (defined GAMEVER_RESTORATION_BS6_210)

#define README_LUMP_START		34
#define README_LUMP_END			78

#define CONTROLS_LUMP_START		79
#define CONTROLS_LUMP_END		92

#define LATCHPICS_LUMP_START		106
#define LATCHPICS_LUMP_END		164

#elif (defined GAMEVER_RESTORATION_BS1_200) || (defined GAMEVER_RESTORATION_BS1_210)

#define README_LUMP_START		33
#define README_LUMP_END			77

#define CONTROLS_LUMP_START		78
#define CONTROLS_LUMP_END		91

#define LATCHPICS_LUMP_START		107
#define LATCHPICS_LUMP_END		165

#elif (defined GAMEVER_RESTORATION_BS6_100)

#define README_LUMP_START		34
#define README_LUMP_END			78

#define CONTROLS_LUMP_START		77
#define CONTROLS_LUMP_END		90

#define LATCHPICS_LUMP_START		104
#define LATCHPICS_LUMP_END		162

#elif (defined GAMEVER_RESTORATION_BS1_100)

#define README_LUMP_START		33
#define README_LUMP_END			77

#define CONTROLS_LUMP_START		76
#define CONTROLS_LUMP_END		89

#define LATCHPICS_LUMP_START		105
#define LATCHPICS_LUMP_END		163

#endif


//
// Amount of each data item
//
#ifdef GAMEVER_RESTORATION_BS6_300
#define NUMCHUNKS    225 // OK
#define NUMPICS      162
#elif defined GAMEVER_RESTORATION_BS1_300
#define NUMCHUNKS    212 // OK
#define NUMPICS      163
#elif (defined GAMEVER_RESTORATION_BS6_200) || (defined GAMEVER_RESTORATION_BS6_210)
#define NUMCHUNKS    223 // OK
#define NUMPICS      159
#elif (defined GAMEVER_RESTORATION_BS1_200) || (defined GAMEVER_RESTORATION_BS1_210)
#define NUMCHUNKS    210 // OK
#define NUMPICS      160
#elif (defined GAMEVER_RESTORATION_BS6_100)
#define NUMCHUNKS    212 // OK
#define NUMPICS      157
#elif (defined GAMEVER_RESTORATION_BS1_100)
#define NUMCHUNKS    199 // OK
#define NUMPICS      158
#endif
#define NUMFONT      5 // OK
#define NUMFONTM     0
//#define NUMPICS      162
#define NUMPICM      0
#define NUMSPRITES   0
#define NUMTILE8     72 // OK
#define NUMTILE8M    0
#define NUMTILE16    0
#define NUMTILE16M   0
#define NUMTILE32    0
#define NUMTILE32M   0
#define NUMEXTERNS   59 // NOT USED (apparently 57 for correct sum, TILE8 is considered 1)
//
// File offsets for data items
//
#define STRUCTPIC    0

#define STARTFONT    1 // OK
#define STARTFONTM   6 // USED IN COMMENTED OUT CODE ONLY
#define STARTPICS    6 // OK
#ifdef GAMEVER_RESTORATION_BS6_300
#define STARTPICM    168 // UNUSED
#define STARTSPRITES 168 // MENTIONED BUT UNUSED (zero sprites)
#define STARTTILE8   168
#define STARTTILE8M  169
#define STARTTILE16  169
#define STARTTILE16M 169
#define STARTTILE32  169
#define STARTTILE32M 169
#define STARTEXTERNS 169
#elif defined GAMEVER_RESTORATION_BS1_300
#define STARTPICM    169 // UNUSED
#define STARTSPRITES 169 // MENTIONED BUT UNUSED (zero sprites)
#define STARTTILE8   169
#define STARTTILE8M  170
#define STARTTILE16  170
#define STARTTILE16M 170
#define STARTTILE32  170
#define STARTTILE32M 170
#define STARTEXTERNS 170
#elif (defined GAMEVER_RESTORATION_BS6_200) || (defined GAMEVER_RESTORATION_BS6_210)
#define STARTPICM    165 // UNUSED
#define STARTSPRITES 165 // MENTIONED BUT UNUSED (zero sprites)
#define STARTTILE8   165
#define STARTTILE8M  166
#define STARTTILE16  166
#define STARTTILE16M 166
#define STARTTILE32  166
#define STARTTILE32M 166
#define STARTEXTERNS 166
#elif (defined GAMEVER_RESTORATION_BS1_200) || (defined GAMEVER_RESTORATION_BS1_210)
#define STARTPICM    166 // UNUSED
#define STARTSPRITES 166 // MENTIONED BUT UNUSED (zero sprites)
#define STARTTILE8   166
#define STARTTILE8M  167
#define STARTTILE16  167
#define STARTTILE16M 167
#define STARTTILE32  167
#define STARTTILE32M 167
#define STARTEXTERNS 167
#elif (defined GAMEVER_RESTORATION_BS6_100)
#define STARTPICM    163 // UNUSED
#define STARTSPRITES 163 // MENTIONED BUT UNUSED (zero sprites)
#define STARTTILE8   163
#define STARTTILE8M  164
#define STARTTILE16  164
#define STARTTILE16M 164
#define STARTTILE32  164
#define STARTTILE32M 164
#define STARTEXTERNS 164
#elif (defined GAMEVER_RESTORATION_BS1_100)
#define STARTPICM    164 // UNUSED
#define STARTSPRITES 164 // MENTIONED BUT UNUSED (zero sprites)
#define STARTTILE8   164
#define STARTTILE8M  165
#define STARTTILE16  165
#define STARTTILE16M 165
#define STARTTILE32  165
#define STARTTILE32M 165
#define STARTEXTERNS 165
#endif

//
// Thank you for using IGRAB!
//
