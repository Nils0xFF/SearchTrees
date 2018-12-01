#pragma once
#include "RBNode.h"

class RBTree
{
private:
	RBNode * root = NULL;

protected:
	bool checkSubtree(RBNode* start);
	bool checkSubtree(RBNode* start, int max,int min);
	void remove(int key, RBNode* start);
	void rotateLeft(RBNode*);
	void rotateRight(RBNode*);
	void binaryInsert(RBNode*);
	void clean(RBNode*);
	std::string inorder(RBNode*);
	std::string levelOrderHelper(RBNode*);
	int heightSubtree(RBNode*);
	int blackHeight(RBNode* );
	int max(int a, int b) {
		if (a > b) return a;
		return b;
	}
public:
	RBTree() { root = NULL; }
	~RBTree() { clean(root), root = NULL; }
	void insert(RBNode* e);
	bool check();
	std::string search(int key);
	std::string toString();
	int height();
};

