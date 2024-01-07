/*
 * HuffmanCoder.cpp
 * Eleanor Harty
 * Nov. 10, 2023
 * 
 * CS 15: Project 3 Zap
 *
 * This file contains an implementation of the HuffmanCoder class.
*/

#include "HuffmanCoder.h"

using namespace std;

/*
 * name:      HuffmanCoder
 * purpose:   default constructor to initialize program
 * arguments: none
 * returns:   nothing
 * effects:   no linker errors for not having a default constructor
*/
HuffmanCoder::HuffmanCoder() {

}

/*
 * name:      ~HuffmanCoder
 * purpose:   delete/recycle heap allocated data
 * arguments: none
 * returns:   nothing
 * effects:   no linker errors for not having a destructor
*/

HuffmanCoder::~HuffmanCoder() {

}

/*
 * name:      encoder
 * purpose:   to encode a given file of normal text
 * arguments: references to the names of an input and output file provided by 
 *            the user
 * returns:   nothing
 * effects:   creates a file containing the encoded version of the input
*/
void HuffmanCoder::encoder(const std::string &inputFile, const std::string
&outputFile) {
    //declare var
    ifstream given_file;

    //check that you can open the file, count char frequencies then close it
    open_or_die(given_file, inputFile);
    bool empty_file = count_freqs(given_file);
    given_file.close();

    //check if the file is empty
    if (empty_file) {
        cout << inputFile << " is empty and cannot be compressed." << endl;
        return;
    }

    //build the tree and generate codes for its pathways
    HuffmanTreeNode *root1 = build_tree();
    assign_branch_paths(root1, "", root1);

    //encode the text
    string encoded_text = encode(inputFile);

    //copy the text to an output file using BinaryIO and print out results
    BinaryIO binary_file;
    binary_file.writeFile(outputFile, serialize_tree(root1), encoded_text);
    cout << "Success! Encoded given text using " << encoded_text.length();
    cout << " bits." << endl;
    post_order_deletion(root1);
}

/*
 * name:      decoder
 * purpose:   decode a given file of encoded text
 * arguments: references to the names of an input and output file provided by 
 *            the user
 * returns:   nothing
 * effects:   creates a file containing the decoded version of the input
*/
void HuffmanCoder::decoder(const std::string &inputFile, const std::string
&outputFile) {
    //declare var
    ofstream output;

    //read in and decode the given encoded text
    BinaryIO reader;
    std::pair <string, string> return_pair = reader.readFile(inputFile);

    //deserialize the tree and return the encoded text
    HuffmanTreeNode *root2 = deserialize_tree(return_pair.first);
    string given_encoded_text = return_pair.second;
    string decoded_text = decode(given_encoded_text, root2);

    //open the output file copy your results to it and close the file
    open_or_die(output, outputFile);
    output << decoded_text;
    output.close();
    post_order_deletion(root2);
}

/*
 * name:      count_freqs
 * purpose:   read the input and count the occurrences of each character
 * arguments: an istream reference containing text
 * returns:   a boolean indicating if the file is empty or not
 * effects:   counts characters frequencies
*/
bool HuffmanCoder::count_freqs(istream &given_file) {
    //declare array and var
    int frequency_of_chars[256] = {0};
    char input;
    int count_empties = 0;

    //read in text for each char and store it's frequency in the array
    while (given_file.get(input)) {
        frequency_of_chars[int(input)] += 1;
    }

    //loop through array and print it's index as the char and value as freq
    for (int i = 0; i < 256; i++) {
        int frequency = frequency_of_chars[i];
        if (frequency != 0) {
            HuffmanTreeNode *new_node = new HuffmanTreeNode(i, frequency);
            node_queue.push(new_node);
        } else {
            count_empties++;
        }
    }
    
    //check if no frequencies were added to the array (ie the file is empty)
    if(count_empties == 256) {
        return true;
    }

    return false;
}

/*
 * name:      build_tree
 * purpose:   build a Huffman Tree
 * arguments: none
 * returns:   the root node of the Huffman Tree it constructs
 * effects:   creates new nodes
*/
HuffmanTreeNode *HuffmanCoder::build_tree() {
    //declare var
    HuffmanTreeNode *l;
    HuffmanTreeNode *r;

    //build the tree by creating and adding the nodes with a priority queue
    //from the bottom of the tree up
    while(node_queue.size () > 1) {
        l = node_queue.top();
        node_queue.pop();
        r = node_queue.top();
        node_queue.pop();
        HuffmanTreeNode *parent = new HuffmanTreeNode('\0', l->get_freq() + 
        r->get_freq(), l, r);
        node_queue.push(parent);
    }

    //return the root node
    return node_queue.top();
}

/*
 * name:      assign_branch_paths
 * purpose:   assign different codes to different pathways along the tree
 * arguments: A node representing the current node being used of the Huffman 
 *            Tree and a string to hold the paths generated, and a node that is
 *            the root node of the tree
 * returns:   nothing
 * effects:   creates codes representing different pathways
*/
void HuffmanCoder::assign_branch_paths(HuffmanTreeNode *curr, string path,
HuffmanTreeNode *root1) {
    //check if the curr node is a nullpointer or a leaf
    if (curr == nullptr) {
        return;
    } else if (curr->isLeaf()) {
        //if the leaf is not a root add it's value to the path
        if(curr == root1) {
            path = "0";
        }
        tree_pathways[curr->get_val()] = path;
    } else {
        //if you go left add a 0 to the path and if you go right add a 1
        assign_branch_paths(curr->get_left(), path + "0", root1);
        assign_branch_paths(curr->get_right(), path + "1", root1);
    }
}

