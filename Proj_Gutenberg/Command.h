/*
 * Command.h
 * Eleanor Harty and Allen Wang
 * Dec. 5, 2023
 * 
 * CS 15: Project 4 Gerp
 *
 * This class represents the gerp program. It will read in and store all
 * distinct words in a user provided directory and if the user decides to 
 * search for them will print to an outputFile where the user can find these
 * words in terms of the file, line number, and entire line which contains
 * the word. The user may search for words with only the same capitialization
 * as they input with a sensitive search, disregard capitalization and search
 * matching words of any permutation of capitalization. They can also choose
 * midway through searching to direct the results of their search to another
 * file and from then on their results will be printed there. When the user
 * is done searching or the file they've provided ends the program will quit. 
*/

#ifndef COMMAND_H
#define COMMAND_H

//boilerplate
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

#include "stringProcessing.h"
#include "DirNode.h"
#include "FSTree.h"

using namespace std;

//struct for information on each stored word
struct ValueInfo {
    std::string file_path;
    int line_num;
    string original_word;

    ValueInfo(std::string &file_path, int line_num, 
    std::string &original_word);
};

class Command {
//public functions (constuctor and destructor)
public:
    void start_gerp(DirNode *inputDirectory, std::ofstream &outputFile);
    ~Command();

private:
    //declare variables and data structures
    vector<list<ValueInfo>>my_hash;
    int capacity;
    int numItems;
  
    list<ValueInfo> values_list;
    
    //private member functions
    void expand();
    void init_hash();
    void query_loop(std::ofstream &outputFile);
    void traverser (DirNode *root, std::string &path);
    void read(string &path);
    void save_line(string &line_content, string &path, int line_num);
    void insertion(string &word, string &path, int line_num);
    void perform_search(string &word, bool i_search, ofstream &outputFile);
    void print_not_found (string &processed_word, bool i_search, 
    ofstream &outputFile);
    void print(string &path, int line_num, ofstream &outputFile);
};

#endif