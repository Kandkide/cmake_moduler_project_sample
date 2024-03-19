# components root 1.0.7
cmake_minimum_required(VERSION 3.5...3.27)

# Set names and other constants
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(MY_PROJECT_NAME ${DIR_NAME})
set(MY_PROJECT_VERSION 1.2.3)
if (NOT MY_PACKAGE_NAME) # suceeds package name if it's already set in upper level project
    set(MY_PACKAGE_NAME ${DIR_NAME})
endif()

set(EXCLUDE_DIRS "build" "__pycache__") # excludes from add_subdirectory()

# project name and version are set above (not here)
project(${MY_PROJECT_NAME} VERSION ${MY_PROJECT_VERSION} LANGUAGES CXX)

# Search and add all subdirectories within the directory
file(GLOB SUBDIR_LIST RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)
foreach(SUBDIR IN LISTS SUBDIR_LIST)
    # Process the subdirectory only if it is not included in the exclude list
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR} AND NOT "${SUBDIR}" IN_LIST EXCLUDE_DIRS)
        add_subdirectory(${SUBDIR})
    endif()
endforeach()

# Generate the config file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${MY_PACKAGE_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${MY_PACKAGE_NAME}Config.cmake
    INSTALL_DESTINATION lib/cmake/${MY_PACKAGE_NAME}
)

# Install the config files
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${MY_PACKAGE_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${MY_PACKAGE_NAME}ConfigVersion.cmake
    DESTINATION lib/cmake/${MY_PACKAGE_NAME}
)

# Install the export set for use with the install/export command
install(EXPORT ${MY_PACKAGE_NAME}Targets
    FILE ${MY_PACKAGE_NAME}Targets.cmake
    NAMESPACE ${MY_PACKAGE_NAME}::
    DESTINATION lib/cmake/${MY_PACKAGE_NAME}
)
