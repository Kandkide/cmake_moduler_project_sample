# in applications directories with souce files (build exe file)
cmake_minimum_required(VERSION 3.27)

# Get the directory name
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Specify the project name (no need for version as it's set at the root)
project(${DIR_NAME}_project_apps)

# Set C++23 as the standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set compiler options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3") ## DO CUSTOMIZE ##

# Specify all source files that start with "main"
file(GLOB MAIN_SOURCES main*.cpp) ## DO CUSTOMIZE ##

# Set the executable name (using the directory name here)
set(EXE_TARGET_NAME ${DIR_NAME}) ## DO CUSTOMIZE ##

# Create the executable target
add_executable(${EXE_TARGET_NAME} ${MAIN_SOURCES})

# Uncomment and use the following lines if using Qt 6
find_package(Qt6 COMPONENTS Widgets REQUIRED)
target_link_libraries(${EXE_TARGET_NAME} PRIVATE Qt6::Widgets)

# Uncomment and use the following lines if using pybind11
# find_package(pybind11 REQUIRED)
# target_link_libraries(${EXE_TARGET_NAME} PRIVATE pybind11::pybind11)

# Uncomment and use the following lines if using within-project library (directory name is "feature1")
# target_link_libraries(${EXE_TARGET_NAME} PRIVATE feature1_lib)

# Add a post-build command to run the executable after building
add_custom_command(TARGET ${EXE_TARGET_NAME}
                    POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E echo "Running ${EXE_TARGET_NAME}..."
                    COMMAND $<TARGET_FILE:${EXE_TARGET_NAME}>)

# Specify the installation directory (parent directory's bin in this case)
install(TARGETS ${EXE_TARGET_NAME} DESTINATION ${APP_INSTALL_DIR})

# Create uninstall target
add_custom_target(uninstall-${EXE_TARGET_NAME}
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake
)

# Generate uninstall script with correct executable name
configure_file(
    "${CMAKE_SOURCE_DIR}/uninstall_apps.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake"
    @ONLY
)

# Allow uninstall target to depend on install
add_dependencies(uninstall-${EXE_TARGET_NAME} ${EXE_TARGET_NAME})