/*
 * name:      encode
 * purpose:   create a string of the encoded version of the input file
 * arguments: a string representing the name of the inputfile
 * returns:   a string that contains the encoded version of the text in the
 *            provided file
 * effects:   returns a string
*/
string HuffmanCoder::encode(string file_name) {
    //declare var and open file
    ifstream in_file;
    open_or_die(in_file, file_name);
    stringstream stored_encoded_text;
    char input;

    //loop through the file and store the encoded version of it's data
    while(in_file.get(input)) {
        stored_encoded_text << tree_pathways[input];
    }
    
    //close the file and return the encoded text
    in_file.close();
    return stored_encoded_text.str();
}

/*
 * name:      serialize_tree
 * purpose:   create a serialized version of a given Huffman tree
 * arguments: a pointer to the root of a Huffman tree
 * returns:   a string that is a serialized version of the tree given to it
 * effects:   creates a serialized version of a tree
*/
string HuffmanCoder::serialize_tree(HuffmanTreeNode *curr) {
    //check if the tree is empty or one node, if not recursively go through the
    //left & right nodes of the tree, store the chars in leaves
    if (curr == nullptr) {
        return "\0";
    } else if (curr->isLeaf()) {
        string one_node_tree = "L";
        one_node_tree += curr->get_val();

        return one_node_tree;
    } else {
        string all_nodes = "I" + serialize_tree(curr->get_left()) + 
        serialize_tree(curr->get_right());

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
HuffmanTreeNode *HuffmanCoder::deserialize_tree(const std::string &s) {
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
HuffmanTreeNode *HuffmanCoder::deserialize_recursion(std::istringstream 
&serialized_tree) {
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
 * name:      decode
 * purpose:   decode the provided encoded text
 * arguments: a string of the encoded text given and a pointer to the current
 *            node
 * returns:   a string representing the decoded version of the text
 * effects:   decodes the text
*/
string HuffmanCoder::decode(string given_encoded_text, HuffmanTreeNode *curr) {
    //declare var
    string decrypted_text = "";
    stringstream encoded_ss(given_encoded_text);
    HuffmanTreeNode *root3 = curr;
    char input;

    //check if the root is a leaf, if so loop through the string and print the
    if(curr->isLeaf()) {
        return one_letter(given_encoded_text, curr);
    }

    //go through the encoded text and move through the given pathways until
    //reaching a leaf node, there return the leaf's value
    while(encoded_ss.get(input)) {
        if (input == '0') {
            curr = curr->get_left();
        } else {
            curr = curr->get_right();
        } if (curr->isLeaf()) {
            decrypted_text += curr->get_val();
            curr = root3;
        }
    }

    //check the encoding matches the HuffmanTree, if so return the decoded text
    if(curr != root3) {
        throw std::runtime_error("Encoding did not match Huffman tree.");
    }
    return decrypted_text;
}

/*
 * name:      one_letter
 * purpose:   decode files with only one type of character in them
 * arguments: a string of the encoded text given and a pointer to the current
 *            node
 * returns:   a string of the single character type in the file
 * effects:   creates a string of characters
*/
string HuffmanCoder::one_letter(string given_encoded_text, 
HuffmanTreeNode *curr) {
    //declare var
    char input = curr->get_val();
    string decrypted_text = "";

    //loop through the length of the encoded text and print the character
    //as many times as needed
    for (int i = 0; i < given_encoded_text.length(); i++) {
            if (given_encoded_text[i] == '0') {
                decrypted_text += input;
            } else {
                throw std::runtime_error
                    ("Encoding did not match Huffman tree.");
            }
        }
    
    //return results
    return decrypted_text;
}

/*
 * name:      open_or_die
 * purpose:   check if the file will open and if not throw an error
 * arguments: an stream variable and the name of the file we're trying to open
 * returns:   nothing
 * effects:   show an error if the file won't open
*/
template<typename streamtype>
void HuffmanCoder::open_or_die(streamtype &stream, string file_name) {
    //open the file and if it won't open show an error
    stream.open(file_name);
    if (not stream.is_open()) {
            throw std::runtime_error("Unable to open file " + file_name);
    }
}

/*
 * name:      post_order_deletion
 * purpose:   prevent valgrind errors and delete a given tree
 * arguments: a node that is initially the root of the tree used to traverse 
 *            and delete the tree
 * returns:   nothing
 * effects:   deletes a tree
*/
void HuffmanCoder::post_order_deletion(HuffmanTreeNode *curr) {
    //return if the root is null
    if(curr == nullptr) {
        return;
    }
    //traverse the tree in post order and delete it
    post_order_deletion(curr->get_left());
    post_order_deletion(curr->get_right());
    delete curr;
}