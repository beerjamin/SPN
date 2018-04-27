# 
#

cmake_minimum_required(VERSION 2.6)
project(SPN)
include_directories(include)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.c")

add_executable(ECB-test ${SOURCES})
