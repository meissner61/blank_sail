::Start the Development Environment
echo The Current Directory is %cd%

title %cd%

::Change this line to match your Visual Studio vcvars.bat directory
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

:: Path to the Visual Studio executable
set VS_DEVENV="C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.exe"

:: Path to the compiled executable
set TARGET_EXE=..\bin\x64\main.exe

:: Source files to open
set SRC_FILES=..\src\*.cpp ..\src\*.h

call cd

::Change to your personal LIBRARY DIRECTORIES, REMEMBER NO SPACES AROUND = sign
set SDL2="C:\libs\SDL2-2.28.1"

::INCLUDE DIRECTORIES
set SDL2_INCLUDE="%SDL2%\include"
set SDL2_GFX_INCLUDE=""

::LIBRARY DIRECTORIES
set SDL2_lib="%SDL2%\lib\x64"

::SOURCE FILES
set SRC_FILES=  ../src/*.cpp

::Make bin and intermediate directory if its not there
call mkdir ..\bin\x64\
call mkdir ..\intermediate\

::copy require .DLLs
call copy "%SDL2_lib%\SDL2.dll" "..\bin\x64\"



::compile with the aformentioned flags and directories
call cl %SRC_FILES% /std:c++17 /EHsc /W4 /Zi^
        /Fo../intermediate/ ^
        /I%SDL2_INCLUDE% ^
        /link ^
        /LIBPATH:%SDL2_lib% ^
        user32.lib ^
        SDL2main.lib ^
        SDL2.lib ^
        shell32.lib ^
        /SUBSYSTEM:CONSOLE /out:../bin/x64/main.exe

:: Start debugging with the target executable and open the source files for editing
%VS_DEVENV% /DebugExe %TARGET_EXE% /Command "File.OpenFile C:\devop\blank_sail\src\main.cpp"

:: Uncomment to directly invoke the debugger
    ::devenv /DebugExe ..\bin\x64\main.exe

::%VS_DEVENV% /DebugExe %TARGET_EXE% %SRC_FILES%