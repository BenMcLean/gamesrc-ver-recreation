bcc makeobj.c
makeobj f introscn.scn ..\introscn.obj IntroscnSeg _introscn
makeobj c audiodct.c3d ..\c3dadict.obj _audiodict
makeobj f audiohhd.c3d ..\c3dahead.obj _AudioHeader _audiohead
makeobj c egadict.c3d ..\c3dedict.obj _EGAdict
makeobj f egahead.c3d ..\c3dehead.obj EGA_grafixheader _EGAhead
makeobj f mtemp.tmp ..\c3dmhead.obj MapHeader _maphead
