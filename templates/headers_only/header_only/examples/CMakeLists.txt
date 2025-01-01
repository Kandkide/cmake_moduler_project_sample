# header_only.examples.leaf-0.0.3

# Search for all example*.cpp files in the current directory
file(GLOB EXAMPLE_SOURCES "example*.cpp")

# Debugging: output the found sources
message(STATUS "Found example files: ${EXAMPLE_SOURCES}")

# Common libraries to link
set(COMMON_LIBRARIES
    # Add additional libraries here if needed
)

# Create executable targets for each example
foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
    # Generate executable target name
    get_filename_component(EXAMPLE_TARGET_NAME ${EXAMPLE_SOURCE} NAME_WE)
    # set(EXAMPLE_TARGET_NAME "${EXAMPLE_NAME}")

    # Add executable target
    add_executable(${EXAMPLE_TARGET_NAME} ${EXAMPLE_SOURCE})
    target_link_libraries(${EXAMPLE_TARGET_NAME} PRIVATE ${COMMON_LIBRARIES})

    # Link dependencies
    target_include_directories(${EXAMPLE_TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/header_only)

    # # Append to the list of executable targets
    # list(APPEND EXECUTABLE_TARGETS ${EXAMPLE_TARGET_NAME})

    # Post build execution of exe
    if(RUN_EXECUTABLE_POST_BUILD)
        # Add a POST_BUILD command to run each example after it’s built
        add_custom_command(
            TARGET ${EXAMPLE_TARGET_NAME}
            POST_BUILD
            COMMAND $<TARGET_FILE:${EXAMPLE_TARGET_NAME}>
            COMMENT "Running ${EXAMPLE_TARGET_NAME}..."
        )
    endif()

    # 名前を付けたカスタムターゲット
    add_custom_target(run_${EXAMPLE_TARGET_NAME}
        COMMAND ${CMAKE_COMMAND} -E echo "Running ${EXAMPLE_TARGET_NAME}..."
        COMMAND $<TARGET_FILE:${EXAMPLE_TARGET_NAME}>
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running custom command for ${EXAMPLE_TARGET_NAME}"
        VERBATIM
        USES_TERMINAL
    )

endforeach()

