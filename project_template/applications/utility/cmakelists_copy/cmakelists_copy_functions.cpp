#include <iostream>
#include <filesystem>
#include <fstream>
#include <functional>
#include <string>
#include <kkd/process_option_simply.hpp>
#include "cmakelists_copy_functions.hpp"

/**
 * @brief Searches for files with the specified name in the given directory and its subdirectories, and applies a process function to each found file.
 * 
 * @param directory The directory to start the search from.
 * @param targetFileName The name of the file to search for.
 * @param processFile The function to apply to each found file.
 */
void searchFilesAbsolute(const auto& directory, const std::string& targetFileName, const auto& processFile) {
    namespace fs = std::filesystem;
    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (fs::is_regular_file(entry) && entry.path().filename() == targetFileName) {
            processFile(entry.path());
        }
    }
}

/**
 * @brief Searches for directories with the specified name in the given directory and its subdirectories, and applies a process function to each found directory.
 * 
 * @param directory The directory to start the search from.
 * @param targetDirectoryName The name of the directory to search for.
 * @param processDirectory The function to apply to each found directory.
 */
void searchDirectoriesAbsolute(const auto& directory, const std::string& targetDirectoryName, const auto& processDirectory) {
    namespace fs = std::filesystem;
    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (fs::is_directory(entry) && entry.path().filename() == targetDirectoryName) {
            processDirectory(entry.path());
        }
    }
}

/**
 * @brief Finds files of the same kind as the reference file and performs operations such as copying and renaming based on their versions.
 * 
 * @memo added after cmakelists_check is created.
 * 
 * @param referenceFilePath The path to the reference file.
 * @param copyToThisPath The path to copy the files of the same kind to.
 */
void helper_find_the_same_kind(const auto& referenceFilePath, const auto& copyToThisPath){
    namespace fs = std::filesystem;
    const auto targetPath = referenceFilePath.parent_path();
    const auto targetName = referenceFilePath.stem().string();
    // std::cout << targetPath << ": " << targetName << "\n";
    // "cmakelists_copy_data": components.leaf-1.2.3.cmake
    auto itFound = targetName.find('-');
    std::string kindPrefixStr;
    std::string versionStr;
    if (itFound != std::string::npos) {
        kindPrefixStr = targetName.substr(0, itFound + 1);
        versionStr = targetName.substr(itFound + 1);
        // std::cout << kindPrefixStr << ": " << versionStr << "\n";
        // // components.leaf-: 1.2.3
        for (const auto& entry : fs::directory_iterator(targetPath)) {
            // note: entry.path() is the copy source path to use later
            std::string counterpartStemName = entry.path().stem().string();
            if (counterpartStemName.find(kindPrefixStr) == 0) {
                auto it = counterpartStemName.find('-');
                std::string counterpartVersion;
                if (it != std::string::npos) {
                    counterpartVersion = counterpartStemName.substr(it + 1);
                    if (versionStr < counterpartVersion) {
                        std::cout << "new version found: " << counterpartStemName << "\n";
                        std::cout << "Copy it back to project_template?: enter 'y' or 'n' \n";
                        // std::cout << "copy? (y or no): " << entry.path().string() << " => " << copyToThisPath.string() << "\n";

                        std::string userInput = "n";
                        std::cin >> userInput;
                        if (userInput == "y") {
                            try {
                                fs::rename(copyToThisPath, copyToThisPath.parent_path() / referenceFilePath.filename());
                                std::cout << "rename older CMakeLists.txt " << "\n";
                            } catch (const std::filesystem::filesystem_error& e) {
                                std::cerr << e.what() << "\n";
                                fs::remove(copyToThisPath);
                                std::cout << "delete older CMakeLists.txt " << "\n";
                            }
                            std::cout << "copying ... " << "\n";
                            std::cout << "copying: " << entry.path().string() << " => " << copyToThisPath.string() << "\n";
                            fs::copy_file(entry.path(), copyToThisPath, fs::copy_options::overwrite_existing);
                        }
                    }
                }
            }
        }
    }
}

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
int cmakelists_copy_main(int argc, char *argv[]) {

    namespace fs = std::filesystem;
    using namespace std::string_literals;

    const char* helpText = R"(- Description of cmakelists_copy command.
    Check CMakeLists.txt in "project_template" and copy them to "cmakelists_copy_data" directory, execute
    Command: .\cmakelists_copy.exe
    While copying, CMakeLists.txt are renamed, using its top comment line, to something like "project.top_1.2.2.cmake"
    Mod .cmake files then copy back operation is to be conducted (asked y or n)
    )";
    // const char* templateDirectoryName = "project_template"; //< VARIANT: for itself (comment-out)
    const std::string dataDirectoryName = "cmakelists_copy_data";

    if (kkd::process_help(argc, argv, helpText)) return 0;

     //< VARIANT: for itself (comment-out followings)
    // auto currentPath = std::filesystem::current_path();

    // /* --- to find project_template directory --- */
    // std::filesystem::path templatePath; // TODO: 今のところ２つ上のディレクトリから検索で見つけているが、もっと確実な方法に変えること
    // // ディレクトリを再帰的に検索し、見つかったディレクトリに対してラムダ関数を適用
    // searchDirectoriesAbsolute(currentPath.parent_path().parent_path(), templateDirectoryName, [&templatePath](const auto& foundDirectory) {
    //     if (templatePath.empty()) templatePath = foundDirectory;
    // });
    // // std::cout << "Found directory: " << templatePath << std::endl;
    // if (templatePath.empty()) {
    //     std::cout << "can not find " << templateDirectoryName << " folder.\n";
    //     return 1;
    // }

    auto templatePath = std::filesystem::current_path(); //< VARIANT: for itself

    /* --- to find path of CMakeLists.txt under the project_template directory --- */
    // std::cout << "\n--- Type_of_CMakeLists.txt [location] ---\n";
    // ファイルを再帰的に検索し、見つかったファイルに対してラムダ関数を適用
    searchFilesAbsolute(templatePath, "CMakeLists.txt", [&templatePath, &dataDirectoryName](const auto& foundPath) {
        std::ifstream file(foundPath);
        if (file.is_open()) {
            std::string line;
            file >> line; // one word
            file >> line; // second word
            // std::cout << line << " [" 
            // << std::filesystem::relative(foundPath, templatePath).parent_path().string() << "]\n";

            file.close(); // this is needed, since the file may become a copy target in helper_find_the_same_kind().

            fs::create_directories(dataDirectoryName);
            if (!line.empty()){
                std::filesystem::path destinationPath{dataDirectoryName + "/" + line + ".cmake"};
                try {
                    if (!fs::exists(destinationPath)){
                        fs::copy_file(foundPath, destinationPath, fs::copy_options::overwrite_existing);
                        std::cout << "copy file: " << destinationPath.string() << std::endl;
                    }

                    // added after cmakelists_check is created
                    helper_find_the_same_kind(destinationPath, foundPath);

                } catch (const fs::filesystem_error& ex) {
                    std::cerr << "fail to copy file: " << ex.what() << std::endl;
                }
            }
        } else {
            std::cerr << "Unable to open file: " << foundPath.string() << std::endl;
        }
    });

    return 0;
}

