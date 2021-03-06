// WOLFHACK.C

#include "WL_DEF.H"

#define	MAXVIEWHEIGHT	200

int		spanstart[MAXVIEWHEIGHT/2];

fixed	stepscale[MAXVIEWHEIGHT/2];
fixed	basedist[MAXVIEWHEIGHT/2];

extern	char	far	planepics[8192];	// 4k of ceiling, 4k of floor

int		halfheight = 0;

// *** S3DNA RESTORATION ***
#ifdef GAMEVER_NOAH3D
byte	*planeylookup[MAXVIEWHEIGHT/2];
#else
byte	far *planeylookup[MAXVIEWHEIGHT/2];
#endif
unsigned	mirrorofs[MAXVIEWHEIGHT/2];

fixed	psin, pcos;

fixed FixedMul (fixed a, fixed b)
{
	return (a>>8)*(b>>8);
}


int		mr_rowofs;
int		mr_count;
int		mr_xstep;
int		mr_ystep;
int		mr_xfrac;
int		mr_yfrac;
int		mr_dest;

// *** S3DNA RESTORATION ***
#ifdef GAMEVER_NOAH3D
void	MapRow (void);
#endif

/*
==============
=
= DrawSpans
=
= Height ranges from 0 (infinity) to viewheight/2 (nearest)
==============
*/

void DrawSpans (int x1, int x2, int height)
{
	fixed		length;
	int			ofs;
	int			prestep;
	fixed		startxfrac, startyfrac;

	int			x, startx, count, plane, startplane;
	// *** S3DNA RESTORATION ***
#ifdef GAMEVER_NOAH3D
	byte		*toprow;
#else
	byte		far	*toprow, far *dest;
#endif

	toprow = planeylookup[height]+bufferofs;
	mr_rowofs = mirrorofs[height];
	// *** S3DNA RESTORATION ***
#ifdef GAMEVER_NOAH3D
	if (!height)
		Quit ("DrawSpans(): Zero height!");
#endif

	mr_xstep = (psin<<1)/height;
	mr_ystep = (pcos<<1)/height;

	length = basedist[height];
	startxfrac = (viewx + FixedMul(length,pcos));
	startyfrac = (viewy - FixedMul(length,psin));

// draw two spans simultaniously

	plane = startplane = x1&3;
	prestep = viewwidth/2 - x1;
	do
	{
		outportb (SC_INDEX+1,1<<plane);
		mr_xfrac = startxfrac - (mr_xstep>>2)*prestep;
		mr_yfrac = startyfrac - (mr_ystep>>2)*prestep;

		startx = x1>>2;
		mr_dest = (unsigned)toprow + startx;
		mr_count = ((x2-plane)>>2) - startx + 1;
		x1++;
		prestep--;
		if (mr_count)
			MapRow ();
		plane = (plane+1)&3;
	} while (plane != startplane);

}




// *** S3DNA RESTORATION ***
#ifdef GAMEVER_NOAH3D
void LoadFloorTiles (int tile)
{
	unsigned char	far *dest, far *src;
	int		x;

	tile = tile*2+(PMSpriteStart-8);
	if (tile+1 >= PMSpriteStart)
	{
		sprintf (str,"LoadFloorTiles(): Invalid floor tile %u!", (tile-(PMSpriteStart-8))/2);
		Quit (str);
	}
	src = PM_GetPage (tile+1);
	dest = planepics;
	for (x=0;x<PMPageSize;x++)
	{
		*dest = *src++;
		dest += 2;
	}
	
	src = PM_GetPage (tile);
	dest = planepics+1;
	for (x=0;x<PMPageSize;x++)
	{
		*dest = *src++;
		dest += 2;
	}
}
#endif

/*
===================
=
= SetPlaneViewSize
=
===================
*/

void SetPlaneViewSize (void)
{
	int		x,y;
	byte 	far *dest, far *src;

	halfheight = viewheight>>1;


	for (y=0 ; y<halfheight ; y++)
	{
		// *** S3DNA RESTORATION ***
		// It's technically useless to cast 0xa0000000l to a 16-bit near
		// pointer, but this helps to (re)generate some ASM instruction
#ifdef GAMEVER_NOAH3D
		planeylookup[y] = (byte *)0xa0000000l + (halfheight-1-y)*SCREENBWIDE;
#else
		planeylookup[y] = (byte far *)0xa0000000l + (halfheight-1-y)*SCREENBWIDE;;
#endif
#if 0
	asm	nop
	asm	nop
	asm	nop
#endif
		mirrorofs[y] = (y*2+1)*SCREENBWIDE;

		stepscale[y] = y*GLOBAL1/32;
		if (y>0)
			basedist[y] = GLOBAL1/2*scale/y;
	}

// *** S3DNA RESTORATION ***
#ifndef GAMEVER_NOAH3D
	src = PM_GetPage(0);
	dest = planepics;
	for (x=0 ; x<4096 ; x++)
	{
		*dest = *src++;
		dest += 2;
	}
	src = PM_GetPage(1);
	dest = planepics+1;
	for (x=0 ; x<4096 ; x++)
	{
		*dest = *src++;
		dest += 2;
	}
#endif

}


/*
===================
=
= DrawPlanes
=
===================
*/

void DrawPlanes (void)
{
	int		height, lastheight;
	int		x;

	// *** S3DNA RESTORATION ***
#ifndef GAMEVER_NOAH3D
	if (viewheight>>1 != halfheight)
		SetPlaneViewSize ();		// screen size has changed
#endif


	psin = viewsin;
	if (psin < 0)
		psin = -(psin&0xffff);
	pcos = viewcos;
	if (pcos < 0)
		pcos = -(pcos&0xffff);

//
// loop over all columns
//
	lastheight = halfheight;

	for (x=0 ; x<viewwidth ; x++)
	{
		height = wallheight[x]>>3;
		if (height < lastheight)
		{	// more starts
			do
			{
				spanstart[--lastheight] = x;
			} while (lastheight > height);
		}
		else if (height > lastheight)
		{	// draw spans
			if (height > halfheight)
				height = halfheight;
			for ( ; lastheight < height ; lastheight++)
				DrawSpans (spanstart[lastheight], x-1, lastheight);
		}
	}

	height = halfheight;
	for ( ; lastheight < height ; lastheight++)
		DrawSpans (spanstart[lastheight], x-1, lastheight);
}

