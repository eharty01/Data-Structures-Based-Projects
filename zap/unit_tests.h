/*
 * unit_tests.h
 * Eleanor Harty
 * Nov. 8, 2023
 *
 * CS 15: Project 3 Zap
 *
 * Create tests to check that functions within my phaseOne and HuffmanCoder
 * class are running properly.
*/

#include "phaseOne.h"
#include "HuffmanCoder.h"
#include "ZapUtil.h"
#include <cassert>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

//test count_freq with an empty string
void no_rep_count_freq() {
    std::string example = "";
    std::istringstream test(example);
    count_freqs(test);
}

//test count_freq with a word with no repetition
void no_rep_count_freq() {
    std::string example = "cat";
    std::istringstream test(example);
    count_freqs(test);
}

//test count_freq when there are repeating letters
void rep_count_freq() {
    std::string example = "Banana";
    std::istringstream test(example);
    count_freqs(test);
}

//test count freq when there are unusual characters
void weird_char_count_freq() {
    std::string example = "!#(&%@PÊ";
    std::istringstream test(example);
    count_freqs(test);
}

//test serialize on an empty tree
void serialize_empty {
    HuffmanTreeNode *root = nullptr;
    
    std::string input = serialize_tree(root);
    assert(input == "\0");
}

//test serialize on tree of one node
void serialize_one_node {
    HuffmanTreeNode *root = HuffmanTreeNode('a', 1);
    
    std::string input = serialize_tree(root);
    assert(input == "a");
}

//test serialize tree on a small tree
void serialize_tree_simple() {
    HuffmanTreeNode leaf1 = HuffmanTreeNode('a', 1);
    HuffmanTreeNode leaf2 = HuffmanTreeNode('b', 2);
    HuffmanTreeNode *internalnode = HuffmanTreeNode('\0', -1, leaf1, leaf2);

    std::string input = serialize_tree(internalnode);
    assert(input == "ILaLb");
}

//see if it can serialize the example tree in the spec
void serialize_tree_given() {
    char internalNodeVal = '\0';
    HuffmanTreeNode *root1 = makeFigure1Tree(internalNodeVal);

    std::string input = serialize_tree(root1);
    assert(input == "IIILaLbILeLfILcLd");

    post_order_deletion(root1);
}

//see if it can deserialize a small tree
void deserialize_tree_simple() {
    HuffmanTreeNode leaf1 = HuffmanTreeNode('a', 1);
    HuffmanTreeNode leaf2 = HuffmanTreeNode('b', 2);
    HuffmanTreeNode *internalnode = HuffmanTreeNode('\0', -1, leaf1, leaf2);

    printTree(internalnode, internalNodeVal);
    post_order_deletion(internalnode);
}

//see if it can deserialize the example tree given in the spec
void deserialize_given() {
    char internalNodeVal = '\0';

    HuffmanTreeNode *root1 = makeFigure1Tree(internalNodeVal);

    std::string input = serialize_tree(root1);
    HuffmanTreeNode *root2 = deserialize_tree(input);

    assert(treeEquals(root1, root2, false, true));
    post_order_deletion(root1);
    post_order_deletion(root2);
}

//test building the tree given in the spec
void test_build_tree() {
    char internalNodeVal = '\0';
    HuffmanTreeNode *root2 = makeFigure1Tree(internalNodeVal);

    HuffmanCoder array;

    array.count_freqs['a'] = 1;
    array.count_freqs['b'] = 1;
    array.count_freqs['c'] = 2;
    array.count_freqs['d'] = 2;
    array.count_freqs['e'] = 1;
    array.count_freqs['f'] = 1;
    array.build_tree();
    assert(treeEquals(root2, array.root1, true, true));
}

//test assinging pathways on the tree given in the spec
void test_assign_branch_pathways() {
    char internalNodeVal = '\0';
    HuffmanTreeNode *root2 = makeFigure1Tree(internalNodeVal);

    HuffmanCoder array;
    array.assign_branch_paths(root2, "");

    tree_pathways['a'] = "000";
    tree_pathways['b'] = "001";
    tree_pathways['c'] = "10";
    tree_pathways['d'] = "11";
    tree_pathways['e'] = "010";
    tree_pathways['f'] = "011";

    for(int i = 0; i < 256; i++) {
        assert(tree_pathways[char(i)] == array.tree_pathways[char(i)]);
    }
}