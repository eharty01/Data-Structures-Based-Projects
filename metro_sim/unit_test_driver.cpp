
/*
unit_test_driver.cpp
Matt Russell
COMP15 2020 Summer
Updated 12/16/2020

This file is used as the driver for unit testing.

The 'tests' map will be auto-populated in the form:

    { "test_name", test_name }

Where "test_name" maps to the associated test function in unit_tests.h.
*/

#include <map>
#include <string>
#include <iostream>
#include "unit_tests.h"

typedef void (*FnPtr)();

int main(int argc, char **argv) {

    /* will be filled in by the unit_test script */
    std::map<std::string, FnPtr> tests {
	{ "passenger_print_empty", passenger_print_empty },
	{ "passenger_print_passengers", passenger_print_passengers },
	{ "passengerQueue_dequeue_one", passengerQueue_dequeue_one },
	{ "passengerQueue_dequeue_many", passengerQueue_dequeue_many },
	{ "passengerQueue_enqueue_empty", passengerQueue_enqueue_empty },
	{ "passengerQueue_enqueue_one", passengerQueue_enqueue_one },
	{ "passengerQueue_enqueue_many", passengerQueue_enqueue_many },
	{ "passengerQueue_empty_size", passengerQueue_empty_size },
	{ "passengerQueue_one_size", passengerQueue_one_size },
	{ "passengerQueue_many_size", passengerQueue_many_size },
	{ "passengerQueue_empty_print", passengerQueue_empty_print },
	{ "passengerQueue_one_print", passengerQueue_one_print },
	{ "passengerQueue_many_print", passengerQueue_many_print },

    };

    /* first argument to main() is the string of a test function name */
    if (argc <= 1) {
        std::cout << "No test function specified. Quitting" << std::endl;
        return 1;
    }

    /* extract the associated fn pointer from "tests", and run the test */
    FnPtr fn = tests[argv[1]];
    fn();

    return 0;
}
