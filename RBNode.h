#pragma once
#include "BinaryNode.h"
#include <sstream>

enum COLOR {
	BLACK,
	RED
};

class RBNode
{
private:
	int key;
	RBNode* left;
	RBNode* right;
	RBNode* parent;
	std::string value;
	COLOR color;
public:
	RBNode(int key, std::string value){
		this->key = key;
		this->value = value;
		color = BLACK;
	};
	~RBNode();

	COLOR getColor() { return color; }
	void setColor(COLOR c) { color = c; }

	int getKey() { return key; }
	std::string getValue() { return value; }
	RBNode* getLeftChild() { return left; }
	RBNode* getRightChild() { return right; }
	RBNode* getParent() { return parent; }


	void setLeftChild(RBNode* n) { left = n; }
	void setRightChild(RBNode* n) { right = n; }
	void setParent(RBNode* n) { parent = n; }
	void copyValues(const RBNode& other) {
		this->value = other.value;
		this->key = other.key;
	}


	RBNode* getGrandparent()
	{
		return this->getParent()->getParent();
	}

	RBNode* getUncle()
	{
		if (getParent() == getGrandparent()->getLeftChild())
			return getGrandparent()->getRightChild();
		else
			return getGrandparent()->getLeftChild();
	}

	std::string toString() const {
		std::stringstream str;
		str << "[" << key << "] " << value << " Color: " << this->color;;
		return str.str();
	}

};

