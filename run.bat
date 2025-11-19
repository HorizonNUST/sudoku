@echo off
setlocal enabledelayedexpansion

:: Default build type
set "BUILD_TYPE=Debug"

if "%~1"=="--release" (
    set "BUILD_TYPE=Release"
)

:: Colors (ANSI)
for /f "tokens=2 delims==" %%I in ('"echo prompt $E ^| cmd"') do set "ESC=%%I"
set "GREEN=%ESC%[0;32m"
set "RED=%ESC%[0;31m"
set "YELLOW=%ESC%[1;33m"
set "CYAN=%ESC%[0;36m"
set "PURPLE=%ESC%[0;35m"
set "RESET=%ESC%[0m"

echo %CYAN%Assuming Platform is Windows...%RESET%

cls
cls
cls

:: Stop on errors
setlocal enabledelayedexpansion
set ERRLEV=0

:: Ensure build folder exists
if not exist build (
    mkdir build
)

:: Generate build files
echo %YELLOW%Generating CMake build files...%RESET%
cmake -B build -S . ^
    -DCMAKE_TOOLCHAIN_FILE=%cd%\external\vcpkg\scripts\buildsystems\vcpkg.cmake ^
    -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
if errorlevel 1 (
    echo %RED% Failed to configure CMake.%RESET%
    exit /b 1
)

:: Build project
echo %YELLOW%Compiling using CMake...%RESET%
cmake --build build --config %BUILD_TYPE%
if errorlevel 1 (
    echo %RED% Build failed.%RESET%
    exit /b 1
)

:: Run the executable and measure time
echo %PURPLE%Executable Started...%RESET%

set "starttime=%time%"
build\main.exe
set "endtime=%time%"

:: Calculate elapsed time
:: Convert start and end times to seconds
for /f "tokens=1-4 delims=:.," %%a in ("%starttime%") do (
    set /a startsecs=(%%a*3600)+(%%b*60)+%%c
)
for /f "tokens=1-4 delims=:.," %%a in ("%endtime%") do (
    set /a endsecs=(%%a*3600)+(%%b*60)+%%c
)

set /a elapsedsecs=!endsecs!-!startsecs!
if !elapsedsecs! LSS 0 set /a elapsedsecs+=86400

echo %PURPLE%Elapsed Time: !elapsedsecs! seconds%RESET%

endlocal
pause
