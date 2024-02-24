
# ディレクトリ内のすべてのサブディレクトリを検索して追加
file(GLOB SUBDIR_LIST RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)

foreach(SUBDIR IN LISTS SUBDIR_LIST)
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR})
        add_subdirectory(${SUBDIR})
        # featureのターゲットがfeaturesディレクトリのターゲットに依存することを明示的に指定
        add_dependencies(features_target ${SUBDIR}_target) # HARD-CORDED: 特定の名前(features)に依存
    endif()
endforeach()
