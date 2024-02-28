
# 特定のサブディレクトリの名前をリストにする
set(EXCLUDE_DIRS "excluded_feature1" "excluded_feature2")

# featuresディレクトリ内のすべてのサブディレクトリを検索して追加
file(GLOB SUBDIR_LIST RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)

foreach(SUBDIR IN LISTS SUBDIR_LIST)
    # サブディレクトリが除外リストに含まれていない場合のみ処理を行う
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR} AND NOT "${SUBDIR}" IN_LIST EXCLUDE_DIRS)
        add_subdirectory(${SUBDIR})
        # featureのターゲットがfeaturesディレクトリのターゲットに依存することを明示的に指定
        add_dependencies(features_target ${SUBDIR}_target)
    endif()
endforeach()
