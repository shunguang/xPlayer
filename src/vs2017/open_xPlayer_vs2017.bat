@echo off

REM define environment variables, do not change the variable name, just it's value!
set FFTW_X64=C:\pkg\fftw\fftw-3.3.5-dll64
set BOOST_INC=C:\pkg\boost_1_63_0
set BOOST_LIB=C:\pkg\boost_1_63_0\lib64-msvc-14.0
set CV_INC=C:\pkg\opencv\v3.2\install_local_w_extra_modules_vs2015x64\include
set CV_LIB=C:\pkg\opencv\v3.2\install_local_w_extra_modules_vs2015x64\x64\vc14\lib
set QT_DIR=C:\pkg\Qt\5.9.1\5.9.1\msvc2017_64
set QT_INC=C:\pkg\Qt\5.9.1\5.9.1\msvc2017_64\include
set QT_LIB=C:\pkg\Qt\5.9.1\5.9.1\msvc2017_64\lib
set FFMPEG_INC=C:\pkg\ffmpeg\ffmpeg-20170503-a75ef15-win64-dev\include
set FFMPEG_LIB=C:\pkg\ffmpeg\ffmpeg-20170503-a75ef15-win64-dev\lib

set PROJ_SRC=C:\Projects\xPlayer\src
set PROJ_BUILD=C:\Projects\xPlayer\build-vs2017-x64\int
set PROJ_EXPORT=C:\Projects\xPlayer\build-vs2017-x64\bin

"C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\Common7\IDE\devenv.exe" %PROJ_SRC%\vs2017\xPlayer.sln

REM ---eof---/Users/wus1/Projects/2020/p803/software/payload-cpu/pyxis-analysis/vs2017/pyxisAnalysis.props


