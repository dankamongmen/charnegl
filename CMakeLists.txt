cmake_minimum_required (VERSION 3.2) # necessary for C++11 support
project (charn)

# Include external CMake config files
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(Config++ REQUIRED)

add_library(charn src/libcharn/configfile.cpp)
