# components.root-1.1.0

set(EXCLUDE_DIRS "build" "__pycache__") # excludes from add_subdirectory()

# Search and add all subdirectories within the directory
file(GLOB SUBDIR_LIST RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)
foreach(SUBDIR IN LISTS SUBDIR_LIST)
    # Process the subdirectory only if it is not included in the exclude list
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR} AND NOT "${SUBDIR}" IN_LIST EXCLUDE_DIRS)
        add_subdirectory(${SUBDIR})
    endif()
endforeach()

# Generate the config file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
)

# Install the config files
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION lib/cmake/${PROJECT_NAME}
)

# Install the export set for use with the install/export command
install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION lib/cmake/${PROJECT_NAME}
)

# Configure the .pc file for pkg-config
set(PKG_CONFIG_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/MyPackage.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
    @ONLY
)

# Install the .pc file
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
    DESTINATION ${PKG_CONFIG_INSTALL_DIR}
)
