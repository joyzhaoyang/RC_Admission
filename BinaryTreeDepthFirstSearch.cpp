/*
This file: BinaryTree.cpp
Programmer: Joy Zhao (yangzhao@tepper.cmu.edu)

Description: 
1. Basic infrastrucutre for binary tree (not binary search tree)
2. Implement Depth First Search

Notes:
1. BinaryTree class: Included a function "serialize" to visualize the tree (by depth and by breadth-using queue)
2. BinaryTree class: Included a function "deserialize" to (easily) construct the tree (by depth and by breadth-using queue)
3. Assume lower case is different from upper case - case sensitive
   (case insensitive code included in the comments)

Known bugs:
1. Assume the node value is a single size string, i.e. a character 
--- fixed on 01/08/16

2. For "serialize" and "deserialize"(by depth), the null children of leaf nodes are still printed out
--- Comments on 01/08/16: this should be no problem for by depth printing, otherwise it may cause confusion.

3. Depth first search implemented using recursion, may not be efficient

To be improved:
1. More checks on node value to be a single string, or change it to char
--- changed the value of the node from string to char on 01/08/16
--- improved the testing cases in the main function on 01/08/16

2. Other methods for "serialize" and "deserialize", e.g. by breadth
--- added "serialize" and "deserialize" (by breadth) functions using queue on 01/09/16

3. Other methods for Depth first search 
4. Breadth first search
5. Binary Tree -> General Tree (i.e. number of child nodes can be more than two)

Start on:      12/30/15
version 1:     01/08/16
version 2:     01/09/16
Last Modified: 01/09/16
*/

#include <iostream>
#include <sstream>
#include <string>
#include <assert.h>
#include <queue> 


using namespace std;


//############################## class Node ##############################

class Node {

public:

//********** member variables **********
	char val;
	Node *lChild;
	Node *rChild;

//********** constructor **********
	Node(char x)                  : val(x),lChild(NULL),rChild(NULL) {}
	Node(char x, Node* l, Node* r): val(x),lChild(l),rChild(r) {}
	Node(char x, Node* l)         : val(x),lChild(l),rChild(NULL) {} // if only one child, always the left child

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
//	BinaryTree() {}
	BinaryTree(): root(NULL){}
	BinaryTree(Node* r): root(r){}

//********** destructor **********
	~BinaryTree() {
		if (root != NULL) delete root;
	}

//********** other functions **********

//***** Encodes a tree to a single string.
	// Method 1: by recursion
    string serialize() {
        ostringstream oss;;
		serialize(root,oss);
		return oss.str();
    }

	// Method 2; using queue
	string serializeByQueue(){
		queue<Node*> q;
		string output;
		
		q.push(root);

		while (!q.empty()){
			if (q.front()==nullptr) {
				output = output + "$ ";
			}else {
				q.push(q.front()->lChild); // insert at the back
				q.push(q.front()->rChild);
				output = output + q.front()->val + " ";
			} // end of if
			q.pop();
		} // end of while
		return output;
	}

//***** Decodes your encoded data to tree.
	// Method 1: by recursion
    void deserialize(string data) {
        istringstream iss(data);
        root = deserialize(iss);
    }

	// Method 2; using queue
	void deserializeByQueue(string data) {
        root = nullptr;
        queue <Node**> q; // store the address of all the nodes
        // so that when the node is poped from the queue, we can still reference to the nodes
        
        q.push(&root); // address of the root node
        
        string::iterator curr = data.begin();
        string::iterator last;
        string s_val;
		char   c_val; // initialize a value for debugging 
		int ii = 1; // loop control, for debugging

        while(curr != data.end()){
            Node ** addr = q.front();
            
            if(*curr == '$'){ // null node
                advance(curr,2); // move to next char
                // 2 because we need to consider the empty space between the chars
                // because all the nodes are initialized with NULL, no need to change its value
            } else {
                last = find(curr,data.end(),' '); // find the next empty space 
				s_val = string(curr,last); 
				c_val = s_val[0]; // convert the string to char
                *addr = new Node(c_val);
                q.push(&((*addr)->lChild)); // push the left child of the current node to the queue
                // null value at the moment, the value will be assigned in the next while loop
                q.push(&((*addr)->rChild));// same for the right child

                curr = next(last); // move to the next char
            } // end of if
            q.pop(); // remove the current front node (address)
			ii++;
        } // end of while
        
    }

//***** Depth first search: by recursion
	string dfSearch (char c_input) {
//		assert(input.size()==1);
		return dfSearch(c_input, root);
	}

//********** private functions **********
private:

//***** Support "serialize" function.
    void serialize(Node* root, ostringstream & oss) {
        if(root) {
            oss << root-> val << " ";
//			if (root->lChild==NULL && root->rChild==NULL){}
//			else{
				serialize(root->lChild,oss);
//              oss << " ";
				serialize(root->rChild,oss);
//			}
        } else {
            oss << "$ "; // denote null
        }
    }

//***** Support "deserialize" function.
    Node* deserialize(istringstream & iss) {
        string val;
        iss >> val;
        if (val == "$") return nullptr;
        
		char c_val = val[0]; // convert it to char
        Node* root = new Node(c_val);
        root->lChild = deserialize(iss);
        root->rChild = deserialize(iss);
        
        return root;       
    }

//***** Support "dfSearch" function.
	string dfSearch (char c_input, Node* root) {
		// conver c_input to a string
		string s_input; 
		s_input.push_back(c_input);

		if(root == NULL) {return "Not Found!";}
//		else if (tolower(root->val) == tolower(c_input)) {return s_input;} // case insensitive
		else if (root->val == c_input) {return s_input;}  // case sensitive

		string searchLeft  = dfSearch(c_input, root->lChild);
		string searchRight = dfSearch(c_input, root->rChild);

		if(searchLeft == s_input || searchRight == s_input) {return s_input;}
		else {return "Not Found!";}
	}

};

