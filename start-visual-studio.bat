cd %~dp0

call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"
call set-env.bat

devenv "CellularAutomaton\CellularAutomaton.sln"
