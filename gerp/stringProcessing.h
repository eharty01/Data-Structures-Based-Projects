/*
 * stringProcessing.h
 * Eleanor Harty and Allen Wang
 * Dec. 2, 2023
 * 
 * CS 15: Project 4 Gerp
 *
 * This file contains the function declaration of stripNonAlphaNum and
 * alphaNumCheck which are relied on by the gerp program ensure user inputs
 * align with the definition of a word that the program can use (ie it removes
 * any nonalphanumeric characters from the front or back of a user input). It
 * also includes the function toLower which allows the program to perform
 * insensitive searches where capitalization doesn't matter.
*/

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdexcept>


std::string stripNonAlphaNum(std::string input);
bool alphaNumCheck(char input);
std::string toLower(const std::string &str);