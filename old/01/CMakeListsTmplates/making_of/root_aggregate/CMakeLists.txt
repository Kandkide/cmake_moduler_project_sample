# in the root directory (only one)
cmake_minimum_required(VERSION 3.27)

# Get the directory name (DIR_NAME)
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

#----- Project-wide variable settings (DO CUSTOMIZE) -----#

# Set the installation directory for the application executable (APP_INSTALL_DIR)
if(NOT DEFINED APP_INSTALL_DIR)
    set(APP_INSTALL_DIR ${CMAKE_SOURCE_DIR}/../bin)
endif()
# It can be specified using the CMake command line as '-DAPP_INSTALL_DIR=...'

# Add build options (whether to build the main program in the 'features' directory)
if(NOT DEFINED BUILD_FEATURES_MAIN_PROGRAM)
    set(BUILD_FEATURES_MAIN_PROGRAM ON) ## OPTION ##
endif()

# Project version number
if(NOT DEFINED MY_PROJECT_VERSION)
    set(MY_PROJECT_VERSION 1.2.3)
endif()

# List of specific subdirectory names to be excluded (do not add to project)
set(EXCLUDE_DIRS "groups" "build")

#----- Project-wide variable settings (end) -----#

# Specify the project name and version
project(${DIR_NAME}_project_root VERSION ${MY_PROJECT_VERSION} LANGUAGES CXX)

# Search and add all subdirectories within the directory
file(GLOB SUBDIR_LIST RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)

foreach(SUBDIR IN LISTS SUBDIR_LIST)
    # Process the subdirectory only if it is not included in the exclude list
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR} AND NOT "${SUBDIR}" IN_LIST EXCLUDE_DIRS)
        add_subdirectory(${SUBDIR})
    endif()
endforeach()
