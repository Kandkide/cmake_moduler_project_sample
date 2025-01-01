# components.leaf.SettingComponentsLeaf-1.2.8

set(OTHER_SOURCE_FILE_NAMES "") ### add sources if any ###

# -------------------- CONTROL INCLUDE AND LINK -------------------- #

# --- EXTERNAL LIBRARIES --- #

# # pybind11
# find_package(pybind11 REQUIRED)

# find_package(Python3 REQUIRED COMPONENTS Development)
# include_directories(${Python3_INCLUDE_DIRS})

# # Qt 6
# find_package(Qt6 COMPONENTS Widgets REQUIRED)

# # OpneCV
# find_package(OpenCV REQUIRED)

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

# # Link the executable with the required libraries (windows platform)
# target_link_libraries(${LIB_TARGET_NAME} PRIVATE comdlg32 ole32) => append comdlg32 ole32 instead

# # Boost の指定したバージョンを見つける
# find_package(Boost 1.70 REQUIRED COMPONENTS program_options)

# # Boost が見つかった場合に include パスやリンクを設定
# if (Boost_FOUND)
#     include_directories(${Boost_INCLUDE_DIRS})
#     # target_link_libraries(your_target_name PRIVATE ${Boost_LIBRARIES})
# endif()

# find_package(kkd-lib REQUIRED)

# -------------------- CONTROL INCLUDE AND LINK END -------------------- #

set(MY_LINK_ITEMS_LIST "") 
# append followings if needed
# pybind11::embed, Qt6::Widgets, ${OpenCV_LIBS} PkgConfig::LIBAV
# comdlg32 ole32, component1, and etc.