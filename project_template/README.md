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

# To create executables (applications).  
1. Copy, rename, and modify **"sample_application" subdirectory** for creating executables 
2. Change values of variables in **SettingAppsBottom.cmake** if necessary.  

# Link other libraries (common to above two)  
1. **find_package(package_name)** in **SettingComponentsLeaf.cmake** or **SettingAppsBottom.cmake**.  
2. And append **"package_name::library_name"** to **MY_LINK_ITEMS_LIST** in SettingComponentsLeaf.cmake (or SettingAppsBottom.cmake).  
* If it is inside the project, no need to find_package, and just append library_name to **MY_LINK_ITEMS_LIST** without package_name.  
* Even this is not necessary in case of executables if you aggregate libraries (following next item).  

# For convenience: components/aggregate/aggregate.hpp
1. After creating new components (libraries), execute **set_aggregate.exe** in the project root directory.  
2. It automatically include the new library header in **aggregate/aggregate.hpp**  
3. Then, aggregated libraries automatically linked to inside-project executables.  
* If you do not need this, just delete aggregate sub-directory.  
* But you have to append library name to **MY_LINK_ITEMS_LIST** in **SettingAppsBottom.cmake** manually.  

# Utilize libraries from outside-project after installation  
1. In relevant CMakeLists.txt:    
       **find_package(project_template REQUIRED)**   
       **target_link_libraries(some_target PRIVATE project_template::aggregate)**   
2. In relevant source file:   
       **#include <project_template/aggregate.hpp>**  

# Utilize libraries inside the project  
1. Usage in relevant source file:  
       **#include <aggregate.hpp>**   
* In case of components, you need to append **"aggregate"** to **MY_LINK_ITEMS_LIST** in **SettingComponentsLeaf.cmake**  

# Locate header-only libraries (optional).  
1. Copy and/or rename **"previous_works"** subdirectory for adding header-only libraries.  
2. Multiple header files can be put in a single directory.  
3. The name of this directory is used as the name of installing subdirectory.   

* It is optional, since header-only libraries are easy to handle even if they are outside the project.  
* Still, there are two merits of locating header-only libraries inside the project:  
* (1) enables to install header-only libraries as a set.  
* (2) using them inside the project without installing them.  


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


# Other convenient commands
1. install a single application:   
**cmake --install .\build\applications\sample_application**\  

2. run application:   
**cmake --build build --target run_sample_application**  

(as of 2024-03-24 03:56:41)