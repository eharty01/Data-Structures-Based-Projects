/*
 * RPNCalc.h
 * Eleanor Harty
 * Oct. 20, 2023
 *
 * CS 15: Project 2 CalcYouLater
 *
 * This class represents a calculator that uses Reverse Polish Notation. The 
 * user can input integers, boolean values, and rstrings. The calculator can
 * perform arithmetic on integers given by the user and comparisons on any type
 * of input the user gives. The user can see the results of their requests by
 * requesting to print (print will also show the must recently added input no 
 * matter whay), it can also duplicate an input given to it, swap the most 
 * recent inputs, remove an input, or swap the value of a boolean
 * input. They can also perform commands nested in rstrings, input a file with
 * commands for the program to run, and execute one of two rstrings given based
 * on the value of a user given boolean. This class is implemented using a stack
 * so clients will have fast access to the most recent inputs.
 */

#ifndef RPNCALC_H
#define RPNCALC_H
//include statements
#include "DatumStack.h"
#include "parser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <list>
#include <cctype>

using namespace std;

class RPNCalc {
    //declare public functions and member variables
    public:
        //default constructor, destructor, and a run to start the program
        RPNCalc();
        ~RPNCalc();
        void run();

    //declare private functions and member variables
    private:
        //query loop to run the calculator
        void run_commands(std::istream &command);

        //simpler commands
        void push_number(string input);
        void push_bool(bool t_or_f);
        void not_command();
        void print();
        void drop();
        void dup();
        void swap();
        void math_operators(string input);
        void comparison_operators(string input);

        //harder commands
        void pass_to_parse(std::istream &r_string);
        void exec();
        void file();
        void if_command();

        //initialize DatumStack
        DatumStack stack;

        //non spec functions
        void display_error(string error);
        void perform_math(Datum data1, Datum data2, string input);
        Datum perform_comparison(Datum data1, Datum data2, string input);
        string process_RString(string temp);
        bool invalid_top();
        bool invalid_if_input(int which_input);

        //given function
        bool got_int(string s, int *resultp);

        //kill switch for query loop
        bool go;
        int place_holder;
};

#endif