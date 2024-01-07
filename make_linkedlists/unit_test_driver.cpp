
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
	{ "CharLinkedList_correct_1", CharLinkedList_correct_1 },
	{ "CharLinkedList_correct_2", CharLinkedList_correct_2 },
	{ "CharLinkedList_correct_3", CharLinkedList_correct_3 },
	{ "CharLinkedList_copy_constructor", CharLinkedList_copy_constructor },
	{ "CharLinkedList_assigment_operator", CharLinkedList_assigment_operator },
	{ "isEmpty_correct", isEmpty_correct },
	{ "isEmpty_incorrect_1_char", isEmpty_incorrect_1_char },
	{ "isEmpty_incorrect_many_char", isEmpty_incorrect_many_char },
	{ "clear_empty_array", clear_empty_array },
	{ "clear_single_char", clear_single_char },
	{ "clear_many_char", clear_many_char },
	{ "size_empty_array", size_empty_array },
	{ "size_single_char", size_single_char },
	{ "size_many_char", size_many_char },
	{ "first_empty_array", first_empty_array },
	{ "first_single_char", first_single_char },
	{ "first_many_char", first_many_char },
	{ "last_empty_array", last_empty_array },
	{ "last_single_char", last_single_char },
	{ "last_many_char", last_many_char },
	{ "elementAt_empty_array", elementAt_empty_array },
	{ "elementAt_single_char", elementAt_single_char },
	{ "elementAt_many_char", elementAt_many_char },
	{ "elementAt_out_of_range", elementAt_out_of_range },
	{ "toString_empty_array", toString_empty_array },
	{ "toString_single_char", toString_single_char },
	{ "toString_multiple_elements", toString_multiple_elements },
	{ "toReverseString_empty_array", toReverseString_empty_array },
	{ "toReverseString_single_char", toReverseString_single_char },
	{ "toReverseString_many_char", toReverseString_many_char },
	{ "pushAtBack_empty_array", pushAtBack_empty_array },
	{ "pushAtBack_single_char_array", pushAtBack_single_char_array },
	{ "pushAtBack_many_char", pushAtBack_many_char },
	{ "pushAtFront_empty_array", pushAtFront_empty_array },
	{ "pushAtFront_single_char", pushAtFront_single_char },
	{ "pushAtFront_many_char", pushAtFront_many_char },
	{ "insertAt_empty_correct", insertAt_empty_correct },
	{ "insertAt_empty_incorrect", insertAt_empty_incorrect },
	{ "insertAt_front_singleton_list", insertAt_front_singleton_list },
	{ "insertAt_back_singleton_list", insertAt_back_singleton_list },
	{ "insertAt_many_elements", insertAt_many_elements },
	{ "insertAt_front_large_list", insertAt_front_large_list },
	{ "insertAt_back_large_list", insertAt_back_large_list },
	{ "insertAt_middle_large_list", insertAt_middle_large_list },
	{ "insertAt_nonempty_incorrect", insertAt_nonempty_incorrect },
	{ "insertInOrder_empty_array", insertInOrder_empty_array },
	{ "insertInOrder_single_char_back", insertInOrder_single_char_back },
	{ "insertInOrder_single_char_front", insertInOrder_single_char_front },
	{ "insertInOrder_many_char", insertInOrder_many_char },
	{ "popFromFront_empty_array", popFromFront_empty_array },
	{ "popFromFront_single_char", popFromFront_single_char },
	{ "popFromFront_many_char", popFromFront_many_char },
	{ "popFromBack_empty_array", popFromBack_empty_array },
	{ "popFromBack_single_char", popFromBack_single_char },
	{ "popFromBack_many_char", popFromBack_many_char },
	{ "removeAt_empty_array", removeAt_empty_array },
	{ "removeAt_single_char", removeAt_single_char },
	{ "removeAt_many_char", removeAt_many_char },
	{ "removeAt_range_error", removeAt_range_error },
	{ "replaceAt_empty_array", replaceAt_empty_array },
	{ "replaceAt_single_char", replaceAt_single_char },
	{ "replaceAt_many_char", replaceAt_many_char },
	{ "replaceAt_range_error", replaceAt_range_error },

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
