/*
 *  CharLinkedList.cpp
 *  Eleanor Harty
 *  Sept. 24, 2023
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to get linked up in Fur
 *
 *  This file contains an implementation of the CharLinkedList class.
 *
 */

#include "CharLinkedList.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;


//implement constructors

 /*
 * name:      CharLinkedList 
 * purpose:   initializes an empty linked list
 * arguments: none
 * returns:   nothing
 * effects:   an empty linked list is created
 */
CharLinkedList::CharLinkedList() {
    //initialize an empty linked list with num_items of 0
    front = nullptr;
    back = front;
    num_items = 0;
}

 /*
  * name:      CharLinkedList 
  * purpose:   initialize a linked list with one element and an initial 
  *            capacity of 1
  * arguments: a single character that will be the only element in the list
  * returns:   nothing
  * effects:   an linked list with one element and a capacity of 1 is made
  */
CharLinkedList::CharLinkedList(char c) {
    //initialize a list with one node
    Node *new_node = newNode(c, nullptr, nullptr);

    //set front and back equal and num_items to 1
     front = new_node;
     back = new_node;

     num_items = 1;
}

/*
 * name:      CharLinkedList
 * purpose:   create a linked list containing the characters in the linked 
 *            list, the linked list should have an initialy capacity equal to 
 *            the length passed
 * arguments: a linked list of characters and an integer representing 
 *            the length of that linked list
 * returns:   nothing
 * effects:   creates a linked list of characters based on the elements and
 *            size passed for that linked list
 */
CharLinkedList::CharLinkedList(char arr[], int size) {
    //initialize num_items and front pointer
    num_items = 0;
    front = nullptr;

    //run a for loop to create and fill new nodes
    for (int i = 0; i < size; i++) {
        pushAtBack(arr[i]);
    }
}

/*
 * name:      CharLinkedList
 * purpose:   make a deep copy of the given instance
 * arguments: reference to another char linked list (that you want to copy)
 * returns:   nothing
 * effects:   creates a deepy copy
 */
CharLinkedList::CharLinkedList (const CharLinkedList &other){
    //initialize num_items and front pointer
    num_items = 0;
    front = nullptr;
    
    //set curr_node to the front of the other list
    Node *curr_node = other.front;

    //run a for loop to create a deep copy of the list
    for (int i = 0; i < other.size(); i++) {
        pushAtBack(curr_node->data);
        curr_node = curr_node->next;
    }
}

//implement destructor

/*
 * name:      ~CharLinkedList
 * purpose:   delete/recycle all heap allocated data in the current linked list
 * arguments: none
 * returns:   nothing
 * effects:   calls a function that gets rid of heap linked list data
 */
CharLinkedList::~CharLinkedList() {
    //call private helper function to recycle memory
    recursiveDestructor(front);
}

//implement assignment operator
/*
 * name:      CharLinkedList
 * purpose:   make a deep copy of the instance on the right hand side into
 *            the instance on the left, and recycle storage for the left 
 * arguments: pointer to a char linked list
 * returns:   nothing
 * effects:   makes a deep copy of the right hand side of the expression
 */
CharLinkedList &CharLinkedList::operator=(const CharLinkedList &other) {
    //check that that left and right hand side are the same object
    if (this == &other) {
        return *this;
    }

    //initialize list starting conditions
    clear();
    //set curr_node to the front of the other list
    Node *curr_node = other.front;

    //run a for loop to create a deep copy of the list
    for (int i = 0; i < other.size(); i++) {
        pushAtBack(curr_node->data);
        curr_node = curr_node->next;
    }

    //return copy
    return *this;
}

//public functions to identify or modify elements of the linked list
/*
 * name:      isEmpty
 * purpose:   determine if the linked list is empty or contains characters
 * arguments: none
 * returns:   a boolean value that signifies if the linked list is empty or not
 * effects:   informs user if the linked list is empty or not
 */
bool CharLinkedList::isEmpty() const {
    //check if the front goes anywhere, return bool based on that
    if (front == nullptr) {
        return true;
    }
    else {
        return false;
    }
}

/*
 * name:      clear
 * purpose:   to make the instance into an empty linked list list
 * arguments: none
 * returns:   nothing
 * effects:   after this is run on an linked list if isEmpty is called on that
 *            linked list it will return true
 */
