# cmake_moduler_project_sample
A set of simple CMakeLists.txt templates for hierarchical projects.

# usage
The names of the directories are used to name the libraries and its components. 
See samples in sample_components and sample_application directories. 

* The files in the cmakelists_templates directory are the same as those used in the example.

# directories
## under the components directory
use for making headers and libraries. 

there are two subdirectories: 
* cmakelists_templates
* sample_components

## under the applications directory
use for making executables (i.e. applications) 

there are two subdirectories: 
* cmakelists_templates
* sample_application

# command lines
## common
cmake -S . -B build
cmake --build build

## install
cmake --install build
(exe file is installed in case of applications) 
(headers, libraries, and config.cmake files in case of components)

## uninstall (applicable only to applications)
cmake --build build --target uninstall

## build partially
cmake --build build --target feature1_lib    

