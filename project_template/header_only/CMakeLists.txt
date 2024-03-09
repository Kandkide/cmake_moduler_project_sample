# header_only root 1.0.6
cmake_minimum_required(VERSION 3.5...3.27)

# ------------------ CUSTOMIZE ------------------ #
set(MY_HEADER_ONLY_INSTALL_PREFIX C:/msys64/ucrt64) # header-only install prefixe

set(EXCLUDE_DIRS "build" "__pycache__") # excludes from add_subdirectory()

get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(MY_PROJECT_NAME ${DIR_NAME})
set(MY_PROJECT_VERSION 1.2.3)
# ------------------ CUSTOMIZE END -------------- #

project(${MY_PROJECT_NAME} VERSION ${MY_PROJECT_VERSION} LANGUAGES CXX)

# Search and add all subdirectories within the directory
file(GLOB SUBDIR_LIST RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)
foreach(SUBDIR IN LISTS SUBDIR_LIST)
    # Process the subdirectory only if it is not included in the exclude list
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR} AND NOT "${SUBDIR}" IN_LIST EXCLUDE_DIRS)
        add_subdirectory(${SUBDIR})
    endif()
endforeach()

