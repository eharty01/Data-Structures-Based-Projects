/*
 *  CharArrayList.cpp
 *  Eleanor Harty
 *  Sept. 17 2023
 *
 *  COMP 15 HW 1 Cheshire ConCATenation
 *
 *  This file contains an implementation of the CharArrayList class.
 *
 */

#include "CharArrayList.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;


    //implement constructors

    /*
     * name:      CharArrayList 
     * purpose:   initializes an empty array list
     * arguments: none
     * returns:   nothing
     * effects:   an array list with an initial capacity of 0 is initialized
     */
    CharArrayList::CharArrayList() {
        //initialize an array with a capacity of 0
        data = nullptr;
        num_items = 0;
        capacity = 0;
    }

    /*
     * name:      CharArrayList 
     * purpose:   initialize an array with one element and an initial 
     *            capacity of 1
     * arguments: a single character that will be the only element in the array
     * returns:   nothing
     * effects:   an array list with one element and a capacity of 1 is made
     */
    CharArrayList::CharArrayList(char c) {
        //create an array with an initial capacity of one
        num_items = 1;
        capacity = 5;

        //pass the given char as the sole element of the array
        data = new char[capacity];
        data[0] = c;
    }

    /*
     * name:      CharArrayList
     * purpose:   create an array list containing the characters in the array,
     *            the array should have an initialy capacity equal to the 
     *            length passed
     * arguments: an array of characters and an integer representing the length
     *            of that array
     * returns:   nothing
     * effects:   creates an array of characters based on the elements and
     *            size passed for that array
     */
    CharArrayList::CharArrayList (char arr[], int size) {
        //set capacity and num_items
        num_items = size;
        capacity = 2*size;

        //create new array to copy into
        data = new char[capacity];

        //copy array and count the number of char elements in it
        for (int i = 0; i < num_items; i++) {
            data[i] = arr[i];
        }
    }

    /*
     * name:      CharArrayList
     * purpose:   make a deep copy of the given instance
     * arguments: none
     * returns:   nothing
     * effects:   creates a deepy copy
     */
    CharArrayList::CharArrayList (const CharArrayList &other){
        data = new char[other.capacity];
        capacity = other.capacity;
        num_items = other.num_items;

        for (int i = 0; i < other.num_items; i++) {
            data[i] = other.data[i];
        }
    }

    //implement destructor

    /*
     * name:      ~CharArrayList
     * purpose:   delete/recycle all heap allocated data in the current array
     * arguments: none
     * returns:   nothing
     * effects:   gets rid of heap array data
     */
    CharArrayList::~CharArrayList() {
        //delete heap allocated array data
        delete []data;
    }

    //implement assignment operator
    /*
     * name:      CharArrayList
     * purpose:   make a deep copy of the instance on the right hand side into
     *            the instance on the left, and recycle storage for the left 
     * arguments: pointer to a char array list
     * returns:   nothing
     * effects:   makes a deep copy of the right hand side of the expression
     */
    CharArrayList &CharArrayList::operator=(const CharArrayList &other) {
        //check that that left and right hand side are the same object
        if (this == &other) {
            return *this;
        }

        //copy capacity and num_items
        this->num_items = other.num_items;
        this-> capacity = other.capacity;

        //clear array
        delete[] this->data;

        //reset it as a deep copy
        this->data = new char[other.capacity];

        for (int i = 0; i < num_items; i++) {
            this->data[i] = other.data[i];
        }

        //return copy
        return *this;
    }

    //public functions to identify or modify elements of the array

    /*
     * name:      isEmpty
     * purpose:   determine if the array is empty or contains characters
     * arguments: none
     * returns:   a boolean value that signifies if the array is empty or not
     * effects:   informs user if the array is empty or not
     */
    bool CharArrayList::isEmpty() const {
        //check if there are any indexes or elements in the array or not
        if (num_items == 0) {
            return true;
        }
        else {
            return false;
        }
    }

    /*
     * name:      clear
     * purpose:   to make the instance into an empty array list
     * arguments: none
     * returns:   nothing
     * effects:   after this is run on an array if isEmpty is called on that
     *            array it will return true
     */
    void CharArrayList::clear() {
        //set number of elements in the array to 0
        num_items = 0;
    }

    /*
     * name:      size
     * purpose:   state the number of characters in an array
     * arguments: none
     * returns:   an integer representing the amount of characters in the list
     * effects:   tells user the number of characters in the array
     */
    int CharArrayList::size() const {
        //create variable to return
       int size = num_items;

        //check if isEmpty is true and if not return the above variable
       if (isEmpty()) {
        return 0;
       }
       else {
        return size;
       }
    }

    /*
     * name:      first
     * purpose:   find the first character in an array
     * arguments: none
     * returns:   the first character in the array list
     * effects:   determines the first character in an array
     */
    char CharArrayList::first() const {
        //check if array is empty
        if (isEmpty()) {
            throw std::runtime_error("cannot get first of empty ArrayList");
        }
        else {
            //find the first element of the array and return it
            char first_element = front->data;
            return first_element;
        }
    }

    /*
     * name:      last
     * purpose:   find the last character in an array
     * arguments: none
     * returns:   the last character in the array
     * effects:   determines the last character in an array
     */
    char CharArrayList::last() const {
        //check if array is empty
        if (isEmpty()) {
            throw std::runtime_error("cannot get last of empty ArrayList");
        }
        else {
            //find the last element of the array and return it
            char last_element = back->data;
            return last_element;
        }
    }

    /*
     * name:      elementAt
     * purpose:   find the 
     * arguments: an integer representing the index of the array
     * returns:   the character element of the array at the input index
     * effects:   determines the element at the specified index
     */
    char CharArrayList::elementAt(int index) const {
        //check if array is empty if so throw error message
        if (index >= num_items or index < 0) {
            throw std::range_error("index (" + to_string(index) 
            + ") not in range " + "[0.." + to_string(num_items) + ")");
        }
        else {
            //find the specified index in the array and return it
            char indexed_element = data[index];
            return indexed_element;
        }
    }

    /*
     * name:      toString
     * purpose:   display all info contained in the array and it's size
     * arguments: none
     * returns:   a string which contains the characters of the CharArrayList
     * effects:   prints the contents and size of the array list
     */
    std::string CharArrayList::toString() const {
        //check isEmpty
        std::stringstream temp;
        if(isEmpty()) {
            temp << "[CharArrayList of size 0 <<>>]";
        }
        //else print each element of the array
        else {
            temp << "[CharArrayList of size " << num_items << " <<";
            for (int i = 0; i < num_items; i++) {
                temp << data[i];
            }
            temp << ">>]";
        }

        return temp.str();
    }

    /*
     * name:      toReverseString
     * purpose:   display all info contained in the array (in reverse) and 
     *            it's size
     * arguments: none
     * returns:   a string which contais the characters of the CharArrayList
     *            in reverse
     * effects:   prints the contents (in reverse) and size of the array list
     */
    std::string CharArrayList::toReverseString() const {
        //check isEmpty
        std::stringstream temp;
        if(isEmpty()) {
            temp << "[CharArrayList of size 0 <<>>]";
        }
        //else print each element of the array
        else {
            temp << "[CharArrayList of size " << num_items <<
            " <<";
            for (int i = (num_items - 1); i >= 0; i--) {
                temp << data[i];
            }
            temp << ">>]";
        }

        return temp.str();
    }

    /*
     * name:      pushAtBack
     * purpose:   insert the given new element after the end of the existing
     *            elements of the array list
     * arguments: an element char to place at the back of the array
     * returns:   nothing
     * effects:   increments num_items and adds a new element at the back
     *            of the exesting elements in the array
     */
    void CharArrayList::pushAtBack(char c) {
        //make sure the list has the capacity to add an element
        if (num_items == capacity) {
            ensureCapacity();
        }

        //insert the element after the last element in the array
        data[num_items] = c;
        //increment num_items since it's not 0 indexed
        num_items++;
    }

    /*
     * name:      pushAtFront
     * purpose:   insert the given new element in front of the existing 
     *            elements of the array list
     * arguments: an element char to place at the front of the array
     * returns:   nothing
     * effects:   increments num_items and adds a new elment at the front of
     *            of the array pushing back the other elements by 1
     */
    void CharArrayList::pushAtFront(char c) {
        //ensure the array has the capacity to add an element
        if (num_items == capacity) {
            ensureCapacity();
        }

        //copy the all the elements except for the first element into the next
        //highest index
        for (int i = num_items; i > 0; i--) {
            data[i] = data[i - 1];
        }

        //replace the first element of the array with the given char
        data[0] = c;
        //increment num_items since it's not 0 indexed
        num_items++;
    }

    /*
     * name:      insertAt
     * purpose:   insert a given char at a given index, pushing back all
     *            other data in the index
     * arguments: an element char to replace the element at the specified
     *            index and an integer representing the specified index
     * returns:   nothing
     * effects:   pushes back all elements of the array at and after the
     *            given index and increments num_items
     */
    void CharArrayList::insertAt(char c, int index) {
        //check if the index given is valid
        if (index > num_items or index > 0) {
            throw std::range_error("index (" + to_string(index) 
            + ") not in range " + "[0.." + to_string(num_items) + "]");
        }

        //ensure the array has the capacity to add an element
        if (num_items == capacity) {
            ensureCapacity();
        }

        //copy all the elements at or greater than the given index into the
        //next highest index
        for (int i = num_items; i > index; i--) {
            data[i] = data[i - 1];
        }

        //replace the element at the given index with the given char
        data[index] = c;
        //increment num_items since it's not 0 indexed
        num_items+= 1;
    }

    /*
     * name:      insertInOrder
     * purpose:   insert a character into the array list in ASCII order
     * arguments: a char element
     * returns:   nothing
     * effects:   pushes back all elements of the array at and after the
     *            given char in terms of ASCII order
     */
    void CharArrayList::insertInOrder(char c) {
        //initialize index counter
        int ordered_index = 0;
        char temp;

        //run a for loop to compare char to array elements
        for (int i = 0; i < num_items; i++) {
            //use if statement to determine if char c is before the
            //given element and if so break the for loop
            temp = data[i];
            if (c > temp) {
                ordered_index++;
            }
            else {
                i = num_items + 5;
            }
        }

        //call insertAt to place char c
        insertAt(c, ordered_index);
    }

    /*
     * name:      popFromFront
     * purpose:   remove the first element of the list
     * arguments: none
     * returns:   nothing
     * effects:   moves all the elements in the array up by one index
     */
    void CharArrayList::popFromFront() {
        //check if the array is empty
        if (isEmpty()) {
            throw std::runtime_error("cannot pop from empty ArrayList");
        }
        //move all data in the array up by one index
        for (int i = 0; i < num_items; i++) {
            data[i] = data[i + 1];
        }

        num_items--;
    }

    /*
     * name:      popFromBack
     * purpose:   removes the last element from the array list
     * arguments: none
     * returns:   nothing
     * effects:   calls removeAt function
     */
    void CharArrayList::popFromBack() {
        //check if the array is empty
        if (isEmpty()) {
            throw std::runtime_error("cannot pop from empty ArrayList");
        }
        //call the removeAt function
        removeAt(num_items - 1);
    }

    /*
     * name:      removeAt
     * purpose:   removes the element at a specifed index
     * arguments: an integer representing an array index
     * returns:   nothing
     * effects:   moves all the elements in the array at or after the 
     *            specified index up by one index
     */
    void CharArrayList::removeAt(int index) {
        //check if the index given is valid
        if (index >= num_items) {
            throw std::range_error("index (" + to_string(index) 
            + ") not in range " + "[0.." + to_string(num_items) + ")");
        }
        //move all data in the array at or after the given index up by
        //one index
        for (int i = index; i < num_items; i++) {
            data[i] = data[i + 1];
        }
        num_items--;
    }

    /*
     * name:      replaceAt
     * purpose:   replaces the element at a specified index with the new
     *            element
     * arguments: an element char and an integer representing an array index
     * returns:   nothing
     * effects:   replaces the element at the specified integer
     */
    void CharArrayList::replaceAt(char c, int index) {
        //check if the index given is valid
        if (index >= num_items) {
            throw std::range_error("index (" + to_string(index) 
            + ") not in range " + "[0.." + to_string(num_items) + ")");
        }
        //replace the info stored at the given index with the given char
        data[index] = c;
    }

    /*
     * name:      concatenate
     * purpose:   add a copy of the list pointed to in the parameters
     *            to the end of the original array list
     * arguments: a pointer to a second CharArrayList
     * returns:   nothing
     * effects:   adds one array to the back of another
     */
    void CharArrayList::concatenate(CharArrayList *other) {
        //find the size of the other array
        int other_num_items = other->size();
        //set a temporary var to store each element
        char temp;

        //run a for loop to add each element of the other array to the original
        for (int i = 0; i < other_num_items; i++) {
            temp = other->elementAt(i);
            pushAtBack(temp);
        }
    }

    //private functions to help implement some of the public ones above

    /*
     * name:      ensureCapacity
     * purpose:   ensure the array has enough capacity to handle new insertions
     * arguments: none
     * returns:   nothing
     * effects:   increases the array's capacity and creates a new copy of
     *            the array
     */
     void CharArrayList::ensureCapacity() {
        //increase the capacity
        capacity = capacity*2 + 2;

        //make a new array of the new capacity
        char *arr = new char[capacity];

        //copy the old array into this bigger array
        for (int i = 0; i < num_items; i++) {
            arr[i] = data[i];
        }
        
        //delete the old array
        delete [] data;
        
        //return the new array
        data = arr;
    }

