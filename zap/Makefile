###
### Makefile for Zap Project
### Zap encodes and decodes texts using Huffman trees
###
### Author:  Eleanor Harty
### Date:    Nov. 16 2023
### This file builds an executable with which one can compile and run the zap
### program.

MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

#This rule builds the executable
zap: main.o HuffmanTreeNode.o BinaryIO.o HuffmanCoder.o
	$(CXX) $(CXXFLAGS) -o zap $^

#This rule builds HuffmanCoder.o
HuffmanCoder.o: HuffmanCoder.cpp HuffmanCoder.h HuffmanTreeNode.o BinaryIO.o
	$(CXX) $(CXXFLAGS) -c HuffmanCoder.cpp

#This rule runs unit tests
unit_test: unit_test_driver.o phaseOne.o HuffmanTreeNode.o ZapUtil.o \
HuffmanCoder.o
	$(CXX) $(CXXFLAGS) $^

#This rule builds phaseOne.o
phaseOne.o: phaseOne.cpp phaseOne.h HuffmanTreeNode.h
	$(CXX) $(CXXFLAGS) -c phaseOne.cpp

#This rule builds main.o
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

# remove executables, object code, and temporary files from the current folder 
# -- the executable created by unit_test is called a.out
clean: 
	rm *.o *~ a.out