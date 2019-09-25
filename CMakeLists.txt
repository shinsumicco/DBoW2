cmake_minimum_required(VERSION 3.1)
project(DBoW2 CXX C)

option(BUILD_DBoW2 "Build DBoW2" ON)
option(BUILD_UTIL "Build utility executables" ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU"
       OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang"
       OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "AppleClang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
endif()

set(SOURCES
  src/BowVector.cpp
  src/FeatureVector.cpp
  src/QueryResults.cpp
  src/ScoringObject.cpp
  src/FORB.cpp
  src/FBrief.cpp)

find_package(OpenCV 4.0 QUIET)
if(NOT OpenCV_FOUND)
  find_package(OpenCV 3.0 QUIET)
  if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV >= 3.0 not found")
  endif()
endif()
message(STATUS "Use OpenCV ${OpenCV_VERSION}")

include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(include)

if(BUILD_DBoW2)
  set(LIB_TYPE "SHARED")
  if(WIN32)
    set(LIB_TYPE "STATIC")
  endif(WIN32)
  add_library(${PROJECT_NAME} ${LIB_TYPE} ${SOURCES})
  target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
endif(BUILD_DBoW2)

configure_file(DBoW2.cmake.in ${PROJECT_BINARY_DIR}/DBoW2Config.cmake @ONLY)

if(BUILD_DBoW2)
  install(DIRECTORY include/DBoW2
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
  install(TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
endif(BUILD_DBoW2)

if(BUILD_UTIL)
  add_executable(convert_orb_vocab util/convert_orb_vocab.cpp)
  target_link_libraries(convert_orb_vocab ${PROJECT_NAME})
endif(BUILD_UTIL)

install(FILES ${PROJECT_BINARY_DIR}/DBoW2Config.cmake
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake/DBoW2/)
