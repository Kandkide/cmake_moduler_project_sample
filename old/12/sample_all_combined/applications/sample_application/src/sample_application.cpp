#include "sample_application.hpp"
#include <iostream>
#include <sample_component.hpp>
// #include <components_only/sample_component.hpp>

void sample_app(){
    std::cout << "Hello from sample_application!\n";
    sample_component();
}