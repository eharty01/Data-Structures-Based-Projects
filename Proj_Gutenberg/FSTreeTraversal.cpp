// /*
//  * FSTreeTraversal.cpp
//  * Eleanor Harty and Allen Wang
//  * Dec. 2, 2023
//  * 
//  * CS 15: Project 4 Gerp
//  *
//  * This program prints the subdirectories and files contained in a directory
//  * input by the user.
// */

// #include <iostream>
// #include <cstdlib>
// #include <cstdint>
// #include <string>

// #include "DirNode.h"
// #include "FSTree.h"
// #include "stringProcessing.h"
// #include "hash_table.h"

// // these are the includes needed for storing in the hash table
// #include <vector>
// #include <fstream>
// #include <sstream>
// #include <cctype>
// // algorithm is for to lower function
// #include <algorithm>
// // need to make sure the insert function in working and it handles the lower case words
// #include "hash_table.h"

// using namespace std;

// /*
//  * name:      main
//  * purpose:   see if we are traversing and reporting the directories correctly
//  * arguments: the files provided by the user (int argc and char *argv[])
//  * returns:   an int
//  * effects:   prints the results of tree travesal/the subdirectories and files
//  */

// // int main(int argc, char *argv[]) {
// //     //declare var
// //     string placeholder = "";

// //     //std::cout << "kiwi gets here" << std::endl;
// //     //check for the correct number of arguments
// //     if (argc != 2) {
// //         cerr << "Usage : ./traversal incorrect args" << endl;
// //         return EXIT_FAILURE;
// //     } 

// //     else {
// //         FSTree starter(argv[1]);

// //         std::cout << traverser(starter.getRoot(), placeholder);
// //     }
// //     return 0;
// // }

// void Command::query_loop(DirNode *inputDirectory) {
//     string command, word;
    
//     //while not at the end of the file query user for input and respond
//     //accordingly
//     while (not cin.eof()) {
//         cout << "Query? ";
//         cin >> command;
        
//         if (command == "@i" or "@insensitive") {
//             cin >> word;
//             string processed_word = stripNonAlphaNum(word);
//             string key = toLower(processed_word);
//             std::cout << "ready to call the function" << std::endl;
            
//             all_values_new(inputDirectory);
//         }
//     }
// }


// /*
//  * name:      traverser
//  * purpuse:   to traverse the given data and find all subdirectories & files
//  * arguments: a root to the base of the FSTree and a string to store previous
//  *            subdirectory and file names found
//  * returns:   a string that represents the span of directories and files given
//  * effects:   creates a string of 
// */
// std::string traverser (DirNode *root, std::string links) {
//     //declare var
//     std::string table_of_contents = "";

//     //check that there are files/subdirectories to inspect
//     if (root->isEmpty() or root == nullptr) {
//         return "";
//     } 

//     //check for subdirectories and recursively go through them to print their
//     //files
//     if (root->hasSubDir()) {
//         for (int i = 0; i < root->numSubDirs(); i++) {
//             table_of_contents += traverser(root->getSubDir(i), links + 
//             root->getName() + "/");
//         }
//     } 

//     //check for files and if so print their names
//     if (root->hasFiles()) {
//         for (int j = 0; j < root->numFiles(); j++) {
//             table_of_contents += links + root->getName() + "/" + 
//             root->getFile(j) + '\n';
//         }
//     }

//     //return the results of 
//     return table_of_contents;
// }

// vector<ValueInfo> all_values_new(DirNode *inputDirectory) {
//     // string path = traverser(inputdirectory, "");
//     std::cout << "finally get here" << std::endl;
//     // ValueInfo new_value_info(path, 100, "I love fruits");
    
//     // vector<ValueInfo> result;

//     // result.push_back(new_value_info);
// }


















// /*

// // process line
// void store_lines(string &filename, HashTable &HashTable) {
//     ifstream infile(filename);
//     if(infile.fail()) {
//         cerr << "Unable to open file " << filename << endl;
//         exit(EXIT_FAILURE);
//     }

//     // use traverser function to get the file path
//     string file_path = traverser(HashTable.getRoot());

//     string line_to_store;
//     int curr_line_num = 1;

//     while (getline(file, line_to_store)) {
//         store_info(line_to_store, file_path, curr_line_num, Hashtable);
//         curr_line_num++;
//     }

//     infile.close();
// }



// */

// // process_file
// // void process_file(string &inputFile) {
// //     std::ifsteam infile(inputfile);

// //     if(infile.fail()) {
// //         std::cerr << "Unable to open file " << inputFile << std::endl;
// //         exit(EXIT_FAILURE);
// //     }

// //     string line;
// //     while (getline(infile, line)) {
// //         istringsteam iss(line);
// //         store_key_info(line, HashTable &HashTable);
// //     }
// // }



// // // store keys
// // void store_key_info(std::string &line_content, HashTable &HashTable) {

// //     istringstream iss(line_content);
// //     string word;

// //     int num = 1;

// //     // we can try to figure how to use traverser function
// //     DirNode *newNode = getRoot();
// //     string path = traverser(newNode, "");


// //     while(iss >> word) {
// //         string word_to_extract = stripNonAlphaNum(word);
// //         std::cout << word_to_extract << std::endl;
// //         // KeyInfo key_info(word_to_extract);
// //         // ValueInfo value_info(path, num, "");
// //         // HashTable.insert(key_info, value_info);
// //         num++;
// //     }
// // }