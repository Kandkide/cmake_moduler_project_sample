# components leaf 1.1.3
# Set names
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(LIB_TARGET_NAME ${DIR_NAME}) # Library name
set(LIB_HEADER_NAME ${DIR_NAME}.hpp)
set(LIB_CPP_FILE_NAME ${DIR_NAME}.cpp)
set(MY_INSTALL_SUBDIRECTORY_NAME ${MY_PACKAGE_NAME}) # ${MY_PACKAGE_NAME} must be defined in root project

# # Set compiler flags
# set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")

# Library
add_library(${LIB_TARGET_NAME} ${LIB_HEADER_NAME} ${LIB_CPP_FILE_NAME})

# Set include directories for the target
target_include_directories(${LIB_TARGET_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

# Install targets
install(TARGETS ${LIB_TARGET_NAME} # ${EXE_TARGET_NAME}
    EXPORT ${MY_PACKAGE_NAME}Targets # ${MY_PACKAGE_NAME} must be defined in root project
    # RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib/${MY_INSTALL_SUBDIRECTORY_NAME}
    ARCHIVE DESTINATION lib/${MY_INSTALL_SUBDIRECTORY_NAME}
)

# Install the headers
install(FILES ${LIB_HEADER_NAME} DESTINATION include/${MY_INSTALL_SUBDIRECTORY_NAME})


# -------------------- CONTROL INCLUDE AND LINK -------------------- #

# --- LINK AND INCLUDE --- #

# # pybind11: find, Include, and link with ${LIB_TARGET_NAME}
# find_package(pybind11 REQUIRED)
# target_link_libraries(${LIB_TARGET_NAME} PUBLIC pybind11::embed)
# # target_include_directories(${LIB_TARGET_NAME} PUBLIC ${pybind11_INCLUDE_DIR})

# # Qt 6を使用する場合
# find_package(Qt6 COMPONENTS Widgets REQUIRED)
# target_link_libraries(${LIB_TARGET_NAME} PUBLIC Qt6::Widgets)

# # Link the executable with the required libraries (windows platform)
# target_link_libraries(${LIB_TARGET_NAME} PRIVATE comdlg32 ole32)

# # component1に依存する場合（component1は同一プロジェクト内にあるとする）
# target_link_libraries(${LIB_TARGET_NAME} PRIVATE component1)

# -------------------- CONTROL INCLUDE AND LINK END -------------------- #

