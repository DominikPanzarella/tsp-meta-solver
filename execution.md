Compilare ed eseguire 

🔹 Debug

cmake --preset cli-debug
cmake --build --preset cli-debug
./build-debug/frontend/tsp-meta-solver

🔹 Release

cmake --preset cli-release
cmake --build --preset cli-release
./build-release/frontend/tsp-meta-solver

🔹 Test
#from root
cd build-release/backend 
# or
cd build-debug/backend 
ctest [-V]