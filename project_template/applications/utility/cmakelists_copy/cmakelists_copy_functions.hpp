/**
 * @file cmakelists_copy_functions.hpp
 * @brief Declaration of functions for copying and handling CMakeLists.txt files.
 * @version 0.1
 * @date 2024-03-14
 * 
 * This header file contains declarations for functions used to copy CMakeLists.txt files,
 * search for files and directories, and perform operations such as renaming based on version changes.
 * 
 * Functions in this file:
 * - renameIfCommentedVersionChanged
 * - searchFilesAbsolute
 * - searchDirectoriesAbsolute
 * - helper_find_the_same_kind
 * - cmakelists_copy_main
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef CMAKELISTS_COPY_FUNCTIONS_HPP
#define CMAKELISTS_COPY_FUNCTIONS_HPP

#include <filesystem>
#include <string>

/**
 * @brief Rename the file if the commented version in the filename has changed.
 * 
 * This function compares the version extracted from the filename with the provided version string.
 * If they match, it renames the file to reflect the new version.
 * 
 * @param targetPath The path to the file to check and possibly rename.
 * @param toCompare The version string to compare against the version in the filename.
 * @return true If renaming was conducted.
 * @return false If renaming was not conducted.
 */
bool renameIfCommentedVersionChanged(const std::filesystem::path& targetPath, const std::string& toCompare);

/**
 * @brief Searches for files with the specified name in the given directory and its subdirectories, and applies a process function to each found file.
 * 
 * @param directory The directory to start the search from.
 * @param targetFileName The name of the file to search for.
 * @param processFile The function to apply to each found file.
 */
void searchFilesAbsolute(const auto& directory, const std::string& targetFileName, const auto& processFile);

/**
 * @brief Searches for directories with the specified name in the given directory and its subdirectories, and applies a process function to each found directory.
 * 
 * @param directory The directory to start the search from.
 * @param targetDirectoryName The name of the directory to search for.
 * @param processDirectory The function to apply to each found directory.
 */
void searchDirectoriesAbsolute(const auto& directory, const std::string& targetDirectoryName, const auto& processDirectory);

/**
 * @brief Finds files of the same kind as the reference file and performs operations such as copying and renaming based on their versions.
 * 
 * @param referenceFilePath The path to the reference file.
 * @param copyToThisPath The path to copy the files of the same kind to.
 */
void helper_find_the_same_kind(const auto& referenceFilePath, const auto& copyToThisPath);

/**
 * @brief Main function for copying CMakeLists.txt files from a template directory and handling file operations.
 * 
 * This function iterates over CMakeLists.txt files in a specified template directory.
 * It copies each file to a target directory and handles file operations such as renaming and copying based on version changes.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Exit code.
 */
int cmakelists_copy_main(int argc, char *argv[]);

#endif // CMAKELISTS_COPY_FUNCTIONS_HPP
