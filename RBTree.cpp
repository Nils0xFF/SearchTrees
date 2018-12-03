#include "RBTree.h"
#include <queue>
using namespace std;

void RBTree::remove(int key, RBNode* start) {

}

void RBTree::insert(RBNode* node) {

	// if there is no root the new Node is now the root
	if (root == NULL) {
		// color the root Black
		node->setColor(BLACK);
		root = node;
		return;
	}
	// color the new node Red
	node->setColor(RED);
	node->setLeftChild(NULL); // NIL-Knoten
	node->setRightChild(NULL); // NIL-Knoten
	// make a binary insert
	binaryInsert(node);

	// fix the violation in the tree
	RBNode* currentNode = node;
	while ((currentNode != root) && (currentNode->getColor() == RED) && (currentNode->getParent()->getColor() == RED)) {

		// Case A: parent is left child of grandparent
		if (currentNode->getParent() == currentNode->getGrandparent()->getLeftChild()) {
			// Case A1: The uncle is also Red
			// Just recolor the subtree and continue upwards
			if (currentNode->getUncle() != NULL && currentNode->getUncle()->getColor() == RED) {
				currentNode->getGrandparent()->setColor(RED);
				currentNode->getParent()->setColor(BLACK);
				currentNode->getUncle()->setColor(BLACK);
				currentNode = currentNode->getGrandparent();
			}
			// Case A2: The uncle is black
			else {
				// Case A2a: currentNode is the rigth Child
				// rotate left
				if (currentNode == currentNode->getParent()->getRightChild()) {
					currentNode = currentNode->getParent();
					rotateLeft(currentNode);
				}

				// Case A2a and A2b: currentNode now is the rightChild
				// rotate right
				currentNode->getParent()->setColor(BLACK);
				currentNode->getGrandparent()->setColor(RED);
				rotateRight(currentNode->getGrandparent());

			}
		}
		// Case B: parent is right child of grandparent
		else {			
			// Case B1: The uncle is also Red
			// Just recolor the subtree and continue upwards
			if (currentNode->getUncle() != NULL && currentNode->getUncle()->getColor() == RED) {
				currentNode->getGrandparent()->setColor(RED);
				currentNode->getParent()->setColor(BLACK);
				currentNode->getUncle()->setColor(BLACK);
				currentNode = currentNode->getGrandparent();
			}
			// Case B2: The uncle is black
			else {
				// Case B2a: currentNode is the left Child
				// rotate left
				if (currentNode == currentNode->getParent()->getLeftChild()) {
					currentNode = currentNode->getParent();
					rotateRight(currentNode);
				}
				// Case B2a and B2b: currentNode now is the rightChild
				// rotate right
				currentNode->getParent()->setColor(BLACK);
				currentNode->getGrandparent()->setColor(RED);
				rotateLeft(currentNode->getGrandparent());
			}
		}
	}
	root->setColor(BLACK);
}

void RBTree::binaryInsert(RBNode* n) {
	if (this->root == NULL) {
		this->root = n;
		return;
	}
	RBNode* currentNode = root;
	while (currentNode) {
		if (n->getKey() > currentNode->getKey()) {
			if (currentNode->getRightChild()) {
				currentNode = (RBNode*)currentNode->getRightChild();
				continue;
			}
			n->setParent(currentNode);
			currentNode->setRightChild(n);
			return;
		}
		else {
			if (currentNode->getLeftChild()) {
				currentNode = (RBNode*)currentNode->getLeftChild();
				continue;
			}
			n->setParent(currentNode);
			currentNode->setLeftChild(n);
			return;
		}
	}
}

void RBTree::rotateLeft(RBNode* currentNode) {
	// temp for the right child
	RBNode *right = currentNode->getRightChild();
	// set the new child
	currentNode->setRightChild(right->getLeftChild());

	// if the right child is not NULL set the parent
	if (currentNode->getRightChild() != NULL)
		currentNode->getRightChild()->setParent(currentNode);

	// set the parent for the temp
	right->setParent(currentNode->getParent());

	// if current node is the root, swap the root with the right child
	if (currentNode->getParent() == NULL)
		root = right;

	// find the new place for the right child
	else if (currentNode == currentNode->getParent()->getLeftChild())
		currentNode->getParent()->setLeftChild(right);

	else
		currentNode->getParent()->setRightChild(right);

	// swap the right child with its parent
	right->setLeftChild(currentNode);
	currentNode->setParent(right);
} 

