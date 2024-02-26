cmake_minimum_required(VERSION 3.27)

get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# プロジェクト名を指定（バージョン不要：ルートで設定済み）
project(${DIR_NAME}_project_features)

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
