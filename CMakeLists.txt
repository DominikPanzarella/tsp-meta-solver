cmake_minimum_required(VERSION 3.19)
project(TSP-META-SOLVER LANGUAGES CXX)

# Copia la directory external nella directory di build
file(COPY ${CMAKE_SOURCE_DIR}/external DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})

# Aggiungi il backend sempre (è core)
add_subdirectory(backend)
add_subdirectory(frontend)
