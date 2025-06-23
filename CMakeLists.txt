cmake_minimum_required(VERSION 3.19)
project(TSP-META-SOLVER LANGUAGES CXX)

find_package(Qt6 6.9 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(TSP-META-SOLVER
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_link_libraries(TSP-META-SOLVER
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS TSP-META-SOLVER
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET TSP-META-SOLVER
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})