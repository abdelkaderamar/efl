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

#include(cmake/CPM.cmake)

include(FetchContent)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v3.0.0
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

Include_Directories (${CMAKE_SOURCE_DIR}/src)

add_subdirectory ( src )

