# featureディレクトリ内のCMakeLists.txt
cmake_minimum_required(VERSION 3.27)

# ディレクトリ名を取得
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# プロジェクト名とバージョンを指定
project(${DIR_NAME}_project VERSION 1.0)

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

# feature1に依存する場合
# add_subdirectory(${PROJECT_SOURCE_DIR}/features/group1/feature1)  # PROJECT_SOURCE_DIRを使用してプロジェクトのルートディレクトリを基準とした相対パスを指定
# target_link_libraries(${DIR_NAME} PRIVATE feature1_lib)
# PROJECT_SOURCE_DIRはadd_subdirectoryの関係をたどった最上位のディレクトリを指す

# feature1に依存する場合（別解）NG?
# find_package(feature1_project REQUIRED)  # feature1_projectを探し、その情報を取得
target_link_libraries(${DIR_NAME}_lib PRIVATE feature1_lib)
# feature1でproject(feature1_project)と命名しており、add_library(feature1 ...)としている場合の例

# # feature1に依存する場合
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../feature1 ${CMAKE_CURRENT_SOURCE_DIR}/../feature1/build)  # feature1のCMakeLists.txtを含むディレクトリを指定
# target_link_libraries(${DIR_NAME}_lib PRIVATE feature1_lib)

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
