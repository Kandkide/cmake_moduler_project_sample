# cmake_moduler_project_sample: project_template
A set of simple CMakeLists.txt templates for hierarchical projects.  
Copy project_template directory and customize it for your use.  
* We use the word **"component"** interchangeably with **"library"** in the following description.  

# Usage in brief
1. Move to "project_template/" directory  
   
2. Build:  
**cmake -S . -B build**   
**cmake --build build**  
  
3. Install libraries:  
**cmake --install .\build\components**\   
  
4. Install executables:  
**cmake --install .\build\applications**\  
  
5. Install header-only:  
**cmake --install .\build\header_only**\  
  
## Note
* Default install destination is **user home directory**  
* (files are installed to its subdirectories, **lib/, include/, lib/cmake/,** and **program/bin/**, depending on file type.)  
* As for header-only, one more subdirectory is made (using source directory name)  


## "project_template" Directory structure

project_template/
├── applications/
│   ├── sample_application/  ***1**     
│   └── ...
├── components/
│   ├── aggregate/
│   ├── sample_component/  ***2**   
│   └── ...
├── header_only/
│   ├── previous_works/  ***3**    
│   └── ...
└── ...
  
***1** copy and modify to make **executables**  
***2** copy and modify to make **libraries**  
***3** copy and modify to make **header-only** headers   
* Only relevant parts are shown.  
* CMakeLists.txt are located in all directories.  


# Customize install destination
(In CMakeLists.txt in project_template directory)  
Default settings for components, executables, and header-only are defined as follows.  
  
**set(CMAKE_INSTALL_PREFIX "${USER_HOME}")**   
  
**set(MY_EXE_EXPORT_DIR ${CMAKE_INSTALL_PREFIX}/program/bin)**  
  
**set(MY_HEADER_ONLY_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})**  
  
* Set the above three variables according to your project.  


# To create libraries.  
1. Copy, rename, and modify **"sample_component" subdirectory** for creating your library  
2. Rename the .cpp and .hpp files to match the new directory name.  


# To create libraries.  
1. Copy, rename, and modify **"sample_application" subdirectory** for creating executables 
2. Use library (component) name without package name for linking and including libraries. 


# For convenience: components/aggregate.hpp
1. You can create multiple components (libraries) in a project   
2. Include these created library headers in **aggregate/aggregate.hpp**  
3. To link to "aggregate" is to link all those libraries.
4. Usage in relevant CMakeLists.txt:   
         **find_package(project_template REQUIRED)**   
         **target_link_libraries(some_target PRIVATE project_template::aggregate)**   
5. Usage in relevant source file:   
       **#include <project_template/aggregate.hpp>** 

* see "sample_cliant_to_project_template" directory as an example

## Note to above: in case of inside the same project  
6. No need of find_package(project_template REQUIRED) and project name, i.e.,  
       **target_link_libraries(some_target PRIVATE aggregate)**

7. No need of project name, i.e., 
       **#include <aggregate.hpp>**  

# Locate header-only libraries (optional).  
1. Copy and/or rename **"previous_works"** subdirectory for adding header-only libraries.  
2. Multiple header files can be put in a single directory.  
3. The name of this directory is used as the name of installing subdirectory.   

* I say this is optional, since header-only libraries are easy to handle even if they are outside the project.  
* Still, there are two merits of locating header-only libraries inside the project:  
* (1) enables to install header-only libraries as a set.  
* (2) using them inside the project without installing them.  

# Other convenient commands
1. install a single application:   
**cmake --install .\build\applications\sample_application**\  

2. run application:   
**cmake --build build --target run_sample_application**  

(as of 2024-03-20 16:11:10)