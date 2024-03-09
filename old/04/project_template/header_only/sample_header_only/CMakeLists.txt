# header_only leaf 1.1.4
# Set names
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
# set(MY_INSTALL_SUBDIRECTORY_NAME ${MY_PACKAGE_NAME}) # ${MY_PACKAGE_NAME} must be defined in root project

# ヘッダーファイルのリストを取得
file(GLOB HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

# Install the headers
# Set MY_HEADER_ONLY_INSTALL_PREFIX variable appropriately in root CMakeLists.txt
install(FILES ${HEADER_FILES} DESTINATION ${MY_HEADER_ONLY_INSTALL_PREFIX}/include/${DIR_NAME})

