# applications.bottom.SettingAppsBottom.cmake-1.3.3

set(MY_PROJECT_VERSION 1.2.3) # project version
# set(EXE_SOURCE_FILE_NAMES "main.cpp") ### add sources if any ###
set(COPY_EXECUTABLE_TO_PROJECT_ROOT off) # copy exe file after build

if(NOT DEFINED RUN_EXECUTABLE_POST_BUILD)
    set(RUN_EXECUTABLE_POST_BUILD on) # execute exe file after build
endif()

# -------------------- MAIN BUISINESS -------------------- #
# # Qt6
# find_package(Qt6 COMPONENTS Widgets REQUIRED)

# # pybind11
# find_package(pybind11 REQUIRED)
# find_package(Python3 REQUIRED COMPONENTS Development)
# include_directories(${Python3_INCLUDE_DIRS})

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

# # Boost の指定したバージョンを見つける
# find_package(Boost 1.70 REQUIRED COMPONENTS program_options)

# # Boost が見つかった場合に include パスやリンクを設定
# if (Boost_FOUND)
#     include_directories(${Boost_INCLUDE_DIRS})
#     # target_link_libraries(your_target_name PRIVATE ${Boost_LIBRARIES})
# endif()


find_package(kkd-lib REQUIRED)

# append items to MY_LINK_ITEMS_LIST if necessary
set(MY_LINK_ITEMS_LIST "kkd-lib::sample_component") # append here: "Qt6::Widgets" "pybind11::embed" ${OpenCV_LIBS} "PkgConfig::LIBAV" etc.
# -------------------- MAIN BUISINESS END -------------------- #
