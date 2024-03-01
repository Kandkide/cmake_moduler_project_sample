cmake_minimum_required(VERSION 3.27)

project(init_directories)

set(TMPLATES_ROOT_DIR ${CMAKE_SOURCE_DIR}/templates)
message("TMPLATES_ROOT_DIR: ${TMPLATES_ROOT_DIR}")

set(TMPLATES_FEATURES_DIR ${TMPLATES_ROOT_DIR}/features)
message("TMPLATES_FEATURES_DIR: ${TMPLATES_FEATURES_DIR}")

set(TARGET_FEATURES_DIR ${CMAKE_SOURCE_DIR}/features)
message("TARGET_FEATURES_DIR: ${TARGET_FEATURES_DIR}")

# ディレクトリ内の全てのファイルを取得（注意: キャッシュが更新されない可能性がある）
file(GLOB files_in_directory ${TMPLATES_FEATURES_DIR}/root/*)
foreach(each_file ${files_in_directory})
    get_filename_component(filename ${each_file} NAME)
    configure_file(${each_file} ${TARGET_FEATURES_DIR}/${filename} COPYONLY)
    # message("${each_file}: ${filename}")
endforeach()

# 取得したファイル一覧を表示
# message("Files in directory: ${files_in_directory}")


# configure_file(${TMPLATES_ROOT_DIR}/FeaturesRootCMakeLists.txt ${TARGET_ROOT_DIR}/CMakeLists.txt COPYONLY)
# configure_file(${TMPLATES_ROOT_DIR}/FeaturesRootConfig.cmake.in ${TARGET_ROOT_DIR}/Config.cmake.in COPYONLY)





# # Get the directory name
# get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# # Exclude specific subdirectories
# set(EXCLUDE_DIRS "build") ## DO CUSTOMIZE ##

# # Search and add all subdirectories within the directory
# file(GLOB SUBDIR_LIST RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)

# foreach(SUBDIR IN LISTS SUBDIR_LIST)
#     # Process the subdirectory only if it is not included in the exclude list
#     if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR} AND NOT "${SUBDIR}" IN_LIST EXCLUDE_DIRS)
#         add_subdirectory(${SUBDIR})
#     endif()
# endforeach()
