#include "BinaryNode.h"
using namespace std;

BinaryNode::BinaryNode(int key, string value)
{
	this->key = key;
	this->value = value;
	this->left = NULL;
	this->right = NULL;
	this->parent = NULL;
}

