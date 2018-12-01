#pragma once
#include <string>
#include <sstream>


class BinaryNode{

private:
	int key;
	BinaryNode* left;
	BinaryNode* right;
	BinaryNode* parent;
	std::string value;

public:

	BinaryNode(int, std::string);
	~BinaryNode() {};

	int getKey() { return key; }
	std::string getValue() { return value; }
	BinaryNode* getLeftChild() { return left; }
	BinaryNode* getRightChild() { return right; }
	BinaryNode* getParent() { return parent; }

	
	void setLeftChild(BinaryNode* n) { left = n; }
	void setRightChild(BinaryNode* n) { right = n; }
	void setParent(BinaryNode* n) { parent = n; }
	void copyValues(const BinaryNode& other) {
		this->value = other.value;
		this->key = other.key;
	}


	std::string toString() const {
		std::stringstream str;
		str << "[" << key << "] " << value;
		return str.str();
	}

};


