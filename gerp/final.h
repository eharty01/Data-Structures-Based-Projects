/*
 * Command.h
 * Eleanor Harty
 * Dec. 5, 2023
 * 
 * CS 15: Project 4 Gerp
 *
 * FILE PURPOSE
*/

#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

#include "stringProcessing.h"
#include "DirNode.h"
#include "FSTree.h"

using namespace std;

struct KeyInfo{ 
    std::string key_name;
    std::vector<std::string> same_keys;

    KeyInfo(std::string &key_name, std::vector<std::string> &same_keys);
};


struct ValueInfo {
    std::string file_path;
    int line_num;
    std::string line_content;
    string original_word;

    // std::vector<std::string> already_processed;
    
    ValueInfo(std::string &file_path, int line_num, std::string &line_content,
    std::string &original_word);
};

class Command {

public:
    void start_gerp(DirNode *inputDirectory, std::ofstream &outputFile);
    ~Command();


private:
    vector<list<ValueInfo>>my_hash;
    int capacity = 10000;
    int numItems;
  
    vector<string> all_keys;
    list<ValueInfo> values_list;
    
    // // vector<ValueInfo> all_values_new;
    void expand();
    void init_hash();
    void print();
    void query_loop(std::ofstream &outputFile);
    void traverser (DirNode *root, std::string path);


    void read(string path);
    void save_line(string line_content, string path, int line_num);
    void insertion(string word, string path, int line_num, 
    string line_content);
    void perform_search(string word, bool i_search, ofstream &outputFile);
    void print_not_found (string processed_word, bool i_search, 
    ofstream &outputFile);
    // bool print_insensitive(string key, ofstream &outputFile);
    // void print(const ValueInfo &valueinfo : values_list);
    //void print(string word, bool i_search, int index);
    // void print(const ValueInfo& value_info);
    //void random_name(DirNode *inputDirectory);
};

#endif