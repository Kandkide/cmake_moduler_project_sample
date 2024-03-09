// kkd auto: cmake -S . -B build --fresh
// kkd auto: cmake --build build
// kkd auto: cmake --install build
// // kkd auto: cmake --build build --target uninstall

#include <sample_components/component1.hpp>
#include <sample_components/component2.hpp>
#include <iostream>

int main(){
    std::cout << "Include <sample_components/component1.hpp> then calls component1() ==> ";
    component1();
    std::cout << "Include <sample_components/component2.hpp> then calls component2() ==> ";
    component2();
}