# components.leaf-2.0.0
# (mod from 1.2.7: supposed directory structure changed!)
# Set names
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(LIB_TARGET_NAME ${DIR_NAME}) # Library name

# --- reading from SettingComponentsLeaf.cmake if it exists else define here --- #
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/SettingComponentsLeaf.cmake")
    include(SettingComponentsLeaf.cmake)
else()
    set(MY_LINK_ITEMS_LIST "")
    set(OTHER_SOURCE_FILE_NAMES "")
endif()
# ------ #

# Collect header and source files
set(LIB_HEADER_FILES "")
set(LIB_SOURCE_FILES "")

# Add all headers from "include" directory
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include")
    file(GLOB_RECURSE LIB_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
endif()

# Add all sources from "src" directory
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src")
    file(GLOB_RECURSE LIB_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
endif()

# Add library only if source files are found
if(LIB_SOURCE_FILES)
  # Library
  add_library(${LIB_TARGET_NAME} ${LIB_HEADER_FILES} ${LIB_SOURCE_FILES} ${OTHER_SOURCE_FILE_NAMES})

  # Include directories
  target_include_directories(${LIB_TARGET_NAME}
    PUBLIC
      $<INSTALL_INTERFACE:include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  )

  # Install library and headers
  install(TARGETS ${LIB_TARGET_NAME}
      EXPORT ${MY_PACKAGE_NAME}Targets
      LIBRARY DESTINATION lib/${MY_INSTALL_SUBDIRECTORY_NAME}
      ARCHIVE DESTINATION lib/${MY_INSTALL_SUBDIRECTORY_NAME}
  )
  install(FILES ${LIB_HEADER_FILES} DESTINATION include/${MY_INSTALL_SUBDIRECTORY_NAME})

else()
  # INTERFACE library for header-only case
  add_library(${LIB_TARGET_NAME} INTERFACE)

  # Include directories
  target_include_directories(${LIB_TARGET_NAME}
    INTERFACE
      $<INSTALL_INTERFACE:include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  )

  # Install headers only
  install(TARGETS ${LIB_TARGET_NAME}
      EXPORT ${MY_PACKAGE_NAME}Targets
      LIBRARY DESTINATION lib/${MY_INSTALL_SUBDIRECTORY_NAME}
      ARCHIVE DESTINATION lib/${MY_INSTALL_SUBDIRECTORY_NAME}
  )
  install(FILES ${LIB_HEADER_FILES} DESTINATION include/${MY_INSTALL_SUBDIRECTORY_NAME})
endif()

# Link dependencies
target_link_libraries(${LIB_TARGET_NAME} PRIVATE ${MY_LINK_ITEMS_LIST})

target_include_directories(${LIB_TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/header_only)
