// // kkd auto: cmake -S . -B build
// kkd auto: cmake --build build
// kkd auto: .\build\sample_set.exe

// // kkd auto: cmake --install build
// // kkd auto: cmake --build build --target uninstall

#include <iostream>
#include <project_template/aggregate.hpp>

int main(){
    std::cout << "Hello from use_case_of_project_template\nrun sample_component() and sample_header_only<999>():\n";
    sample_component();
    sample_header_only<999>();
}