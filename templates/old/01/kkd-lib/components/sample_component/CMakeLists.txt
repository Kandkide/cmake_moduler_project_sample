# components.leaf-2.0.1
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
      EXPORT ${PROJECT_NAME}Targets
      LIBRARY DESTINATION lib/${PROJECT_NAME}
      ARCHIVE DESTINATION lib/${PROJECT_NAME}
  )
  install(FILES ${LIB_HEADER_FILES} DESTINATION include/${PROJECT_NAME})

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
      EXPORT ${PROJECT_NAME}Targets
      LIBRARY DESTINATION lib/${PROJECT_NAME}
      ARCHIVE DESTINATION lib/${PROJECT_NAME}
  )
  install(FILES ${LIB_HEADER_FILES} DESTINATION include/${PROJECT_NAME})
endif()

# Link dependencies
target_link_libraries(${LIB_TARGET_NAME} PRIVATE ${MY_LINK_ITEMS_LIST})

target_include_directories(${LIB_TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/header_only)

# # add tests directory
# add_subdirectory(tests)

# # add examples directory
# add_subdirectory(examples)

# Define options to include examples and tests
option(ENABLE_EXAMPLES "Include examples in the build" ON)
option(ENABLE_TESTS "Include tests in the build" ON)

# Conditionally add the examples directory
if(ENABLE_EXAMPLES)
    message(STATUS "Including examples in the build.")
    add_subdirectory(examples)
else()
    message(STATUS "Excluding examples from the build.")
endif()

# Conditionally add the tests directory
if(ENABLE_TESTS)
    message(STATUS "Including tests in the build.")
    add_subdirectory(tests)
else()
    message(STATUS "Excluding tests from the build.")
endif()

