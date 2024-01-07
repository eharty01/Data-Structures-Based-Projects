/*
 *  CharArrayList.h
 *  Eleanor Harty
 *  Sept. 17 2023
 *
 *  COMP 15 HW 1 Cheshire ConCATenation
 *
 *  CharArrayList is a class representing a given array of characters. The
 *  class constructs arrays and creates deep copies of them . You can get
 *  specified elements of the array (using size, first, last, atElement).
 *  You can also print the entirety of the contents of the array with
 *  forwards and backwards with functions like toString and toReverseString.
 *  Additionally you can insert elements at the front and back of the list or
 *  at a specified index or insert your element in the specified order 
 *  (pushAt Back, pushAtFront, insertAt, and insertInOrder). You can also 
 *  remove elements at any index you want or replace them (popFromFront,
 *  popFromBack, removeAt, replaceAt). You can also add another array to the
 *  back of an array of this class with the concatenate function. Finally 
 *  when your program finishes running a destructor will recycle the array.
 */
#ifndef CHAR_ARRAY_LIST_H
#define CHAR_ARRAY_LIST_H

#include <string>

class CharArrayList {
    //create public classes
    public:
    //create constructors
    CharArrayList();
    CharArrayList(char c);
    CharArrayList (char arr[], int size);
    CharArrayList (const CharArrayList &other);

    //create destructor
    ~CharArrayList();

    //assignment operator
    CharArrayList &operator=(const CharArrayList &other);

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
    void concatenate(CharArrayList *other);

    //define private members
    private:

    //
    int num_items;
    int capacity;
    char *data;

    //helper function to ensure sufficent capacity
    void ensureCapacity ();
};

#endif
