#include "cmakelists_copy_functions.hpp"
#include <filesystem>
#include <iostream>
#include <kkd/process_option_simply.hpp>

/**
 * @brief Entry point of the program for copying CMakeLists.txt files.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Exit code.
 */
int main(int argc, char *argv[]) {

    if (!kkd::process_help(argc, argv, "")) {
        const char* filename = "cmakelists_check.exe";

        if (std::filesystem::exists(filename)) {
            std::cout << "Pre-processing: executing " << filename << " ...\n";
            std::system(filename);
        } 
    }

    return cmakelists_copy_main(argc, argv);
}
