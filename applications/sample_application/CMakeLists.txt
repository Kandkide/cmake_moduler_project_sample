cmake_minimum_required(VERSION 3.5...3.27)

# CMAKE_INSTALL_PREFIX and CMAKE_PREFIX_PATH are set to USER_HOME (common to all projects)
if (UNIX)
execute_process(COMMAND sh -c "echo $HOME" OUTPUT_VARIABLE USER_HOME)
elseif (WIN32)
execute_process(COMMAND cmd.exe /c "echo %USERPROFILE%" OUTPUT_VARIABLE USER_HOME)
string(REPLACE "\\" "/" USER_HOME ${USER_HOME})
endif ()
string(STRIP ${USER_HOME} USER_HOME)

set(CMAKE_INSTALL_PREFIX "${USER_HOME}")
set(CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}")
# ------------------------------------------------------------- #

# Set names
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(MY_PROJECT_NAME ${DIR_NAME})
set(MY_PROJECT_VERSION 1.2.3)
set(EXE_TARGET_NAME ${DIR_NAME})
set(EXE_SOURCE_FILE_NAMES "main.cpp") ### add sources if any ###
set(MY_EXE_EXPORT_DIR ${CMAKE_INSTALL_PREFIX}/program/bin) ### CUSTOMIZE ###
# set(MY_EXE_EXPORT_DIR ${CMAKE_INSTALL_PREFIX}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # exports json file (optional)

# Specify the project name and version
project(${MY_PROJECT_NAME} VERSION ${MY_PROJECT_VERSION} LANGUAGES CXX)

# Add the executable
add_executable(${EXE_TARGET_NAME} ${EXE_SOURCE_FILE_NAMES})

# -------------------- MAIN BUISINESS -------------------- #
# # Qt 6を使用する場合
# find_package(Qt6 COMPONENTS Widgets REQUIRED)
# target_link_libraries(${LIB_TARGET_NAME} PUBLIC Qt6::Widgets)

# Find the installed sample_components package and link it with the executable
find_package(sample_components REQUIRED)
target_link_libraries(${EXE_TARGET_NAME} PRIVATE sample_components::component1)
# target_link_libraries(${EXE_TARGET_NAME} PRIVATE sample_components::component2)

# # supposing pybind11 is linked in sample_components' components
# find_package(pybind11 REQUIRED)
# -------------------- MAIN BUISINESS END -------------------- #

## PROCESS INSTALL ##
# Install the executable to the specified directory
install(TARGETS ${EXE_TARGET_NAME} DESTINATION ${MY_EXE_EXPORT_DIR})

## PROCESS UNINSTALL ##
# Generate uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)