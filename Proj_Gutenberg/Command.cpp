
/*
 * Command.cpp
 * Eleanor Harty and Allen Wang
 * Dec. 5, 2023
 * 
 * CS 15: Project 4 Gerp
 *
 * This file contains the implementation of the Command.h class.
 */

//boilerplate
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>

#include "Command.h"
#include "FSTree.h"
#include "DirNode.h"

using namespace std;

/*
 * name:      ValueInfo
 * purpose:   make a struct containing information about each word
 * arguments: a reference to a string containing the file where the word 
 *            within the directory, and the word itself. Finally we pass an 
 *            integer representing the line number of the file where the word 
 *            appeared.
 * returns:   nothing
 * effects:   creates a struct
*/
ValueInfo::ValueInfo(std::string &file_path, int line_num, 
std::string &original_word) {
    //fill in data points for the struct with passed in info
    this->file_path = file_path;
    this->line_num = line_num;
    this->original_word = original_word;
}

/*
 * name:      ~Command
 * purpose:   initializes an empty hash table of given capacity
 * arguments: none
 * returns:   nothing
 * effects:   prevents memory errors
*/
Command::~Command() {

}

/*
 * name:      start_gerp
 * purpose:   begin the gerp program
 * arguments: a node that is the root of the tree representing the
 *            subdirectories and files of the given directory, and an output
 *            file to write user search results to.
 * returns:   nothing
 * effects:   starts the gerp program
*/
void Command::start_gerp(DirNode *inputDirectory, ofstream &outputFile) {
    //call functions to start gerp
    init_hash();
    traverser(inputDirectory, "");
    query_loop(outputFile);
    cout << "Goodbye! Thank you and have a nice day." << endl;
    outputFile.close();
}

/*
 * name:      init_hash
 * purpose:   initializes an empty hash table
 * arguments: none
 * returns:   nothing
 * effects:   initializes our hash table
*/
void Command::init_hash() {
    //declare var
    numItems = 0;
    capacity = 10000;

    //push back a list for each instance of the vector
    for (int i  = 0; i < capacity; i++) {
        list<ValueInfo> starter_list;
        my_hash.push_back(starter_list);
    }
} 

/*
 * name:      query_loop
 * purpose:   accept user's commands and performs corresponding 
 *            functionalities
 * arguments: an output file to print the search results to
 * returns:   nothing
 * effects:   promt the user for different queries, and print the serach 
 *            results into a provided file based on users' commands
*/
void Command::query_loop(std::ofstream &outputFile) {
    //declare var start query
    string command, word, file_name;
    cout << "Query? ";

    // while not at the end of the file query user for input and respond
    // accordingly
    while (cin >> command) {
        if (command == "@q" or command == "@quit") {
            return;
        } else if (command == "@i" or command == "@insensitive") {
            cin >> word;
            perform_search(word, true, outputFile);
        } else if (command == "@f") {
            cin >> file_name;
            outputFile.close();
            outputFile.open(file_name);
        } else {
            perform_search(command, false, outputFile);
        }
        cout << "Query? ";
    }
}

/*
 * name:      traverser
 * purpuse:   to traverse the given data and find all subdirectories & files
 * arguments: a root to the base of the tree representing the subdirectories
 *            and files within the directory
 *            names found
 * returns:   nothing
 * effects:   stores the name of files within the directory
*/
void Command::traverser (DirNode *root, std::string &path) {
    //store names of the subdirectories and files leading to the current file
    path += root->getName() + "/";
    if (root->hasFiles()) {
        for (int i = 0; i < root->numFiles(); i++) {
            read(path + root->getFile(i));
        }
    }

    //check for subdirectories and recursively go through them to print their
    //files
    if (root->hasSubDir()) {
        for (int j = 0; j < root->numSubDirs(); j++) {
            traverser(root->getSubDir(j), path);
        }
    }
}

/*
 * name:      read
 * purpose:   read the file and process the lines
 * arguments: a string that represents the path of the file
 * returns:   nothing
 * effects:   declare and update the variables for line content
 *            and the line number, traverse each line in the file, 
 *            and call the save_line function to save the values 
 *            to the hash table
 */
void Command::read(string &path) {
    //declare var
    string line_content = "";
    int line_num = 1;

    //check if you can open file
    ifstream infile(path);

    //traverse file and save line and line number
    while(getline(infile, line_content)) {
        save_line(line_content, path, line_num);
        line_num++;
    }

    //close file
    infile.close();
} 

/*
 * name:      save_line
 * purpose:   processes words from the lines and save them to the hash table
 * arguments: a string line content that representst the content of the line,
 *            a string path that represents where the file and line are found,
 *            & a integer line_num that represents the line number in the file
 * returns:   nothing
 * effects:   make an input string stream that represents the line content, 
 *            process each word from the line, and call insertion function to 
 *            insert the values into the hash table
 */
