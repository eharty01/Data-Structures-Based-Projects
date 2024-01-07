/*
 * parser.cpp
 * Eleanor Harty
 * Oct. 17, 2023
 *
 * CS 15: Project 2 CalcYouLater
 *
 * This file contains an implementation of parser class.
 */

#include <string>
#include <sstream>
#include <iostream>
using namespace std;

/*
 * name:      parseRString
 * purpuse:   create formatted rstrings from inputs
 * arguments: a reference to an istream to continue reading input from
 * returns:   an rstring
 * effects:   returns a string
*/
std::string parseRString(std::istream &input) {
    //declare var
    std::string first_string;
    first_string = "{";
    string command;
    string hold;
    string start = "{";
    string close = "}";
    int starter = 1;
    int closer = 0;
    bool go = true;

    //run while loop to find when it closes (open and closing brackets are 
    //equal) or the file runs out
    while(go or input.fail()) {
        input >> command;

        hold = hold + " " + command;
        if (command == start) {
            starter++;
        } else if (command == close) {
            closer++;
        } if (starter == closer) {
            go = false;
        }
    }

    //return parsed rstring
    return first_string + hold;
}
