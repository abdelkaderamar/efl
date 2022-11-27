cmake_minimum_required(VERSION 3.7)

project ( efl 
  VERSION 0.0.1
  LANGUAGES CXX )

If (PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  Message(
    FATAL_ERROR
      "In-source builds not allowed [${PROJECT_SOURCE_DIR}] vs [${PROJECT_BINARY_DIR}]. Please make a new directory (called a build directory) and run CMake from there."
  )
Endif()

set ( CMAKE_CXX_STANDARD 20 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS OFF )

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

#Find_Package ( Boost COMPONENTS log  program_options REQUIRED )
#If ( Boost_FOUND )
#  Include_Directories ( ${Boost_INCLUDE_DIRS} )
#  Add_Definitions ( "-DBOOST_LOG_DYN_LINK" )
#Endif ()

Find_Package (Boost REQUIRED 
   system)

include (cmake/CPM.cmake)
include (cmake/CodeCoverage.cmake)


CPMAddPackage(
  NAME json
  GITHUB_REPOSITORY nlohmann/json
  VERSION 3.11.2
  OPTIONS "JSON_INSTALL 1"
)

CPMAddPackage("gh:fmtlib/fmt#9.1.0")
CPMAddPackage("gh:gabime/spdlog@1.11.0")

CPMAddPackage(
  NAME googletest
  GITHUB_REPOSITORY google/googletest
  GIT_TAG release-1.12.1
  VERSION 1.12.1
  OPTIONS "INSTALL_GTEST OFF" "gtest_force_shared_crt"
)

CPMAddPackage(
  NAME benchmark
  GITHUB_REPOSITORY google/benchmark
  VERSION 1.7.1
  OPTIONS "BENCHMARK_ENABLE_TESTING Off"
)

if(benchmark_ADDED)
  # enable c++11 to avoid compilation errors
  set_target_properties(benchmark PROPERTIES CXX_STANDARD 11)
endif()

# include(FetchContent)

# FetchContent_Declare(ftxui
#   GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
#   GIT_TAG v3.0.0
# )

# FetchContent_GetProperties(ftxui)
# if(NOT ftxui_POPULATED)
#   FetchContent_Populate(ftxui)
#   add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
# endif()

#--- options
OPTION( EFL_TEST       "Build EFL tests." OFF )
OPTION( EFL_COVERAGE   "Build EFL for coverage." OFF )

If ( EFL_COVERAGE )
  APPEND_COVERAGE_COMPILER_FLAGS()
  
  Setup_Target_For_Coverage_LCOV (
    NAME efl_coverage
    EXECUTABLE efl_tests
    EXCLUDE "${PROJECT_SOURCE_DIR}/test/*" "${PROJECT_BINARY_DIR}/_deps/*" "/usr/local/*" "/usr/*" 
            "${PROJECT_SOURCE_DIR}/src/efl/date.h"
            "${PROJECT_SOURCE_DIR}/src/efl/csv.h"
    )
  
    Endif ( EFL_COVERAGE )


Include_Directories (${CMAKE_SOURCE_DIR}/src)

add_subdirectory ( src )

add_subdirectory ( test )

