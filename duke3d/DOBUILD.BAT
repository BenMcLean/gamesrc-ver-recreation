@echo off
cls
type BATCHLST.TXT
choice /C:123450 /N Please select what to build:
echo.
if ERRORLEVEL 6 goto end
if ERRORLEVEL 1 set TARGET=DN3D14
if ERRORLEVEL 2 set TARGET=DN3D15
if ERRORLEVEL 3 set TARGET=NAM10
if ERRORLEVEL 4 set TARGET=WW2GI10
if ERRORLEVEL 5 set TARGET=EDK20023

if not %TARGET% == DN3D14 goto task
if not exist ..\kenbuild\19960820\cache1d.obj goto dn3d14error
if not exist ..\kenbuild\19960820\engine.obj goto dn3d14error
goto task
:dn3d14error
echo Can't recreate Duke3D 1.4, you need compatible Build engine
echo object files ready under ..\kenbuild.
goto end
:task
mkdir %TARGET%
wmake.exe "appver_exedef = %TARGET%"
:end
