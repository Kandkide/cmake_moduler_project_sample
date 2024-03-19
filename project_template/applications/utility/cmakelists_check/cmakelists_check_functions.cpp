#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <kkd/process_option_simply.hpp>
#include "cmakelists_check_functions.hpp"

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
bool renameIfCommentedVersionChanged(const auto& targetPath, const std::string& toCompare){
    namespace fs = std::filesystem;
    auto target = targetPath.stem().string();

    std::cout << "checking: " << targetPath.string() << " ... ";

    std::istringstream targetSS(target);
    std::istringstream toCompareSS(toCompare);
    std::string targetToken;
    std::string toCompareToken;
    std::getline(targetSS, targetToken, '-');
    std::getline(toCompareSS, toCompareToken, '-');

    // if target and toCompare are NOT in the same kind (do nothing and return false)
    if (targetToken != toCompareToken) return false;

    std::getline(targetSS, targetToken, '-');
    std::getline(toCompareSS, toCompareToken, '-');

    // if target and toCompare are in the same version (do nothing and return false)
    if (targetToken == toCompareToken) return false;

    auto newFilePath =  targetPath.parent_path()/(toCompare + targetPath.extension().string());

    // if newFilePath exists (do nothing and return false)
    if (fs::exists(newFilePath)) return false;
    
    try {
        fs::rename(targetPath, newFilePath);
        std::cout << "\nrename to " << newFilePath.string() << "\n";
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << e.what() << "\n";
        return false;
    }

    return true;
}

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
int cmakelists_check_main(int argc, char *argv[]) {

    namespace fs = std::filesystem;
    using namespace std::string_literals;

    const char* helpText = R"(- Description of cmakelists_check command.
    Check CMakeLists.txt in "cmakelists_copy_data" directory.
    If commented version changes, rename file to that version, execute
    Command: .\cmakelists_check.exe
    )";
    // const char* templateDirectoryName = "project_template";
    const std::string dataDirectoryName = "cmakelists_copy_data";

    if (kkd::process_help(argc, argv, helpText)) return 0;

    if (!fs::exists(dataDirectoryName)) return 0;

    auto currentPath = std::filesystem::current_path();

    for (const auto& entry : fs::directory_iterator(dataDirectoryName)) {
        if (entry.path().extension().string() != ".cmake") continue;

        std::ifstream file(entry.path());
        if (file.is_open()) {
            std::string line;
            file >> line;
            file >> line;
            file.close(); // need to close here, since rename may be conducted below.
            if (!renameIfCommentedVersionChanged(entry.path(), line)) {
                std::cout << "leave it as it is.\n";
            } else {
                // no message is needed for now. 
            }
        } else {
            std::cerr << "Unable to open file: " << entry.path().string() << std::endl;
        }
    }
    return 0;
}
