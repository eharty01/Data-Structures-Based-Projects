/*
 * main.cpp
 * Eleanor Harty and Allen Wang
 * Dec. 5, 2023
 * 
 * CS 15: Project 4 Gerp
 *
 * This contians the main function to check that the user is submitting 
 * correctly formatted requests and prompt gerp to run. It also provides the
 * Command class with the the necessary information to traverse through the 
 * directory and find subdirectories and files.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "Command.h"
#include "FSTree.h"
#include "DirNode.h"

using namespace std;

/*
 * name:      main
 * purpose:   open and close files
 * arguments: the files provided by the user (int argc and char *argv[])
 * returns:   an int
 * effects:   calls gerp if files are correct
*/
int main(int argc, char *argv[]) {
    //check for correct number of args
    if (argc != 3) {
        cerr << "Usage: ./gerp inputDirectory outputFile" << endl;
        return EXIT_FAILURE;
    }

    //check the directory will build, if so start program
    try {
        FSTree new_tree(argv[1]);
        DirNode *root = new_tree.getRoot();
        ofstream outputFile(argv[2]);
        Command obj;
        obj.start_gerp(root, outputFile);
    } catch (const std::runtime_error &e) {
        cerr << "Could not build index, exiting." << endl;
        return EXIT_FAILURE;
    }

    return 0;
}