void CharLinkedList::clear() {
    //call the function used in the destructor to clear the linked list
    recursiveDestructor(front);

    //reset initial list conditions for an empty list
    front = nullptr;
    num_items = 0;
}

/*
 * name:      size
 * purpose:   state the number of characters in an linked list
 * arguments: none
 * returns:   an integer representing the amount of characters in the list
 * effects:   tells user the number of characters in the linked list
 */
int CharLinkedList::size() const {
    //give back current num_items
    return num_items;
}

/*
 * name:      first
 * purpose:   find the first character in an linked list
 * arguments: none
 * returns:   the first character in the linked list list
 * effects:   determines the first character in an linked list
 */
char CharLinkedList::first() const {
    //check if the list is empty, if so throw error
    if (isEmpty()) {
            throw std::runtime_error("cannot get first of empty LinkedList");
    }
    //return first char in the linked list
    else {
        return front->data;
    }
}

/*
 * name:      last
 * purpose:   find the last character in an linked list
 * arguments: none
 * returns:   the last character in the linked list
 * effects:   determines the last character in an linked list
 */
char CharLinkedList::last() const {
    //check if the linked list is empty and if so throw error
    if (isEmpty()) {
            throw std::runtime_error("cannot get last of empty LinkedList");
    }

    //return the character stored in back
    return back->data;
}

/*
 * name:      elementAt
 * purpose:   find the 
 * arguments: an integer representing the index of the linked list
 * returns:   the character element of the linked list at the input index
 * effects:   determines the element at the specified index
 */
char CharLinkedList::elementAt(int index) const {
    //check if index is in range
    if (index >= num_items or index < 0) {
        throw std::range_error("index (" + to_string(index) + ") not in range " 
        + "[0.." + to_string(num_items) + ")");
    }

    //set curr_node and count variable
    Node *curr_node;
    int count = 0;

    //call private function to find the correct node and return the char in it
    curr_node = recurElementAt(index, count, front);
    return curr_node->data;
}

/*
 * name:      toString
 * purpose:   display all info contained in the linked list and it's size
 * arguments: none
 * returns:   a string which contains the characters of the CharLinkedList
 * effects:   prints the contents and size of the linked list list
 */
std::string CharLinkedList::toString() const {
    //start curr_node at the front
    Node *curr_node = front;

    //check isEmpty
    std::stringstream temp;
    if(isEmpty()) {
        temp << "[CharLinkedList of size 0 <<>>]";
    }
    //intake each char in the list and return it as a string
    else {
        temp << "[CharLinkedList of size " << num_items << " <<";
        while (curr_node != nullptr) {
            temp << curr_node->data;
            curr_node = curr_node->next;
        }
        temp << ">>]";
    }

    return temp.str();
}

/*
 * name:      toReverseString
 * purpose:   display all info contained in the linked list (in reverse) and 
 *            it's size
 * arguments: none
 * returns:   a string which contais the characters of the CharLinkedList
 *            in reverse
 * effects:   prints the contents (in reverse) and size of the linked list
 */
std::string CharLinkedList::toReverseString() const {
    //start curr node at the back
    Node *curr_node = back;

    //check isEmpty
    std::stringstream temp;
    if(isEmpty()) {
        temp << "[CharLinkedList of size 0 <<>>]";
    }
    //intake each char for linked list in reverse and return as a string
    else {
        temp << "[CharLinkedList of size " << num_items << " <<";
        while (curr_node != nullptr) {
            temp << curr_node->data;
            curr_node = curr_node->prev;
        }
        temp << ">>]";
    }

    return temp.str();
}

/*
 * name:      pushAtBack
 * purpose:   insert the given new element after the end of the existing
 *            elements of the linked list list
 * arguments: an element char to place at the back of the linked list
 * returns:   nothing
 * effects:   increments num_items and adds a new element at the back
 *            of the exesting elements in the linked list
 */
void CharLinkedList::pushAtBack(char c) {
    //if the list is empty make a one element list
    if (front == nullptr) {
        front = newNode(c, nullptr, nullptr);
        back = front;
    } 
    //otherwise create a new node at the back and adjust pointers & num_items
    else {
        back = newNode(c, nullptr, back);
        back->prev->next = back;
    }

    num_items++;
}

