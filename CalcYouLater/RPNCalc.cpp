/*
 * RPNCalc.cpp
 * Eleanor Harty
 * Oct. 17, 2023
 *
 * CS 15: Project 2 CalcYouLater
 *
 * This file contains an implementation of the RPNCalc class.
 */

#include "RPNCalc.h"
#include <istream>

using namespace std;

/*
 * name:      RPNCalc
 * purpuse:   default constructor to initialize program
 * arguments: none
 * returns:   nothing
 * effects:   ensures program will run/take user input
*/
RPNCalc::RPNCalc() {
    //set for while loop
    go = true;
}

/* 
 * name:      run
 * purpose:   start the program, print goodbye message
 * arguments: none
 * returns:   nothing
 * effects:   pints goodbye the program stops running
*/
void RPNCalc::run() {
    //call querey loop
    run_commands(cin);
    cerr << "Thank you for using CalcYouLater." << endl;
}

/* 
 * name:      run_commands
 * purpose:   receive commands given by the user and calls functions to perform
 *            them
 * arguments: an istream containing commands from the user or a file the user
 *            provides
 * returns:   nothing
 * effects:   manages user input
*/
void RPNCalc::run_commands(std::istream &command) {
    //initialize variables and run command loop
    string input = "";

    //receive input and call the corresponding function
    while(go and command >> input) {
        if (input == "quit") {
            go = false;
        } 
        else if (got_int(input, &place_holder)) {
            push_number(input);
        }
        else if (input == "#t") {
            push_bool(true);
        } 
        else if (input == "#f") {
            push_bool(false);
        } 
        else if (input == "not") {
            not_command();
        }
        else if (input == "print") {
            print();
        } 
        else if (input == "clear") {
            stack.clear();
        } 
        else if (input == "drop") {
            drop();
        } 
        else if (input == "dup") {
            dup();
        }
        else if (input == "swap") {
            swap();
        } 
        else if (input == "+" or input == "-" or input == "*" or input == "/" 
        or input == "mod") {
            math_operators(input);
        } 
        else if (input == "<" or input == ">" or input == "<=" 
        or input ==  ">=" or input == "==") {
            comparison_operators(input);
        } 
        else if (input == "{") {
            pass_to_parse(command);
        } 
        else if (input == "exec") {
            exec();
        } 
        else if (input == "file") {
            file();
        } 
        else if (input == "if") {
            if_command();
        }
        else if (input == "#") {
            display_error("invalid boolean #");
        } 
        else {
            cerr << input << ": unimplemented" << endl;
        }
    }
}

/* 
 * name:      push_number
 * purpose:   add a number given by the user to the stack
 * arguments: a string containing input given by the user
 * returns:   nothing
 * effects:   adds an new element to the stack
*/
void RPNCalc::push_number(string input) {
    //declare var
    stringstream hold;
    int num;

    //transfer input to a string stream to an integer
    hold << input;
    hold >> num;

    //use the integer to create and push a new datum element
    Datum new_top(num);
    stack.push(new_top);
}

/* 
 * name:      push_bool
 * purpose:   adds a boolean value based on user input to the stack
 * arguments: a boolean based on input given by the user that determines if the
 *            new boolean will contain true or false
 * returns:   nothing
 * effects:   adds a new datum to the stack
*/
void RPNCalc::push_bool(bool t_or_f) {
    //push a new datum based on user input
    Datum new_top(t_or_f);
    stack.push(new_top);
}

/* 
 * name:      not_command
 * purpose:   remove a boolean from the stack and place the opposite boolean on
 *            the stack
 * arguments: none
 * returns:   nothing
 * effects:   pushes a new datum on the stack
*/
void RPNCalc::not_command() {
    //if the top is valid, declare var and drop the top element
    if (invalid_top()) {
        return;
    }
    Datum temp = stack.top();
    drop();

    //check the datum is a bool
    try {
        temp.getBool();
    } catch (const std::runtime_error &e) {
        display_error(e.what());
        return;
    }

    //add the opposite bool to the stack
    bool old_bool = temp.getBool();
    Datum new_top(not old_bool);
    stack.push(new_top);
}

/* 
 * name:      print
 * purpose:   print the top element of the stack
 * arguments: none
 * returns:   nothing
 * effects:   informs user of the top element of the stack
*/
void RPNCalc::print() {
    //check top is valid, if so declare var
    if(invalid_top()) {
        return;
    }
    Datum top = stack.top();

    //print the top element
    cout << stack.top().toString() << endl;
}

/* 
 * name:      drop
 * purpose:   remove the top element of the stack
 * arguments: none
 * returns:   nothing
 * effects:   removes an element from the stack
*/
void RPNCalc::drop() {
    //check for errors when executing the command
    if(invalid_top()) {
        return;
    }
    stack.pop();
}

/* 
 * name:      dup
 * purpose:   duplicate the top element of the stack
 * arguments: none
 * returns:   nothing
 * effects:   pushes a copy of the top element onto the stack
*/
void RPNCalc::dup() {
    //check top is valid;
    if(invalid_top()) {
        return;
    }

    //create a copy of the top and push it to the top of the stack
    Datum dup = stack.top();
    stack.push(dup);
}

