@echo off
cls
type BATCHLST.TXT
choice /C:123450 /N Please select what to clean:
echo.
if ERRORLEVEL 6 goto end
if ERRORLEVEL 1 set DIR=DN3D14
if ERRORLEVEL 2 set DIR=DN3D15
if ERRORLEVEL 3 set DIR=NAM10
if ERRORLEVEL 4 set DIR=WW2GI10
if ERRORLEVEL 5 set DIR=EDK20023

del %DIR%\*.*
:end
