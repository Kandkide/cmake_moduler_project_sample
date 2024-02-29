#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "mypr_features::feature1" for configuration ""
set_property(TARGET mypr_features::feature1 APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(mypr_features::feature1 PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/mypr_features/libfeature1.a"
  )

list(APPEND _cmake_import_check_targets mypr_features::feature1 )
list(APPEND _cmake_import_check_files_for_mypr_features::feature1 "${_IMPORT_PREFIX}/lib/mypr_features/libfeature1.a" )

# Import target "mypr_features::feature2" for configuration ""
set_property(TARGET mypr_features::feature2 APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(mypr_features::feature2 PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/mypr_features/libfeature2.a"
  )

list(APPEND _cmake_import_check_targets mypr_features::feature2 )
list(APPEND _cmake_import_check_files_for_mypr_features::feature2 "${_IMPORT_PREFIX}/lib/mypr_features/libfeature2.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
