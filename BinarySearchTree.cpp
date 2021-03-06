#include "BinarySearchTree.hpp"
#include <sstream>
#include <iostream>

using namespace std;

BinarySearchTree::~BinarySearchTree() {
	clean(root);
	root = NULL;
};

void BinarySearchTree::insert(BinaryNode* n) {
	if (this->root == NULL) {
		this->root = n;
		return;
	}
	BinaryNode* currentNode = root;
	while (currentNode != NULL) {
		if (n->getKey() > currentNode->getKey()) {
			if (currentNode->getRightChild()) { 
				currentNode = currentNode->getRightChild();
				continue; 
			}
			n->setParent(currentNode);
			currentNode->setRightChild(n);
			return;
		}
		else {
			if (currentNode->getLeftChild()) {
				currentNode = currentNode->getLeftChild();
				continue;
			} 
			n->setParent(currentNode);
			currentNode->setLeftChild(n);
			return;
		}
	}
}

string BinarySearchTree::search(int key) {
	BinaryNode* currentNode = root;
	while (currentNode) {
		if (key == currentNode->getKey()) return currentNode->getValue();
		if (key < currentNode->getKey()) currentNode = currentNode->getLeftChild();
		else currentNode = currentNode->getRightChild();
	}
	return "Not Found";
}

void BinarySearchTree::remove(int key) {
	remove(key, root);
}

void BinarySearchTree::remove(int key, BinaryNode* start) {
	BinaryNode* toRemove = start;
	while (toRemove) {
		if (key == toRemove->getKey()) break;
		if (key < toRemove->getKey()) toRemove = toRemove->getLeftChild();
		else toRemove = toRemove->getRightChild();
	}
	if (toRemove != NULL) {
		// if BinaryNode is a leaf, just drop it
		if ((toRemove->getRightChild() == NULL) && (toRemove->getLeftChild() == NULL)) {
			if (toRemove == root) {
				delete root;
				root = NULL;
				return;
			}
			if (toRemove->getKey() < toRemove->getParent()->getKey()) {
				toRemove->getParent()->setLeftChild(NULL);
			}
			else {
				toRemove->getParent()->setRightChild(NULL);
			}
			delete toRemove;
			return;
		}
		// if BinaryNode has only 1 Subtree, just skip it
		if (toRemove->getRightChild() == NULL) {
			if (toRemove == root) {
				root = toRemove->getLeftChild();
				toRemove->getLeftChild()->setParent(NULL);
			}
			else {
				if (toRemove == toRemove->getParent()->getLeftChild()) {
					toRemove->getParent()->setLeftChild(toRemove->getLeftChild());
					toRemove->getLeftChild()->setParent(toRemove->getParent());
				}
				else {
					toRemove->getParent()->setRightChild(toRemove->getLeftChild());
					toRemove->getLeftChild()->setParent(toRemove->getParent());
				}
			}
			delete toRemove;
			return;
		}
		if (toRemove->getLeftChild() == NULL) {
			if (toRemove == root) {
				root = toRemove->getRightChild();
				toRemove->getRightChild()->setParent(NULL);
			} 
			else {
				if (toRemove == toRemove->getParent()->getLeftChild()) {
					toRemove->getParent()->setLeftChild(toRemove->getRightChild());
					toRemove->getRightChild()->setParent(toRemove->getParent());
				}
				else {
					toRemove->getParent()->setRightChild(toRemove->getRightChild());
					toRemove->getRightChild()->setParent(toRemove->getParent());
				}
			}
			delete toRemove;
			return;
		}
		// if the BinaryNode got 2 Subtrees, search the smallest node in the right tree
		BinaryNode* smallest = toRemove->getRightChild();
		while (smallest->getLeftChild() != NULL) {
			smallest = smallest->getLeftChild();
		}
		// copy the smallest node into the one to be removed
		toRemove->copyValues(*smallest);
		// remove the smallest node form the tree
		remove(smallest->getKey(), smallest);
		return;
	}
	return;
}

bool BinarySearchTree::check() {
	if (root == NULL) return true;
	return checkSubtree(root, INT_MAX, INT_MIN);
}

int BinarySearchTree::height() {
	if (root == NULL) return 0;
	return heightSubtree(root);
}

bool BinarySearchTree::checkSubtree(BinaryNode* start, int max, int min) {

	if (start == NULL) return true;
	if (start->getKey() > max || start->getKey() < min) return false;

	return checkSubtree(start->getLeftChild(), start->getKey() - 1, min) &&
		checkSubtree(start->getRightChild(), max, start->getKey() +1);
}

int BinarySearchTree::heightSubtree(BinaryNode* start) {
	if (start == NULL || (start->getLeftChild() == NULL && start->getRightChild() == NULL)) {
		return 0;
	}
	return 1 + max(heightSubtree(start->getLeftChild()), heightSubtree(start->getRightChild()));
}

string BinarySearchTree::inorder(BinaryNode* start) {
	stringstream str;
	if (start != NULL) {
		
		if (start->getLeftChild()) str << inorder(start->getLeftChild());
		str << start->toString() << endl;
		if (start->getRightChild()) str << inorder(start->getRightChild());
	}
	return str.str();
}

string BinarySearchTree::toString() {
	stringstream str;
	str << inorder(root);
	return str.str();
}

void BinarySearchTree::clean(BinaryNode* start) {
	if (start != NULL) {
		if (start->getLeftChild()) clean(start->getLeftChild());
		if (start->getRightChild()) clean(start->getRightChild());
		delete start;
	}
	return;
}
