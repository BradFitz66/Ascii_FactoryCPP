# Ascii Factory
A C++ remake of my factory game prototype I originally made in Rust with Bevy. This version uses EnTT for the ECS and libtcod for text graphics.

# Credits
This project is built off of the template project for libtcod. EnTT is used for the ECS, and FastNoise2 is used for noise generation.

# Building
Once again, I'm pretty bad at setting up build systems outside of a dedicated IDE like Visual Studio.

The general gist of getting this to build is:
* Configure the cmake cache to use MSVC (Visual Studio 17 2022)
* Make sure all paths for everything is correct. Most of the dependencies are installed via vcpkg, but FastNoise2 isn't because it isn't available via vcpkg (woo I love C++ package managers!) so you'll have to grab all the stuff for that (lib files and such)
* Try building (```cmake --build build```)

