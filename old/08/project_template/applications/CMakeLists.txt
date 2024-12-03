# inbetween-1.0.5
# in directories without source files (guide from upper to lower directories in the project)
cmake_minimum_required(VERSION 3.5...3.27)

# Get the directory name
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Exclude specific subdirectories
set(EXCLUDE_DIRS "build") ## DO CUSTOMIZE ##

# Search and add all subdirectories within the directory
file(GLOB SUBDIR_LIST RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)

foreach(SUBDIR IN LISTS SUBDIR_LIST)
    # Process the subdirectory only if it is not included in the exclude list
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR} AND NOT "${SUBDIR}" IN_LIST EXCLUDE_DIRS)
        add_subdirectory(${SUBDIR})
    endif()
endforeach()
