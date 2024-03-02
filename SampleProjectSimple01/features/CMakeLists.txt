# in the root directory (only one)
cmake_minimum_required(VERSION 3.27)

# Get the directory name (DIR_NAME)
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

#----- Project-wide variable settings (DO CUSTOMIZE) -----#

# Add build options (whether to build the main program in the 'features' directory)
if(NOT BUILD_FEATURES_MAIN_PROGRAM)
    set(BUILD_FEATURES_MAIN_PROGRAM ON) ## OPTION ##
endif()

# Project version number
if(NOT MY_PROJECT_VERSION)
    set(MY_PROJECT_VERSION 1.2.3)
endif()

# List of specific subdirectory names to be excluded (do not add to project)
set(EXCLUDE_DIRS "build")

if(NOT MY_PROJECT_PREFIX)
    set(MY_PROJECT_PREFIX "mypr_")
endif()

# ## DO CUSTOMIZE (STRONG) ##
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/..)

# Set the installation directory for the application executable (APP_INSTALL_DIR) ##  no use in features ##
if(NOT APP_INSTALL_DIR)
    set(APP_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/bin)
endif()
# It can be specified using the CMake command line as '-DAPP_INSTALL_DIR=...'

if(NOT CMAKE_PREFIX_PATH)
    set(CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}")
endif()

#----- Project-wide variable settings (end) -----#

# Specify the project name and version
project(${MY_PROJECT_PREFIX}${DIR_NAME} VERSION ${MY_PROJECT_VERSION} LANGUAGES CXX)

# Search and add all subdirectories within the directory
file(GLOB SUBDIR_LIST RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)

foreach(SUBDIR IN LISTS SUBDIR_LIST)
    # Process the subdirectory only if it is not included in the exclude list
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR} AND NOT "${SUBDIR}" IN_LIST EXCLUDE_DIRS)
        add_subdirectory(${SUBDIR})
    endif()
endforeach()


#---- Targets and Config install related ----#

install(
    EXPORT ${CMAKE_PROJECT_NAME}Targets
    DESTINATION lib/cmake/${CMAKE_PROJECT_NAME}
    NAMESPACE ${CMAKE_PROJECT_NAME}::
    FILE ${CMAKE_PROJECT_NAME}Targets.cmake)

include(CMakePackageConfigHelpers)
configure_package_config_file( 
    "Config.cmake.in" 
    "${CMAKE_PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION lib/cmake/${CMAKE_PROJECT_NAME})

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake"
    DESTINATION lib/cmake/${CMAKE_PROJECT_NAME})