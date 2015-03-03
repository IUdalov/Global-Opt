CC=cc
LIBNAME=libopt.so
BIN_DIR=bin
BUILD_DIR=build
SRC_DIR=src
SRC_LIST=interface
INCLUDES=methos
CFLAGS=-I/usr/share/R/include -fPIC -Wall
LFLAGS=-L/usr/lib/R/lib -lR
CSTD=-std=gnu99


#gcc -std=gnu99 -shared -o methods.so methods.o -L/usr/lib/R/lib -lR
#gcc -std=gnu99 -I/usr/share/R/include -DNDEBUG      -fpic  -O3 -pipe  -g  -c methods.c -o methods.o

all: prep $(SRC_LIST).o
	$(CC) $(CSTD) -shared -o $(BIN_DIR)/$(LIBNAME) $(BUILD_DIR)/$(SRC_LIST).o $(LFLAGS)

$(SRC_LIST).o: $(SRC_DIR)/$(SRC_LIST).c
	$(CC) $(CSTD) $(CFLAGS) -c $(SRC_DIR)/$(SRC_LIST).c -o $(BUILD_DIR)/$(SRC_LIST).o

prep:
	mkdir -p $(BIN_DIR)
	mkdir -p $(BUILD_DIR)

clear:
	rm -rf $(BIN_DIR)
	rm -rf $(BUILD_DIR)