@echo off
setlocal enabledelayedexpansion

:: Colors
set "GREEN="
set "RED="
set "YELLOW="
set "CYAN="
set "PURPLE="
set "RESET="

for /f "tokens=1,2 delims==" %%a in ('"prompt $H & for %%b in (1) do rem"') do set "BS=%%b"

:: Helper to print colors (Windows 10+ supports ANSI)
for /f "tokens=2 delims==" %%I in ('"echo prompt $E ^| cmd"') do set "ESC=%%I"
set "GREEN=%ESC%[0;32m"
set "RED=%ESC%[0;31m"
set "YELLOW=%ESC%[1;33m"
set "CYAN=%ESC%[0;36m"
set "PURPLE=%ESC%[0;35m"
set "RESET=%ESC%[0m"

echo %CYAN%Updating vcpkg submodule...%RESET%
git submodule update --init --recursive
if errorlevel 1 (
    echo %RED%Failed to update git submodules.%RESET%
    exit /b 1
)

echo %CYAN%Detecting platform...%RESET%
set "PLATFORM=windows"
echo %GREEN%Detected platform: %PURPLE%!PLATFORM!%RESET%

:: Bootstrap vcpkg if needed
if not exist "external\vcpkg\vcpkg.exe" (
    echo %YELLOW%Bootstrapping vcpkg...%RESET%
    call external\vcpkg\bootstrap-vcpkg.bat
    if errorlevel 1 (
        echo %RED%Bootstrap failed.%RESET%
        exit /b 1
    )
) else (
    echo %GREEN%vcpkg already bootstrapped.%RESET%
)

:: Install packages
echo %CYAN%Installing sfml package via vcpkg...%RESET%
external\vcpkg\vcpkg.exe install sfml
if errorlevel 1 (
    echo %RED%Failed to install sfml via vcpkg.%RESET%
    exit /b 1
)

echo %CYAN%To install packages run:%RESET%
echo %PURPLE%external\vcpkg\vcpkg.exe install ^<package_name^%%RESET%

:: Setup cmake preset
echo %CYAN%Setting up CMake preset...%RESET%
cmake --preset=default
if errorlevel 1 (
    echo %YELLOW%Warning: Could not configure CMake preset automatically.%RESET%
)

echo %PURPLE%In VS Code, open Command Palette and select 'CMake: Select Build Preset' → 'Default with vcpkg'%RESET%
echo %PURPLE%After successful setup, syntax highlighting and other features will activate.%RESET%

echo %CYAN%Run run.bat to build and run the program.%RESET%
echo %GREEN%Setup complete!%RESET%

endlocal
pause