/*
 * name:      pushAtFront
 * purpose:   insert the given new element in front of the existing 
 *            elements of the linked list list
 * arguments: an element char to place at the front of the linked list
 * returns:   nothing
 * effects:   increments num_items and adds a new elment at the front of
 *            of the linked list pushing back the other elements by 1
 */
void CharLinkedList::pushAtFront(char c) {
    //if the list is empty make a one element list
    if (isEmpty()) {
        front = newNode(c, nullptr, nullptr);
        back = front;
    }
    //otherwise create a new node at the back and adjust pointers & num_items
    else {
        front = newNode(c, front, nullptr);
        front->next->prev = front;
    }

    num_items++;
}

/*
 * name:      insertAt
 * purpose:   insert a given char at a given index, pushing back all
 *            other data in the index
 * arguments: an element char to replace the element at the specified
 *            index and an integer representing the specified index
 * returns:   nothing
 * effects:   pushes back all elements of the linked list at and after the
 *            given index and increments num_items
 */
void CharLinkedList::insertAt(char c, int index) {
    //check first if the index is in range, then if it's at the front or back
    if (index > num_items or index < 0) {
        throw std::range_error("index (" + to_string(index) + ") not in range " 
        + "[0.." + to_string(num_items) + "]");
    } else if (index == 0) {
        pushAtFront(c);
        return;
    } else if (index == num_items) {
        pushAtBack(c);
        return;
    } else {
        //set placeholders then count to the correct node
        Node *curr_node = front;
        int count = 0;

        while (count != index) {
            curr_node = curr_node->next;
            count++;
        }
        //create the node and insert the node, adjust pointers and num_items
        new_node = newNode(c, curr_node, curr_node->prev);
        
        curr_node->prev->next = new_node;
        curr_node->prev = new_node;
        num_items++;
    }
}

/*
 * name:      insertInOrder
 * purpose:   insert a character into the linked list in ASCII order
 * arguments: a char element
 * returns:   nothing
 * effects:   pushes back all elements of the linked list at and after the
 *            given char in terms of ASCII order
 */
void CharLinkedList::insertInOrder(char c) {
    //initialize variables
    Node *curr_node = front;
    int ordered_index = 0;
    bool stop = false;

    //run a while loop to compare given char to list elements
    while (curr_node != nullptr and (not stop)) {
        //use if statement to determine if char c is before the
        //current node's char and if so stop the loop
        if (c > curr_node->data) {
            curr_node = curr_node->next;
            ordered_index++;
        }
        else {
            stop = true;
        }
    }

    //call insertAt on the char for it's correctly ordered index
    insertAt(c, ordered_index);
}

/*
 * name:      popFromFront
 * purpose:   remove the first element of the list
 * arguments: none
 * returns:   nothing
 * effects:   moves all the elements in the linked list up by one index
 */
void CharLinkedList::popFromFront() {
    //check if the linked list is empty and if so throw error
    if (isEmpty()) {
        throw std::runtime_error("cannot pop from empty LinkedList");
    }
    //if it's a single char list make it an empty list
    else if (size() == 1) {
        delete front;
        front = nullptr;
        back = nullptr;
        num_items = 0;
    }
    //otherwise reset front and delete the old front, decrease num_items
    else {
        front = front->next;
        delete front->prev;
        front->prev = nullptr;
    
        num_items--;
    }
}

/*
 * name:      popFromBack
 * purpose:   removes the last element from the linked list list
 * arguments: none
 * returns:   nothing
 * effects:   calls removeAt function
 */
void CharLinkedList::popFromBack() {
    //check if the linked list is empty and if so throw error
    if (isEmpty()) {
        throw std::runtime_error("cannot pop from empty LinkedList");
    }
    //if it's a single char list make it an empty list
    else if (size() == 1) {
        delete front;
        front = nullptr;
        back = nullptr;
        num_items = 0;
    }
    //otherwise reset front and delete the old front, decrease num_items
    else {
        back = back->prev;
        delete back->next;
        back->next = nullptr;

        num_items--;
    }
}

/*
 * name:      removeAt
 * purpose:   removes the element at a specifed index
 * arguments: an integer representing an linked list index
 * returns:   nothing
 * effects:   moves all the elements in the linked list at or after the 
 *            specified index up by one index
 */
