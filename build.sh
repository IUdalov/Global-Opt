#!/bin/bash

############################################
# enviroment variables
############################################

export MAKE_DEBUG_MODE=0 #  1 or 0

	####################
	# Library properties 
	export LIB_PRJ_DIR=${PWD}/cinterface
	export LIB_PRJ_NAME=opt

export BIN_DIRECTORY=${PWD}/bin
export BUILD_DIRECTORY=${PWD}/build
export CMAKE_FLAGS="-DCMAKE_CXX_COMPILER=/usr/bin/g++-4.8"
export CXX_FLAGS="-Wno-unused-but-set-variable -Wno-unused-variable"
export C_FLAGS="-std=c99 $CXX_FLAGS"

############################################
# cmake
############################################

rm -rf $BUILD_DIRECTORY;rm -rf $BIN_DIRECTORY; mkdir $BUILD_DIRECTORY; cd $BUILD_DIRECTORY;
cmake $CMAKE_FLAGS ${LIB_PRJ_DIR}

############################################
# make
############################################

make -j4
