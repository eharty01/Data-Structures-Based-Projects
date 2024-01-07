/*
 * main.cpp
 * Eleanor Harty
 * Oct. 7, 2023
 * 
 * CS 15: Project 1 MetroSim
 *
 * Check for any errors opening files
 */

// boilerplate
#include <iostream>
#include <fstream>
#include <string>

#include "MetroSim.h"

using namespace std;

/*
 * name:      open_or_die
 * purpose:   check if the file will open and if not throw an error
 * arguments: an stream variable and the name of the file we're trying to open
 * returns:   nothing
 * effects:   show an error if the file won't open
*/
template<typename streamtype>
void open_or_die(streamtype &stream, string file_name) {
        //open the file and if it won't open show an error
        stream.open(file_name);
        if (not stream.is_open()) {
                cerr << "Error: could not open file " << file_name << endl;
                exit(EXIT_FAILURE);
        }
}

/*
 * name:      main
 * purpose:   open and close files
 * arguments: the files provided by the user (int argc and char *argv[])
 * returns:   an int
 * effects:   calls MetroSim if files are correct
*/
int main(int argc, char *argv[]) {
        //declare variables
        MetroSim obj;
        ifstream instream;
        ofstream outstream;
        ifstream stations_file;

        //check if there are the proper amount of arguments, and if you can
        //open all the files, if so call the sim, if not exit
        if ((argc < 3) or (argc > 4)) {
                cerr << "Usage: ./MetroSim stationsFile outputFile " <<
                "[commandsFile]" << endl;
                return EXIT_FAILURE;
        }
        open_or_die(stations_file, argv[1]);
        open_or_die(outstream, argv[2]);

        if (argc == 4) {
                open_or_die(instream, argv[3]);

                obj.sim(stations_file, outstream, instream);
                instream.close();
        } else if (argc == 3) {
                obj.sim(stations_file, outstream, cin);
        }

        //close files
        outstream.close();
        stations_file.close();
        return 0;
}