@echo off
cls
type BATCHLST.TXT
choice /C:123456780 /N Please select what to clean:
echo.

if ERRORLEVEL 9 goto end

REM Case 5 needs special handling
if ERRORLEVEL 6 goto simple
if NOT ERRORLEVEL 5 goto simple

del 19961112\*.*
del 19961207\*.*
goto end

:simple
if ERRORLEVEL 1 set DIR=19960501
if ERRORLEVEL 2 set DIR=19960904
if ERRORLEVEL 3 set DIR=19960820
if ERRORLEVEL 4 set DIR=19961012

if ERRORLEVEL 6 set DIR=19970212
if ERRORLEVEL 7 set DIR=19970522
if ERRORLEVEL 8 set DIR=20000614

del %DIR%\*.*

:end
