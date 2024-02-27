cmake_minimum_required(VERSION 3.27)

get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# プロジェクト名を指定（バージョン不要：ルートで設定済み）
project(${MY_PROJECT_PREFIX}_${DIR_NAME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")

###### part of making library (default is static library) ######
# note: INTERFACE or PUBLIC (3 places + 1 place uncommented) I am not sure.

# ヘッダーオンリーの場合のソースファイル
set(LIB_SOURCES ${DIR_NAME}.hpp)

# ライブラリ名を変数に定義
set(LIB_TARGET_NAME ${DIR_NAME}_lib)

# ソースファイルが存在する場合にのみ追加
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${DIR_NAME}.cpp)
    list(APPEND LIB_SOURCES ${DIR_NAME}.cpp)
    # このライブラリのソースファイルを指定
    add_library(${LIB_TARGET_NAME} ${LIB_SOURCES})
    # インクルードディレクトリを指定
    target_include_directories(${LIB_TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})  
else()
    # ライブラリをビルド
    add_library(${LIB_TARGET_NAME} INTERFACE)
    # インクルードディレクトリを指定
    target_include_directories(${LIB_TARGET_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
endif()

# # Set the public headers for the library ##( PLAN A )##
# set_target_properties(${LIB_TARGET_NAME} PROPERTIES
#     PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/${DIR_NAME}.hpp"
# )

# # Qt 6を使用する場合
# find_package(Qt6 COMPONENTS Widgets REQUIRED)
# target_link_libraries(${LIB_TARGET_NAME} PRIVATE Qt6::Widgets)
# PUBLICを使うと、そのターゲットが依存する他のターゲットも同様にリンクされる
# INTERFACEを使用すると、そのターゲットを利用する外部のプロジェクトに対してリンク

# # pybind11を使用する場合
# find_package(pybind11 REQUIRED)
# target_link_libraries(${LIB_TARGET_NAME} PRIVATE pybind11::pybind11)

# feature1に依存する場合（feature1は同一プロジェクト内にあるとする）
# target_link_libraries(${LIB_TARGET_NAME} INTERFACE feature1_lib) # 最後のargのみ書き換える
# シンプルで良いが。必ず、ルートでビルドすること。


###### part of making exe file ######

# メインプログラムのソースファイルを指定
file(GLOB MAIN_SOURCES main*.cpp)

# メインプログラムの名前を変数に定義
set(EXE_TARGET_NAME ${DIR_NAME}_main)

# メインプログラムのソースファイルが存在する場合にのみビルド
if(BUILD_FEATURES_MAIN_PROGRAM AND MAIN_SOURCES)
    add_executable(${EXE_TARGET_NAME} ${MAIN_SOURCES})
    # ライブラリをリンク
    target_link_libraries(${EXE_TARGET_NAME} PRIVATE ${LIB_TARGET_NAME})

    # メインプログラムがビルドされた後に実行されるコマンドを追加
    add_custom_command(TARGET ${EXE_TARGET_NAME}
                       POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E echo "Running ${EXE_TARGET_NAME}..."
                       COMMAND $<TARGET_FILE:${EXE_TARGET_NAME}>)
else()
    message(STATUS "Main program build is disabled or main_${DIR_NAME}.cpp not found. Skipping executable build.")
endif()



# moc destination
set(MY_INSTALL_PREFIX "C:/Users/kandk/Downloads/codes_in_mouse_z6/cmake_moduler_project_sample/moc_destination")

# インストール先ディレクトリの定義
set(INCLUDE_INSTALL_DIR ${MY_INSTALL_PREFIX}/include/${PROJECT_NAME})
set(LIB_INSTALL_DIR ${MY_INSTALL_PREFIX}/lib/${PROJECT_NAME})
set(CMAKE_INSTALL_DIR ${MY_INSTALL_PREFIX}/lib/cmake/${PROJECT_NAME})

# Config.cmake ファイルの生成
configure_file(
  "${CMAKE_SOURCE_DIR}/Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  @ONLY
)

# インストール
install(
  TARGETS
    ${LIB_TARGET_NAME}
  EXPORT
    ${CMAKE_PROJECT_NAME}Export  # これがエクスポート グループの名前です
  LIBRARY DESTINATION ${LIB_INSTALL_DIR}
  ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
#   PUBLIC_HEADER DESTINATION ${INCLUDE_INSTALL_DIR} ##( PLAN A )##
#   RUNTIME DESTINATION bin
#   INCLUDES DESTINATION ${INCLUDE_INSTALL_DIR}
)

# Install header files ##( PLAN B )##
install(
  FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/${DIR_NAME}.hpp
  DESTINATION
    ${INCLUDE_INSTALL_DIR}
)

# Config.cmake ファイルのインストール
install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  DESTINATION
    ${CMAKE_INSTALL_DIR}
)

# # エクスポート グループの作成
# install(
#   EXPORT
#     ${CMAKE_PROJECT_NAME}Export  # エクスポート グループの名前を指定します
#   FILE
#     ${PROJECT_NAME}Targets.cmake  # ターゲット ファイルの名前を指定します
#   DESTINATION
#     ${LIB_INSTALL_DIR}/cmake/${CMAKE_PROJECT_NAME}
# )

# # エクスポート グループの作成
# install(
#   EXPORT
#     ${CMAKE_PROJECT_NAME}Export  # エクスポート グループの名前を指定します
#   FILE
#     ${PROJECT_NAME}Targets.cmake  # ターゲット ファイルの名前を指定します
#   DESTINATION
#     ${CMAKE_INSTALL_DIR}
# )