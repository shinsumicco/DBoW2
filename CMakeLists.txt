cmake_minimum_required(VERSION 3.1)
project(DBoW2 CXX C)

# define build options

option(BUILD_DBoW2 "Build DBoW2" ON)
option(BUILD_UTILS "Build utility executables" ON)
option(BUILD_SHARED_LIBS "Build DBoW2 as a shared library" ON)

# define build types

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

# enable standard C++11

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# find libraries

find_package(Eigen3 3.3 REQUIRED)
find_package(OpenCV 4.0 QUIET)
if(NOT OpenCV_FOUND)
  find_package(OpenCV 3.0 QUIET)
  if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV >= 3.0 not found")
  endif()
endif()
message(STATUS "Use OpenCV ${OpenCV_VERSION}")

# include headers

include_directories(include)

# build and install DBoW2

if(BUILD_DBoW2)
  # create a library
  add_library(DBoW2
    src/BowVector.cpp
    src/FBRIEF.cpp
    src/FeatureVector.cpp
    src/FORB.cpp
    src/QueryResults.cpp
    src/ScoringObject.cpp)

  # set compile options
  if(BUILD_SHARED_LIBS)
    target_compile_options(DBoW2 PRIVATE
      $<$<OR:$<CXX_COMPILER_ID:MSVC>>:
        /W4 /MD$<$<CONFIG:Debug>:d>
      >)
  else()
    target_compile_options(DBoW2 PRIVATE
      $<$<OR:$<CXX_COMPILER_ID:MSVC>>:
        /W4 /MT$<$<CONFIG:Debug>:d>
      >)
  endif()
  target_compile_options(DBoW2 PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
      -Wall -Wextra -pedantic $<$<CONFIG:Debug>:-Og> $<$<CONFIG:Release>:-O3>
    >)

  # set output properties
  set_target_properties(DBoW2 PROPERTIES
    OUTPUT_NAME  "dbow2"
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

  # include libraries
  target_include_directories(DBoW2 PRIVATE ${OpenCV_INCLUDE_DIRS})

  # link libraries
  target_link_libraries(DBoW2 PRIVATE ${OpenCV_LIBS})

  # install
  install(DIRECTORY include/DBoW2
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
  install(TARGETS DBoW2
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
  configure_file(DBoW2.cmake.in ${PROJECT_BINARY_DIR}/DBoW2Config.cmake @ONLY) 
  install(FILES ${PROJECT_BINARY_DIR}/DBoW2Config.cmake
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake/DBoW2)
endif(BUILD_DBoW2)

# build utilities

if(BUILD_UTILS)
  # create a executable
  add_executable(ConvertORBVocabrary util/ConvertORBVocabrary.cpp)

  # set compile options
  target_compile_options(ConvertORBVocabrary PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:MSVC>>:
      /W4 /MT$<$<CONFIG:Debug>:d>
    >
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
      -Wall -Wextra -pedantic
    >)

  # include libraries
  target_include_directories(ConvertORBVocabrary PRIVATE ${OpenCV_INCLUDE_DIRS})

  # link libraries
  target_link_libraries(ConvertORBVocabrary PRIVATE DBoW2 ${OpenCV_LIBS})
endif()
