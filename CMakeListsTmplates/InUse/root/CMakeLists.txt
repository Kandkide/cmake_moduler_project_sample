# featureディレクトリ内のCMakeLists.txt
cmake_minimum_required(VERSION 3.27)

# ディレクトリ名を取得
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)


### プロジェクト全体に関わる変数の設定 ###

# アプリケーション実行ファイルのインストール先(APP_INSTALL_DIR)を設定
# ここではソースディレクトリの親ディレクトリのbinに設定している
set(APP_INSTALL_DIR ${CMAKE_SOURCE_DIR}/../bin CACHE PATH "Application installation directory")
# CMakeコマンドラインで -DAPP_INSTALL_DIR=...として値を指定できる

# ビルドオプションの追加(featuresでのmain programのビルドを行うかどうか)
set(BUILD_FEATURES_MAIN_PROGRAM ON)

# バージョン番号
set(MY_PROJECT_VERSION 1.2.3)

# プロジェクト名とバージョンを指定
project(${DIR_NAME}_project_root VERSION ${MY_PROJECT_VERSION} LANGUAGES CXX)

# 特定のサブディレクトリの名前をリストにする
set(EXCLUDE_DIRS "groups" "build")

# ディレクトリ内のすべてのサブディレクトリを検索して追加
file(GLOB SUBDIR_LIST RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)

foreach(SUBDIR IN LISTS SUBDIR_LIST)
    # サブディレクトリが除外リストに含まれていない場合のみ処理を行う
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR} AND NOT "${SUBDIR}" IN_LIST EXCLUDE_DIRS)
        add_subdirectory(${SUBDIR})
    endif()
endforeach()


