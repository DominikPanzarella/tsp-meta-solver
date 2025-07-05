cmake_minimum_required(VERSION 3.14)
project(tsp_cli)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tsp-meta-solver
    main.cpp
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
