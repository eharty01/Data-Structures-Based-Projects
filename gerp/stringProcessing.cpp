/*
 * stringProcessing.cpp
 * Eleanor Harty and Allen Wang
 * Dec. 2, 2023
 * 
 * CS 15: Project 4 Gerp
 *
 * This file contains an implementation of the functions defined in 
 * stringProcessing.h.
*/

#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

#include "stringProcessing.h"

using namespace std;

/*
 * name:      stripNonAlphaNum
 * purpuse:   ensure a string is properly formatted for gerp to run
 * arguments: the word input by the user
 * returns:   a string that starts and ends with alphanumeric characters
 * effects:   parses the string to fit gerp's definition of a word
*/
string stripNonAlphaNum(string input) {
    //remove all nonalphanumeric characters at the front of the word
    while (not (alphaNumCheck(input[0]))) {
        input.erase(0, 1);
        
        //check there are still characters left in the input
        if(input.length() == 0) {
            return "";
        }
    }

    //remove all nonalphanumeric characters at the end of the word
    while (not (alphaNumCheck(input.back()))) {
        input.pop_back();
    }

    //return the parsed word
    return input;
}

/*
 * name:      alphaNumCheck
 * purpuse:   check if a character is alphanumeric or not
 * arguments: a character from the front or back of the given word
 * returns:   a boolean indicating if the char is alphanumeric or not
 * effects:   returns a boolean
*/
bool alphaNumCheck(char input) {
    //check that the input is between the correct ASCII values to be a letter
    //or number
    if ((('0' <= input) and (input <= '9')) or (('A' <= input) and 
    (input <= 'Z')) or (('a' <= input) and (input <= 'z'))) {
        return true;
    }

    //if not return false
    return false;
}

std::string toLower(const std::string &str) {
    std::string converted;
    for (char c : str) {
        converted += std::tolower(c);
    }
    return converted;
}