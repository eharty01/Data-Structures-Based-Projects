#include <string>

#include "Command.h"
#include "hash_table.h"
#include "FSTreeTraversal.cpp"

KeyInfo::KeyInfo(std::string &key_name, std::vector<std::string> &same_keys) {
    this->key_name = key_name;
    this->same_keys = same_keys;
}

ValueInfo::ValueInfo(std::string &file_path, int line_num, 
std::string &line_content) {
    // Constructor implementation goes here
    this->file_path = file_path;
    this->line_num = line_num;
    this->line_content = line_content;
}

HashTable::HashTable() {
    myHash = new vector <list<ValueInfo>>;
    for (int i = 0; i < capacity; i++) {
        list<ValueInfo> list;
        myHash->push_back(list);
    } 
}

/*
void HashTable::inseeertion(string &word, int line_num, string &line_content) {
    word = stripNonAlphaNum(word);
    if (word == "") {
        return;
    }
   
    string key = toLower(word);

    bool word_exists = false;
    int index = hash<string>{}(key) % capacity;

    ValueInfo new_value_info(path, line_num, line_content);
    myHash->at(index).push_back(new_value_info);
}*/


//     ValueInfo new_value_info(path, line_num, line_content);
//     all_keys.at[index].push_back(new_value_info);

/*
    for (int i = 0; word < words.size(); i++) {
        if (word == words.at[i]) {
            ValueInfo new_value_info(path, line_num, line_content, word);
            words.at[i].list.push_back(new_value_info);
            word_exists = true;
        }
    }

    if (not word_exists) {
        words.push_back(word);
        ValueInfo new_value_info(path, line_num, line_content);
        words.at[end].list.push_back(new_value_info);
    }
    

    //add word info to the struct and push it back to the vector
    ValueInfo new_value_info(path, line_num, line_content);
    int temp = all_values_new.size();
    all_values_new.push_back(new_value_info);
    cout << all_values_new.size() << endl;

for (int i = 0; i < temp; i++) {
        cout << all_values_new[i].file_path << std::endl;
        cout << all_values_new[i].line_num << std::endl;
        cout << all_values_new[i].line_content << std::endl;
    }



    std::vector<std::string> all_keys;
    std::string word;
    std::istringstream iss(line_content);
    while (iss >> word) {
        all_keys.push_back(word);
    }

    int l = all_keys.size();
    for (int i = 0; i < l; i++) {
        std::cout << "after extraction: " << std::endl;
        std::cout << all_keys[i] << std::endl;
    }
    
// }



/*
 * name:      start_query
 * purpose:   
 * arguments: 
 * returns:   
 * effects:   
*/
/*
void Command::insertion(string word, string path, int line_num, 
                                           string line_content) {
    //check that there is a word to add
    if (word == "") {
        return;
    }

    //add word info to the struct and push it back to the vector
    ValueInfo new_value_info(path, line_num, line_content);
    int temp = all_values_new.size();
    all_values_new.push_back(new_value_info);
    cout << all_values_new.size() << endl; */

    /*
    for (int i = 0; i < temp; i++) {
        cout << all_values_new[i].file_path << std::endl;
        cout << all_values_new[i].line_num << std::endl;
        cout << all_values_new[i].line_content << std::endl;
    }*/
//}

// void HashTable::store_file(string file_name) {
//     std::string word;
//     std::istringstream iss(line_content);
    
//     while (iss >> word) {
//         bool keyFound = false;
//         for (auto &entry : table) {
//             if (entry.first.key_name == word) {
//                 entry.first.same_keys.push_back(word);
//                 keyFound = true;
//                 break;
//             }
//         }
        
//         if (!keyFound) {
//             KeyInfo new_key(word);
//             new_key.same_keys.push_back(word);
//             table[new_key] = ValueInfo("", -1, "");
//         }
//     }
// }

// void HashTable::insertion(string word, int line_num, string path) {
//     word = stripNonAlphaNum(word);
//     word = toLower(word);
//     if (word == "") {
//         return;
//     }

    
// }

// void HashTable::perform_search(string word, bool i_search) {
//     word = stripNonAlphaNum(word);

//     if (i_search) {
//         word = toLower(word);
//     }


//}



































// HashTable::HashTable() {
//     KeyInfo key_name = "";
//     ValueInfo string file_path = "";
//     ValueInfo line_num = "";
//     ValueInfo line_content = "";
// }

// HashTable::~HashTable() {

// }


// // KeyInfo::KeyInfo(string &keyword) : key_name(keyword) {

// // }

// // ValueInfo::ValueInfo(const string &file_name, int line_num, const string &line_content)
// //  : file_path(file_name), line_num(line_num), line_content(line_content) {
// //     // this->file_path = file_name;
// //     // this->line_num = line_num;
// //     // this->line_content = line_content;
// // }

// bool HashTable::lowered_exists(vector<string> &stored, vector<string> &to_store) {
//     if (stored.size() != to_store.size()) {
//         return false;
//     }
//     for (size_t i = 0; i < stored.size(); i++) {
//         if (stored[i] != to_store[i]) {
//             return false;
//         }
//     }

//     return true;
// }

// void HashTable::insert(const KeyInfo &key_name, const ValueInfo& value) {
    
//     std::vector<std::string> keys_fromtable;
//     for (const auto &entry : map) {
//         keys_fromtable.push_back(entry.first);
//     }


//     // bool lowered_exists = false;
//     // KeyInfo existed;
//     // for (size_t i = 0; i < keys_fromtable.size(); i++) {
//     //     if (keys_fromtable[i] == key_name) {
//     //         lowered_exists = true;
//     //         break; 
//     //     }
//     // }

//     // if (lowered_exists) {
//     //     for (size_t i = 0; i < keys_fromtable.same_keys_different_cases.size(); i++) {
//     //         if (same_keys_different_cases[i] == key_name) {
//     //             same_keys_different_cases.push_back(value);
//     //         }
//     //     }     
//     // } else {
//     //     vector<ValueInfo>& newloweredValues = map[existed];
//     //     newloweredValues.push_back(value);  
        
//     //     vector <string> newloweredKeys;
//     //     newloweredKeys.push_back(key_name);  
//     // }
// }

// std::vector<ValueInfo> HashTable::search(const std::vector<std::string>& key, bool sensitive) {
//     // if (sensitive) {
//     //     return map.[key];  // Search with the original case
//     // } else {
//     //     // Convert the search key to lowercase
//     //     // vector<string> lowercaseKey;
//     //     // for (const auto& word : key) {
//     //     //     lowercaseKey.push_back(toLower(word));
//     //     // }
//     //     return map.key.same_keys_different_cases.[key]  
//     // }
// }