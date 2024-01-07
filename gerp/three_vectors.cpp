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
#include <chrono>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>
#include <list>

#include "Command.h"
//#include "FSTree.h"
//#include "DirNode.h"

using namespace std;
using namespace std::chrono;

// ValueInfo::ValueInfo() {

// }
/*
 * name:      ValueInfo
 * purpose:   make a struct containing information about each word
 * arguments: a reference to a string containing the location of the word 
 *            within the directory (aka its file path), the word itself, 
 *            and the content of the line on which the word appears 
 *            respectively. Finally we pass an integer representing 
 *            the line number of the file where the word appeared.
 * returns:   nothing
 * effects:   creates a struct
*/
ValueInfo::ValueInfo(std::string &file_path, int line_num, 
std::string &line_content, std::string &original_word) {
    //fill in data points for the struct with passed in info
    this->file_path = file_path;
    this->line_num = line_num;
    this->line_content = line_content;
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
 * returns:   none
 * effects:   starts the gerp program
*/
void Command::start_gerp(DirNode *inputDirectory, ofstream &outputFile) {
    cout << "2" << endl;
    init_hash();
    traverser(inputDirectory, "");
    cout << "14" << endl;
    query_loop(outputFile);
    cout << "Goodbye! Thank you and have a nice day." << endl;
    outputFile.close();
}

/*
 * name:      init_hash
 * purpose:   initializes an empty hash table of given capacity
 * arguments: none
 * returns:   nothing
 * effects:   initializes our hash table
*/
void Command::init_hash() {
    cout << "3" << endl;
    //declare var
    numItems = 0;
    capacity = 200;

    //push back a list for each instance of the vector
    for (int i  = 0; i < capacity; i++) {
        list<ValueInfo> starter_list;
        vector<list<ValueInfo>> bucket;
        bucket.push_back(starter_list);
        my_hash.push_back(bucket);
    }
    cout << "4" << endl;
} 

/*
 * name:      query_loop
 * purpose:   accept user's commands and performs corresponding 
 *            functionalities
 * arguments: a pointer to the root of the directory tree, and an output file 
 *            stream to store the search results
 * returns:   none
 * effects:   promt the user for different queries, and print the serach 
 *            results into a provided file based on users' commands
*/
void Command::query_loop(std::ofstream &outputFile) {
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
            if (not outputFile.is_open()) {
                cerr << "OHNOOOO :( " << endl;
                exit(EXIT_FAILURE);
            }
        } else {
            string processed = stripNonAlphaNum(command);
            perform_search(processed, false, outputFile);
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
 * effects:   creates a path as to where the program is
*/
void Command::traverser (DirNode *root, std::string path) {
    cout << "5" << endl;
    //store names of the subdirectories and files leading to the current file
    path += root->getName() + "/";
    cout << "Processing directory: " << path << endl;

    //check for files and if so print their names
    if (root->hasFiles()) {
        for (int i = 0; i < root->numFiles(); i++) {
            cout << "Reading file: " << path + root->getFile(i) << endl;
            read(path + root->getFile(i));
        }
    }

    //check for subdirectories and recursively go through them to print their
    //files
    
    if (root->hasSubDir()) {
        cout << "Number of subdirectories: " << root->numSubDirs() << endl;
        for (int j = 0; j < root->numSubDirs(); j++) {
            cout << "Entering subdirectory: " << root->getSubDir(j)->getName() << endl;
            traverser(root->getSubDir(j), path);
            cout << "Leaving subdirectory: " << root->getSubDir(j)->getName() << endl;
        }
    }
    cout << "Leaving directory: " << path << endl;
}

/*
 * name:      read
 * purpose:   read the file and process the lines
 * arguments: a string that represents the path of the file
 * returns:   none
 * effects:   declare and update the variables for line content
 *            and the line number, traverse each line in the file, 
 *            and call the save_line function to save the values 
 *            to the hash table
*/
void Command::read(string path) {
    cout << "6" << endl;
    //declare var
    string line_content = "";
    int line_num = 1;

    //check if you can open file
    ifstream infile(path);
    if(not infile.is_open()) {
        cerr << "Cannot open provided file" << endl;
        exit(EXIT_FAILURE);
    }
    cout << "7" << endl;
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
 *            and a integer line_num that represents the line numeber in the 
 *            file
 * returns:   none
 * effects:   make an input string stream that represents the line content, 
 *            process each word from the line, and call insertion function to 
 *            insert the values into the hash table
 */
void Command::save_line(string line_content, string path, int line_num) {
    //declare var
    istringstream line(line_content);
    string word = "";
    string processed_word = "";
    cout << "8" << endl;
    
    //go through line, process words and add them to hash
    while (line >> word) {
        processed_word = stripNonAlphaNum(word);
        insertion(processed_word, path, line_num, line_content);
        cout << " -------------------------" << endl;
    }
    // cout << " ooooooooooooooooooooooooo-" << endl;
}

/*
void Command::expand_bucket(int index) {

    size_t new_bucket_capacity = my_hash.at(index).size() * 2 + 2;

    vector<list<ValueInfo>> new_bucket(new_bucket_capacity);

    for (size_t i = 0; i < my_hash.at(index).size(); i++) {
        for (const ValueInfo& old_info : my_hash.at(index).at(i)) {
            const string& key = toLower(old_info.original_word);
            int new_hash_index = hash<string>{}(key) % new_bucket_capacity;
            new_bucket[new_hash_index].push_back(old_info);
        }
    }

    my_hash.at(index).swap(new_bucket);
}
*/

/*
 * name:      expand
 * purpose:   expand the capacity of the hash table
 * arguments: none
 * returns:   none
 * effects:   it exapnds the capacity of the hash table and rehashes the 
 *            values from the old hash table to the new one and finally
 *            swap the old and the new tables
*/
void Command::expand() {
    cout << "10" << endl;
    capacity = capacity * 2 + 2;
    // copy constructor
    vector <vector<list<ValueInfo>>> new_my_hash(my_hash);
    new_my_hash.resize(capacity);
    // iterator

    for (size_t i = 0; i < my_hash.size(); i++) {
        for (const list<ValueInfo>& old_list : my_hash.at(i)) {
            for (const ValueInfo& old_info : old_list) {

                const string& key = toLower(old_info.original_word);

                int new_hash_index = hash<string>{}(key) % capacity;
                // new_my_hash[new_hash_index].push_back(old_info);
                list<ValueInfo> old_valueinfo;
                old_valueinfo.push_back(old_info);
                new_my_hash[new_hash_index].push_back(old_valueinfo);
                // my_hash.at(index).at(i).push_back(new_value_info);
            }
        }
    }

    cout << "11" << endl;
    my_hash.swap(new_my_hash);
    new_my_hash.clear();
    cout << "end of expand" << endl;
}


/*
 * name:      insertion
 * purpose:   insert the values into the hash table
 * arguments: a struct that includs information of the original word, 
 *            file path, line number, and the line content
 * returns:   none
 * effects:   it checks the load factor and expands the table when it's 
 *            necessary, it creates new ValueInfo objects and inserts them
 */
void Command::insertion(string word, string path, int line_num, 
string line_content) {
    cout << "9" << endl;
    if (word == "") {
        return;
    }

    if (numItems/capacity >= 0.7) {
        expand();
    }
    cout << "12" << endl;
    string key = toLower(word);
    int index = hash<string>{}(key) % capacity;  
    cout << "before for loop " << endl;
    bool stored_already = false;
    for (size_t i = 0; i < my_hash.at(index).size(); i++) {
        cout << "during loop" << endl;
        // if (not (my_hash.at(index).at(my_hash.at(index).at(i).size() - 1)).empty()) {
        //     expand_bucket(index);
        //     cout << "after for expand " << endl;
        // }
        // cout << "size of vector" << my_hash.at(index).size() << endl;
        // for (size_t j = 0; i < 10000; i++) {
        //     cout << "at the " << i << " bucket, the size is " << my_hash.at(j).size() << endl;
        // }
        // bool stored_already = false;
        for (const ValueInfo& stored_valueinfo : my_hash.at(index).at(i)) {
            if (stored_valueinfo.file_path == path and 
                stored_valueinfo.line_num == line_num and
                toLower(stored_valueinfo.original_word) == toLower(word)) {
                // cout << "does it even get here" << endl;
                ValueInfo new_value_info(path, line_num, line_content, word);
                my_hash.at(index).at(i).push_back(new_value_info);
                // cout << "does it even get here" << endl;
                stored_already = true;
            }
            // for (size_t j = 0; i < 10000; i++) {
            // cout << "at the " << i << " bucket, the size is " << my_hash.at(j).size() << endl;
            // }
        }    

        if (not stored_already) {
            ValueInfo new_value_info(path, line_num, line_content, word);
            my_hash.at(index).at(0).push_back(new_value_info);
            numItems++;
        }
        cout << "size of vector" << my_hash.at(index).size() << endl;

    }
    cout << "after for loop" << endl;
    cout << "13" << endl;

    // for (const auto & bucket : my_hash.at(index)) {
    //     for (const ValueInfo & stored_valueinfo : bucket) {
    //         cout << stored_valueinfo.original_word << " ";
    //     }
    // }
    cout << endl;
}

/*
 * name:      perform_search
 * purpose:   search for the value info that corresponds to the given word
 * arguments: a string word that represenst the searching key, a boolean 
 *            i_search to check whether the search case is sensitive
 * returns:   none
 * effects:   print the file path, line number, and the line content for 
 *            the matching valueinfo
*/
void Command::perform_search(string word, bool i_search, 
ofstream &outputFile) {
    cout << "15" << endl;
    string processed_word = stripNonAlphaNum(word);
    if(processed_word == "") {
        return;
    }   

    string key = toLower(processed_word);
    int index = hash<string>{}(key) % capacity;
    cout << "16" << endl;
    for (const auto &bucket : my_hash.at(index)) {
        bool match_found = false;
        for (const ValueInfo &valueinfo : bucket) {
            string stored = toLower(valueinfo.original_word);
            if (i_search == true) {
                if (key == stored) {
                    match_found = true;
                    outputFile << valueinfo.file_path << ":" 
                               << valueinfo.line_num 
                               << ": " << valueinfo.line_content << endl; 
                }
            } else if (not i_search) {
                if (processed_word == valueinfo.original_word) {
                    match_found = true;
                    outputFile << valueinfo.file_path << ":" 
                               << valueinfo.line_num
                               << ": " << valueinfo.line_content << endl; 
                }
            }
        }
        if (not match_found) {
            print_not_found(processed_word, i_search, outputFile);
        }
    }
    cout << "17" << endl;
}


void Command::print_not_found (string processed_word, bool i_search, 
ofstream &outputFile) {
    cout << "18" << endl;
    if (i_search) {
        outputFile << processed_word << " Not Found." << endl;
    } else {
        outputFile << processed_word;
        outputFile << " Not Found. Try with @insensitive or @i." << endl;
    }
}