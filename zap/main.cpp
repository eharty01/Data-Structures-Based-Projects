/*
 * main.cpp
 * Eleanor Harty
 * Nov. 10, 2023
 * 
 * CS 15: Project 3 Zap
 *
 * This contians the main function to check that the user is submitting 
 * correctly formatted requests and prompt zap to run.
 */

// boilerplate
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "HuffmanCoder.h"

using namespace std;

/*
 * name:      main
 * purpose:   to prompt the program zap to run and ensure the user provides
 *            enough files/the correct command for it to do so
 * arguments: an int representing the number of files given and a pointer to 
 *            an array of characters representing the file names given
 * returns:   an int
 * effects:   starts the zap program
*/
int main(int argc, char *argv[]) {
    //check for correct number of files
    if (argc != 4) {
        cerr << "Usage: ./zap [zap | unzap] inputFile outputFile" << endl;
        return EXIT_FAILURE;
    }

    //declare var
    HuffmanCoder obj;
    string command = argv[1];
    string inputFile = argv[2];
    string outputFile = argv[3];

    //they give a proper command and if so run the command the user requested
    if (argc == 4) {
        if (command == "zap") {
            obj.encoder(inputFile, outputFile);
        } else if (command == "unzap") {
            obj.decoder(inputFile, outputFile);
        } else {
            cerr << "Usage: ./zap [zap | unzap] inputFile outputFile" << endl;
            return EXIT_FAILURE;
        }
    }

    return 0;
}