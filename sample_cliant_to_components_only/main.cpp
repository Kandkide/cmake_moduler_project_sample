// // kkd auto: cmake -S . -B build
// kkd auto: cmake --build build
// kkd auto: .\build\sample_set.exe

// // kkd auto: cmake --install build
// // kkd auto: cmake --build build --target uninstall

#include <iostream>
#include <components_only/sample_component.hpp>
#include <previous_works/previous_work.hpp>

int main(){
    std::cout << "Hello from use_case_of_components_only\nrun sample_component():\n";
    sample_component();
    previous_work();
}