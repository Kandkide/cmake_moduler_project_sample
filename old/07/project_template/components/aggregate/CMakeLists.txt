# components.aggregate.leaf-1.2.0
# DERIVED FROM components leaf (at 1.1.3)
# Set names
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(LIB_TARGET_NAME ${DIR_NAME}) # Library name
set(LIB_HEADER_NAME ${DIR_NAME}.hpp)
# set(LIB_CPP_FILE_NAME ${DIR_NAME}.cpp) ## DIFFERENCE HERE (deleted) ##

# Library
add_library(${LIB_TARGET_NAME} INTERFACE) ## DIFFERENCE HERE (below) ##
# add_library(${LIB_TARGET_NAME} ${LIB_HEADER_NAME} ${LIB_CPP_FILE_NAME})

# Set include directories for the target
target_include_directories(${LIB_TARGET_NAME}
  INTERFACE ## DIFFERENCE HERE (PUBLIC) ##
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

# Install targets
install(TARGETS ${LIB_TARGET_NAME}
    EXPORT ${MY_PACKAGE_NAME}Targets # ${MY_PACKAGE_NAME} must be defined in root project
    LIBRARY DESTINATION lib/${MY_INSTALL_SUBDIRECTORY_NAME}
    ARCHIVE DESTINATION lib/${MY_INSTALL_SUBDIRECTORY_NAME}
)

# Install the headers
install(FILES ${LIB_HEADER_NAME} DESTINATION include/${MY_INSTALL_SUBDIRECTORY_NAME})


# set it off and modify else() segment below if you need to link selectively
set(TO_LINK_ALL_COMPONENTS_AUTOMATICALLY on)

if (TO_LINK_ALL_COMPONENTS_AUTOMATICALLY)

  # 親ディレクトリのパスを取得
  get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

  # 親ディレクトリのサブディレクトリのリストを取得
  file(GLOB SUBDIRECTORIES LIST_DIRECTORIES true RELATIVE ${PARENT_DIR} ${PARENT_DIR}/*)

  # カレントディレクトリ(${DIR_NAME})を除外してディレクトリのみをリンク
  foreach(SUBDIR ${SUBDIRECTORIES})
    if(IS_DIRECTORY "${PARENT_DIR}/${SUBDIR}" AND NOT "${SUBDIR}" STREQUAL "${DIR_NAME}")
      target_link_libraries(${LIB_TARGET_NAME} INTERFACE ${SUBDIR})
      # message("Subdirectory: ${SUBDIR}")
    endif()
  endforeach()

else()

  # need to list up all libraries (components) inside the project here
  target_link_libraries(${LIB_TARGET_NAME} INTERFACE sample_component)
  # target_link_libraries(${LIB_TARGET_NAME} INTERFACE another_component)

endif()

