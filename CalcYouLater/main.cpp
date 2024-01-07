/*
 * main.cpp
 * Eleanor Harty
 * Oct. 18, 2023
 * 
 * CS 15: Project 2 CalcYouLater
 *
 * This contains the main function to run the run function starting the
 * calculator.
 */

#include "RPNCalc.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/* 
 * name:      main
 * purpose:   to prompt the calculator to run
 * arguments: an int representing the numbers of files given and a pointer to 
 *            an array of characters representing the filenames given (unused)
 * returns:   an int
 * effects:   calls the run function
*/
int main (int argc, char *argv[]) {
    RPNCalc obj;

    obj.run();
    return 0;
}