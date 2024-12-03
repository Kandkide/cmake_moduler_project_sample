# applications.bottom-1.3.3
cmake_minimum_required(VERSION 3.5...3.27)

# Set names
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(MY_PROJECT_NAME ${DIR_NAME}) # project name
set(EXE_TARGET_NAME ${DIR_NAME})


# --- reading from SettingAppsBottom.cmake if it exists else define here --- #
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/SettingAppsBottom.cmake")
    include(SettingAppsBottom.cmake)
else()
    set(MY_PROJECT_VERSION 1.2.3) # project version
    set(EXE_SOURCE_FILE_NAMES "main.cpp") ### add sources if any ###
    set(RUN_EXECUTABLE_POST_BUILD ON) # execute exe file after build
    set(COPY_EXECUTABLE_TO_PROJECT_ROOT off) # copy exe file after build
    set(MY_LINK_ITEMS_LIST "")
endif()
# ------ #

# # Only when aggregate directory exist, append aggregate to link lists
# find_path(AGGREGATE_DIR aggregate PATHS ${CMAKE_SOURCE_DIR}/components)
# if(AGGREGATE_DIR)
#     set(MY_LINK_ITEMS_LIST ${MY_LINK_ITEMS_LIST} "aggregate")
# endif()

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

# Copy the executable to the current directory
if(COPY_EXECUTABLE_TO_PROJECT_ROOT)
    add_custom_command(TARGET ${EXE_TARGET_NAME}
                       POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy
                               $<TARGET_FILE:${EXE_TARGET_NAME}>
                               ${CMAKE_SOURCE_DIR}/${EXE_TARGET_NAME}.exe)
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

# # -------------------- HERE IS THE RUIN OF MAIN BUISINESS -------------------- #

target_link_libraries(${EXE_TARGET_NAME} PRIVATE ${MY_LINK_ITEMS_LIST})

# uncomment if use header-only headers
target_include_directories(${EXE_TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/header_only)


# --- EXTRE: alternative executables related --- #
# MY_LINK_ITEMS_LIST is used inside. so it must be set beforehand. (CODE ORDER MATTERS)

file(GLOB SOURCES "alt*.cpp")

foreach(SOURCE_FILE ${SOURCES})
    get_filename_component(EXE_NAME ${SOURCE_FILE} NAME_WE)
    set(EXE_NAME ${EXE_TARGET_NAME}_${EXE_NAME})
    add_executable(${EXE_NAME} ${SOURCE_FILE})
    target_link_libraries(${EXE_NAME} PRIVATE ${MY_LINK_ITEMS_LIST})

    add_custom_command(TARGET ${EXE_NAME}
                       POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E echo "Running ${EXE_NAME}..."
                       COMMAND $<TARGET_FILE:${EXE_NAME}>
                       WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endforeach()

