/*
 * phaseOne.h
 * Eleanor Harty
 * Nov. 10, 2023
 * 
 * CS 15: Project 3 Zap
 *
 * FILE PURPOSE
 */

#include <istream>
#include <string>
#include <sstream>

#include "HuffmanTreeNode.h"

void count_freqs(std::istream &text);
std::string serialize_tree(HuffmanTreeNode *root);
HuffmanTreeNode *deserialize_tree(const std::string &s);
HuffmanTreeNode *deserialize_recursion(std::istringstream &serialized_tree);
void post_order_deletion(HuffmanTreeNode *root);