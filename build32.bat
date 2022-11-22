@REM Clear screen
cls

@echo off
	@REM Save root path for this project
	set rootPath=%__CD__%

	@REM Delete .exe file(s)
	del "%rootPath%"bin\x86\*.exe

	@REM Create intermediate folder for .obj files
	mkdir interm
	cd interm
@echo on
@REM Compile code and place in 'interm' folder
cl /c /EHsc /I "%rootPath%include" "%rootPath%src\*.c"

@echo off
	cd "%rootPath%bin\x86"
	set commonFiles[0]="%rootPath%interm\DataIO.obj"
	set commonFiles[1]="%rootPath%interm\FileHelper.obj"
	set commonFiles[2]="%rootPath%interm\OpenCLHelper.obj"
	set libs="%rootPath%lib\x86\OpenCL.lib"
@echo on
link "%rootPath%interm\Add_iArray.obj" %commonFiles[0]% %commonFiles[1]% %commonFiles[2]% %libs%
link "%rootPath%interm\Add_iNumber.obj" %commonFiles[0]% %commonFiles[1]% %commonFiles[2]% %libs%
link "%rootPath%interm\Add_fArray.obj" %commonFiles[0]% %commonFiles[1]% %commonFiles[2]% %libs%
link "%rootPath%interm\Add_fNumber.obj" %commonFiles[0]% %commonFiles[1]% %commonFiles[2]% %libs%
link "%rootPath%interm\Sub_iArray.obj" %commonFiles[0]% %commonFiles[1]% %commonFiles[2]% %libs%
link "%rootPath%interm\Sub_iNumber.obj" %commonFiles[0]% %commonFiles[1]% %commonFiles[2]% %libs%
link "%rootPath%interm\Sub_fArray.obj" %commonFiles[0]% %commonFiles[1]% %commonFiles[2]% %libs%
link "%rootPath%interm\Sub_fNumber.obj" %commonFiles[0]% %commonFiles[1]% %commonFiles[2]% %libs%

@echo off
	@REM Delete intermediate folder
	rmdir /s /q "%rootPath%interm"

	@REM Return to root directory
	cd %rootPath%
@echo on
