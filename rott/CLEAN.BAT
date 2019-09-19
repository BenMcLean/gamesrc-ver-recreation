@echo off
if "%1"=="RTLD13A" goto task
if "%1"=="RTLD13B" goto task
if "%1"=="RTSW13" goto task
if "%1"=="RTRG13" goto task
if "%1"=="RTCD13" goto task
if "%1"=="RTSL13" goto task
echo You need to pass a supported UPPERCASE directory name as an argument.
echo Currently accepted: RTLD13A, RTLD13B, RTSW13, RTRG13, RTCD13, RTSL13
goto end
:task
del %1\*.*
if "%2"=="" goto end
rem Only a single AUDIOLIB revision is currently used

cd ..\audiolib
call clean.bat AL950724
cd ..\rott
:end
