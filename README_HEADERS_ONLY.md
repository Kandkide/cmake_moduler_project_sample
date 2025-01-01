# headers_only
Locate (or install) header-only headers to specified directory.
Build examples and tests.

# Usage in brief
1. Rename headers_only/header_only/**previous_works** directory. 
(The name of this directory, "previous_works" by default, acts as package name.)   

2. Locate header-only hpp files under this directory.  

       - After instlalling (step 4), you can include them by:
         #include <previous_works/xxx.hpp>
   
3. Build:  
**cmake -S . -B build**   
**cmake --build build**  

       - disable tests 
         cmake -S . -B build -DENABLE_TESTS=OFF
       - disable examples
         cmake -S . -B build -DENABLE_EXAMPLES=OFF
       - disable both
         cmake -S . -B build -DENABLE_TESTS=OFF -DENABLE_EXAMPLES=OFF

6. Install header-only:  
**sudo cmake --install build**

7. Conducts step 3. and 4. at once (use bash script)
**build-install-all-in-one.sh**

9. test
**ctest --test-dir build**

7. run example code
**cmake --build build --target run_\<example source name\>**


## Directory structure

headers_only/  
├── header_only/  
│   ├── previous_works/  ***1**    
│   ├── examples/  
│   ├── tests/  
│   └── ...  
└── ...  
  
***1** copy and modify it, and locate **header-only** headers under it   


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
  
**set(MY_HEADER_ONLY_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})**  
  
* They determine install destination of components, executables, and header-only, respectively.
* On **UNIX**, these installation locations are relatively well-defined by convention, and we adopt **"/usr/local"** directory.

(as of 2024-12-28 13:47:42)