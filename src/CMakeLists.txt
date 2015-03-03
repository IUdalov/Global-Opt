cmake_minimum_required(VERSION 2.8)

project(opt)

set ("${PROJECT}_BINARY_DIR" ../bin)
set ("${PROJECT}_SOURCE_DIR" ../src) #:include)
set ("${PROJECT}_LIB_DIR" ../lib)
set(CMAKE_VERBOSE_MAKEFILE true)
set(CMAKE_CXX_FLAGS "-I/usr/share/R/include -fPIC -Wall -L/usr/lib/R/lib -lR")
set(CMAKE_C_FLAGS "-I/usr/share/R/include -fPIC -Wall -L/usr/lib/R/lib -lR -std=c99")
# set(CMAKE_CXX_LINKER_FLAGS "-L/usr/lib/R/lib -lR")
set(SOURCE_LIB interface.c methods.cpp) # methods.h

add_library(opt SHARED ${SOURCE_LIB})


#se t(LFLAGS=-L/usr/lib/R/lib -lR
#set(SOURCE_EXE main.cpp)
#add_executable(main ${SOURCE_EXE})  # Создает исполняемый файл CMAKE_CXX_FLAGS "именем main
#target_link_libraries(main foo)     # Линковка программы с set(библиотекой

