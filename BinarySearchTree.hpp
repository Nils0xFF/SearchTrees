#pragma once
#include "BinaryNode.h"
#include <string>

class BinarySearchTree {
private:
	BinaryNode * root = NULL;

protected:
	bool checkSubtree(BinaryNode* start, int, int);
	int heightSubtree(BinaryNode* start);
	std::string inorder(BinaryNode* start);
	int max(int a, int b) {
		return (a > b ? a : b);
	}
	void clean(BinaryNode* start);

public:
	BinarySearchTree() {};
	~BinarySearchTree();
	void insert(BinaryNode* n);
	std::string search(int key);
	void remove(int key);
	void remove(int key, BinaryNode* start);
	bool check();
	int height();
	std::string toString();
};

