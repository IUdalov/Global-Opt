cmake_minimum_required(VERSION 2.8)

project(rprj)

set ("${PROJECT}_BINARY_DIR"  bin)
set ("${PROJECT}_SOURCE_DIR" ~/Current/r/src)#:include)
set ("${PROJECT}_LIB_DIR" lib)

set( LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

include (src/CMakeLists.txt)

#set(LFLAGS=-L/usr/lib/R/lib -lR
#set(SOURCE_EXE main.cpp)
#add_executable(main ${SOURCE_EXE})  # Создает исполняемый файл CMAKE_CXX_FLAGS "именем main
#target_link_libraries(main foo)     # Линковка программы с set(библиотекой

