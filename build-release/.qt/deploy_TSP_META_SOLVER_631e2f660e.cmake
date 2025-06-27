include("/Users/dominikpanzarella/Library/Mobile Documents/com~apple~CloudDocs/Desktop/SUPSI/Semestre 6/Tesi/tsp-meta-solver/build-release/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/TSP-META-SOLVER-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE TSP-META-SOLVER.app
)
