# project.top-1.2.3
cmake_minimum_required(VERSION 3.5...3.27)

# Get the directory name
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${DIR_NAME})

# ------------------ CUSTOMIZE (project level) ------------------ #
# CMAKE_INSTALL_PREFIX and CMAKE_PREFIX_PATH are set to USER_HOME (common to all projects)
if (UNIX)
execute_process(COMMAND sh -c "echo $HOME" OUTPUT_VARIABLE USER_HOME)
elseif (WIN32)
execute_process(COMMAND cmd.exe /c "echo %USERPROFILE%" OUTPUT_VARIABLE USER_HOME)
string(REPLACE "\\" "/" USER_HOME ${USER_HOME})
endif ()
string(STRIP ${USER_HOME} USER_HOME)
set(CMAKE_INSTALL_PREFIX "${USER_HOME}") ### IMPORTANT ###
set(CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}") ### IMPORTANT ###

# header-only install prefixe
set(MY_HEADER_ONLY_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}) ### IMPORTANT ###
# set(MY_HEADER_ONLY_INSTALL_PREFIX C:/msys64/ucrt64) ### IMPORTANT ###

# executables install directory
set(MY_EXE_EXPORT_DIR ${CMAKE_INSTALL_PREFIX}/program/bin) ### IMPORTANT ###

# exports json file (optional)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# deault to rood directory name
set(MY_PACKAGE_NAME ${DIR_NAME}) 

# used in place of ... in lib/..., include/..., and lib/cmake/...
set(MY_INSTALL_SUBDIRECTORY_NAME ${MY_PACKAGE_NAME})
# ------------------ CUSTOMIZE (local level) -------------- #

# # used in sub-projects
# find_path(AGGREGATE_DIR aggregate PATHS ${CMAKE_SOURCE_DIR}/components)
# message(${AGGREGATE_DIR})

# Exclude specific subdirectories
set(EXCLUDE_DIRS "build" "__pycache__" "cmakelists_copy_data")

# Set compiler flags
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")

# Search and add all subdirectories within the directory
file(GLOB SUBDIR_LIST RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)

foreach(SUBDIR IN LISTS SUBDIR_LIST)
    # Process the subdirectory only if it is not included in the exclude list
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR} AND NOT "${SUBDIR}" IN_LIST EXCLUDE_DIRS)
        add_subdirectory(${SUBDIR})
    endif()
endforeach()

# Important
## DO NOT rename "aggregate" directory.
## DO NOT rename "header_only" directory if you use header-only libraries.

# THREE growth points: "sample_application", "sample_component", and "sample_header_only" directories.
## rename these directry and duplicate them as you like.

# package name: set by the name of project root directory.
## install directories will be: lib/package_name, include/package_name, and lib/cmake/package_name
## MY_PACKAGE_NAME, is the variable representing package name in the code

#HOW to specify library (component)
## inside project: #include "my_component.hpp"
## outside project: #include <package_name/my_component.hpp>

## ALSO: target_link_libraries in client cmakelists.txt
## inside: target_link_libraries(${EXE_TARGET_NAME} PRIVATE my_component)
## outside(1): find_package(package_name REQUIRED)
## outside(2): target_link_libraries(${EXE_TARGET_NAME} PRIVATE package_name::my_component)

#You can do it IN AGGREGATE,
## First, include all your components (libraries) in aggregate/aggregate.hpp. Then,
## inside project: #include "aggregate.hpp"
## outside project: #include <package_name/aggregate.hpp>
## ALSO: target_link_libraries in client cmakelists.txt (see above: replacing "my_componet" to "aggregate")

# header-only header must be specified with its directory name.
## for example, if my_header.hpp is in sample_header_only directory, you have to specify it as
## #include "sample_header_only/my_header.hpp"

# DELETE directories if not in use: "header_only" "applications" can be deleted.


# Commands

# basic operations
# cmake -S . -B build [--fresh (optional)]
# cmake --build build [--clean-first (optional)]

# to re-run sample_application
# cmake --build build --target run_sample_application

# to install (per sub-project)
# cmake --install .\build\components\
# cmake --install .\build\applications\
# cmake --install .\build\applications\sample_application\
# cmake --install .\build\header_only\

