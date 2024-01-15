// #ifndef HASH_TABLE_H
// #define HASH_TABLE_H

// #include <iostream>
// #include <vector>
// #include <cctype>
// #include <functional>
// #include <algorithm>
// #include <string>
// #include <unordered_map>

// #include "Command.h"


// using namespace std;

// struct KeyInfo{ 
//     std::string key_name;
//     std::vector<std::string> same_keys;

//     KeyInfo(std::string &key_name, std::vector<std::string> &same_keys);

// };

// struct ValueInfo {
//     std::string file_path;
//     int line_num;
//     std::string line_content;

//     ValueInfo(std::string &file_path, int line_num, std::string &line_content);

//     // ValueInfo() {
//     //     file_path = "";
//     //     line_num = -1;
//     //     line_content = "";
//     // }
// };

// class HashTable {
// public:
//     HashTable();
//     void inseeertion(string word, string path, int line_num, string line_content);
//     void init_hash();

//     // void HashTable::store_file(string file_name);
// private:

//     // std::unordered_map<KeyInfo, ValueInfo> table;

//     int numItems, capacity;
//     //void insertion(string word, string path, int line_num, string line_content);


//     // std::string toLower(std::string &str);
//     // void insertion(string word, int line_num, string path);
//     // void perform_search(string word, bool i_search);
// };



































// // //struct for key word info
// // struct KeyInfo {
// //     // vector<string> key_words;
// //     string key_name;
// //     vector <string> same_keys_different_cases;

// //     KeyInfo(string &keyword);
// // };

// // //struct for value info
// // struct ValueInfo {
// //     string file_path;
// //     int line_num;
// //     string line_content;

// //     ValueInfo(const string &file_name, int line_num, const string &line_content);
// // };


// // class HashTable {
// // public:
// //     HashTable();
// //     ~HashTable();

// //     // int insertChaining(string keyword, ValueType value, HashFunction 
// //     //hashFunction);
// //     // void print();

// //     // void rehashing();
// //     void insert(const KeyInfo &key_name, const ValueInfo &value_info);
// //     vector<ValueInfo> search(const vector<string>& key, bool sensitive = true);

// // private:
// //     unordered_map<vector<string>, vector<ValueInfo>> map;

// //     bool lowered_exists(vector<string> &stored, vector<string> &to_store);
   
// // };

// #endif