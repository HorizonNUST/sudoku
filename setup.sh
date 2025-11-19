#!/bin/bash

# variables

# Color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
PURPLE='\033[0;35m'
RESET='\033[0m' # No Color
readonly GREEN RED YELLOW CYAN PURPLE RESET

# variables end

set -e

# DO NOT CALL; has been called once; given below for reference only
# git submodule add https://github.com/microsoft/vcpkg.git external/vcpkg

# update submodules
git submodule update --init --recursive

# detect platform
echo -e "${CYAN}Detecting platform...${RESET}"

PLATFORM="unknown"

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    PLATFORM="linux"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    PLATFORM="macos"
elif [[ "$OSTYPE" == "msys"* || "$OSTYPE" == "cygwin"* || "$OSTYPE" == "win"* ]]; then
    PLATFORM="windows"
else
    echo -e "${RED}Unsupported OS type: $OSTYPE${RESET}"
    exit 1
fi

echo -e "${GREEN}Detected platform: ${PURPLE}$PLATFORM${RESET}"
# platform detect end

# bootstrap it to generate ./external/vcpkg/vcpkg
# if bootstrap file `external/vcpkg/vcpkg` does not exists generate it
if [ ! -f "./external/vcpkg/vcpkg" ]; then
    echo -e "${YELLOW}Bootstrapping vcpkg... ${RESET}"
    # ./external/vcpkg/bootstrap-vcpkg.sh
    if [ "$PLATFORM" == "windows" ]; then
        ./external/vcpkg/bootstrap-vcpkg.bat
    elif [ "$PLATFORM" == "linux" ] || [ "$PLATFORM" == "macos" ]; then
        ./external/vcpkg/bootstrap-vcpkg.sh
    else # unknown platform
        echo -e "${RED}Unsupported platform for bootstrapping vcpkg: $PLATFORM${RESET}"
        exit 1
    fi
else
    echo -e "${GREEN}vcpkg already bootstrapped. ${RESET}"
fi

# install packages (for current template)
echo -e "${CYAN}Installing sfml package from vcpkg ${PURPLE}./external/vcpkg/vcpkg install sfml${RESET}"
if [ "$PLATFORM" == "windows" ]; then
    ./external/vcpkg/vcpkg.exe install sfml
elif [ "$PLATFORM" == "linux" ] || [ "$PLATFORM" == "macos" ]; then
    ./external/vcpkg/vcpkg install sfml
else
    echo -e "${RED}Unsupported platform for installing sfml package: $PLATFORM${RESET}"
    exit 1
fi
echo -e "${CYAN}To install packages run ./external/vcpkg/vcpkg install <package_name>${RESET}"

# setup cmake preset; REMOVE after setting up preset
cmake --preset=default
echo -e "${PURPLE}In VS Code, open Command Palette and search for 'CMake: Select Build Preset' select 'Default with vcpkg' ${RESET}"
echo -e "${PURPLE}After succesfully setting up preset, syntax highlighting along with other features should be active. You can safely remove the preset section from "setup.sh" ${RESET}"

echo -e "${CYAN}Run ./run.sh for running the program ${RESET}"
