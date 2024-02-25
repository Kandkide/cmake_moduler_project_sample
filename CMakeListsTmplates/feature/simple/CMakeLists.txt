# featureディレクトリ内のCMakeLists.txt
cmake_minimum_required(VERSION 3.27)

# ディレクトリ名を取得
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# プロジェクト名とバージョンを指定
project(${DIR_NAME}_project VERSION 1.0)

# ライブラリのソースファイルを指定
set(LIB_SOURCES ${DIR_NAME}.cpp ${DIR_NAME}.hpp)

# ライブラリをビルド
add_library(${DIR_NAME} ${LIB_SOURCES}) # library name => lib${DIR_NAME}

# インクルードディレクトリを指定
target_include_directories(${DIR_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) # library name => lib${DIR_NAME}

# メインプログラムのソースファイルを指定
file(GLOB MAIN_SOURCES main_${DIR_NAME}.cpp)

# メインプログラムのソースファイルが存在する場合にのみビルド
if(MAIN_SOURCES)
    add_executable(${DIR_NAME}_main ${MAIN_SOURCES})
    # ライブラリをリンク
    target_link_libraries(${DIR_NAME}_main PRIVATE ${DIR_NAME}) # library name => lib${DIR_NAME}

    # メインプログラムがビルドされた後に実行されるコマンドを追加
    add_custom_command(TARGET ${DIR_NAME}_main
                       POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E echo "Running ${DIR_NAME}_main..."
                       COMMAND $<TARGET_FILE:${DIR_NAME}_main>)
else()
    message(STATUS "main_${DIR_NAME}.cpp not found. Skipping executable build.")
endif()

