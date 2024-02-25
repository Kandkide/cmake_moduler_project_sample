# featureディレクトリ内のCMakeLists.txt
cmake_minimum_required(VERSION 3.27)

# ディレクトリ名を取得
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# プロジェクト名とバージョンを指定
project(${DIR_NAME}_project VERSION 1.0)

# 特定のサブディレクトリの名前をリストにする
set(EXCLUDE_DIRS "build")

# ディレクトリ内のすべてのサブディレクトリを検索して追加
file(GLOB SUBDIR_LIST RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)

foreach(SUBDIR IN LISTS SUBDIR_LIST)
    # サブディレクトリが除外リストに含まれていない場合のみ処理を行う
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR} AND NOT "${SUBDIR}" IN_LIST EXCLUDE_DIRS)
        add_subdirectory(${SUBDIR})
    endif()
endforeach()
