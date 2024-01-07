/*
 * parser.h
 * Eleanor Harty
 * Oct. 17, 2023
 *
 * CS 15: Project 2 CalcYouLater
 *
 * This class represents a parser which is used by the calculator when it is 
 * given an rstring. It formats the user provided rstring in a way that is 
 * usable to the calculator and returns it so the calculator can perform 
 * operations the parsed rstring.
 */

//include statement
#include <string>
using namespace std;

//function call
string parseRString(istream &input);
