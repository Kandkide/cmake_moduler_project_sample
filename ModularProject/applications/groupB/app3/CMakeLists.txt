# featureディレクトリ内のCMakeLists.txt
cmake_minimum_required(VERSION 3.27)

# ディレクトリ名を取得
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# プロジェクト名を指定（バージョン不要：ルートで設定済み）
project(${DIR_NAME}_project)

# C++23を使用するための設定
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# コンパイラオプションの設定
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")

# メインプログラムのソースファイルを指定
file(GLOB MAIN_SOURCES main_${DIR_NAME}.cpp)

# 実行ファイル名を設定（ここではディレクトリ名）
set(EXE_TARGET_NAME ${DIR_NAME})

add_executable(${EXE_TARGET_NAME} ${MAIN_SOURCES})

# # Qt 6を使用する場合
# find_package(Qt6 COMPONENTS Widgets REQUIRED)
# target_link_libraries(${EXE_TARGET_NAME} PRIVATE Qt6::Widgets)
# PUBLICを使うと、そのターゲットが依存する他のターゲットも同様にリンクされる
# INTERFACEを使用すると、そのターゲットを利用する外部のプロジェクトに対してリンク

# # pybind11を使用する場合
# find_package(pybind11 REQUIRED)
# target_link_libraries(${EXE_TARGET_NAME} PRIVATE pybind11::pybind11)

# feature1に依存する場合（同一プロジェクト内での依存関係）
# target_link_libraries(${EXE_TARGET_NAME} PRIVATE feature3_lib)
target_link_libraries(${EXE_TARGET_NAME} PRIVATE feature2_lib)

# メインプログラムがビルドされた後に実行されるコマンドを追加
add_custom_command(TARGET ${EXE_TARGET_NAME}
                    POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E echo "Running ${EXE_TARGET_NAME}..."
                    COMMAND $<TARGET_FILE:${EXE_TARGET_NAME}>)

# インストール先の変数を参照
# message(STATUS "Installation directory: ${APP_INSTALL_DIR}")
# インストール先のディレクトリを指定（ソースディレクトリの親ディレクトリのbinに）
install(TARGETS ${EXE_TARGET_NAME} DESTINATION ${APP_INSTALL_DIR})