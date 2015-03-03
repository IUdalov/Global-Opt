cmake_minimum_required(VERSION 2.8)

set(PRJ_NAME "$ENV{LIB_PRJ_NAME}")
project(${PRJ_NAME})

set(CMAKE_CXX_FLAGS "-I/usr/share/R/include -fPIC -Wall -L/usr/lib/R/lib -lR $ENV{CXX_FLAGS}")
set(CMAKE_C_FLAGS "-I/usr/share/R/include -fPIC -Wall -L/usr/lib/R/lib -lR $ENV{C_FLAGS}")
#set(SOURCE_LIB interface.c methods.cpp)
file(GLOB SOURCE_LIB
    "*.cpp"
    "*.c"
)
set(LIBRARY_OUTPUT_PATH $ENV{BIN_DIRECTORY})

add_library(${PRJ_NAME} SHARED ${SOURCE_LIB})
install(TARGETS ${PRJ_NAME} DESTINATION $ENV{BIN_DIRECTORY})
