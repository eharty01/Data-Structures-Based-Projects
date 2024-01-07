/*
 * unit_tests.h
 * Eleanor Harty
 * Oct. 17, 2023
 *
 * CS 15: Project 2 CalcYouLater
 *
 * Create tests to ensure that my code is running properly.
 */

#include "DatumStack.h"
#include "parser.h"
#include "Datum.h"
#include <cassert>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

//test DatumStack class
//test default constructor
void default_datumstack_constructor() {
    DatumStack d;

    assert(d.size() == 0);
    assert(d.isEmpty());
}

//test parameterized constructor
void datumstack_constructor() {
    Datum a(1);
    Datum b(2);
    Datum c(3);
    
    Datum arr[3] = {a,b,c};
    DatumStack d(arr, 3);

    assert(d.size() == 3);
}

//test isEmpty when the array is empty
void isEmpty_true () {
    DatumStack d;

    assert(d.isEmpty());
}

//test isEmpty with one element in the array
void isEmpty_one_element() {
    Datum a(1);

    Datum arr[1] = {a};
    DatumStack d(arr, 1);

    assert(not d.isEmpty());
}

//test isEmpty with several elements in the array
void isEmpty_many_element() {
    Datum a(1);
    Datum b(2);
    Datum c(3);
    
    Datum arr[3] = {a,b,c};
    DatumStack d(arr, 3);

    assert(not d.isEmpty());
}

//test clear on an empty array
void clear_empty() {
    DatumStack d;

    d.clear();
    assert(d.isEmpty());
}

//test clear on a single element array
void clear_one_element() {
    Datum a(1);

    Datum arr[1] = {a};
    DatumStack d(arr, 1);

    d.clear();
    assert(d.isEmpty());
}

//test clear on a many element array
void clear_many_elements() {
    Datum a(1);
    Datum b(2);
    Datum c(3);
    
    Datum arr[3] = {a,b,c};
    DatumStack d(arr, 3);

    d.clear();
    assert(d.isEmpty());
}

//test size on an empty array
void size_empty() {
    DatumStack d;

    assert(d.size() == 0);
}

//test size on a single element array
void size_single_element() {
    Datum a(1);

    Datum arr[1] = {a};
    DatumStack d(arr, 1);

    assert(d.size() == 1);
}

//test size on an array of many elements
void size_many_elements() {
    Datum a(1);
    Datum b(2);
    Datum c(3);
    
    Datum arr[3] = {a,b,c};
    DatumStack d(arr, 3);

    assert(d.size() == 3);
}

//test top an an empty array
void top_empty() {
    bool runtime_error_thrown = false;
    std::string error_message = "";
    DatumStack d;

    try {
        // top for empty stack
        d.top();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    std::cerr << error_message << std::endl;
    assert(error_message == "empty_stack");
}

//test top an an array of one element
void top_single_element() {
    Datum a(1);

    Datum arr[1] = {a};
    DatumStack d(arr, 1);

    assert(d.top().getInt() == 1);
}

//test top on an array of many elements
void top_many_elements() {
    Datum a(1);
    Datum b(2);
    Datum c(3);
    
    Datum arr[3] = {a,b,c};
    DatumStack d(arr, 3);

    assert(d.top().getInt() == 3);
}

//test pop on an empty array
void pop_empty() {
    bool runtime_error_thrown = false;
    std::string error_message = "";
    DatumStack d;

    try {
        // pop for empty stack
        d.pop();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    std::cerr << error_message << std::endl;
    assert(error_message == "empty_stack");
}

//test pop on an array of one element
void pop_single_element() {
    Datum a(1);

    Datum arr[1] = {a};
    DatumStack d(arr, 1);

    d.pop();
    assert(d.size() == 0);
    assert(d.isEmpty());
}

//test pop on an array of many elements
void pop_many_elements() {
    Datum a(1);
    Datum b(2);
    Datum c(3);
    
    Datum arr[3] = {a,b,c};
    DatumStack d(arr, 3);

    d.pop();
    assert(d.size() == 2);
    assert(d.top().getInt() == 2);
}

//test push on an empty array
void push_empty() {
    DatumStack d;
    assert(d.isEmpty());
    assert(d.size() == 0);

    Datum a(1);
    d.push(a);

    assert(not d.isEmpty());
    assert(d.size() == 1);
    assert(d.top().getInt() == 1);
}

//test push on a single array
void push_single_element() {
    Datum a(1);

    Datum arr[1] = {a};
    DatumStack d(arr, 1);

    Datum b(2);
    d.push(b);

    assert(d.size() == 2);
    assert(d.top().getInt() == 2);
}

//test push on many elements
void push_many_elements() {
    Datum a(1);
    Datum b(2);
    Datum c(3);
    
    Datum arr[3] = {a,b,c};
    DatumStack d(arr, 3);

    Datum x(4);
    d.push(x);

    assert(d.size() == 4);
    assert(d.top().getInt() == 4);
}

//Parse class
//parse test basic rstring
void parse_test() {
    string test = " 1 2 + }";
    std::istringstream input(test);

    assert(parseRString(input) == "{ 1 2 + }");
}

//parse test strings/things without spaces
void parse_string() {
    string test = " Hello World! }";
    std::istringstream input(test);

    assert(parseRString(input) == "{ Hello World! }");
}

//parse test with nested rstring
void parse_nested() {
    string test = " 1 { 5 4 - } + }";
    std::istringstream input(test);

    assert(parseRString(input) == "{ 1 { 5 4 - } + }");
}

//parse test double nested rstring with integers and strings
void parse_double_dif_var() {
    string test = " 12 { inside { double nest } ! } * -4 }";
    std::istringstream input(test);

    assert(parseRString(input) == "{ 12 { inside { double nest } ! } * -4 }");
}

//parse test input after closed brackets
void parse_extra() {
    string test = " 5 5 + } hi";
    std::istringstream input(test);

    assert(parseRString(input) == "{ 5 5 + }");
}