# header_only.root-1.2.0

# Exclude specific subdirectories
set(EXCLUDE_DIRS "build" "examples" "tests") ## DO CUSTOMIZE ##

# Search and add all subdirectories within the directory
file(GLOB MY_HEADER_SUBDIR_LIST RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)

foreach(SUBDIR IN LISTS MY_HEADER_SUBDIR_LIST)
    # Process the subdirectory only if it is not included in the exclude list
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR} AND NOT "${SUBDIR}" IN_LIST EXCLUDE_DIRS)
        add_subdirectory(${SUBDIR})
    endif()
endforeach()

# # Link dependencies
# target_include_directories(${LIB_TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/header_only)

# Define options to include examples and tests
option(ENABLE_EXAMPLES "Include examples in the build" ON)
option(ENABLE_TESTS "Include tests in the build" ON)

# Conditionally add the examples directory
if(ENABLE_EXAMPLES)
    message(STATUS "Including examples in the build.")
    add_subdirectory(examples)
else()
    message(STATUS "Excluding examples from the build.")
endif()

# Conditionally add the tests directory
if(ENABLE_TESTS)
    message(STATUS "Including tests in the build.")
    add_subdirectory(tests)
else()
    message(STATUS "Excluding tests from the build.")
endif()
