# cmake_moduler_project_sample
cmake_moduler_project_sample


# command line
cmake -S . -B build
cmake --build build

# command line to install application file to bin folder which is specified in CMakeLists.txt
cmake --install build
(uninstall afterward)
cmake --build build --target uninstall-app1 
    *note: directory name added

# fresh
cmake -S . -B build --fresh

# target clean
cmake --build build --clean-first
(or) 
cmake --build build --target clean
cmake --build build

# build partially
cmake --build build --target feature1_lib    

# build or ../build
either will do