void Command::save_line(string &line_content, string &path, int line_num) {
    //declare var
    istringstream line(line_content);
    string word = "";
    string processed_word = "";
    
    //go through line, process words and add them to hash
    while (line >> word) {
        processed_word = stripNonAlphaNum(word);
        if (processed_word != "") {
            insertion(processed_word, path, line_num);
        }
    }
}

/*
 * name:      expand
 * purpose:   expand the capacity of the hash table
 * arguments: none
 * returns:   nothing
 * effects:   it exapnds the capacity of the hash table and rehashes the 
 *            values from the old hash table to the new one and finally
 *            swap the old and the new tables
*/
void Command::expand() {
    capacity = capacity * 2 + 2;
    //copy constructor
    vector<list<ValueInfo>> new_my_hash(my_hash);
    new_my_hash.resize(capacity);

    //iterator and copy over from table
    for (size_t i = 0; i < my_hash.size(); i++) {
        list<ValueInfo> &old_list = my_hash.at(i);
  
        for (const ValueInfo& old_info : old_list) {
            
            const string& key = toLower(old_info.original_word);
            int new_hash_index = hash<string>{}(key) % capacity;
            new_my_hash[new_hash_index].push_back(old_info);
        }

        my_hash.swap(new_my_hash);
    }
}

/*
 * name:      insertion
 * purpose:   insert the values into the hash table
 * arguments: a struct that includs information of the original word, 
 *            file path, line number, and the line content
 * returns:   nothing
 * effects:   it checks the load factor and expands the table when it's 
 *            necessary, it creates new ValueInfo objects and inserts them
 */
void Command::insertion(string &word, string &path, int line_num) {
    if (word == "") {
        return;
    }

    if (numItems/capacity >= 0.7) {
        expand();
    }
    
    //assign bucket
    string key = toLower(word);
    int index = hash<string>{}(key) % capacity;   

    //check if the word is already stored and if not add it to the list
    bool stored_already = true; 
    if (my_hash.at(index).back().line_num != line_num) {
        stored_already = false;
    } 
    if (my_hash.at(index).back().original_word != word ){
        stored_already = false;
    }

    if (not stored_already) {
        ValueInfo new_value_info(path, line_num, word);
        my_hash.at(index).push_back(new_value_info);
        //zoological line will be discussed in read me
        if (word == "Zoological" or word == "zoological") 
        numItems++;            
    }
}    

/*
 * name:      perform_search
 * purpose:   search for the value info that corresponds to the given word
 * arguments: a string word that represents the searching key, a boolean 
 *            i_search to check whether the search case is sensitive or not
 *            and an output file to print searc results to
 * returns:   nothing
 * effects:   print the file path, line number, and the line content for 
 *            the matching valueinfo
*/
void Command::perform_search(string &word, bool i_search, 
ofstream &outputFile) {
    string processed_word = stripNonAlphaNum(word);
    if(processed_word == "") {
        return;
    }   

    //find index, based on requested search iterate through list for matches
    string key = toLower(processed_word);
    int index = hash<string>{}(key) % capacity;
    values_list = my_hash.at(index);
    bool match_found = false;

    for (const ValueInfo &valueinfo : values_list) {
        if (i_search) {
            string stored = toLower(valueinfo.original_word);
            if (key == stored) {
                    match_found = true;
                    print(valueinfo.file_path, valueinfo.line_num, outputFile);
            }
        } else if (not i_search) {
            if (processed_word == valueinfo.original_word) {
                match_found = true;
                print(valueinfo.file_path, valueinfo.line_num, outputFile);
            }
        }
    }

    if (not match_found) {
        print_not_found(processed_word, i_search, outputFile);
    }
}

/*
 * name:      print
 * purpose:   print message when search is  found
 * arguments: a string that represents the file path, an integer that 
 *            represents the line number, and an ofstream output stream to 
 *            store the output messages
 * returns:   nothing
 * effects:   print the corresponding message when the search is found
*/
void Command::print(string &path, int line_num, ofstream &outputFile) {
    //open fine, declare var
    ifstream infile(path);
    int line_match = 0;
    string line_content = "";

    //iterate through file to the correct line then print it
    while (line_match < line_num) {
        getline(infile, line_content);
        line_match++;
    }
    infile.close();
    outputFile << path << ":" << line_num << ": " << line_content << endl;
}

/*
 * name:      print_not_found
 * purpose:   print message when search is not found
 * arguments: a string word that represenst the searching requested, a boolean 
 *            i_search to check whether the search case is sensitive or not, an
 *            ofstream output stream to store the output messages
 * returns:   nothing
 * effects:   print the corresponding message when the search is not found
*/
void Command::print_not_found(string &processed_word, bool i_search, 
ofstream &outputFile) {
    //print insensitive or insensitive unsuccessful search message
    if (i_search) {
        outputFile << processed_word << " Not Found." << endl;
    } else {
        outputFile << processed_word;
        outputFile << " Not Found. Try with @insensitive or @i." << endl;
    }
}