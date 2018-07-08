@echo off

call set-env.bat

cd %~dp0

set GAME_DIR=CellularAutomaton\x64\Debug

%GAME_DIR%\CellularAutomaton.exe
