/*
 * DataumStack.h
 * Eleanor Harty
 * Oct. 17, 2023
 *
 * CS 15: Project 2 CalcYouLater
 *
 * This class respresents a the stack of datums, that when used by RPNCalc will
 * represent a stack of user given inputs. A client can add or remove an
 * an input from the top of the stack. They can clear the stack and verify if 
 * it is empty or not. They can see the top element of the stack and check the 
 * size of the stack. It is implemented using lists to provide quick insertion 
 * and deletion of input.
 */

#ifndef DATUMSTACK_H
#define DATUMSTACK_H
//include statements
#include "Datum.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <list>
using namespace std;

//create DatumStack Class
class DatumStack {
    public: 
        //declare public var. and functions
        DatumStack();
        DatumStack(Datum arr[], int arr_size);
        bool isEmpty();
        void clear();
        int size();
        Datum top();
        void pop();
        void push(Datum data);

    //declare private var. and functions
    private:
        //implementing vector of Datum
        std::list <Datum> my_data;

};

#endif