/*
 * PassengerQueue.cpp
 * Eleanor Harty
 * Oct. 3 2023
 *
 * CS 15 Project 1: MetroSim
 *
 * This file contains an implementation of the PassengerQueue class.
*/

#include "PassengerQueue.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

/*
 * name:      front
 * purpose:   return the element at the front of the queue
 * arguments: none
 * returns:   the element at the front of the queue
 * effects:   reports the front element in the queue
 */
Passenger PassengerQueue::front() {
    //call vector function
    return passengers.front();
}

/*
 * name:      dequeue
 * purpose:   removes the element at the front of the queue
 * arguments: none
 * returns:   nothing
 * effects:   after it runs the queue has one less element taken from the back
 */
 void PassengerQueue::dequeue() {
    //call vector functions
    passengers.erase(passengers.begin());
 }

 /*
 * name:      enqueue
 * purpose:   insert a new passenger at the end of the queue
 * arguments: address of a passenger we want to add
 * returns:   nothing
 * effects:   after it runs the queue has one more elment inserted at the front
 */
 void PassengerQueue::enqueue(const Passenger &passenger) {
    //call vector function
    passengers.push_back(passenger);
 }

/*
 * name:      size
 * purpose:   return the number of elements in the queue
 * arguments: none
 * returns:   an integer representing the number of elements in the queue
 * effects:   ascertains the amount of elements in the queue
 */
 int PassengerQueue::size() {
    //call vector function
    return passengers.size();
 }

 /*
 * name:      print
 * purpose:   print each passeneger in the PassengerQueue to the given output
              stream
 * arguments: output stream to print passengers
 * returns:   nothing
 * effects:   prints about the passengers
 */
 void PassengerQueue::print(std::ostream &output) {
    //loop through vector from front to end printing the info for each
    //passenger
    for (std::vector<Passenger>::iterator it = passengers.begin();
    it != passengers.end(); it++) {
        output << "[" << it->id << ", " << it->from << "->"
        << it->to << "]";
    }
 }