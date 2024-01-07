/*
 * DataumStack.cpp
 * Eleanor Harty
 * Oct. 17, 2023
 *
 * CS 15: Project 2 CalcYouLater
 *
 * This file contains an implementation of the DatumStack class.
 */

#include "DatumStack.h"

/*
 * name:      DatumStack
 * purpuse:   default constructor to initialize and empty stack
 * arguments: none
 * returns:   nothing
 * effects:   creates an empty stack
*/
DatumStack::DatumStack() {
    
}

/*
 * name:      DatumStack
 * purpuse:   initializes a stack with the arrays elements (element 0 pushed on
 *            first)
 * arguments: an array of datum and an integer indicating the array's size
 * returns:   nothing
 * effects:   creates a stack with the array passed into it
*/
DatumStack::DatumStack(Datum arr[], int arr_size) {
    //build DatumStack
    for (int i = 0; i < arr_size; i++) {
        push(arr[i]);
    }
}

/*
 * name:      isEmpty
 * purpuse:   check if the Datum is empty or not
 * arguments: none
 * returns:   a boolean that is true if it's empty, false if not
 * effects:   verifies if Datum is empty or not
*/
bool DatumStack::isEmpty() {
    //check size
    if(my_data.size() == 0) {
        return true;
    } else {
        return false;
    }
}

/*
 * name:      clear
 * purpuse:   make the current stack an empty stack
 * arguments: none
 * returns:   nothing
 * effects:   clear the stack and resets current element to nothing
*/
void DatumStack::clear() {
    my_data.clear();
}

/*
 * name:      size
 * purpuse:   determine the size of the stack
 * arguments: none
 * returns:   an int indicating the number of Datum elements in the stack
 * effects:   returns an int
*/
int DatumStack::size() {
    return my_data.size();
}

/*
 * name:      top
 * purpuse:   indicate the top Datum element on the stack
 * arguments: none
 * returns:   the top Datum element on the stack
 * effects:   retrurns a Datum
*/
Datum DatumStack::top() {
    //check for errors, if none return the front of the list
    if(isEmpty()) {
        throw std::runtime_error("empty_stack");
    } else {
        return my_data.front();
    }
}

/*
 * name:      pop
 * purpuse:   remove the top element on the stack
 * arguments: none
 * returns:   nothing
 * effects:   
*/
void DatumStack::pop() {
    //check for errors, if none remove the front of the list
    if(isEmpty()) {
        throw std::runtime_error("empty_stack");
    } else {
        my_data.pop_front();
    }
}

/*
 * name:      push
 * purpuse:   places a new Datum element on top of the stack
 * arguments: a Datum element
 * returns:   nothing
 * effects:   puts a new element on the stack
*/
void DatumStack::push(Datum data) {
    my_data.push_front(data);
}