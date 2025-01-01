# header_only.tests.leaf-0.0.1


# 同じディレクトリ内の test_*.cpp ファイルをすべて検索
file(GLOB TEST_SOURCES "test_*.cpp")

# 検索結果を出力（デバッグ用）
message(STATUS "Found test files: ${TEST_SOURCES}")

# 共通でリンクするライブラリを設定
set(COMMON_LIBRARIES
    gtest
    gtest_main
    # pthread
)

# 各テストソースファイルに対してテストターゲットを作成
foreach(TEST_SOURCE ${TEST_SOURCES})
    # テストターゲット名を生成
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE) # ファイル名（拡張子なし）
    set(TEST_TARGET_NAME "test_${TEST_NAME}")

    # テスト実行ファイルの追加
    add_executable(${TEST_TARGET_NAME} ${TEST_SOURCE})

    # Google Testをリンク
    target_link_libraries(${TEST_TARGET_NAME} PRIVATE ${COMMON_LIBRARIES})

    # Link dependencies
    target_include_directories(${TEST_TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/header_only)

    # テストの登録
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_TARGET_NAME})
endforeach()

# ctest --test-dir build/