/* 
 * name:      swap
 * purpose:   swaps the top two elements on the stack
 * arguments: none
 * returns:   nothing
 * effects:   switches top stack elements
*/
void RPNCalc::swap() {
    //verify the top two elements are valid and remove them
    if(invalid_top()) {
        return;
    }
    Datum data1 = stack.top();
    drop();

    if(invalid_top()) {
        return;
    }
    Datum data2 = stack.top();
    drop();

    //reinsert them in reverse order
    stack.push(data1);
    stack.push(data2);
}

/* 
 * name:      math_operators
 * purpose:   verify the top two stack elements are integers, drop them, and 
 *            pass on the two integers for performing arithmetic
 * arguments: a string containing the operation input by the user
 * returns:   nothing
 * effects:   calls a function to perform the arithmetic
*/
void RPNCalc::math_operators(string input) {
    //verify the top two elements are valid and remove them
    if(invalid_top()) {
        return;
    }
    Datum data1 = stack.top();
    drop();

    if(invalid_top()) {
        return;
    }
    Datum data2 = stack.top();
    drop();

    //check that both elements are intgers
    try {
        data1.getInt();
        data2.getInt();
    } catch (const std::runtime_error &e) {
        display_error(e.what());
        return;
    }

    //call a function to perform the operation
    perform_math(data1, data2, input);
}

/* 
 * name:      math_operators
 * purpose:   perform the given mathematical operation on the top two elements
 *            and push the result to the stack
 * arguments: two integers from the top of the stack, and a 
 *            string representing the operation given by the user
 * returns:   nothing
 * effects:   performs simple calculations
*/
void RPNCalc::perform_math(Datum data1, Datum data2, string input) {
    //declare var
    int var1 = data1.getInt();
    int var2 = data2.getInt();

    //check which input was given and perform the corresponding operation
    if (input == "+") {
        stack.push(Datum (var2 + var1));
    } else if (input == "-") {
        stack.push(Datum (var2 - var1));
    } else if (input == "*") {
        stack.push(Datum (var2 * var1));
    } else if (input == "/") {
        if (var1 == 0) {
        display_error("division by 0.");
        } else {
            stack.push(Datum (var2/var1));
        }
    } else {
        if( var1 == 0) {
            display_error("division by 0.");
        } else {
            stack.push(Datum (var2%var1));
        }
    }
}

/* 
 * name:      comparison_operators
 * purpose:   verify (unless the user is checking equality) that the top two
 *            elements are integers then drop them, and push the result of 
 *            their comparison on the stack
 * arguments: a string containing the operator input by the user
 * returns:   nothing
 * effects:   adds a boolean value to the stack
*/
void RPNCalc::comparison_operators(string input) {
    //get the top two elements and remove them
    if (invalid_top()) {
        return;
    }
    Datum data1 = stack.top();
    drop();

    if (invalid_top()) {
        return;
    }
    Datum data2 = stack.top();
    drop();
    
    //check if they are integers (except in the case that the input was ==)
    if (input != "==") {
        try {
            data1.getInt();
            data2.getInt();
        } catch (const std::runtime_error &e) {
            display_error(e.what());
            return;
        }
    }

    //call a function to perform the operation and push it's result to the stack
    Datum result = perform_comparison(data1, data2, input);
    stack.push(result);
}

/* 
 * name:      perform_comparison
 * purpose:   verify if the given comparison is true or not
 * arguments: two elements removed from the top of the stack, and a 
 *            string representing the operation given by the user
 * returns:   a datum containing a boolean that indicates if the comparison was
 *            true or not
 * effects:   returns result of comparison
*/
Datum RPNCalc::perform_comparison(Datum data1, Datum data2, string input) {
    //declare var
    Datum result(false);

    //compare results if the input is ==
    if(input == "==") {
        if(data1 == data2) {
            return Datum(true);
        } else {
            return Datum(false);
        }
    } else {
        //declare var
        int var1 = data1.getInt();
        int var2 = data2.getInt();

        //compare the datums based on the input
        if (input == ">" and var2 > var1) {
            return Datum(true);
        } else if (input == "<" and var2 < var1) {
            return Datum(true);
        } else if (input == ">=" and var2 >= var1) {
            return Datum(true);
        } else if (input == "<=" and var2 <= var1) {
            return Datum(true);
        } else {
            return Datum(false);
        }
    }
}

/* 
 * name:      pass_to_parse
 * purpose:   parses a user given rstring and add it to the stack
 * arguments: a string containing input from the user
 * returns:   nothing
 * effects:   adds an rstring to the stack
*/
void RPNCalc::pass_to_parse(std::istream &r_string) {
    //call parseRString on input
    string parsed_input = parseRString(r_string);

    //add the rstring to the stack
    Datum new_top(parsed_input);
    stack.push(new_top);
}