void RBTree::rotateRight(RBNode* currentNode)
{
	// temp for the old left child
	RBNode *left = currentNode->getLeftChild();

	// set the new left child to be the right child of the left child
	currentNode->setLeftChild(left->getRightChild());

	// if the new left child exists, set its parent
	if (currentNode->getLeftChild() != NULL)
		currentNode->getLeftChild()->setParent(currentNode);

	// set the new parent for the left child
	left->setParent(currentNode->getParent());

	// if the curent node is the root, replace it with the left child
	if (currentNode->getParent() == NULL)
		root = left;

	// find the new position for the current node
	else if (currentNode == currentNode->getParent()->getLeftChild())
		currentNode->getParent()->setLeftChild(left);

	else
		currentNode->getParent()->setRightChild(left);

	// swap the left child with its parent
	left->setRightChild(currentNode);
	currentNode->setParent(left);
}

bool RBTree::check() {
	if (root == NULL) return true;
	if (root->getColor() == RED) return false;
	return checkSubtree(root, INT_MAX, INT_MIN);
}

int RBTree::height() {
	if (root == NULL) return 0;
	return heightSubtree(root);
}

int RBTree::blackHeight(RBNode* start) {
	// blackheight of the node
	int black = 0;
	if (start == NULL) return 0;
	if (start->getColor() == BLACK) black = 1;
	// when the current Node got no children, return the black height of the Node
	if (start->getLeftChild() == NULL && start->getRightChild() == NULL) {
		return black;
	}
	// when the current Node got children
	// return the black height of the subtree with the largest black heigth 
	if (start->getLeftChild() == NULL) {
		return (black + blackHeight(start->getRightChild()));
	}
	if (start->getRightChild() == NULL) {
		return (black + blackHeight(start->getLeftChild()));
	}
	return (black + max(blackHeight(start->getLeftChild()),blackHeight(start->getRightChild())));
}

bool RBTree::checkSubtree(RBNode* start, int max, int min) {
	// if the tree is empty is correct
	if (start == NULL) return true;
	// the root always has to be black
	if (start->getParent() == NULL && start->getColor() == RED) {
		return false;
	}
	// if the current Node is larger then the max or smaller then the min of the subtree
	if (start->getKey() > max || start->getKey() < min) return false;
	// a Red Node cant have a black parent
	if (start->getParent() != NULL) {
		if (start->getColor() == RED && start->getParent()->getColor() == RED) {
			return false;
		}
	}
	// check all the subtrees and compare the black heigths
	return (checkSubtree(start->getLeftChild(), start->getKey() - 1, min) &&
		checkSubtree(start->getRightChild(), max, start->getKey() + 1) && (blackHeight(start->getLeftChild()) == blackHeight(start->getRightChild())));
}

int RBTree::heightSubtree(RBNode* start) {
	// if the node is NULL or its a leaf the heigth is 0
	if (start == NULL || (start->getLeftChild() == NULL && start->getRightChild() == NULL)) {
		return 0;
	}
	// calculate the heigth by adding 1 to the largest subtree
	return (1 + max(heightSubtree(start->getLeftChild()), heightSubtree(start->getRightChild())));
}

string RBTree::inorder(RBNode* start) {
	stringstream str;
	if (start != NULL) {

		if (start->getLeftChild()) str << inorder((RBNode*)start->getLeftChild());
		str << start->toString() << endl;
		if (start->getRightChild()) str << inorder((RBNode*)start->getRightChild());
	}
	return str.str();
}

string RBTree::levelOrderHelper(RBNode* start) {
	if (root == NULL) return "";
	stringstream str;
	std::queue<RBNode*> q;
	q.push(root);
	while (!q.empty()){
		RBNode* temp = q.front();
		str << temp->toString() << endl;
		q.pop();
		if (temp->getLeftChild() != NULL)
			q.push(temp->getLeftChild());
		if (temp->getRightChild() != NULL)
		q.push(temp->getRightChild());
	}
	return str.str();
}

string RBTree::toString() {
	return levelOrderHelper(root);
}

string RBTree::search(int key) {
	RBNode* currentNode = root;
	while (currentNode) {
		if (key == currentNode->getKey()) return currentNode->getValue();
		if (key < currentNode->getKey()) currentNode = currentNode->getLeftChild();
		else currentNode = currentNode->getRightChild();
	}
	return "Not Found";
}

void RBTree::clean(RBNode* start) {
	if (start != NULL) {
		if (start->getLeftChild()) clean(start->getLeftChild());
		if (start->getRightChild()) clean(start->getRightChild());
		delete start;
	}
	return;
}