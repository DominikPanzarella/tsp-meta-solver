cmake_minimum_required(VERSION 3.19)
project(TSP-META-SOLVER LANGUAGES CXX)

# Opzione per abilitare o disabilitare Qt GUI
option(ENABLE_QT "Build with Qt GUI support" ON)

# Aggiungi il backend sempre (è core)
add_subdirectory(backend)

if(ENABLE_QT)
    # Cerca Qt solo se serve la GUI
    find_package(Qt6 6.9 REQUIRED COMPONENTS Core Widgets)
    add_subdirectory(frontend)
endif()
