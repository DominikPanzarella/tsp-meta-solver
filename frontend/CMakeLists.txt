cmake_minimum_required(VERSION 3.14)
project(tsp_cli)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tsp-meta-solver
    src/main.cpp
    src/start.cpp         
    src/utils/initializer.cpp   
)

target_include_directories(tsp-meta-solver PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(tsp-meta-solver
    PRIVATE tsp_backend
)

# Installazione opzionale
include(GNUInstallDirs)

install(TARGETS tsp-meta-solver
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

add_definitions(-DLKH3_PATH="${CMAKE_BINARY_DIR}/external/LKH-3.0.13/LKH")
add_definitions(-DCONCORDE_PATH="${CMAKE_BINARY_DIR}/external/concorde/build/TSP/concorde")
add_definitions(-DCONFIG_PATH="${CMAKE_BINARY_DIR}/tspmetasolver.set")

target_compile_definitions(tsp_backend PRIVATE LKH3_PATH="${CMAKE_BINARY_DIR}/external/LKH-3.0.13/LKH")
target_compile_definitions(tsp_backend PRIVATE CONCORDE_PATH="${CMAKE_BINARY_DIR}/external/concorde/build/TSP/concorde")
target_compile_definitions(tsp-meta-solver PRIVATE CONFIG_PATH="${CMAKE_BINARY_DIR}/tspmetasolver.set")