# cmake_moduler_project_sample
A set of simple CMakeLists.txt templates for hierarchical projects.  
Copy project_template directory and customize it for your use.  
* We use the word "component" interchangeably with "library" in the following description.  

# project_template usage
1. Use "components" subdirectory to create libraries (components).  
2. copy, rename, and modify "sample_component" subdirectory for creating your library  
   Also rename the .cpp and .hpp files to match the new directory name.   
3. build and install (see Command Lines part below)  
4. Find your package and link it in the other project's CMakeLists.txt.    
   your package name: = name of root directory (default: project_template)  
   your library name: = sample_component (or renamed directory name)  
5. For example  
   find(project_template REQUIRED)  
   target_link_libraries(some_target PRIVATE project_template::sample_component)  

# Note
1. CMAKE_INSTALL_PREFIX which is used for the install destination is set in root project CMakeLists.txt  
2. CMAKE_PREFIX_PATH is also set at the same place.  
   It might have unpredicted side effects and cause surprises. Please set it in accordance to your environment.  

# for convenience: use components/aggregate
1. By copying "sample_component", you can create multiple components (libraries) in a project   
2. Include these created libraries in aggregate/aggregate.hpp  
3. Only a single line is necessary to include all those libraries:    
   target_link_libraries(some_target PRIVATE project_template::aggregate)  
   * inside the project, get rid of "project_template::"  
4. In the target source file, #include <project_template/aggregate.hpp>, is needed.  
   * case of inside-project target source file, #include "aggregate.hpp"  

# create executables: use applications subdirectory
1. Usage: see "sample_application" directory and files in it.  
2. copy, rename, and modify it as you like.  
3. Note:  
   Use library (component) name without package name for linking and including libraries.   
   You can also use "aggregate" and "aggregate.hpp" if you have set it up already.   

# Command Lines
Always build in the project root directory (project_template/)  

## common
cmake -S . -B build  
cmake --build build  

## install components (libraries)  
cmake --install .\build\components\  

## install applications or an application  
cmake --install .\build\applications\   
cmake --install .\build\applications\sample_application\  

## run application  
cmake --build build --target run_sample_application  

(as of 2024-03-10 00:54:52)