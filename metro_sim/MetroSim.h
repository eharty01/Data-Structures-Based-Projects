/*
 * MetroSim.h
 * Eleanor Harty
 * Oct. 7 2023
 *
 * CS 15: Project 1 MetroSim
 *
 * MetroSim is a class that represents the lists of stations and train that
 * help run the MetroSimulator. Stations are created with a file provided by
 * the user listing station names and stations are also given numbers and queues
 * of passengers by the program. Users can either provide the simulator with a 
 * list of commands they want to perform or can choose to enter them manually.
 * Commands a user can give the simulator include adding a passenger at any
 * station of their choosing (the user must provide the arrival and departure
 * station of the passenger, which can be any of their choosing within the range
 * of stations they've provided). They can move the train along the line of 
 * stations and it will pick up passengers waiting at the station and disembark
 * passengers who were listed to depart at this station. The simulator will also
 * keep track of and report to the user the passengers on the train and 
 * information about them such as their arrival and departure station and their
 * passenger id (the simulation counts each passenger that enters the train
 * and their order of entering the train is their passenger id). Finally, when
 * the user wants to end the simulation, MetroSim will print a parting message
 * and terminate the program, creating an output file that logs the departure of
 * all the passengers. This class interacts with both the Passenger and
 * PassengerQueue class to provide to queues of passengers to the train and 
 * various stations and to add individual passengers to the simulation. Both
 * the station and train lists are implemented using vectors to give quick
 * access to passengers and simplify adding or removing them from the list.
 */

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include "Passenger.h"

// Put any other necessary includes here
#include "PassengerQueue.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Put any other structs you need here

//create stations struct
struct Station {
    //variables w/in station struct
    std::string station_name;
    int station_number;
    PassengerQueue waiting_passengers;

    //station constructor
    Station(std::string name, int number, PassengerQueue passengers) {
        station_name = name;
        station_number = number;
        waiting_passengers = passengers;
    }; 
};

//MetroSim class
class MetroSim {

    //create public functions
    public:
        //declare sim here so it can be used in main
        void sim(std::ifstream &stations_file, std::ofstream &output, 
        std::istream &command);

    //create private functions/members
    private:
        //declare variables
        int train_position;
        int pass_id;
        int total_stations;

        //declare functions
        void commands(std::istream &command, std::ofstream &output);
        void commands_cin();
        void p_command(int arrival, int departure);
        void m_m_command(std::ofstream &output);
        void print_sim();
        void boarding();
        void exit(std::ostream &output);
        void make_stations(std::ifstream &input);

        //declare vectors
        std::vector <Station> stations;
        std::vector <PassengerQueue> train;
};

#endif
