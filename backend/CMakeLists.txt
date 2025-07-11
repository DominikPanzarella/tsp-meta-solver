cmake_minimum_required(VERSION 3.14)
project(tsp_backend)

# IMPORTANTE: Genera compile_commands.json per VSCode
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Assicurati di usare C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Includi FetchContent per librerie esterne
include(FetchContent)

# === NLOHMANN JSON ===
FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

# === HEADER GLOBALI ===
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/resources)

# === SORGENTE LIBRERIA ===
file(GLOB_RECURSE BACKEND_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/resources"
)

add_library(tsp_backend STATIC ${BACKEND_SOURCES})

target_include_directories(tsp_backend PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/resources
)

target_compile_features(tsp_backend PUBLIC cxx_std_20)
target_link_libraries(tsp_backend PUBLIC nlohmann_json::nlohmann_json)

# === DEFINES GLOBALI ===
add_definitions(-DLKH3_PATH="${CMAKE_BINARY_DIR}/external/LKH-3.0.13/LKH")
add_definitions(-DCONCORDE_PATH="${CMAKE_BINARY_DIR}/external/concorde/build/TSP/concorde")
add_definitions(-DOPTIMA_PATH="${CMAKE_BINARY_DIR}/resources/tsp_optima.csv")

target_compile_definitions(tsp_backend PRIVATE
    LKH3_PATH="${CMAKE_BINARY_DIR}/external/LKH-3.0.13/LKH"
    CONCORDE_PATH="${CMAKE_BINARY_DIR}/external/concorde/build/TSP/concorde"
    OPTIMA_PATH="${CMAKE_BINARY_DIR}/resources/tsp_optima.csv"
)

# === COPIA RISORSE DOPO BUILD ===
add_custom_command(TARGET tsp_backend POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    ${CMAKE_CURRENT_BINARY_DIR}/resources
)

