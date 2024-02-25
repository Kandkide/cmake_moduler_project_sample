# Usage:
# rewrite #### HARD CODED #### part namually
# cmake -S . -B build
# cmake --build build
# cmake --install build
# Need: main.cpp in the current folder
# Normally with: ${PROJECT_NAME}.cpp (contain functions, classes, etc. for use in main.cpp) and ${PROJECT_NAME}.hpp
# Optionally: other .cpps => static library is made, named to ${PROJECT_NAME}. available everywhere after intall.
# Optionally: some.hpp => installed to ${CMAKE_INSTALL_PREFIX}/include/${MY_SUBDIR_IDENTIFIER}
# Optionally: ${PROJECT_NAME}.cpp and ${PROJECT_NAME}_test.cpp => do google test if BUILD_TESTS option is set or,
    # by command: cmake -S . -B build -DBUILD_TESTS=ON

cmake_minimum_required(VERSION 3.26)
# cmake_minimum_required(VERSION 3.13)

# カレントディレクトリの名前を取得=>プロジェクト名、実行可能ファイル名などに使用
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

project(${PROJECT_NAME} CXX)

# ------------------ Set Related Variables ------------------------ #

# ユーザーのホームディレクトリを取得するための環境変数を使う
if (UNIX)
    execute_process(COMMAND sh -c "echo $HOME" OUTPUT_VARIABLE USER_HOME)
elseif (WIN32)
    execute_process(COMMAND cmd.exe /c "echo %USERPROFILE%" OUTPUT_VARIABLE USER_HOME)
    # バックスラッシュをスラッシュに置き換える
    string(REPLACE "\\" "/" USER_HOME ${USER_HOME})
endif ()

string(STRIP ${USER_HOME} USER_HOME) # 取得したディレクトリから不要な空白を削除する

# programディレクトリ（自分ルール）
set(USER_HOME_PROGRAM ${USER_HOME}/program) #### HARD CODED ####

# 自作ファイル収納用のサブディレクトリ名として使う
set(MY_SUBDIR_IDENTIFIER kkdfirst) #### HARD CODED ####

# インストール先の絶対パスを指定
set(CMAKE_INSTALL_PREFIX C:/msys64/ucrt64) #### HARD CODED ####
# set(CMAKE_INSTALL_PREFIX ${USER_HOME}/program)

# リンクが必要なライブラリのリスト (if any)
# set(MY_LIBS_TO_LINK rename_to_dir) #### HARD CODED ####
# set(MY_LIBS_TO_LINK rename_to_dir another_library third_library) #### HARD CODED ####


# オプション: テストを有効化するかどうかを指定
option(BUILD_TESTS "Build tests" OFF)
# # コマンドラインからテストを有効にする場合
# cmake -S . -B build -DBUILD_TESTS=ON

# テスト用のソースファイルを定義
set(TEST_SOURCES
    ${PROJECT_NAME}.cpp
    ${PROJECT_NAME}_test.cpp
    # 追加のテストソースファイルを必要に応じてここに追加
    #### HARD CODED #### (if any)
)

# 除外するファイル名のリストを定義
set(EXCLUDE_FILES "exclude_file.cpp" "main.cpp") #### HARD CODED ####

# ------------------ Main Section ------------------------ #

# カレントディレクトリ内の.cppファイルを取得
file(GLOB SOURCES *.cpp)
# file(GLOB_RECURSE SOURCES *.cpp)  # サブディレクトリも含めて.cppファイルを再帰的に取得

# 除外するファイルをリストから除外する
foreach(EXCLUDE_FILE ${EXCLUDE_FILES})
    list(FILTER SOURCES EXCLUDE REGEX ${EXCLUDE_FILE})
endforeach()

# 除外するファイルを除外パターンで指定
list(FILTER SOURCES EXCLUDE REGEX "_test\\.cpp$") #### HARD CODED ####
list(FILTER SOURCES EXCLUDE REGEX "_alt\\.cpp$") #### HARD CODED ####

# 静的ライブラリ名を定義 & 静的ライブラリを作成
if(SOURCES)
    set(MY_STATIC_LIB ${PROJECT_NAME}_static)
    set(MY_STATIC_LIB_OPTION -l${MY_STATIC_LIB}) # used in template.pc.in
    
    add_library(${MY_STATIC_LIB} STATIC ${SOURCES})
endif()

# 一般的なコンパイラオプションを追加（静的ライブラリと実行可能ファイルの両方に適用）
add_compile_options(-Wall -O3 -std=c++23)
# 例: -Wallは警告を有効にし、-O2は最適化レベルを設定 #### HARD CODED ####

# 実行可能ファイルを作成
add_executable(${PROJECT_NAME} main.cpp)

# 静的ライブラリをリンク
if(MY_STATIC_LIB)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${MY_STATIC_LIB})
endif()

# # GTK3.0のパッケージを検索
# find_package(GTK3 REQUIRED)
# # ライブラリをリンク
# target_link_libraries(${PROJECT_NAME} PRIVATE GTK3::GTK3)
# libcomdlg32をリンク
# target_link_libraries(${PROJECT_NAME} PRIVATE comdlg32)

