# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "frontend/CMakeFiles/TSP-META-SOLVER_autogen.dir/AutogenUsed.txt"
  "frontend/CMakeFiles/TSP-META-SOLVER_autogen.dir/ParseCache.txt"
  "frontend/TSP-META-SOLVER_autogen"
  )
endif()
