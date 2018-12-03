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
		else {			// Case B1: The uncle is also Red
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
	RBNode *right = currentNode->getRightChild();

	currentNode->setRightChild(right->getLeftChild());

	if (currentNode->getRightChild() != NULL)
		currentNode->getRightChild()->setParent(currentNode);

	right->setParent(currentNode->getParent());

	if (currentNode->getParent() == NULL)
		root = right;

	else if (currentNode == currentNode->getParent()->getLeftChild())
		currentNode->getParent()->setLeftChild(right);

	else
		currentNode->getParent()->setRightChild(right);

	right->setLeftChild(currentNode);
	currentNode->setParent(right);
} 

void RBTree::rotateRight(RBNode* currentNode)
{
	RBNode *left = currentNode->getLeftChild();

	currentNode->setLeftChild(left->getRightChild());

	if (currentNode->getLeftChild() != NULL)
		currentNode->getLeftChild()->setParent(currentNode);

	left->setParent(currentNode->getParent());

	if (currentNode->getParent() == NULL)
		root = left;

	else if (currentNode == currentNode->getParent()->getLeftChild())
		currentNode->getParent()->setLeftChild(left);

	else
		currentNode->getParent()->setRightChild(left);

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
	int black = 0;
	if (start == NULL) return black;
	if (start->getColor() == BLACK) black = 1;
	if (start->getLeftChild() == NULL && start->getRightChild() == NULL) {
		return black;
	}
	if (start->getLeftChild() == NULL) {
		return (black + blackHeight(start->getRightChild()));
	}
	if (start->getRightChild() == NULL) {
		return (black + blackHeight(start->getLeftChild()));
	}
	return (black + max(blackHeight(start->getLeftChild()),blackHeight(start->getRightChild())));
}

bool RBTree::checkSubtree(RBNode* start, int max, int min) {

	if (start == NULL) return true;
	if (start->getKey() > max || start->getKey() < min) return false;
	if (start->getParent() != NULL) {
		if (start->getColor() == RED && start->getParent()->getColor() == RED) {
			return false;
		}
	}
	return (checkSubtree(start->getLeftChild(), start->getKey() - 1, min) &&
		checkSubtree(start->getRightChild(), max, start->getKey() + 1) && (blackHeight(start->getLeftChild()) == blackHeight(start->getRightChild())));
}

int RBTree::heightSubtree(RBNode* start) {
	if (start == NULL || (start->getLeftChild() == NULL && start->getRightChild() == NULL)) {
		return 0;
	}
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

		while (!q.empty())
		{
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
		if (start->getLeftChild()) clean((RBNode*)start->getLeftChild());
		if (start->getRightChild()) clean((RBNode*)start->getRightChild());
		delete start;
	}
	return;
}