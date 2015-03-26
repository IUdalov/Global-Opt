#!/bin/bash
FLAGS=-O3

all: direct_search agp_plain

direct_search: direct_search.c
	cc direct_search.c $(FLAGS) -o direct_search.bin -lm

agp_plain: agp_plain.cpp
	g++ agp_plain.cpp $(FLAGS) -o agp_plain.bin

clean:
	rm -f *.bin