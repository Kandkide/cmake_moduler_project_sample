# applications_only directory
CMakeLists.txt templates for applications.  
Copy applications_only directory and customize it for your use.  

# Usage in brief
1. Copy **"applications_only/"** directory, **rename** it and move to its root directory.  
   
2. Rename sample_application directory.  
(The name of this directory becomes your **executable name**.)   

3. Build:  
**cmake -S . -B build**   
**cmake --build build**  

       - suppress auto-run after build
         cmake -S . -B build -DRUN_EXECUTABLE_POST_BUILD=OFF

5. Install executables:  
**sudo cmake --install build**   
  
7. install executable from a single application:   
**cmake --install .\build\applications\sample_application**\  

8. run application:   
**cmake --build build --target run_sample_application**  

<!-- 9. test
**ctest --test-dir build** -->


## Note
* Default install destination is **user home directory** (Windows) 
* Default install destination is **/usr/local** (UNIX) 
* (files are installed to its subdirectories, **program/bin/** (Windows), **bin/** (UNIX).)  
* For customizing destination (Windows), **see the last item below**.  

## Directory structure

applications_only/  
├── applications/  
│   ├── sample_application/  ***1**     
│   └── ...  
└── ...  
  
***1** copy and modify it to make **executables**  


## Link outside-project libraries  
Modify **SettingAppsBottom.cmake**.  
1. **find_package(package_name)**  
2. Append **"package_name::library_name"** to **MY_LINK_ITEMS_LIST**.  


# Customize install destination (Windows)
In CMakeLists.txt **in project root directory**.   
Modify following variables according to your project.  
  
**set(CMAKE_INSTALL_PREFIX "${USER_HOME}")**   
  
**set(MY_EXE_EXPORT_DIR ${CMAKE_INSTALL_PREFIX}/program/bin)**  
  
* They determine install destination of components, executables, and header-only, respectively.
* On **UNIX**, these installation locations are relatively well-defined by convention, and we adopt **"/usr/local"** directory.

(as of 2024-12-28 13:51:43)