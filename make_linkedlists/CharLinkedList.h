/*
 *  CharLinkedList.h
 *  Eleanor Harty
 *  Sept. 24 2023
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to get linked up in Fur
 *
 *  CharLinkedList is a class that represents a list containing
 *  characters. A list can be empty or filled with one or many
 *  characters. Characters can be added or removed anywhere in the lis the
 *  user would like. You can also access any character in the list or print 
 *  all of them at once (in order or reverse order) alongside the size of the
 *  list. Users can also replace any character in the list with a character of 
 *  their choosing. Users can also add lists to each other. Finally, the list
 *  is implemented using a linked list so it provides quick insertion or 
 *  deletion of characters at the front.
 */

#ifndef CHAR_LINKED_LIST_H
#define CHAR_LINKED_LIST_H

#include <string>

class CharLinkedList {
    //create public functions
    public:
        //create constructors
        CharLinkedList();
        CharLinkedList(char c);
        CharLinkedList (char arr[], int size);
        CharLinkedList (const CharLinkedList &other);

        //create destructor
        ~CharLinkedList();

        //assignment operator
        CharLinkedList &operator=(const CharLinkedList &other);

        //functions to identify or modify elements of the array
        bool isEmpty() const;
        void clear();
        int size() const;
        char first() const;
        char last() const;
        char elementAt(int index) const;
        std::string toString() const;
        std::string toReverseString() const;
        void pushAtBack(char c);
        void pushAtFront(char c);
        void insertAt(char c, int index);
        void insertInOrder(char c);
        void popFromFront();
        void popFromBack();
        void removeAt(int index);
        void replaceAt(char c, int index);
        void concatenate(CharLinkedList *other);

    //create private members/functions
    private:
        //create struct for nodes
        struct Node {
            char data;
            Node *next;
            Node *prev;
        };

        //declare front, back and new node
        Node *front;
        Node *back;
        Node *new_node;

        //private helper functions
        void recursiveDestructor(Node *curr_node);
        Node *recurElementAt(int index, int count, Node *curr_node) const;
        void recurReplaceAt(char c, int index, int count, Node *curr_node);
        Node *newNode(char c, Node *next, Node *prev);

        //declare num_items
        int num_items;
};

#endif
