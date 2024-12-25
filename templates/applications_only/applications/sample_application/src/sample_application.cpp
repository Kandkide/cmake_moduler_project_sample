#include "sample_application.hpp"
#include <iostream>
#include <components_only/sample_component.hpp>

void sample_app(){
    std::cout << "Hello from applications_only!\n";
    sample_component();
}