//############################## test ##############################

void main() {

	// Test case 1: ~ the tree in the question except this is a binary tree
	Node * nodeh = new Node('h');
	Node * nodeg = new Node('g',nodeh);
	Node * nodec = new Node('c',nodeg);
	Node * noded = new Node('d');
	Node * nodef = new Node('f');
	Node * nodeb = new Node('b',noded,nodef);
	Node * nodea = new Node('a',nodeb,nodec);
	BinaryTree * bTree1 = new BinaryTree(nodea);

	string str1      = "a b d $ $ f $ $ c g h $ $ $ $ ";
	BinaryTree * bTree1copy = new BinaryTree();
	bTree1copy -> deserialize(str1);

//	string str1queue = "a,b,c,d,f,g,$,$,$,$,$,h,$,$,$ ";
	string str1queue = "a b c d f g $ $ $ $ $ h $ $ $ ";
	BinaryTree * bTree1queuecopy = new BinaryTree();
	bTree1queuecopy -> deserializeByQueue(str1queue);

	cout << "Print binary tree 1           :   " << bTree1->serialize() << endl;
	cout << "Print binary tree 1 copy      :   " << bTree1copy->serialize() << endl;
	cout << "Print binary tree 1 queue     :   " << bTree1->serializeByQueue() << endl;
	cout << "Print binary tree 1 queue copy:   " << bTree1queuecopy->serializeByQueue() << endl << endl;
	
	cout << "Enter a char to search: " << endl;
	char input;
	cin >> input;
	cout << "The result of depth search in tree 1:   " << bTree1->dfSearch(input) << endl << endl;


	// Test case 2: empty tree

//	string str2 = "$";
	BinaryTree * bTree2 = new BinaryTree();
//	bTree2 -> deserialize(str2);
	cout << "Print binary tree 2      :   " << bTree2->serialize() << endl;
	cout << "Print binary tree 2 queue:   " << bTree2->serializeByQueue() << endl << endl;
	cout << "The result of depth search in tree 2:   " << bTree2->dfSearch(input) << endl << endl;


	// Test case 3: tree include every letter
	Node * node3u = new Node('u'); // 5.1
	Node * node3b = new Node('b'); // 5.2
	Node * node3d = new Node('d'); // 5.3
	Node * node3h = new Node('h'); // 5.4
	Node * node3i = new Node('i'); // 5.5
	Node * node3f = new Node('f'); // 5.6
	Node * node3t = new Node('t'); // 5.7
	Node * node3p = new Node('p'); // 5.8
	Node * node3v = new Node('v'); // 5.9
	Node * node3x = new Node('x'); // 5.10
	Node * node3w = new Node('w'); // 5.11

	Node * node3z = new Node('z',node3u,node3b); // 4.1
	Node * node3q = new Node('q',node3d,node3h); // 4.2
	Node * node3y = new Node('y',node3i,node3f); // 4.3
	Node * node3l = new Node('l',node3t,node3p); // 4.4
	Node * node3j = new Node('j',node3v,node3x); // 4.5
	Node * node3k = new Node('k',node3w);       // 4.6
	Node * node3a = new Node('a');             // 4.7
	Node * node3g = new Node('g');             // 4.8

	Node * node3m = new Node('m',node3z,node3q); // 3.1
	Node * node3o = new Node('o',node3y,node3l); // 3.2
	Node * node3s = new Node('s',node3j,node3k); // 3.3
	Node * node3r = new Node('r',node3a,node3g); // 3.4

	Node * node3e = new Node('e',node3m,node3o); // 2.1
	Node * node3n = new Node('n',node3s,node3r); // 2.2

	Node * node3c = new Node('c',node3e,node3n); // 1.1

	BinaryTree * bTree3 = new BinaryTree(node3c);

	string str3 = "c e m z u $ $ b $ $ q d $ $ h $ $ o y i $ $ f $ $ l t $ $ p $ $ n s j v $ $ x $ $ k w $ $ $ r a $ $ g $ $ ";
	BinaryTree * bTree3copy = new BinaryTree();
	bTree3copy -> deserialize(str3);

	string str3queue = "c e n m o s r z q y l j k a g u b d h i f t p v x w $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ ";
	BinaryTree * bTree3queuecopy = new BinaryTree();
	bTree3queuecopy -> deserializeByQueue(str3queue);

	cout << "Print binary tree 3           :   " << bTree3->serialize() << endl;
	cout << "Print binary tree 3 copy      :   " << bTree3copy->serialize() << endl;
	cout << "Print binary tree 3 queue     :   " << bTree3->serializeByQueue() << endl;
	cout << "Print binary tree 3 queue copy:   " << bTree3queuecopy->serializeByQueue() << endl << endl;
	cout << "The result of depth search in tree 3:   " << bTree3->dfSearch(input) << endl << endl;

	// delete the trees
	delete bTree1;
	delete bTree1copy;
	delete bTree1queuecopy;
	delete bTree2;
	delete bTree3;
	delete bTree3copy;
	delete bTree3queuecopy;
	
	// The fix
	cout << "Enter a char to end the program: " << endl;
	char c;
	cin >> c;

}
