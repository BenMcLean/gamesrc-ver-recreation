@echo off
if "%1" == "" goto error
if "%2" == "" goto error
mkdir %2
wmake %1 BUILDREV=%2
goto end
:error
echo This script shouldn't be run independently
:end
