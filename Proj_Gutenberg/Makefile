###
### Makefile for the Gerp Project
### Gerp searches for keywords from a user provided directory and places its
### results in an output file.
###
### Author:  Eleanor Harty and Allen Wang
### Date:    Dec. 4, 2023
### This file builds an executable with which one can compile and run the gerp
### program. 

MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

#This rule builds gerp
gerp: main.o Command.o stringProcessing.o DirNode.o FSTree.o
	$(CXX) $(CXXFLAGS) -o gerp $^

#This rule builds stringProcessing.o
stringProcessing.o: stringProcessing.cpp stringProcessing.h
	$(CXX) $(CXXFLAGS) -c stringProcessing.cpp

# This rule builds main.o
main.o: main.cpp Command.o FSTree.o DirNode.o
	$(CXX) $(CXXFLAGS) -c main.cpp

#This rule builds Command.o
Command.o: Command.cpp Command.h stringProcessing.o FSTree.o DirNode.o
	$(CXX) $(CXXFLAGS) -c Command.cpp

#This rule runs unit tests
unit_test: unit_test_driver.o stringProcessing.o FSTreeTraversal.o DirNode.o \
FSTree.o
	$(CXX) $(CXXFLAGS) $^

# remove executables, object code, and temporary files 
# from the current folder 
# -- the executable created by unit_test is called a.out
clean: 
	rm *.o *~ a.out