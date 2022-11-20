@REM Clear screen
cls

@echo off
	@REM Save root path for this project
	set rootPath=%__CD__%

	@REM Create intermediate folder for .obj files
	mkdir interm
	cd interm
@echo on

@REM Compile code and place in 'interm' folder
cl /c /EHsc /I "%rootPath%include" "%rootPath%src\*.c"

@REM Build program for 32 bit system
@echo off
	cd "%rootPath%bin\x64"
@echo on
link /OUT:"main.exe" "%rootPath%lib\x64\OpenCL.lib" "%rootPath%interm\*.obj"

@REM Delete intermediate folder
@echo off
	rmdir /s /q "%rootPath%interm"
@echo on

@REM Run main file
main.exe

@echo off
	@REM Delete main file
	@REM del main.exe

	@REM Return to root directory
	cd %rootPath%
@echo on
