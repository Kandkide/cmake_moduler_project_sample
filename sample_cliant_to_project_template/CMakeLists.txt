# single folder application 1.2.0
cmake_minimum_required(VERSION 3.5...3.27)

# ------------------------------------------------------------- #
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
# ------------------------------------------------------------- #

get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME) # Get the directory name
set(MY_PROJECT_NAME ${DIR_NAME}) # project name
set(MY_PROJECT_VERSION 1.2.3) # project version
project(${MY_PROJECT_NAME} VERSION ${MY_PROJECT_VERSION} LANGUAGES CXX)

# ------------------ CUSTOMIZE ------------------ #
set(EXE_TARGET_NAME ${DIR_NAME})
set(EXE_SOURCE_FILE_NAMES "main.cpp") ### add sources if any ###

set(MY_EXE_EXPORT_DIR ${CMAKE_INSTALL_PREFIX}/program/bin) # install dir

set(RUN_EXECUTABLE_POST_BUILD ON) # execute exe file after build (flag)

# Set compiler flags
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # exports json file (optional)
# ------------------ CUSTOMIZE END -------------- #

# Add the executable
add_executable(${EXE_TARGET_NAME} ${EXE_SOURCE_FILE_NAMES})

# --- execution related --- #
# Post build execution of exe
if(RUN_EXECUTABLE_POST_BUILD)
    add_custom_command(TARGET ${EXE_TARGET_NAME}
                       POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E echo "Running ${EXE_TARGET_NAME}..."
                       COMMAND $<TARGET_FILE:${EXE_TARGET_NAME}>
                       WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif()

# 名前を付けたカスタムターゲット
add_custom_target(run_${EXE_TARGET_NAME}
    COMMAND ${CMAKE_COMMAND} -E echo "Running ${EXE_TARGET_NAME}..."
    COMMAND $<TARGET_FILE:${EXE_TARGET_NAME}>
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running custom command for ${EXE_TARGET_NAME}"
    VERBATIM
    USES_TERMINAL
)

# --- install related --- #
install(TARGETS ${EXE_TARGET_NAME} DESTINATION ${MY_EXE_EXPORT_DIR})


# -------------------- MAIN BUISINESS -------------------- #
# # Qt 6を使用する場合 (if Qt6 is linked in including library, find_package is enough in this place)
# find_package(Qt6 COMPONENTS Widgets REQUIRED)
# # target_link_libraries(${EXE_TARGET_NAME} PUBLIC Qt6::Widgets)  # append "Qt6::Widgets" to MY_LINK_ITEMS_LIST instead

# # Find the installed sample_components package and link it with the executable
# find_package(sample_components REQUIRED)
# # target_link_libraries(${EXE_TARGET_NAME} PRIVATE sample_components::component1) # append "sample_components::component1"
find_package(project_template REQUIRED)

# # supposing pybind11 is linked in sample_components' components
# find_package(pybind11 REQUIRED)

# append items to MY_LINK_ITEMS_LIST if necessary
set(MY_LINK_ITEMS_LIST "project_template::sample_component") # append here: "Qt6::Widgets" etc.
# -------------------- MAIN BUISINESS END -------------------- #

target_link_libraries(${EXE_TARGET_NAME} PRIVATE ${MY_LINK_ITEMS_LIST})

# # uncomment if use header-only headers
# target_include_directories(${EXE_TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/header_only)


# # --- EXTRE: alternative executables related --- #
# # MY_LINK_ITEMS_LIST is used inside. so it must be set beforehand. (CODE ORDER MATTERS)

# file(GLOB SOURCES "alt*.cpp")

# foreach(SOURCE_FILE ${SOURCES})
#     get_filename_component(EXE_NAME ${SOURCE_FILE} NAME_WE)
#     set(EXE_NAME ${EXE_TARGET_NAME}_${EXE_NAME})
#     add_executable(${EXE_NAME} ${SOURCE_FILE})
#     target_link_libraries(${EXE_NAME} PRIVATE ${MY_LINK_ITEMS_LIST})

#     add_custom_command(TARGET ${EXE_NAME}
#                        POST_BUILD
#                        COMMAND ${CMAKE_COMMAND} -E echo "Running ${EXE_NAME}..."
#                        COMMAND $<TARGET_FILE:${EXE_NAME}>
#                        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
# endforeach()

