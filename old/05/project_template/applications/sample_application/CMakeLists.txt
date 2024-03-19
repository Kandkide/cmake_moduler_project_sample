# applications bottom 1.2.2
cmake_minimum_required(VERSION 3.5...3.27)

# Set names
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(MY_PROJECT_NAME ${DIR_NAME}) # project name
set(MY_PROJECT_VERSION 1.2.3) # project version
set(EXE_TARGET_NAME ${DIR_NAME})
set(EXE_SOURCE_FILE_NAMES "main.cpp") ### add sources if any ###

set(RUN_EXECUTABLE_POST_BUILD ON) # execute exe file after build

project(${MY_PROJECT_NAME} VERSION ${MY_PROJECT_VERSION} LANGUAGES CXX)

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

## PROCESS INSTALL ##
# Install the executable to the specified directory
install(TARGETS ${EXE_TARGET_NAME} DESTINATION ${MY_EXE_EXPORT_DIR})

# -------------------- MAIN BUISINESS -------------------- #
# # Qt 6を使用する場合 (if Qt6 is linked in including library, find_package is enough in this place)
# find_package(Qt6 COMPONENTS Widgets REQUIRED)
# target_link_libraries(${LIB_TARGET_NAME} PUBLIC Qt6::Widgets)

# # Find the installed sample_components package and link it with the executable
# find_package(sample_components REQUIRED)
# target_link_libraries(${EXE_TARGET_NAME} PRIVATE sample_components::component1)
# target_link_libraries(${EXE_TARGET_NAME} PRIVATE sample_components::component2)

# # supposing pybind11 is linked in sample_components' components
# find_package(pybind11 REQUIRED)
# -------------------- MAIN BUISINESS END -------------------- #

# use in-project components: use "aggregate" to link all inside-project libraries
target_link_libraries(${EXE_TARGET_NAME} PRIVATE aggregate)

# # uncomment if use header-only headers
# target_include_directories(${EXE_TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/header_only)
