// kkd auto: cmake -S . -B build
// kkd auto: cmake --build build
// feature2.cpp
// rm -r .\build

#include "feature2.hpp"
#include <feature1.hpp>
#include <iostream>

void feature2(){
    std::cout << "This is feature2(): and calls feature1() ==> ";
    feature1();
}