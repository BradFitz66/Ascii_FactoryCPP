#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "libtcod::libtcod" for configuration "Release"
set_property(TARGET libtcod::libtcod APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(libtcod::libtcod PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/libtcod.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "utf8proc"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/libtcod.dll"
  )

list(APPEND _cmake_import_check_targets libtcod::libtcod )
list(APPEND _cmake_import_check_files_for_libtcod::libtcod "${_IMPORT_PREFIX}/lib/libtcod.lib" "${_IMPORT_PREFIX}/bin/libtcod.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
