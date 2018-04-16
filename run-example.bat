@echo off

call set-env.bat

cd %~dp0

set GAME_DIR=SfmlExample\x64\Debug

%GAME_DIR%\SfmlExample.exe