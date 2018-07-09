@echo off
echo "Start"
if not exist "%~dp0\CellularAutomaton" (
	echo "CellularAutomaton dir does not exist!"
	echo "Cannot run cmake"
	
	goto END
)

if not exist "%~dp0\CellularAutomaton\build" (
	echo "Creating build dir..."
	mkdir "%~dp0\CellularAutomaton\build"
)

if not exist "%~dp0\CellularAutomaton\build" (
	echo "CellularAutomaton\build dir does not exist!"
	echo "Cannot run cmake"
	
	goto END
)

call set-env.bat

cd "%~dp0\CellularAutomaton\build"
cmake -DCMAKE_GENERATOR_PLATFORM=x64 ..

:END
