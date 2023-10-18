
echo The Current Directory is %cd%

title %cd%

::Change this line to match your Visual Studio vcvars.bat directory
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

call cd
cmd /k