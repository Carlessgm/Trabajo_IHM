# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Trabajo_IHM_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Trabajo_IHM_autogen.dir\\ParseCache.txt"
  "Trabajo_IHM_autogen"
  )
endif()
