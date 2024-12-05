# cmake_moduler_project_sample
A set of simple CMakeLists.txt templates for hierarchical projects.  
Copy project_template directory and customize it for your use.  
* We use the word **"component"** interchangeably with **"library"** in the following description. 
* The same goes for **"applications"** with **"executables"**.  

# Usage in brief
1. Copy **"project_template/"** directory, **rename** it and move to its root directory.  
(The name of this directory becomes your **project name**.)   
   
2. Create components and applications (see following items below).  

3. Build:  
**cmake -S . -B build**   
**cmake --build build**  
  
4. Install libraries:  
**cmake --install .\build\components**\   
  
5. Install executables:  
**cmake --install .\build\applications**\  
  
6. Install header-only:  
**cmake --install .\build\header_only**\  

7. install executable from a single application:   
**cmake --install .\build\applications\sample_application**\  

8. run application:   
**cmake --build build --target run_sample_application**  

* Ubuntu or Debian: Put **"sudo"** at the beginning (when install). And replace **"\\"** with **"/"**.

## Note
* Default install destination is **user home directory** (Windows) 
* Default install destination is **/usr/local** (UNIX) 
* (files are installed to its subdirectories, **lib/, include/, lib/cmake/,** **program/bin/** (Windows), **bin/** (UNIX), depending on file type.)  
* As for header-only, one more layer of subdirectory is made (using source directory name)  
* For customizing destination, **see the last item below**.  

## Directory structure

project_template/  
├── applications/  
│   ├── sample_application/  ***1**     
│   └── ...  
├── components/  
│   ├── sample_component/  ***2**   
│   └── ...  
├── header_only/  
│   ├── previous_works/  ***3**    
│   └── ...  
└── ...  
  
***1** copy and modify it to make **executables**  
***2** copy and modify it to make **libraries**  
***3** copy and modify it to make **header-only** headers   


## To create libraries (components).  
1. Copy, rename, and modify **"sample_component" subdirectory** for creating your library  
2. Rename the .cpp and .hpp files to match the new directory name.  
* **The name of the directory** becomes **library name**.  

## To create executables (applications).  
1. Copy, rename, and modify **"sample_application" subdirectory** for creating executables  
2. Change values of variables in **SettingAppsBottom.cmake** if necessary.  
* **The name of the directory** becomes **name of the executable**.  

## Link outside-project libraries  
In **SettingComponentsLeaf.cmake** or **SettingAppsBottom.cmake**.  
1. **find_package(package_name)**  
2. Append **"package_name::library_name"** to **MY_LINK_ITEMS_LIST**.  

## Link inside-project libraries
1. Append **library_name** to **MY_LINK_ITEMS_LIST** without package_name.  

## Utilize libraries from outside the project after installation  
1. In relevant CMakeLists.txt:    
       **find_package(package_name REQUIRED)**   
       **target_link_libraries(some_target PRIVATE package_name::sample_component)**   

## Locate header-only libraries (optional).  
1. Copy and/or rename **"previous_works"** subdirectory for adding header-only libraries.  
2. Multiple header files can be put in a single directory.  
3. The name of this directory is used as the name of installing subdirectory.   

* It is optional, since header-only libraries are easy to handle even if they are outside the project.  
* Still, there are two merits of locating header-only libraries inside the project:  
* (1) enables to install header-only libraries as a set.  
* (2) using them inside the project without installing them.  

# Customize install destination (Windows)
In CMakeLists.txt **in project root directory**.   
Modify following three variables according to your project.  
  
**set(CMAKE_INSTALL_PREFIX "${USER_HOME}")**   
  
**set(MY_EXE_EXPORT_DIR ${CMAKE_INSTALL_PREFIX}/program/bin)**  
  
**set(MY_HEADER_ONLY_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})**  
  
* They determine install destination of components, executables, and header-only, respectively.
* On **UNIX**, these installation locations are relatively well-defined by convention, and we adopt **"/usr/local"** directory.

(as of 2024-12-05 01:53:04)