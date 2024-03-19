/**
 * @file cmakelists_check_functions.hpp
 * @brief Declaration of functions for checking and renaming CMakeLists.txt files based on version changes.
 * @author [Your Name]
 * @version 0.1
 * @date 2024-03-14
 * 
 * This header file contains declarations for functions used to check CMakeLists.txt files
 * for changes in the commented version and rename them accordingly.
 * 
 * Functions in this file:
 * - renameIfCommentedVersionChanged
 * - cmakelists_check_main
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef CMAKELISTS_CHECK_FUNCTIONS_HPP
#define CMAKELISTS_CHECK_FUNCTIONS_HPP

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
bool renameIfCommentedVersionChanged(const auto& targetPath, const std::string& toCompare);

/**
 * @brief Main function for checking and renaming CMakeLists.txt files based on version changes.
 * 
 * This function iterates over CMakeLists.txt files in a specified directory.
 * It reads the first line of each file and compares it with the version extracted from the filename.
 * If the versions do not match, it renames the file to reflect the new version.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Exit code.
 */
int cmakelists_check_main(int argc, char *argv[]);

#endif // CMAKELISTS_CHECK_FUNCTIONS_HPP
