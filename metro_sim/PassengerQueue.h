/*
 * PassengerQueue.h
 * Eleanor Harty
 * Oct. 3 2023
 *
 * CS 15 Project 1: MetroSim
 *
 * PassengerQueue is a class that represents a queue of student instances.
 * This class allows the users to remove passengers from the front of the queue
 * and add passengers to the back of the queue. They can also access
 * the passenger at the front of the queue and information about the number
 * of passengers in the queue. Finally, the user can print each passenger in
 * the passenger queue and their associated information like their passenger id
 * as well as their arrival and depature stations. It's implemented using a 
 * vector so it provides quick access to elements.
 */

//boilerplate
#ifndef PASSENGER_QUEUE_H
#define PASSENGER_QUEUE_H

#include <string>
#include <vector>
#include "Passenger.h"

//declare class
class PassengerQueue {
    //create public functions specified in spec
    public:
       Passenger front();
       void dequeue();
       void enqueue(const Passenger &passenger);
       int size();
       void print(std::ostream &output); 

    //create vector
    private:
        std::vector <Passenger> passengers;
};

#endif