# cmake_moduler_project_sample
A set of simple CMakeLists.txt templates for hierarchical projects.  
Copy project_template directory and customize it for your use.  
* We use the word "component" interchangeably with "library" in the following description.  

# Demo
1. Move to "project_template/" directory  
2. Build:  
cmake -S . -B build
cmake --build build
3. Install:
cmake --install .\build\components\

* default install destination is user home directory (lib/, include/, and lib/cmake/ subdirectories)

4. Install executables:
cmake --install .\build\applications\ 

* default install destination is user home directory (program/bin/ subdirectory)

5. Install header-only:
cmake --install .\build\header_only\

* default install destination is user home directory (include/ subdirectory)  
* subdirectory is made (e.g. for previous_work.hpp, include/previous_works/previous_work.hpp)


# Install destination
is defined in CMakeLists.txt in project_template directory.  
Default settings for components, executables, and header-only are as follows.  

set(CMAKE_INSTALL_PREFIX "${USER_HOME}")  

set(MY_EXE_EXPORT_DIR ${CMAKE_INSTALL_PREFIX}/program/bin)  

set(MY_HEADER_ONLY_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})  

* set the above three variables according to your project.


# Use "components" subdirectory to create libraries.  
1. copy, rename, and modify "sample_component" subdirectory for creating your library  
2. Rename the .cpp and .hpp files to match the new directory name.  


# Use "applications" subdirectory to create libraries.  
1. copy, rename, and modify "sample_application" subdirectory for creating executables 
2. Use library (component) name without package name for linking and including libraries. 


# Use "header_only" subdirectory to create header-only libraries.  
1. copy, rename, and modify "previous_works" subdirectory for adding header-only headers.  
2. Put header-only headers in this directory.  
3. Multiple header files can be put in a single directory.  
4. The name of this directory is used as the name of installing subdirectory.   


# for convenience: use components/aggregate
1. You can create multiple components (libraries) in a project   
2. Include these created libraries in aggregate/aggregate.hpp  
3. Then, linking to "aggregate" represents all libraries, e.g.,    
         find_package(project_template REQUIRED) 
         target_link_libraries(some_target PRIVATE project_template::aggregate)   
4. And for including libraries,  
       #include <project_template/aggregate.hpp> 

5. Above 3. and 4. are case of outside project. In case of inside project,
   no need of prefix "project_template::" and "project_template/"  
   no need of find_package(project_template REQUIRED)  

# see "sample_cliant_to_project_template"

# install a single application  
cmake --install .\build\applications\sample_application\  

# run application  
cmake --build build --target run_sample_application  

(as of 2024-03-19 15:31:49)