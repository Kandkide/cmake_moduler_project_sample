# featureディレクトリ内のCMakeLists.txt
cmake_minimum_required(VERSION 3.27)

# ディレクトリ名を取得
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# プロジェクト名とバージョンを指定
project(${DIR_NAME}_project VERSION 1.0)

# C++23を使用するための設定
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# コンパイラオプションの設定
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")

# ライブラリのソースファイルを指定
set(LIB_SOURCES ${DIR_NAME}.cpp ${DIR_NAME}.hpp)

# ライブラリをビルド
add_library(${DIR_NAME}_lib ${LIB_SOURCES}) # library name => lib${DIR_NAME}

# # Qt 6を使用する場合
# find_package(Qt6 COMPONENTS Core REQUIRED)
# target_link_libraries(${DIR_NAME} PRIVATE Qt6::Core)
# PUBLICを使うと、そのターゲットが依存する他のターゲットも同様にリンクされる
# INTERFACEを使用すると、そのターゲットを利用する外部のプロジェクトに対してリンク

# # pybind11を使用する場合
# find_package(pybind11 REQUIRED)
# target_link_libraries(${DIR_NAME} PRIVATE pybind11::pybind11)

# feature1に依存する場合（同一プロジェクト内での依存関係）
target_link_libraries(${DIR_NAME}_lib PRIVATE feature1_lib) # 最後のargのみ書き換える
# シンプルで良いが。難は、ルートでビルドする必要があること。current dirでのビルドは通らない。

# インクルードディレクトリを指定
target_include_directories(${DIR_NAME}_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) # library name => lib${DIR_NAME}

# メインプログラムのソースファイルを指定
file(GLOB MAIN_SOURCES main_${DIR_NAME}.cpp)

# メインプログラムのソースファイルが存在する場合にのみビルド
if(MAIN_SOURCES)
    add_executable(${DIR_NAME}_main ${MAIN_SOURCES})
    # ライブラリをリンク
    target_link_libraries(${DIR_NAME}_main PRIVATE ${DIR_NAME}_lib) # library name => lib${DIR_NAME}

    # メインプログラムがビルドされた後に実行されるコマンドを追加
    add_custom_command(TARGET ${DIR_NAME}_main
                       POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E echo "Running ${DIR_NAME}_main..."
                       COMMAND $<TARGET_FILE:${DIR_NAME}_main>)
else()
    message(STATUS "main_${DIR_NAME}.cpp not found. Skipping executable build.")
endif()
