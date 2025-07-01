cmake_minimum_required(VERSION 3.14)
project(tsp_backend)

# IMPORTANTE: Genera compile_commands.json per VSCode
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Assicurati di usare C++17 o superiore
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Includi FetchContent per scaricare GTest
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt OFF CACHE BOOL "" FORCE) # Per Windows
FetchContent_MakeAvailable(googletest)

# === GLOBALE ===
# Includi tutte le cartelle header
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# === SORGENTE LIBRERIA ===
file(GLOB_RECURSE BACKEND_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# Libreria statica (può essere shared se vuoi)
add_library(tsp_backend STATIC ${BACKEND_SOURCES})

target_include_directories(tsp_backend PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(tsp_backend PUBLIC cxx_std_17)

# === CLI ===
#add_executable(tsp_cli ${CMAKE_CURRENT_SOURCE_DIR}/src/main_cli.cpp)
#target_link_libraries(tsp_cli PRIVATE tsp_backend)

# === TEST ===
enable_testing()

file(GLOB_RECURSE BACKEND_TESTS
    "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp"
)

if(BACKEND_TESTS)  # se la lista non è vuota
  add_executable(tsp_tests ${BACKEND_TESTS})

  target_include_directories(tsp_tests PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/src
      ${CMAKE_CURRENT_SOURCE_DIR}/test
  )

  target_link_libraries(tsp_tests
      PRIVATE
      tsp_backend
      GTest::gtest_main
  )

  include(GoogleTest)
  gtest_discover_tests(tsp_tests)
else()
  message(WARNING "No test source files found in ${CMAKE_CURRENT_SOURCE_DIR}/test")
endif()

add_custom_command(TARGET tsp_backend POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    ${CMAKE_CURRENT_BINARY_DIR}/resources
)

find_package(OpenMP REQUIRED)

if(OpenMP_CXX_FOUND)
    target_link_libraries(tsp_backend PRIVATE OpenMP::OpenMP_CXX)
    target_compile_options(tsp_backend PRIVATE ${OpenMP_CXX_FLAGS})
endif()
