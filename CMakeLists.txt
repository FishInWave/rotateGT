cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(rotateGT)
add_definitions(-std=c++11)

find_package(PCL 1.2 REQUIRED)

# json
#set(Jsoncpp_INCLUDE_PATH "/usr/include/jsoncpp")
#set(Jsoncpp_LIBRARY "/usr/lib/x86_64-linux-gnu/libjsoncpp.so")
#include_directories(${Jsoncpp_INCLUDE_PATH})
# PCL
#include_directories(${PCL_INCLUDE_DIRS})
#link_directories(${PCL_LIBRARY_DIRS})
#add_definitions(${PCL_DEFINITIONS})
# Eigen
find_package(Eigen3)
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})
# own
include_directories(include)

add_executable (rotateGT ./src/rotateGT.cpp)
#target_link_libraries (analysJson ${Jsoncpp_LIBRARY})
#target_link_libraries (analysJson ${PCL_LIBRARIES})