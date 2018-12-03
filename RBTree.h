#pragma once
#include "RBNode.h"

class RBTree
{
private:
	RBNode * root = NULL;

protected:
	// helper function to check the given subtree for violations
	bool checkSubtree(RBNode* start, int max,int min);
	void remove(int key, RBNode* start); // NOT IMPLEMENTED
	// left rotates the subtree around the parent
	void rotateLeft(RBNode*);
	// right rotates the subtree around the parent
	void rotateRight(RBNode*);
	// binaryInsertFunction
	void binaryInsert(RBNode*);
	// recursive function to free the dynamic allocated memory
	void clean(RBNode*);
	// helperfunctions for toString methods
	std::string inorder(RBNode*);
	std::string levelOrderHelper(RBNode*);
	// helper function to calculate the heigth of the given subtree
	int heightSubtree(RBNode*);
	// helper function to calculate the black heigth of the given subtree
	int blackHeight(RBNode* );
	// helper function to return the greater of two integers
	int max(int a, int b) {
		if (a > b) return a;
		return b;
	}
public:
	// constructor
	RBTree() { root = NULL; }
	// destructor
	~RBTree() { clean(root), root = NULL; }
	// insert Function
	void insert(RBNode* e);
	// checks the tree for posible violations
	bool check();
	// returns the value for the node with the given key
	std::string search(int key);
	// toString method
	std::string toString();
	// returns the heigth of the tree
	int height();
};