/* 
 * name:      exec
 * purpose:   execute content of an rstring as a series of commands
 * arguments: none
 * returns:   nothing
 * effects:   gives result of the commands in the rstring to the stack
*/
void RPNCalc::exec() {
    //chech if the top is valid, if so declare var and drop it
    if (invalid_top()) {
        return;
    }
    Datum rstring = stack.top();
    drop();

    //check datum is an RString, execute it if it is, print error if it's not
    if(not rstring.isRString()) {
        display_error("cannot execute non rstring");
        return;
    } else {
        stringstream executable;

        executable << process_RString(rstring.getRString());
        if(executable.str() == "") {
            return;
        }

        run_commands(executable);
    }
}

/* 
 * name:      process_RString
 * purpose:   process the rstring so the calculator can take commands or a 
 *            filename from it
 * arguments: a string of user input
 * returns:   a string exec can use
 * effects:   creates a string
*/
string RPNCalc::process_RString(string temp) {
    //declare var
    stringstream result;
    int temp_length = temp.length() - 2;
    string garbage;

    //check it's not empty brackets
    if(temp.length() < 4) {
        return "";
    }

    //get the rstring without braces and the space next to the brace
    for(int i = 0; i < temp_length; i++) {
        if (i == 0 or i == 1) {
            garbage = temp[i];
        } else {
            result << temp[i];
        }
    }
    
    //return the processed rstring
    return result.str();
}

/* 
 * name:      file
 * purpose:   read and process commands from a file given by the user
 * arguments: none
 * returns:   nothing
 * effects:   opens and reads a file
*/
void RPNCalc::file() {
    //check if valid top, if so declare var and drop it
    if(invalid_top()) {
        return;
    }
    Datum temp = stack.top();
    drop();

    //check if the top is an rstring and if so open the file, if not print an
    //error message
    if (temp.isRString()) {
        //declare var and open file
        ifstream intake;
        string filename = process_RString(temp.getRString());

        intake.open(filename);

        //print error if unable to open or read the file
        if (not intake.is_open()) {
            cerr << "Unable to read " << filename << endl;
            return;
        }

        //pass the file to run commands and close file
        run_commands(intake);
        intake.close();

    } else {
        display_error("file operand not rstring");
    }
}

/* 
 * name:      if_command
 * purpose:   removes 2 rstrings from the stack and then a boolean (also from 
 *            the top of the stack) and executes the commands for one of the 
 *            rstrings based on the boolean's value
 * arguments: none
 * returns:   nothing
 * effects:   calls execute on an rstring
*/
void RPNCalc::if_command() {
    //check if the false rstring is valid
    if(invalid_if_input(1)) {
        return;
    }
    Datum rstring_false = stack.top();
    drop();
    
    //check if the true rstring is valid
    if(invalid_if_input(1)) {
        return;
    }
    Datum rstring_true = stack.top();
    drop();
    
    //check if the boolean is valid
    if(invalid_if_input(2)) {
        return;
    }
    Datum boolean = stack.top();
    drop();

    bool determiner = boolean.getBool(); //push the chosen rstring's result
    if(determiner) {
        stack.push(rstring_true);
        exec();
    } else {
        stack.push(rstring_false);
        exec(); 
    }
}

/* 
 * name:      display_error
 * purpose:   print appropriate error message
 * arguments: a string containing the desired error message
 * returns:   nothing
 * effects:   displays an error message
*/
void RPNCalc::display_error(string error_message) {
    //print the given error message
    cerr << "Error: " << error_message << endl;
}

/* 
 * name:      ~RPNCalc
 * purpose:   prevent memory leaks or errors
 * arguments: none
 * returns:   nothing
 * effects:   prevents memory problems
*/
RPNCalc::~RPNCalc() {

}

/* 
 * name:      got_int (taken from got_int.cpp)
 * purpose:   verify if a string is an integer or not
 * arguments: a string given by user and a pointer
 * returns:   a boolean indicating if the given string is an integer
 * effects:   indicates if a string is an integer
*/
bool RPNCalc::got_int(string s, int *resultp)
{
        /* Holds the first non-whitespace character after the integer */
        char extra;

        return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}

/* 
 * name:      invalid_top
 * purpose:   check if the stack is empty
 * arguments: none
 * returns:   a boolean returning if the stack is empty
 * effects:   prints an error message if's empty
*/
bool RPNCalc::invalid_top() {
    //check if empty
    if(stack.isEmpty()) {
        display_error("empty_stack");
        return true;
    }

    //if it's not empty return false
    return false;
}

/* 
 * name:      invalid_if_input
 * purpose:   check if a given input is valid for what the user wants to do
 * arguments: an integer indicating what type of input we're testing
 * returns:   a boolean returning if input is the correct type
 * effects:   prints an error message if it's incorrect
*/
bool RPNCalc::invalid_if_input(int which_input) {
    //check if there's a valid top
    if(invalid_top()){
        return true;
    }
    Datum demo_rstring = stack.top();

    //check depending on given int if we have an rstring or boolean
    if (which_input == 1) {
        if (not demo_rstring.isRString()) {
            display_error("expected rstring in if branch");
            drop();
            return true;
        }
    } else {
        if (not demo_rstring.isBool()) {
            display_error("expected boolean in if test");
            drop();
            return true;
        }
    }
    
    //return false if the input is valid
    return false;
}