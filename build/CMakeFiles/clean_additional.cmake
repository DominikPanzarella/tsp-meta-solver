# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles/TSP-META-SOLVER_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/TSP-META-SOLVER_autogen.dir/ParseCache.txt"
  "TSP-META-SOLVER_autogen"
  )
endif()