void CharLinkedList::removeAt(int index) {
    //check for range error, if it's at the front or back (call function if so)
    if (index >= num_items or index < 0) {
        throw std::range_error("index (" + to_string(index) + ") not in range " 
        + "[0.." + to_string(num_items) + ")");
    } else if (index == 0) {
        popFromFront();
        return;
    } else if (index == num_items - 1) {
        popFromBack();
        return;
    }
    //count to the given index and reset pointers then remove the node
    else {
        int count = 0;
        Node *curr_node = front;

        while (count != index) {
            curr_node = curr_node->next;
            count++;
        }
        curr_node->prev->next = curr_node->next;
        curr_node->next->prev = curr_node->prev;

        delete curr_node;
        num_items--;
    }
}

/*
 * name:      replaceAt
 * purpose:   replaces the element at a specified index with the new
 *            element
 * arguments: an element char and an integer representing an linked list index
 * returns:   nothing
 * effects:   calls a function to replace the element at the specified integer
 */
void CharLinkedList::replaceAt(char c, int index) {
    //initialize count integer
    int count = 0;

    //check for range error
    if (index >= num_items or index < 0) {
        throw std::range_error("index (" + to_string(index) + ") not in range " 
        + "[0.." + to_string(num_items) + ")");
    }

    //call a function to replace the index
    recurReplaceAt(c, index, count, front);
}

/*
 * name:      concatenate
 * purpose:   add a copy of the list pointed to in the parameters
 *            to the end of the original linked list list
 * arguments: a pointer to a second CharLinkedList
 * returns:   nothing
 * effects:   adds one linked list to the back of another
 */
void CharLinkedList::concatenate(CharLinkedList *other) {
    //set curr_node the front of the other list and a variable to the
    //num_items of the other list
    Node *curr_node = other->front;
    int count = other->size();

    //check if the other list is empty and if so do nothing
    if (other->isEmpty()) {
        return;
    }
    //add the other list's nodes by pushing each one in order to the
    //back of the list
    else {
        while (count != 0) {
            pushAtBack(curr_node->data);
            curr_node = curr_node->next;
            count--;
        }
    }
}

/*
 * name:      recursiveDestructor
 * purpose:   delete/recycle all heap allocated data in the current linked list
 * arguments: a pointer to the current node
 * returns:   nothing
 * effects:   gets rid of heap linked list data
*/
void CharLinkedList::recursiveDestructor(Node *curr_node) {
    //if you have a null pointer stop recurring
    if (curr_node == nullptr) {
        return;
    }
    //otherwise recur the function on the next node and delete the current node
    else {
        recursiveDestructor(curr_node->next);
        delete curr_node;
    }
}

/*
 * name:      recurElementAt
 * purpose:   find the element at a given index
 * arguments: an integer representing the index of where we can find the
 *            desired information, an int variable to count the index as we
 *            move through the list, and a pointer to the current node
 * returns:   a node (at the specified index)
 * effects:   locates an element
*/
CharLinkedList::Node *CharLinkedList::recurElementAt(int index, int count, 
                                                    Node *curr_node) const {
    //check if it's the correct index if so return
    if (count == index) {
        return curr_node;
    }
    //if it's not follow the list to the correct node
    else {
            count++;
            return recurElementAt(index, count, curr_node->next);
    }
}

/*
 * name:      recurReplaceAt
 * purpose:   replaace a character at a given index
 * arguments: a character to input at the given index, an integer representing 
 *            the index of where we can find the desired information, an int 
 *            variable to count the index as we move through the list, and a 
*             pointer to the current node
 * returns:   nothing
 * effects:   replaces a character within the linked list at the given index
*/
void CharLinkedList::recurReplaceAt(char c, int index, int count, 
                                                Node *curr_node) {
    //if it's the correct index replace data
    if (count == index) {
        curr_node->data = c;
    }
    //if it's not follow the list to the currect node
    else {
        count++;
        recurReplaceAt(c, index, count, curr_node->next);
    }
}

/*
 * name:      newNode
 * purpose:   create a new node with the desired information
 * arguments: the information the new node is meant to contain specifically 
 *            a character and pointer to the next and previous node
 * returns:   a new node
 * effects:   creates a new node which can be added to the list
*/
CharLinkedList::Node *CharLinkedList::newNode (char c, Node *next, 
                                                        Node *prev) {
    //set new node
    Node *new_node = new Node;

    //fill in the data
    new_node->data = c;
    new_node->next = next;
    new_node->prev = prev;

    //return filled in node
    return new_node;
}