# その他に必要な指定されたライブラリをリンク
find_package(PkgConfig REQUIRED)
foreach(LIB ${MY_LIBS_TO_LINK})
    pkg_check_modules(MY_PKG_${LIB} REQUIRED ${MY_SUBDIR_IDENTIFIER}/${LIB})
    message("MY_PKG_${LIB}_INCLUDE_DIRS: ${MY_PKG_${LIB}_INCLUDE_DIRS}")
    message("MY_PKG_${LIB}_LDFLAGS: ${MY_PKG_${LIB}_LDFLAGS}")
    # ライブラリをリンク
    if (MY_PKG_${LIB}_FOUND)
        include_directories(${MY_PKG_${LIB}_INCLUDE_DIRS})
        target_link_libraries(${PROJECT_NAME} ${MY_PKG_${LIB}_LDFLAGS})
    else()
        message(FATAL_ERROR "Error: ${LIB} package not found.")
    endif()
endforeach()


# 実行可能ファイルをビルド後に実行する
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ./${PROJECT_NAME}  # 実行可能ファイルの名前を指定
    COMMAND ${CMAKE_COMMAND} -E echo "${PROJECT_NAME}.exe executing..."
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}  # 実行するディレクトリを指定
)

# execute_process(COMMAND ./${PROJECT_NAME} WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

# $ cmake -S . -B build
# $ cmake --build build

# ------------------ Install Related Section ------------------------ #
# cmake --install build

# ヘッダーファイルをインストール
file(GLOB_RECURSE HEADER_FILES *.hpp)  # ヘッダーファイルのリストを取得
# 除外するファイルを除外パターンで指定
list(FILTER HEADER_FILES EXCLUDE REGEX "_old\\.hpp$") #### HARD CODED ####

if(HEADER_FILES)
    install(
        FILES ${HEADER_FILES}
        DESTINATION include/${MY_SUBDIR_IDENTIFIER}
    )
endif()

if(MY_STATIC_LIB)
    # ライブラリをインストール
    install(
        TARGETS ${MY_STATIC_LIB}
        DESTINATION lib/${MY_SUBDIR_IDENTIFIER}
    )


    # pkg-configファイルの生成 # NOTE: home dir is hard coded in resulting .pc file
    configure_file(
        ${USER_HOME_PROGRAM}/cmakelists/template.pc.in
        ${CMAKE_BINARY_DIR}/pkg-config/${PROJECT_NAME}.pc
        @ONLY
    )

    # インストールコマンドを使って.pcファイルをインストールする場合
    install(
        FILES ${CMAKE_BINARY_DIR}/pkg-config/${PROJECT_NAME}.pc
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig/${MY_SUBDIR_IDENTIFIER}
        # DESTINATION C:/msys64/ucrt64/lib/pkgconfig/kkd
    )
endif()

## CMAKE_BINARY_DIR と CMAKE_CURRENT_BINARY_DIR の使い分けについては不勉強

# # アンインストールターゲットの作成
# configure_file(
#     "${USER_HOME_PROGRAM}/cmakelists/cmake_uninstall.cmake.in"
#     "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
#     IMMEDIATE @ONLY
# )

# add_custom_target(uninstall
#     COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
# )

# ------------------ Test Related Section ------------------------ #


if(BUILD_TESTS)

    # バイナリディレクトリを指定する
    set(GTEST_BINARY_DIR ${CMAKE_BINARY_DIR}/gtest) # 例としてCMAKE_BINARY_DIRにgtestを配置する場合

    # # ソースディレクトリを指定する 
    add_subdirectory(${USER_HOME_PROGRAM}/test/google_test ${GTEST_BINARY_DIR}) #### HARD CODED ####
    # add_subdirectory(path/to/your/google_test_directory ${GTEST_BINARY_DIR})

    # あなたのプロジェクトの設定など...

    # テスト用の実行可能ファイル名を定義
    set(TEST_EXECUTABLE ${PROJECT_NAME}_test)

    # テスト名を定義
    set(TEST_NAME YourTestName) #### HARD CODED ####

    # あなたのプロジェクトの追加の設定やターゲットなど...

    # テスト用の実行可能ファイルを作成する
    add_executable(${TEST_EXECUTABLE} ${TEST_SOURCES}) # テスト用のソースファイルを追加

    target_link_libraries(${TEST_EXECUTABLE} gtest gtest_main) # Google Testのライブラリをリンク

    # あなたのプロジェクトの追加の設定やターゲットなど...

    # テストの実行
    enable_testing() # テストを有効にする
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_EXECUTABLE})

    # ビルド後にシェルコマンドを実行する
    add_custom_command(TARGET ${TEST_EXECUTABLE} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Tests are built. Executing..."
        COMMAND ${CMAKE_COMMAND} -E echo "Running tests..."
        COMMAND ${TEST_EXECUTABLE}
    )

    # cmake --build . --target test
else()
    message(STATUS "Tests are not enabled.")
endif()
