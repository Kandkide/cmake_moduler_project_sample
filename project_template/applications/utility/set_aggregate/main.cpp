#include <iostream>
#include <filesystem>
#include <fstream>
#include <kkd/process_option_simply.hpp>
// #include <kkdfirst/process_option_simply.hpp>

int main(int argc, char *argv[]) {
    const char* helpText = R"(- Description of set_aggregate command.
    After change of sub-directories of "components", execute
    Command: .\set_aggregate.exe
    NOTE: We assume flat structure of components directory.
    )";
    if (kkd::process_help(argc, argv, helpText)) return 0;

    auto currentPath = std::filesystem::current_path();
    auto componentsRootPath = currentPath/"components";
    auto aggregateHppFile = componentsRootPath/"aggregate/aggregate.hpp";

    if (!std::filesystem::exists(aggregateHppFile)){
        std::cout << aggregateHppFile.string() << " dose not exist.\n";
        return 1;
    }

    std::ofstream outputFile(aggregateHppFile.string());

    if (outputFile.is_open()) {
        outputFile << "#pragma once\n\n";

        for (const auto& entry : std::filesystem::directory_iterator(componentsRootPath)) {
            if (std::filesystem::is_directory(entry.status()) && entry.path().filename().string() != "aggregate") {
                outputFile << "#include \"" << entry.path().filename().string() << ".hpp\"\n";
            }
        }

    } else {
        std::cerr << "fail to open file: " << aggregateHppFile.string() << "\n";
        return 1;
    }

    return 0;
}
