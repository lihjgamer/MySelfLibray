@echo off
set ROOT_PATH=%cd%
echo %ROOT_PATH%

cd ..
set P_PATH = %cd%
echo %P_PATH%

rem
::for /R %%s in (.,*) do ( 
::echo %%s 
::) 

for /r %%I in (*.vcproj,*.vcxproj,*.sln,*.obj,*.pdb,*.filters,*.user,*.log) do (
	del /f %%I
)

cd %ROOT_PATH%
pause
premake5.exe --file=premake5.lua vs2013
pause