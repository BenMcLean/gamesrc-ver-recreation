/*** BLAKE STONE: ALIENS OF GOLD RESTORATION ***/
// Relocated code to a separate file from 3D_MAIN.C,
// since this is a part of JM_FREE.C in AOG (versions 2.1 and 3.0).
//
// - Should be #include'd from the right location.
// - A couple of char arrays are accessed as near buffers in AOG and far in PS.
// - Note that MAX_DEST_PATH_LEN isn't defined here. In PS, it's defined
// in 3D_MAIN.C long before the definition of InitDestPath.

//-------------------------------------------------------------------------
// InitDestPath()
//-------------------------------------------------------------------------
void InitDestPath(void)
{
	char *ptr;

#pragma warn -pia
	if (ptr=getenv("APOGEECD"))
	{
		struct ffblk ffblk;
		short len;

#ifdef GAMEVER_RESTORATION_AOG
		len = strlen(ptr);
#else
		len = _fstrlen(ptr);
#endif
		if (len > MAX_DEST_PATH_LEN)
		{
			printf("\nAPOGEECD path too long.\n");
			exit(0);
		}

#ifdef GAMEVER_RESTORATION_AOG
		strcpy(destPath,ptr);
#else
		_fstrcpy(destPath,ptr);
#endif
		if (destPath[len-1] == '\\')
			destPath[len-1]=0;

		if (findfirst(destPath,&ffblk,FA_DIREC) == -1)
		{
			printf("\nAPOGEECD directory not found.\n");
			exit(0);
		}

#ifdef GAMEVER_RESTORATION_AOG
		strcat(destPath,"\\");
#else
		_fstrcat(destPath,"\\");
#endif
	}
	else
#ifdef GAMEVER_RESTORATION_AOG
		strcpy(destPath,"");
#else
		_fstrcpy(destPath,"");
#endif
#pragma warn +pia
}
