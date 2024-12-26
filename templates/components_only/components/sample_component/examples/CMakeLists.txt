# components.examples.leaf-0.0.2

# Search for all example*.cpp files in the current directory
file(GLOB EXAMPLE_SOURCES "example*.cpp")

# Debugging: output the found sources
message(STATUS "Found example files: ${EXAMPLE_SOURCES}")

# Common libraries to link
set(COMMON_LIBRARIES
    ${LIB_TARGET_NAME}  # Link with the custom library
    # Add additional libraries here if needed
)

# Create executable targets for each example
foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
    # Generate executable target name
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)
    set(EXAMPLE_TARGET_NAME "${EXAMPLE_NAME}_${LIB_TARGET_NAME}")

    # Add executable target
    add_executable(${EXAMPLE_TARGET_NAME} ${EXAMPLE_SOURCE})
    target_link_libraries(${EXAMPLE_TARGET_NAME} PRIVATE ${COMMON_LIBRARIES})

    # Append to the list of executable targets
    list(APPEND EXECUTABLE_TARGETS ${EXAMPLE_TARGET_NAME})

    # Add a POST_BUILD command to run each example after it’s built
    add_custom_command(
        TARGET ${EXAMPLE_TARGET_NAME}
        POST_BUILD
        COMMAND $<TARGET_FILE:${EXAMPLE_TARGET_NAME}>
        COMMENT "Running ${EXAMPLE_TARGET_NAME}..."
    )
endforeach()
