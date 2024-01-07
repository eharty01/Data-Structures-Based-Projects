/*
 * unit_test.h
 * Eleanor Harty
 * Oct. 3 2024
 * 
 * CS 15 Project 1: MetroSim
 *
 * Create tests to ensure that my code is running properly.
 */

#include "Passenger.h"
#include "PassengerQueue.h"
#include "MetroSim.h"

#include <iostream>
#include <string>
#include <cassert>
#include <sstream>

//test Passenger class//
//test default passenger
void passenger_print_empty () {
    //intitalize passenger
    std::ostringstream out;
    Passenger p;

    //call function and test
    p.print(out);
    assert(out.str() == "[-1, -1->-1]");
}

//test passengers w/ real info
void passenger_print_passengers() {
    //initialize passenger
    std::ostringstream out;
    Passenger p(1, 2, 5);
    
    //call function and test
    p.print(out);
    assert(out.str() == "[1, 2->5]");
}

//test PassengerQueue class//
//front tests
//see if it finds the front of a queue with one element
void passengerQueue_front_one() {
    //intitalize passenger queue and input
    PassengerQueue pq;
    Passenger p(1, 2, 5);
    pq.enqueue(p);
    
    //call function and test
    pq.front();
    assert(pq.front().id == 1);
}

//see if it finds the front of a queue with several elements
void passengerQueue_front_many() {
    //intitalize passenger queue and input
    PassengerQueue pq;
    Passenger p(1, 2, 5);
    pq.enqueue(p);
    Passenger q(2, 3, 4);
    pq.enqueue(q);
    Passenger t(3, 4, 6);
    pq.enqueue(t);

    //call function and test
    pq.front();
    assert(pq.front().id == 1);
}

//dequeue tests
//remove a passenger from a queue with one element
void passengerQueue_dequeue_one() {
    //intitalize passenger queue and input
    std::ostringstream out;
    PassengerQueue pq;
    Passenger p(1, 2, 5);
    pq.enqueue(p);

    //call function and test
    pq.dequeue();
    pq.print(out);

    assert(out.str() == "");
}

//remove a passenger from a queue with several passengers
void passengerQueue_dequeue_many() {
    //intitalize passenger queue and input
    std::ostringstream out;
    PassengerQueue pq;
    Passenger p(1, 2, 5);
    pq.enqueue(p);
    Passenger q(2, 3, 4);
    pq.enqueue(q);
    Passenger t(3, 4, 6);
    pq.enqueue(t);

    //call function and test
    pq.dequeue();
    pq.print(out);

    assert(out.str() == "[2, 3->4][3, 4->6]");
}

//enqueue tests
//add a passenger to the back of an empty queue
void passengerQueue_enqueue_empty() {
    //intitalize passenger queue and input, call function
    std::ostringstream out;
    PassengerQueue pq;
    Passenger p(1, 2, 5);
    pq.enqueue(p);

    //test
    pq.print(out);
    assert(out.str() == "[1, 2->5]");
}

//add a passenger to the back of a queue with one element
void passengerQueue_enqueue_one() {
    //intitalize passenger queue and input, call function
    std::ostringstream out;
    PassengerQueue pq;
    Passenger p(1, 2, 5);
    pq.enqueue(p);
    Passenger q(2, 3, 4);
    pq.enqueue(q);

    //test
    pq.print(out);
    assert(out.str() == "[1, 2->5][2, 3->4]");
}
//add a passenger to the back of a queue with several elements
void passengerQueue_enqueue_many() {
    //intitalize passenger queue and input, call function
    std::ostringstream out;
    PassengerQueue pq;
    Passenger p(1, 2, 5);
    pq.enqueue(p);
    Passenger q(2, 3, 4);
    pq.enqueue(q);
    Passenger t(3, 4, 6);
    pq.enqueue(t);

    //test
    pq.print(out);
    assert(out.str() == "[1, 2->5][2, 3->4][3, 4->6]");
}

//size tests
//see if it works on an empty queue
void passengerQueue_empty_size() {
    //intitalize passenger queue
    PassengerQueue pq;

    //call function and test
    pq.size();
    assert(pq.size() == 0);
}

//see if it works on a queue with one element
void passengerQueue_one_size() {
    //intitalize passenger queue and input
    PassengerQueue pq;
    Passenger p(1, 2, 5);
    pq.enqueue(p);

    //call function and test
    pq.size();
    assert(pq.size() == 1);
}

//see if it works on a queue with several elements
void passengerQueue_many_size() {
    //intitalize passenger queue and input
    PassengerQueue pq;
    Passenger p(1, 2, 5);
    pq.enqueue(p);
    Passenger q(2, 3, 4);
    pq.enqueue(q);
    Passenger t(3, 4, 6);
    pq.enqueue(t);

    //call function and test
    pq.size();
    assert(pq.size() == 3);
}

//print tests
//print empty queue
void passengerQueue_empty_print() {
    //intitalize passenger queue and input
    std::ostringstream out;
    PassengerQueue pq;

    //call function and test
    pq.print(out);
    assert(out.str() == "");
}

//print queue of 1 passenger
void passengerQueue_one_print() {
    //intitalize passenger queue and input
    std::ostringstream out;
    PassengerQueue pq;
    Passenger p(1, 2, 5);
    pq.enqueue(p);

    //call function and test
    pq.print(out);
    assert(out.str() == "[1, 2->5]");
}

//print queue of several passengers
void passengerQueue_many_print() {
    //intitalize passenger queue and input
    std::ostringstream out;
    PassengerQueue pq;
    Passenger p(1, 2, 5);
    pq.enqueue(p);
    Passenger q(2, 3, 4);
    pq.enqueue(q);
    Passenger t(3, 4, 6);
    pq.enqueue(t);
    
    //call funciton and test
    pq.print(out);
    assert(out.str() == "[1, 2->5][2, 3->4][3, 4->6]");
}

//MetroSim tests