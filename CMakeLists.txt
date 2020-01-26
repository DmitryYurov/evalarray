cmake_minimum_required(VERSION 3.10)
project(evalarray VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)

include(CTest)
include(configuration)

add_subdirectory(tests)



 
