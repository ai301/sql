cmake_minimum_required(VERSION 2.6)

project(sql CXX)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)

find_package(Sqlite REQUIRED)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
  add_definitions(-DNDEBUG=1)
endif (CMAKE_BUILD_TYPE STREQUAL "Release")

add_subdirectory(sql)
