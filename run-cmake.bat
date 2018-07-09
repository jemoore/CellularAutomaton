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

set SFML_DIR=%THIRD_PARTY_DIR%\sfml\SFML-2.4.2-windows-vc14-64-bit\SFML-2.4.2\cmake\Modules

cd "%~dp0\CellularAutomaton\build"
cmake -DCMAKE_GENERATOR_PLATFORM=x64 ..

:END
