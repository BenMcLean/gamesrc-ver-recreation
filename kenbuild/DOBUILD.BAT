@echo off
cls
type BATCHLST.TXT
choice /C:123456780 /N Please select what to build:
echo.

if ERRORLEVEL 9 goto end
if ERRORLEVEL 8 goto 20000614
if ERRORLEVEL 7 goto 19970522
if ERRORLEVEL 6 goto 19970212
if ERRORLEVEL 5 goto DN3D15
if ERRORLEVEL 4 goto 19961012
if ERRORLEVEL 3 goto DN3D14
if ERRORLEVEL 2 goto 19960904
if ERRORLEVEL 1 goto 19960501

:19960501
call bldhlpr a.obj 19960501
goto end
:19960904
call bldhlpr mmulti.obj 19960904
goto end
:DN3D14
call bldhlpr engine.obj 19960820
if ERRORLEVEL 1 goto end
call bldhlpr cache1d.obj 19960820
goto end
:19961012
call bldhlpr engine.obj 19961012
goto end
:DN3D15
call bldhlpr engine.obj 19961112
if ERRORLEVEL 1 goto end
call bldhlpr cache1d.obj 19961207
goto end
:19970212
call bldhlpr engine.obj 19970212
goto end
:19970522
call bldhlpr engine.obj 19970522
goto end
:20000614
call bldhlpr game.exe 20000614
goto end

:end
