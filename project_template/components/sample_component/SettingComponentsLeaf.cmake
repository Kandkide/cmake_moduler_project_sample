# components.leaf.SettingComponentsLeaf-1.2.6

set(OTHER_SOURCE_FILE_NAMES "parts_of_component.cpp") ### add sources if any ###

# -------------------- CONTROL INCLUDE AND LINK -------------------- #

# --- EXTERNAL LIBRARIES --- #

# # pybind11
# find_package(pybind11 REQUIRED)

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

# --- NOT IN PACKAGE, Specify library individually --- #

# # Link the executable with the required libraries (windows platform)
# # target_link_libraries(${LIB_TARGET_NAME} PRIVATE comdlg32 ole32) => append comdlg32 ole32 instead

# --- INTERNAL LIBRARIES --- #

# # component1に依存する場合（component1は同一プロジェクト内にあるとする）
# # target_link_libraries(${LIB_TARGET_NAME} PRIVATE component1) => append component1 instead

# -------------------- CONTROL INCLUDE AND LINK END -------------------- #

set(MY_LINK_ITEMS_LIST "") 
# append followings if needed
# pybind11::embed, Qt6::Widgets, ${OpenCV_LIBS} PkgConfig::LIBAV
# comdlg32 ole32, component1, and etc.