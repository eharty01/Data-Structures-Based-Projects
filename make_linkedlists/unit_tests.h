/*
 *  unit_tests.h
 *  Eleanor Harty
 *  Sept. 24, 2023
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to linked up in Fur
 *
 *  Create tests to ensure that my code is running properly.
 *
*/

#include "CharLinkedList.h"
#include <cassert>

//first constructor and destructor tests
//check that default constructor initializes an empty linked list of size 0
void CharLinkedList_correct_1() {

    CharLinkedList test_list;
    assert(test_list.size() == 0);
    assert(test_list.isEmpty());
}


//second constructor tests
//check that the second constructor initializes a linked list with 1 node
void CharLinkedList_correct_2() {

    CharLinkedList test_list('e');
    assert(test_list.size() == 1);
    assert(test_list.elementAt(0) == 'e');
}


//third constructor tests
//check that the 3rd constructor when given a linked list will construct a
//linked list of the same size with the correct data in the correct order 
void CharLinkedList_correct_3() {
    char arr[7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

    CharLinkedList test_list(arr, 7);
    assert(test_list.size() == 7);
    assert(test_list.elementAt(3) == 'd');
}

//copy constructor test
//see if a deep copy is made when you change something
void CharLinkedList_copy_constructor() {
    char arr[3] = {'c', 'a', 't'};
    CharLinkedList test_list_1(arr, 3);
    CharLinkedList test_list_2(test_list_1);

    assert(test_list_1.toString() == "[CharLinkedList of size 3 <<cat>>]");
    assert(test_list_2.toString() == "[CharLinkedList of size 3 <<cat>>]");

    test_list_1.replaceAt('n', 2);
    assert(test_list_1.toString() == "[CharLinkedList of size 3 <<can>>]");
    assert(test_list_2.toString() == "[CharLinkedList of size 3 <<cat>>]");
}

//assignment operator test
//see if a deep copy is made when you change something
void CharLinkedList_assigment_operator() {
    char arr[3] = {'c', 'a', 't'};
    CharLinkedList test_list_1(arr, 3);
    CharLinkedList test_list_2;
    test_list_2 = test_list_1;

    assert(test_list_1.toString() == "[CharLinkedList of size 3 <<cat>>]");
    assert(test_list_2.toString() == "[CharLinkedList of size 3 <<cat>>]");

    test_list_1.replaceAt('n', 2);
    assert(test_list_1.toString() == "[CharLinkedList of size 3 <<can>>]");
    assert(test_list_2.toString() == "[CharLinkedList of size 3 <<cat>>]");
}

//isEmpty tests
//check isEmpty on an empty linked list
void isEmpty_correct() {
    CharLinkedList test_list;
    assert(test_list.isEmpty());
}

//check isEmpty on a linked list with 1 element
void isEmpty_incorrect_1_char() {
    CharLinkedList test_list('b');
    assert(not test_list.isEmpty());
}

//check isEmpty on a linked list with many elements
void isEmpty_incorrect_many_char() {
    char arr[7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

    CharLinkedList test_list(arr, 7);
    assert(not test_list.isEmpty());
}

//clear tests
//check clear on an empty linked list and check that it remains
//an empty linked list with a size of 0
void clear_empty_array() {
    CharLinkedList test_list;

    test_list.clear();
    assert(test_list.isEmpty());
    assert(test_list.size() == 0);
}

//check clear on a linked list with one element and check if it
//now passes isEmpty and a size of 0 after clear
void clear_single_char() {
    CharLinkedList test_list('b');
    assert(test_list.size() == 1);

    test_list.clear();
    assert(test_list.isEmpty());
    assert(test_list.size() == 0);
}

//check clear on a linked list with many elements and check if it
//now passes isEmpty and a size of 0 after clear
void clear_many_char() {
    char arr[7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

    CharLinkedList test_list(arr, 7);
    assert(test_list.size() == 7);

    test_list.clear();
    assert(test_list.isEmpty());
    assert(test_list.size() == 0);
}

//size tests
//check size of an empty linked list
void size_empty_array() {
    CharLinkedList test_list;

    assert(test_list.size() == 0);
}

//check size of a linked list initialized with one element
void size_single_char() {
    CharLinkedList test_list('f');

    assert(test_list.size() == 1);
}

//check size of a linked list with multiple elements
void size_many_char() {
    char arr[7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

    CharLinkedList test_list(arr, 7);
    assert(test_list.size() == 7);
}

//first tests
//check for the first element of an empty linked list list
void first_empty_array() {
    CharLinkedList test_list;
    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.first();
    }
    catch (const std::runtime_error &e) {
    runtime_error_thrown = true;
    error_message = e.what();
    }
    
    assert(runtime_error_thrown);
    std::cerr << error_message << std::endl;
    assert(error_message == "cannot get first of empty LinkedList");
}

//check for the first element of a linked list list with one element
void first_single_char() {
    CharLinkedList test_list('f');

    assert(test_list.first() == 'f');
}

//check for the first element of a linked list list with multiple elements
void first_many_char() {
    char arr[7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

    CharLinkedList test_list(arr, 7);
    assert(test_list.first() == 'a');
}

//last tests
//check for the last element of an empty linked list
void last_empty_array() {
    CharLinkedList test_list;
    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.last();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    
    assert(runtime_error_thrown);
    std::cerr << error_message << std::endl;
    assert(error_message == "cannot get last of empty LinkedList");
}

//check for last element of a single character linked list
void last_single_char() {
    CharLinkedList test_list('f');

    assert(test_list.last() == 'f');
}

//check for last element of a linked list with many characters
void last_many_char() {
    char arr[7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

    CharLinkedList test_list(arr, 7);
    assert(test_list.last() == 'g');
}

//elementAt tests
//check elementAt's reaction to an empty linked list
void elementAt_empty_array() {
    CharLinkedList test_list;
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.elementAt(0);
    }
    catch (const std::runtime_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
    
    assert(range_error_thrown);
    std::cerr << error_message << std::endl;
    assert(error_message == "index (0) not in range [0..0)");
}

//check elementAt's response to a single character linked list
void elementAt_single_char() {
    CharLinkedList test_list('g');

    assert(test_list.elementAt(0) == 'g');
}

//check if elementAt can select the correct character from a large linked list
void elementAt_many_char() {
    char arr[7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

    CharLinkedList test_list(arr, 7);
    assert(test_list.elementAt(5) == 'f');
}

//check elementAt's response to a request that is out of range
void elementAt_out_of_range() {
    char arr[7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

    CharLinkedList test_list(arr, 7);
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.elementAt(7);
    }
    catch (const std::runtime_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
    
    assert(range_error_thrown);
    std::cerr << error_message << std::endl;
    assert(error_message == "index (7) not in range [0..7)");
}

//toString
//check what toString produces for an empty linked list
void toString_empty_array() {
    CharLinkedList test_list;

    assert(test_list.toString() == "[CharLinkedList of size 0 <<>>]");
}

//check what toString prodcues for a single character linked list
void toString_single_char() {
    CharLinkedList test_list('a');

    assert(test_list.toString() == "[CharLinkedList of size 1 <<a>>]");
}

//check what toString produces for a linked list with multiple characters
void toString_multiple_elements() {
    char arr[5] = {'S', 'u', 's', 'a', 'n'};

    CharLinkedList test_list(arr, 5);
    assert(test_list.toString() == "[CharLinkedList of size 5 <<Susan>>]");
}

//toReverseString tests
//test toReverseString on an empty linked list
void toReverseString_empty_array() {
    CharLinkedList test_list;

    assert(test_list.toReverseString() == "[CharLinkedList of size 0 <<>>]");
}

//test to ReverseString on a linked list with one element
void toReverseString_single_char() {
    CharLinkedList test_list('s');

    assert(test_list.toReverseString() == "[CharLinkedList of size 1 <<s>>]");
}

//test toReverseString on a linked list with multiple elements
void toReverseString_many_char() {
    char arr[5] = {'c', 'a', 't'};

    CharLinkedList test_list(arr, 3);
    assert(test_list.toReverseString() == "[CharLinkedList of size 3 <<tac>>]");
}

//pushAtBack tests
//check how pushAtBack interacts with an empty linked list list
void pushAtBack_empty_array() {
    CharLinkedList test_list;

    test_list.pushAtBack('c');
    assert(test_list.size() == 1);
    assert(test_list.toString() == "[CharLinkedList of size 1 <<c>>]");
}

//check how pushAtBack interacts with a single character list
void pushAtBack_single_char_array() {
    CharLinkedList test_list('p');

    test_list.pushAtBack('d');
    assert(test_list.toString() == "[CharLinkedList of size 2 <<pd>>]");
}

//check how pushAtBack interacts with a linked list with many elements
void pushAtBack_many_char() {
    char arr[5] = {'S', 'u', 's', 'a', 'n'};

    CharLinkedList test_list(arr, 5);
    test_list.pushAtBack('M');
    assert(test_list.toString() == "[CharLinkedList of size 6 <<SusanM>>]");
}

//pushAtFront tests
//check if pushAtFront runs correctly foran empty arrays
void pushAtFront_empty_array() {
    CharLinkedList test_list;

    test_list.pushAtFront('c');
    assert(test_list.size() == 1);
    assert(test_list.first() == 'c');
}

//check if pushAtFront runs correctly for single character arrays
void pushAtFront_single_char() {
    CharLinkedList test_list('p');

    test_list.pushAtFront('d');
    assert(test_list.toString() == "[CharLinkedList of size 2 <<dp>>]");
}

//check if pushAtFront runs correctly for arrays with many characters
void pushAtFront_many_char() {
    char arr[5] = {'S', 'u', 's', 'a', 'n'};

    CharLinkedList test_list(arr, 5);
    test_list.pushAtFront('M');
    assert(test_list.toString() == "[CharLinkedList of size 6 <<MSusan>>]");
}

//insertAt tests

void insertAt_empty_correct() { 

    CharLinkedList test_list;
    test_list.insertAt('a', 0);
    assert(test_list.size() == 1);
    assert(test_list.elementAt(0) == 'a');

}

// Tests incorrect insertion into an empty AL.
// Attempts to call insertAt for index larger than 0.
// This should result in an std::range_error being raised.
void insertAt_empty_incorrect() {

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharLinkedList test_list;
    try {
    // insertAt for out-of-range index
    test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
    // if insertAt is correctly implemented, a range_error will be thrown,
    // and we will end up here
    range_error_thrown = true;
    error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    std::cerr << error_message << std::endl;
    assert(error_message == "index (42) not in range [0..0]");
    
}

// Tests correct insertAt for front of 1-element list.
void insertAt_front_singleton_list() {
    // initialize 1-element list
    CharLinkedList test_list('a');

    // insert at front
    test_list.insertAt('b', 0);

    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'b');
    assert(test_list.elementAt(1) == 'a');
}

// Tests correct insertAt for back of 1-element list.
void insertAt_back_singleton_list() {
    
    // initialize 1-element list
    CharLinkedList test_list('a');

    // insert at back
    test_list.insertAt('b', 1);

    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    
}

// Tests calling insertAt for a large number of elements.
// Not only does this test insertAt, it also checks that
// array expansion works correctly.
void insertAt_many_elements() {
    
    CharLinkedList test_list;

    // insert 1000 elements
    for (int i = 0; i < 1000; i++) {
        // always insert at the back of the list
        test_list.insertAt('a', i);
    }

    assert(test_list.size() == 1000);

    for (int i = 0; i < 1000; i++) {
        assert(test_list.elementAt(i) == 'a');
    }
    
}

// Tests insertion into front of a larger list
void insertAt_front_large_list() {
    char test_arr[9] = { 'a', 'b', 'c', 'z', 'd', 'e', 'f', 'g', 'h' };
    CharLinkedList test_list(test_arr, 9);

    test_list.insertAt('y', 0);


    assert(test_list.size() == 10);
    assert(test_list.elementAt(0) == 'y');
    assert(test_list.toString() == 
    "[CharLinkedList of size 10 <<yabczdefgh>>]");

}

// Tests insertion into the back of a larger list
void insertAt_back_large_list() {

    char test_arr[10] = { 'y', 'a', 'b', 'c', 'z', 'd', 'e', 'f', 'g', 'h' };
    CharLinkedList test_list(test_arr, 10);  

    test_list.insertAt('x', 10);

    assert(test_list.size() == 11);
    assert(test_list.elementAt(10) == 'x');
    assert(test_list.toString() == 
    "[CharLinkedList of size 11 <<yabczdefghx>>]"); 

}

// Tests insertion into the middle of a larger list
void insertAt_middle_large_list() {
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharLinkedList test_list(test_arr, 8);

    test_list.insertAt('z', 3);

    assert(test_list.size() == 9);
    assert(test_list.elementAt(3) == 'z');
    assert(test_list.toString() == "[CharLinkedList of size 9 <<abczdefgh>>]");

}

// Tests out-of-range insertion for a non-empty list.
void insertAt_nonempty_incorrect() {
   
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharLinkedList test_list(test_arr, 8);

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    try {
        test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..8]");
    
}

//insertInOrder tests
//see if insertInOrder correctly places a character into an empty list
void insertInOrder_empty_array() {
    CharLinkedList test_list;

    test_list.insertInOrder('j');
    assert(test_list.toString() == "[CharLinkedList of size 1 <<j>>]");
}

//see where insertInOrder places a 'lower' character than the current one
void insertInOrder_single_char_back() {
    CharLinkedList test_list('j');

    test_list.insertInOrder('y');
    assert(test_list.toString() == "[CharLinkedList of size 2 <<jy>>]");
}

//see where insertInOrder places a 'higher' character than the current one
void insertInOrder_single_char_front() {
    CharLinkedList test_list('j');

    test_list.insertInOrder('e');
    assert(test_list.toString() == "[CharLinkedList of size 2 <<ej>>]");
}

//see where insertInOrder places a character in a linked list of multiple
//different elements
void insertInOrder_many_char() {
    char arr[5] = {'s', 'u', 's', 'y', 'n'};

    CharLinkedList test_list(arr, 5);
    test_list.insertInOrder('x');
    assert(test_list.toString() == "[CharLinkedList of size 6 <<susxyn>>]");
}

//popFromFront tests
//see how popFromFront deals with an empty linked list
void popFromFront_empty_array() {
    CharLinkedList test_list;
    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.popFromFront();
    }
    catch (const std::runtime_error &e) {
    runtime_error_thrown = true;
    error_message = e.what();
    }
    
    assert(runtime_error_thrown);
    std::cerr << error_message << std::endl;
    assert(error_message == "cannot pop from empty LinkedList");
}

//see how popFromFront handles a single character linked list
void popFromFront_single_char() {
    CharLinkedList test_list('j');

    test_list.popFromFront();
    assert(test_list.isEmpty());
    assert(test_list.toString() == "[CharLinkedList of size 0 <<>>]");

}

//see how popFromFront deals with a linked list of multiple elements
void popFromFront_many_char() {
    char arr[5] = {'S', 'u', 's', 'a', 'n'};

    CharLinkedList test_list(arr, 5);
    test_list.popFromFront();
    assert(test_list.toString() == "[CharLinkedList of size 4 <<usan>>]");
}

//popFromBack tests
//see if runtime error works for popFromBack foan empty linked list lists
void popFromBack_empty_array() {
    CharLinkedList test_list;
    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.popFromBack();
    }
    catch (const std::runtime_error &e) {
    runtime_error_thrown = true;
    error_message = e.what();
    }
    
    assert(runtime_error_thrown);
    std::cerr << error_message << std::endl;
    assert(error_message == "cannot pop from empty LinkedList");
}

//check popFromBack's response to a linked list list with a single char
void popFromBack_single_char() {
    CharLinkedList test_list('j');

    test_list.popFromBack();
    assert(test_list.isEmpty());
    assert(test_list.toString() == "[CharLinkedList of size 0 <<>>]");
}

//check popFromBack's response to a linked list list with many char
void popFromBack_many_char() {
    char arr[5] = {'S', 'u', 's', 'a', 'n'};

    CharLinkedList test_list(arr, 5);
    test_list.popFromBack();
    assert(test_list.toString() == "[CharLinkedList of size 4 <<Susa>>]");
}

//removeAt tests
//test how removeAt treats an empty linked list
void removeAt_empty_array() {
    CharLinkedList test_list;
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.removeAt(0);
    }
    catch (const std::runtime_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
    
    assert(range_error_thrown);
    std::cerr << error_message << std::endl;
    assert(error_message == "index (0) not in range [0..0)");
}

//test how removeAt handles a single character linked list
void removeAt_single_char() {
    CharLinkedList test_list('j');

    test_list.removeAt(0);
    assert(test_list.isEmpty());
    assert(test_list.toString() == "[CharLinkedList of size 0 <<>>]");
}

//test what removeAt does with a linked list of many characters
void removeAt_many_char() {
    char arr[5] = {'S', 'u', 's', 'a', 'n'};

    CharLinkedList test_list(arr, 5);
    test_list.removeAt(2);
    assert(test_list.toString() == "[CharLinkedList of size 4 <<Suan>>]");
}

//test how removeAt reacts to a range error
void removeAt_range_error() {
    char arr[5] = {'S', 'u', 's', 'a', 'n'};

    CharLinkedList test_list(arr, 5);

    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.removeAt(6);
    }
    catch (const std::runtime_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
    
    assert(range_error_thrown);
    std::cerr << error_message << std::endl;
    assert(error_message == "index (6) not in range [0..5)");
}

//replaceAt tests
//see how replaceAt handles an empty linked list
void replaceAt_empty_array() {
    CharLinkedList test_list;    
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.replaceAt('l', 0);
    }
    catch (const std::runtime_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
    
    assert(range_error_thrown);
    std::cerr << error_message << std::endl;

    assert(error_message == "index (0) not in range [0..0)");
}

//check replaceAt's response to a single character linked list
void replaceAt_single_char() {
    CharLinkedList test_list('j');

    test_list.replaceAt('l', 0);
    assert(test_list.toString() == "[CharLinkedList of size 1 <<l>>]");
}

//check replaceAt's response to a linked list of multiple elements
void replaceAt_many_char() {
    char arr[5] = {'S', 'u', 's', 'a', 'n'};

    CharLinkedList test_list(arr, 5);
    test_list.replaceAt('l', 1);
    assert(test_list.toString() == "[CharLinkedList of size 5 <<Slsan>>]");
}

//check replaceAt's response to a range error
void replaceAt_range_error() {
    char arr[5] = {'S', 'u', 's', 'a', 'n'};

    CharLinkedList test_list(arr, 5);

    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        test_list.replaceAt('l', 6);
    }
    catch (const std::runtime_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
    
    assert(range_error_thrown);
    std::cerr << error_message << std::endl;
    assert(error_message == "index (6) not in range [0..5)");
}


//concatenate tests
//test how an empty first linked list concatenates with the given linked list
void concatenate_empty_array() {
    CharLinkedList test_list_1;

    char arr_other[3] = {'c', 'a', 't'};
    CharLinkedList test_list_2(arr_other, 3);

    test_list_1.concatenate(&test_list_2);
    assert(test_list_1.toString() == "[CharLinkedList of size 3 <<cat>>]");
}

//test how a initialized first linked list would concantenate with an empty 
//linked list
void concatenate_with_empty_array() {
    char arr[5] = {'S', 'u', 's', 'a', 'n'};
    CharLinkedList test_list_1(arr, 5);

    CharLinkedList test_list_2;

    test_list_1.concatenate(&test_list_2);
    assert(test_list_1.toString() == "[CharLinkedList of size 5 <<Susan>>]");
}

//test how a one character linked list would concatenate with another 
//linked list
void concatenate_single_char() {
    CharLinkedList test_list_1('M');

    char arr[5] = {'S', 'u', 's', 'a', 'n'};
    CharLinkedList test_list_2(arr, 5);

    test_list_1.concatenate(&test_list_2);
    assert(test_list_1.toString() == "[CharLinkedList of size 6 <<MSusan>>]");
}

//test how a linked list of multiple elements would concatenate with a linked 
//list of one element
void concatenate_with_single_char() {
    char arr[5] = {'S', 'u', 's', 'a', 'n'};
    CharLinkedList test_list_1(arr, 5);

    CharLinkedList test_list_2('M');

    test_list_1.concatenate(&test_list_2);
    assert(test_list_1.toString() == "[CharLinkedList of size 6 <<SusanM>>]");
}

//test how two arrays of multiple elements would concatenate
void concatenate_many_char() {
    char arr[5] = {'S', 'u', 's', 'a', 'n'};
    CharLinkedList test_list_1(arr, 5);

    char arr_other[3] = {'c', 'a', 't'};
    CharLinkedList test_list_2(arr_other, 3);

    test_list_1.concatenate(&test_list_2);
    assert(test_list_1.toString() == "[CharLinkedList of size 8 <<Susancat>>]");
}


//test how the same linked list would concatenate with itself
void concatenate_same_array() {
    char arr[3] = {'c', 'a', 't'};
    CharLinkedList test_list_1(arr, 3);

    test_list_1.concatenate(&test_list_1);
    assert(test_list_1.toString() == "[CharLinkedList of size 6 <<catcat>>]");
}
