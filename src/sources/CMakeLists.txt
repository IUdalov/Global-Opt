cmake_minimum_required(VERSION 2.8)

set(PRJ_NAME "${LIB_PRJ_NAME}")
project(${PRJ_NAME})

IF(WIN32)
    set(CMAKE_C_FLAGS "${C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")
    message("Additional dependences are needed!")
ELSE()
    set(CMAKE_C_FLAGS "-O3 -I/usr/share/R/include -fPIC -Wall -Wpedantic -L/usr/lib/R/lib -lR ${C_FLAGS}")
    set(CMAKE_CXX_FLAGS "-O3 -I/usr/share/R/include -fPIC -Wall -Wpedantic -L/usr/lib/R/lib -lR ${CXX_FLAGS}")
ENDIF()

file(GLOB SOURCE_LIB
    "*.cpp"
    "*.c"
)

set(LIBRARY_OUTPUT_PATH ${BIN_DIRECTORY})

add_library(${PRJ_NAME} SHARED ${SOURCE_LIB})
install(TARGETS ${PRJ_NAME} DESTINATION ${BIN_DIRECTORY})
