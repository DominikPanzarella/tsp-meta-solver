Compilare ed eseguire con Qt (GUI) + Test (Ctest)

🔹 Debug

cmake --preset debug
cmake --build --preset debug
./build-debug/frontend/TSP-META-SOLVER.app/Contents/MacOS/TSP-META-SOLVER

🔹 Release

cmake --preset release
cmake --build --preset release
./build-release/frontend/TSP-META-SOLVER.app/Contents/MacOS/TSP-META-SOLVER


🔹 Test
#from root
cd build-release/backend 
# or
cd build-debug/backend 
ctest [-V]