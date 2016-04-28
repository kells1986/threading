CC=g++
CFLAGS= -std=c++11 -Wall
LDFLAGS= -lpthread


all: threads.cpp
	g++ threads.cpp $(CFLAGS) $(LDFLAGS) -o threads

openmp: openmp.cpp
	g++ openmp.cpp $(CFLAGS) $(LDFLAGS) -fopenmp -o openmp