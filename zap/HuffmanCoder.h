/*
 * HuffmanCoder.h
 * Eleanor Harty
 * Nov. 10, 2023
 * 
 * CS 15: Project 3 Zap
 *
 * This class represents a HuffmanTree that is made based on the input files
 * given by a user. These trees are used to encode and decode text the user
 * provides. The user must provide an input and output file for the program,
 * if they do they can choose to encode a file of text and have the results of
 * this encoding be placed in the output file they provided. Or they can choose
 * to decode a file and have the now readable results placed in an output file.
 */

#ifndef _HUFFMAN_CODER
#define _HUFFMAN_CODER

#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <istream>
#include <unordered_map>
#include <queue>
#include <vector>
#include "BinaryIO.h"
#include "HuffmanTreeNode.h"

class HuffmanCoder {
    // Feel free to add additional private helper functions as well as a
    // constructor and destructor if necessary
    public:
        //public constructor and destructor
        HuffmanCoder();
        ~HuffmanCoder();

        //predefined functions
        void encoder(const std::string &inputFile, const std::string 
        &outputFile);
        void decoder(const std::string &inputFile, const std::string 
        &outputFile);

    private:
        //declare var and ADTs
        std::unordered_map <char, std::string> tree_pathways;
        std::priority_queue <HuffmanTreeNode*, std::vector <HuffmanTreeNode*>, 
        NodeComparator> node_queue;

        //define private helper functions
        bool count_freqs(std::istream &text);
        HuffmanTreeNode *build_tree();
        void assign_branch_paths(HuffmanTreeNode *curr, std::string path, 
        HuffmanTreeNode *root1);
        std::string serialize_tree(HuffmanTreeNode *curr);
        std::string encode(std::string inputFile);
        HuffmanTreeNode *deserialize_tree(const std::string &s);
        HuffmanTreeNode *deserialize_recursion(std::istringstream 
        &serialized_tree);
        std::string decode(std::string given_encoded_text, 
        HuffmanTreeNode *curr);
        std::string one_letter(std::string given_encoded_text, 
        HuffmanTreeNode *curr);
        void post_order_deletion(HuffmanTreeNode *curr);

        //define previously given open or die function
        template<typename streamtype>
        void open_or_die(streamtype &stream, std::string file_name);
};

#endif