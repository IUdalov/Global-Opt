cmake_minimum_required(VERSION 2.8)	   

project(rprj)

# uncomment for more build info 
message("--------------------------------------------------")
message("CMake user config:")
message("	CMAKE_FLAGS = $ENV{CMAKE_FLAGS}")
message("	C_FLAGS = $ENV{C_FLAGS}")
message("	CXX_FLAGS = $ENV{CXX_FLAGS}")
message("	BUILD_DIRECTORY = $ENV{BUILD_DIRECTORY}")
message("	BIN_DIRECTORY = $ENV{BIN_DIRECTORY}")
message("--------------------------------------------------")

if($ENV{MAKE_DEBUG_MODE})
	set(CMAKE_VERBOSE_MAKEFILE true)
endif()

include_directories(include)
add_subdirectory(sources)

#set(LFLAGS=-L/usr/lib/R/lib -lR
#set(SOURCE_EXE main.cpp)
#add_executable(main ${SOURCE_EXE})  # Создает исполняемый файл CMAKE_CXX_FLAGS "именем main
#target_link_libraries(main foo)     # Линковка программы с set(библиотекой

