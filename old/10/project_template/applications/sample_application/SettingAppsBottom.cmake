# applications.bottom.SettingAppsBottom.cmake-1.3.2

set(MY_PROJECT_VERSION 1.2.3) # project version
# set(EXE_SOURCE_FILE_NAMES "main.cpp") ### add sources if any ###
set(COPY_EXECUTABLE_TO_PROJECT_ROOT off) # copy exe file after build

if(NOT DEFINED RUN_EXECUTABLE_POST_BUILD)
    set(RUN_EXECUTABLE_POST_BUILD on) # execute exe file after build
endif()

# -------------------- MAIN BUISINESS -------------------- #
# # Qt 6を使用する場合 (if Qt6 is linked in including library, find_package is enough in this place)
# find_package(Qt6 COMPONENTS Widgets REQUIRED)
# # target_link_libraries(${EXE_TARGET_NAME} PUBLIC Qt6::Widgets)  # append "Qt6::Widgets" to MY_LINK_ITEMS_LIST instead

# # Find the installed sample_components package and link it with the executable
# find_package(sample_components REQUIRED)
# # target_link_libraries(${EXE_TARGET_NAME} PRIVATE sample_components::component1) # append "sample_components::component1"

# # supposing pybind11 is linked in sample_components' components
# find_package(pybind11 REQUIRED)

# # OpneCV
# find_package(OpenCV REQUIRED)
# # target_link_libraries(${EXE_TARGET_NAME} PRIVATE ${OpenCV_LIBS}) # append ${OpenCV_LIBS} to MY_LINK_ITEMS_LIST instead

# # FFmpeg
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET
#     libavdevice
#     libavfilter
#     libavformat
#     libavcodec
#     libswresample
#     libswscale
#     libavutil
# )
# # target_link_libraries(${EXE_TARGET_NAME} PRIVATE PkgConfig::LIBAV) # append "PkgConfig::LIBAV" to MY_LINK_ITEMS_LIST instead

# append items to MY_LINK_ITEMS_LIST if necessary
set(MY_LINK_ITEMS_LIST "sample_component") # append here: "Qt6::Widgets" "pybind11::embed" ${OpenCV_LIBS} "PkgConfig::LIBAV" etc.
# -------------------- MAIN BUISINESS END -------------------- #
