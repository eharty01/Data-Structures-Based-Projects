/*
 * phaseOne.cpp
 * Eleanor Harty
 * Nov. 8, 2023
 *
 * CS 15: Project 3 Zap
 *
 * This file contains an implementation of the phaseOne functions.
*/

#include "phaseOne.h"
#include "HuffmanTreeNode.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

/*
 * name:      count_freqs
 * purpose:   read the input and count the occurrences of each character
 * arguments: an istream reference containing text
 * returns:   nothing
 * effects:   prints the number of occurrences of each character
*/
void count_freqs(std::istream &text) {
    //declare array and var
    int frequency_of_chars[256] = {0};
    char input;

    //read in text for each char and store it's frequency in the array
    while (text.get(input)) {
        frequency_of_chars[int(input)] += 1;
    }

    //loop through array and print it's index as the char and value as freq
    for (int i = 0; i < 256; i++) {
        int frequency = frequency_of_chars[i];
        if (frequency != 0) {
            cout << char(i) << ": " << frequency << endl;
        }
    }
}

/*
 * name:      serialize_tree
 * purpose:   create a serialized version of a given Huffman tree
 * arguments: a pointer to the root of a Huffman tree
 * returns:   a string that is a serialized version of the tree given to it
 * effects:   creates a serialized version of a tree
*/
std::string serialize_tree(HuffmanTreeNode *root) {
    //check if the tree is empty or one node, if not recursively go through the
    //left & right nodes of the tree, store the chars in leaves
    if (root == nullptr) {
        return "\0";
    } else if (root->isLeaf()) {
        string one_node_tree = "L";
        one_node_tree += root->get_val();

        return one_node_tree;
    } else {
        string all_nodes = "I" + serialize_tree(root->get_left()) + 
        serialize_tree(root->get_right());

        return all_nodes;
    }
}

/*
 * name:      deserialize_tree
 * purpose:   deserialize a given serialized tree
 * arguments: a string containing serialized tree
 * returns:   a pointer to a node that is the root of the reconstructed
 *            Huffman tree
 * effects:   calls a function to reconstruct a Huffman tree
*/
HuffmanTreeNode *deserialize_tree(const std::string &s) {
    //declare var and call recursive helper function
    istringstream serialized_tree(s);
    return deserialize_recursion(serialized_tree);
}

/*
 * name:      deserialize_recursion
 * purpose:   deserialize a given serialized tree
 * arguments: a reference to an istringstream containing serialized tree
 * returns:   a pointer to a node that is the root of the Huffman tree we're
 *            reconstructing
 * effects:   deserializes and returns the nodes of a Huffman tree
*/
HuffmanTreeNode *deserialize_recursion(std::istringstream &serialized_tree) {
    //declare var
    char tree_part = '\0';

    //check if we're at the end of the serialized tree or if you're at a leaf 
    //node (if so return it), if not recur and return each node you find
    if (not serialized_tree.eof()) {
        serialized_tree.get(tree_part);
    } if (tree_part == 'L') {
        serialized_tree.get(tree_part);
        HuffmanTreeNode *leaf = new HuffmanTreeNode(tree_part, -1);
        return leaf;
    } else {
        //create inner node
        HuffmanTreeNode *inner_node = new HuffmanTreeNode('\0', -1);

        //define it's left and right nodes by defining them recursively
        inner_node->set_left(deserialize_recursion(serialized_tree));
        inner_node->set_right(deserialize_recursion(serialized_tree));

        //return found nodes
        return inner_node;
    }
}

/*
 * name:      post_order_deletion
 * purpose:   prevent valgrind errors and delete a given tree
 * arguments: a node that is the root of the tree used to traverse and delete
 *            the tree
 * returns:   nothing
 * effects:   deletes a tree
*/
void post_order_deletion(HuffmanTreeNode *root) {
    //return if the root is null
    if(root == nullptr) {
        return;
    }
    //traverse the tree in post order and delete it
    post_order_deletion(root->get_left());
    post_order_deletion(root->get_right());
    delete root;
}