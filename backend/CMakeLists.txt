# Libreria backend
add_library(tsp_backend
    solver.cpp
    solver.h
)

target_include_directories(tsp_backend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(tsp_backend PUBLIC cxx_std_17)

# Eseguibile CLI
add_executable(tsp_cli
    main_cli.cpp
)

target_link_libraries(tsp_cli
    PRIVATE tsp_backend
)
