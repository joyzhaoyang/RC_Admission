/*
This file: BinaryTreeDepthFirstSearch.cpp
Programmer: Joy Zhao (yangzhao@tepper.cmu.edu)

Description: 
1. Basic infrastrucutre for binary tree (not binary search tree)
2. Implement Depth First Search

Notes:
1. BinaryTree class: Included a function "serialize" to visualize the tree
2. BinaryTree class: Included a function "deserialize" to (easily) construct the tree
3. Assume lower case is different from upper case

Known bugs:
1. Assume the node value is a single size string, i.e. a character
2. For "serialize" and "deserialize", the null children of leaf nodes are still printed out
3. Depth first search implemented using recursion, may not be efficient

To be improved:
1. More checks on node value to be a single string, or change it to char
2. Improve "serialize" and "deserialize"
3. Other methods for Depth first search
4. Breadth first search
5. Binary Tree -> General Tree (i.e. number of child nodes can be more than two)

Start on:      12/30/15
Last Modified: 12/30/15
*/

#include <iostream>
#include <sstream>
#include <string>
#include <assert.h>

using namespace std;

//############################## class Node ##############################

class Node {

public:

//********** member variables **********
	string val;
	Node *lChild;
	Node *rChild;

//********** constructor **********
	Node(string x): val(x),lChild(NULL),rChild(NULL) {}
	Node(string x, Node* l, Node* r): val(x),lChild(l),rChild(r) {}

//********** destructor **********
	~Node() {
		if (lChild != NULL) delete lChild;
		if (rChild != NULL) delete rChild;
	}

//********** other functions **********


};


//############################## class BinaryTree ##############################


class BinaryTree {

public:

//********** member variables **********
	Node* root;

//********** constructor **********
	BinaryTree(): root(NULL){}
	BinaryTree(Node* r): root(r){}

//********** destructor **********
	~BinaryTree() {
		if (root != NULL) delete root;
	}

//********** other functions **********

//***** Encodes a tree to a single string.
    string serialize() {
        ostringstream oss;;
		serialize(root,oss);
		return oss.str();
    }

//***** Decodes your encoded data to tree.
    void deserialize(string data) {
        istringstream iss(data);
        root = deserialize(iss);
    }

//***** Depth first search: by recursion
	string dfSearch (string input) {
		assert(input.size()==1);
		return dfSearch(input, root);
	}

//********** private functions **********
private:

//***** Support "serialize" function.
    void serialize(Node* root, ostringstream & oss) {
        if(root) {
            oss << root-> val << " ";
            serialize(root->lChild,oss);
//            oss << " ";
            serialize(root->rChild,oss);
        } else {
            oss << "$ "; // denote null
        }
    }

//***** Support "deserialize" function.
    Node* deserialize(istringstream & iss) {
        string val;
        iss >> val;
        if (val == "$") return nullptr;
        
        Node* root = new Node(val);
        root->lChild = deserialize(iss);
        root->rChild = deserialize(iss);
        
        return root;       
    }

//***** Support "dfSearch" function.
	string dfSearch (string input, Node* root) {
		if(root == NULL) {return "Not Found!";}
		else if (root->val == input) {return input;}

		string searchLeft  = dfSearch(input, root->lChild);
		string searchRight = dfSearch(input, root->rChild);

		if(searchLeft == input || searchRight == input) {return input;}
		else {return "Not Found!";}
	}

};

//############################## test ##############################

void main() {

	// Test case 1: ~ the tree in the question except this is a binary tree
	string str1 = "a b c d f g $ $ $ $ $ h $ $ $";
	BinaryTree * bTree1 = new BinaryTree();
	bTree1 -> deserialize(str1);
	cout << "Print binary tree 1:" << bTree1->serialize() << endl;
	cout << "Enter a char to search: " << endl;
	string input;
	cin >> input;
	cout << "The result of depth search in tree 1; " << bTree1->dfSearch(input) << endl;

	// Test case 2: empty tree
	string str2 = "$";
	BinaryTree * bTree2 = new BinaryTree();
	bTree2 -> deserialize(str2);
	cout << "Print binary tree 2:" << bTree2->serialize() << endl;
	cout << "The result of depth search in tree 2; " << bTree2->dfSearch(input) << endl;

	// Test case 2: tree include every letter
	string str3 = "c e n m o s r z q y l j k a g u b d h i f t p v x w $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $";
	BinaryTree * bTree3 = new BinaryTree();
	bTree3 -> deserialize(str3);
	cout << "Print binary tree 3:" << bTree3->serialize() << endl;
	cout << "The result of depth search in tree 3; " << bTree3->dfSearch(input) << endl;

	// delete the trees
	delete bTree1;
	delete bTree2;
	delete bTree3;
	
	// The fix
	cout << "Enter a char to end the program: " << endl;
	char c;
	cin >> c;

}
