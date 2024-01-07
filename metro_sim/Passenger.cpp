/*
 * Passenger.cpp
 * Eleanor Harty
 * Oct. 3 2024
 *
 * CS 15 Project 1: MetroSim
 *
 * This file contains an implementation of the Passenger class.
 */

#include <iostream>
#include <string>
#include "Passenger.h"

using namespace std;

/*
 * name:      print
 * purpose:   print the passenger's information
 * arguments: output stream to print passenger
 * returns:   nothing
 * effects:   prints information within the passenger struct
 */
void Passenger::print(std::ostream &output)
{
        //print out the info provided in the passenger struct
        output << "[" << id << ", " << from << "->" << to << "]";
}
