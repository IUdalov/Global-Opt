cmake_minimum_required(VERSION 2.8)	   

project(rprj)

 #  1 or 0
set(MAKE_DEBUG_MODE 0)

####################
# Library properties 
set(LIB_PRJ_DIR "${PWD}cinterface")
set(LIB_PRJ_NAME "opt")

set(BIN_DIRECTORY "${PWD}../bin")
set(BUILD_DIRECTORY "${PWD}build")
set(CXX_FLAGS "-Wno-unused-but-set-variable -Wno-unused-variable")
set(C_FLAGS "-std=c99 $CXX_FLAGS")

message("--------------------------------------------------")
message("CMake user config:")
message("	CMAKE_FLAGS = ${CMAKE_FLAGS}")
message("	C_FLAGS = ${C_FLAGS}")
message("	CXX_FLAGS = ${CXX_FLAGS}")
message("	BUILD_DIRECTORY = ${BUILD_DIRECTORY}")
message("	BIN_DIRECTORY = ${BIN_DIRECTORY}")
message("--------------------------------------------------")

if(${MAKE_DEBUG_MODE})
	set(CMAKE_VERBOSE_MAKEFILE true)
endif()

include_directories(include)
add_subdirectory(sources)
