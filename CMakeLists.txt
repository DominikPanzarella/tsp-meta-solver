cmake_minimum_required(VERSION 3.19)
project(TSP-META-SOLVER LANGUAGES CXX)

# Copia la directory external nella directory di build
file(COPY ${CMAKE_SOURCE_DIR}/external DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})

# Aggiungi il backend sempre (è core)
add_subdirectory(backend)
add_subdirectory(frontend)

add_custom_target(copy_external ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/external
          ${CMAKE_BINARY_DIR}/external
)

add_custom_target(copy_resources ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/resources
          ${CMAKE_BINARY_DIR}/resources
)

add_custom_target(copy_config ALL
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
          ${CMAKE_SOURCE_DIR}/tspmetasolver.set
          ${CMAKE_BINARY_DIR}/tspmetasolver.set
)

add_custom_target(copy_config_json ALL
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
          ${CMAKE_SOURCE_DIR}/tspmetasolver.json
          ${CMAKE_BINARY_DIR}/tspmetasolver.json
)