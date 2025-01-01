# components_only directory
CMakeLists.txt templates for hierarchical projects to **make libraries**.  
Copy the directory and customize it for your use.  

       - The word "component" is interchangeable with "library".  
       - The same gose for "project" with "package".  

# Usage
1. Copy **"components_only/"** directory, **rename** it and move to its root directory.  
(The name of this directory becomes your **package name**.)   
   
2. Rename **sample_component** subdirectory.  
(The name of this directory becomes the **library name**.)   

       - After instlalling (step 4), cmake can find this package and use libraries in it by "package name::library name".
       - An example of usage in external cmakelists.txt would be as follows,

         find_package(package_name REQUIRED)  
         target_link_libraries(someTarget PRIVATE package_name::library_name)  

        + including header in cliant source may be necessary:  
          #include <components_only/sample_component.hpp>
          
3. Build:  
**cmake -S . -B build**   
**cmake --build build**  

       - disable tests 
         cmake -S . -B build -DENABLE_TESTS=OFF
       - disable examples
         cmake -S . -B build -DENABLE_EXAMPLES=OFF
       - disable both
         cmake -S . -B build -DENABLE_TESTS=OFF -DENABLE_EXAMPLES=OFF

4. Install libraries:  
**sudo cmake --install build**   

       - Windows: Remove "sudo" at the beginning.

5. Conducts step 3. and 4. at once (use bash script)  
**build-install-all-in-one.sh**  
  
9. test  
**ctest --test-dir build**  

7. run example code
**cmake --build build --target run_\<example source name\>_\<library name\>**

## Install Destination
* Default install destination is **user home directory** (Windows) 
* Default install destination is **/usr/local** (UNIX) 
* For customizing destination (Windows), **see the last item below**.  

## Directory structure

components_only/   ***1**   
├── components/   
│   ├── sample_component/   ***2**  
│   │   ├── include/   
│   │   ├── src/   
│   │   ├── examples/   
│   │   ├── tests/   
│   └── ...  
└── ...  
  
***1** name of this directory becomes **package name** 
***2** name of this directory becomes **library name** 


## Link outside libraries to your library  
Modify **SettingComponentsLeaf.cmake**:  
1. **find_package(package_name)**  
2. Append **"package_name::library_name"** to **MY_LINK_ITEMS_LIST**.  

## Link inside-package libraries
Modify **SettingComponentsLeaf.cmake**:  
1. Append **library_name** to **MY_LINK_ITEMS_LIST** without package_name.  


# Customize install destination (Windows)
In CMakeLists.txt **in project root directory**.   
Modify following three variables according to your project.  
  
**set(CMAKE_INSTALL_PREFIX "${USER_HOME}")**   
  
**set(MY_EXE_EXPORT_DIR ${CMAKE_INSTALL_PREFIX}/program/bin)**  
  
**set(MY_HEADER_ONLY_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})**  
  
* They determine install destination of components, executables, and header-only, respectively.
* On **UNIX**, these installation locations are relatively well-defined by convention, and we adopt **"/usr/local"** directory.

(as of 2024-12-28 14:40:00)