cmake_minimum_required (VERSION 3.13...3.21)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE
        "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
endif()


project(
    libtcod-vcpkg-template  # Project name, change this as needed.
    LANGUAGES CXX
)
#If debug, use FastNoiseD.lib, otherwise just use FastNoise.lib
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("CMAKE_BUILD_TYPE is Debug")
    set(FASTNOISE_LIB deps/FastNoiseD.lib)
else()
    message("CMAKE_BUILD_TYPE is Release")
    set(FASTNOISE_LIB deps/FastNoise.lib)
endif()

#Add to cmake prefix path
set(CMAKE_PREFIX_PATH ${FASTNOISE_LIB} ${CMAKE_PREFIX_PATH})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")  # Keep all runtime files in one directory.

file(
    GLOB_RECURSE SOURCE_FILES
    CONFIGURE_DEPENDS  # Automatically reconfigure if source files are added/removed.
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*.hpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Ensure the C++17 standard is available.
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/inc/entt ${PROJECT_SOURCE_DIR}/inc/)


# Enforce UTF-8 encoding on MSVC.
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
endif()

# Enable warnings recommended for new projects.
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()


find_package(SDL2 CONFIG REQUIRED)
find_package(libtcod CONFIG REQUIRED)
set(FastNoise_DIR "${CMAKE_CURRENT_SOURCE_DIR}/submodules")
find_package(FastNoise2 CONFIG REQUIRED)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
        libtcod::libtcod
        ../deps/FastNoise
)
#The cmake command to build debug version is:
