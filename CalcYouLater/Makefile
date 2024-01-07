###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author:  Eleanor Harty

MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

#This rule builds the executable
CalcYouLater: main.o Datum.o DatumStack.o parser.o RPNCalc.o
	$(CXX) $(CXXFLAGS) -o CalcYouLater $^

#This Rule builds RPNcalc.o
RPNCalc.o: RPNCalc.cpp RPNCalc.h
	$(CXX) $(CXXFLAGS) -c RPNCalc.cpp

#This rule builds DatumStack.o
DatumStack.o: DatumStack.cpp DatumStack.h Datum.h
	$(CXX) $(CXXFLAGS) -c DatumStack.cpp 

#This rule runs unit tests
unit_test: unit_test_driver.o parser.o DatumStack.o Datum.o RPNCalc.o
	$(CXX) $(CXXFLAGS) $^

#This rule builds parser.o
parser.o: parser.cpp parser.h
	$(CXX) $(CXXFLAGS) -c parser.cpp 

#This rule builds main.o
main.o: main.cpp DatumStack.h Datum.h parser.h
	$(CXX) $(CXXFLAGS) -c main.cpp


## Rules for building an executable from Datum+vector_example.cpp
## This is useful in seeing the behavior of Datum::toString()
Datum+vector_example.o: Datum+vector_example.cpp Datum.h

Datum+vector_example: Datum+vector_example.o Datum.o
	${CXX} ${LDFLAGS} -o $@ $^

##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^

# remove executables, object code, and temporary files from the current folder 
# -- the executable created by unit_test is called a.out
clean: 
	rm *.o *~ a.out
