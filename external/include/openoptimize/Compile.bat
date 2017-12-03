@echo off &SETLOCAL
for /r %%i in (*.asm) do nasm -f win64 %%i

SET t=lib
for /r %%i in (*.obj) do call SET "t=%%t%% %%i"
SET "t=%t% /OUT:..\..\lib\x64\openoptimize.lib"
%t%
@echo on