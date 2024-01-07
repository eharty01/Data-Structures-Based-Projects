/*
 * MetroSim.cpp
 * Eleanor Harty
 * Oct. 7, 2023
 * 
 * CS 15: Project MetroSim
 *
 * This file contains an implementation of the MetroSim class.
 */

// boilerplate
#include "MetroSim.h"
#include "Passenger.h"
#include "PassengerQueue.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
 * name:      sim
 * purpose:   initialize first train position and passenger id, start the 
 *            simulation by creating stations and calling command loop
 * arguments: files to read in containing the stations and commands the sim
 *            will create/run, an output file to write out to when a 
 *            passenger exits
 * returns:   nothing
 * effects:   starts the simulation
*/
void MetroSim::sim(std::ifstream &stations_file, std::ofstream &output, 
std::istream &command) {
    //initialize variables
    train_position = 0;
    pass_id = 1;

    //make stations
    make_stations(stations_file);

    //run query loop
    commands(command, output);
}

/*
 * name:      make_stations
 * purpose:   create the stations
 * arguments: a file containing the list of stations the user gave
 * returns:   nothing
 * effects:   creates the stations structs
*/
void MetroSim::make_stations(ifstream &input) {
    //initialize tracking variables
    int count = 0;
    string current_line;

    //construct stations and increment count for each station in the file
    while(getline(input, current_line)) {
        PassengerQueue boarders;

        Station new_station(current_line, count, boarders);
        stations.push_back(new_station);

        //initialize train
        train.push_back(PassengerQueue());

        count++;
    }

    //save the number of stations
    total_stations = count;
}

/*
 * name:      commands
 * purpose:   run the commands given to the simulator
 * arguments: an instream that can either be a file containing commands or
 *            commands the user has typed in
 * returns:   nothing
 * effects:   calls the various commands MetroSim could run
*/
void MetroSim::commands(std::istream &command, std::ofstream &output) {
    print_sim();
    cout << "Command? ";
    string current_line;

    //run query loop
    while(command >> current_line) {
        if(current_line == "p") {
            //initialize and pass vars then add passengers
            int arrival;
            int departure;
            command >> arrival;
            command >> departure;

            p_command(arrival, departure);
            cout << "Command? ";
        } else if(current_line == "m") {
            //take in next input to distinguish and call which m command it is
            command >> current_line;

            if (current_line == "m") {
                m_m_command(output);
                cout << "Command? ";
            } else if (current_line == "f") {
                cout << "Thanks for playing MetroSim. Have a nice day!" << endl;
                return;
            }
        }
    }
    cout << "Thanks for playing MetroSim. Have a nice day!" << endl;
}

/*
 * name:      p_command
 * purpose:   add a passenger at a given station
 * arguments: an int representing the arrival station and an int representing
 *            the departure station of the passenger
 * returns:   nothing
 * effects:   adds a passenger to the queue of their arrival station and prints
 *            the simulation
*/
void MetroSim::p_command(int arrival, int departure) {
    //create placeholder passenger
    Passenger temp;
    temp = Passenger(pass_id, arrival, departure);
    
    //enqueue the passenger at their arrival station
    stations.at(arrival).waiting_passengers.enqueue(temp);

    //increment passenger id and print simulation
    pass_id++;
    print_sim();
}

/*
 * name:      m_m_command
 * purpose:   pick up any passengers waiting at the current station and have
 *            any passengers who are supposed to depart at this station exit,
 *            and move the train forward by one station
 * arguments: the output file in which to print out/log where a passenger exits
 * returns:   nothing
 * effects:   moves the train forward and prints simulation
*/
void MetroSim::m_m_command(std::ofstream &output) {
    //board passengers at this station
    boarding();

    //increment the train's position or send it back to start from end
    if (train_position != total_stations - 1) {
        train_position++;
    } else if (train_position == total_stations - 1) {
        train_position = 0;
    }

    //exit passengers at their station
    exit(output);

    //print simulation
    print_sim();
}

/*
 * name:      print_sim
 * purpose:   print out the current state of the simulation
 * arguments: none
 * returns:   nothing
 * effects:   displays the most recent version of the simulation
*/
void MetroSim::print_sim () {
    //print passengers currently on the train
    cout << "Passengers on the train: {";
    for (size_t i = 0; i < train.size(); i++) {
        train[i].print(cout);
    }
    cout << "}" << endl;

    //print all the stations, passengers waiting at them and where the train is
    for (int i = 0; i < total_stations; i++) {
        if (i != train_position) {
            cout << "       [" << stations.at(i).station_number << 
            "] " << stations.at(i).station_name << " {"; 
            stations.at(i).waiting_passengers.print(cout); cout << "}" << endl;
        }
        else {
            cout << "TRAIN: [" << stations.at(i).station_number << 
            "] " << stations.at(i).station_name << " {"; 
            stations.at(i).waiting_passengers.print(cout); cout << "}" << endl;
        }
    }
}

/*
 * name:      boarding
 * purpose:   get passengers from their station onto the train
 * arguments: none
 * returns:   nothing
 * effects:   passengers are moved from the station to the train
*/
void MetroSim::boarding () {
    
    //board all passengeers waiting at a station
    while(stations.at(train_position).waiting_passengers.size() != 0) {
        //create a placeholder passenger
        Passenger temp;

        //dequeue the original passenger from the station and enqueue the temp
        //one on the train
        temp = stations.at(train_position).waiting_passengers.front();
        stations.at(train_position).waiting_passengers.dequeue();
        train[temp.to].enqueue(temp);
    }
}

/*
 * name:      exit
 * purpose:   removes passengers from the train and logs their departure in
 *            the output file
 * arguments: the output file to write passenger departures into
 * returns:   nothing
 * effects:   takes a passenger from the train and logs their exit
*/
void MetroSim::exit(std::ostream &output) {

    //go through the size of the train at that position
    while(train[train_position].size() > 0) {
        //log the exiting passenger
        output << "Passenger " << 
        train[train_position].front().id <<
        " left train at station " << stations.at(train_position).station_name <<
        endl;

        //dequeue the the passenger
        train[train_position].dequeue();
    }
}