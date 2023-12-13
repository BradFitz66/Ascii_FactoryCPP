# Ascii Factory
A C++ remake of my factory game prototype I originally made in Rust with Bevy. This version uses EnTT for the ECS and libtcod for text graphics.

# Credits
This project is built off of the template project for libtcod. EnTT is used for the ECS, and FastNoise2 is used for noise generation.

# Building

This uses cmake with the MSVC compiler. These instructions pertain to Windows only, you may have difficulty trying to compile on Linux and other OS

* Run command ```git clone --recurse-submodules https://github.com/BradFitz66/Ascii_FactoryCPP.git```
* Open cmake-gui and configure the cache (Visual Studio 2022 is what I used)
* Setup the necessary paths (libtcod and SDL2 should be fetched automatically by VCPKG). FastNoise2_DIR should point to the folder containing FastNoise2Targets.cmake and FastNoise2Config.cmake (FastNoise2Targets.cmake may be in a different folder to FastNoise2Config.cmake, putting them in the same folder fixed any issues. I found FastNoise2Config.cmake in build/generated after building FastNoise2 w/ cmake and I found FastNoise2Targets.cmake in build/CMakeFiles/Export)
