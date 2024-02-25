# cmake_moduler_project_sample
cmake_moduler_project_sample


# command line
cmake -S . -B ../build
cmake --build ../build

# command line to install application file to bin folder which is specified in CMakeLists.txt
cmake --install ../build

# fresh
cmake -S . -B ../build --fresh

# target clean
cmake --build ../build --clean-first
(or) 
cmake --build ../build --target clean
cmake --build ../build
