cmake_minimum_required(VERSION 3.7)

project (efl VERSION 0.0.1)

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
  thread filesystem program_options system date_time)

Include_Directories (${CMAKE_SOURCE_DIR}/src)

add_subdirectory ( src )

