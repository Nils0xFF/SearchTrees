#include <string>
#include <iostream>
#include "BinarySearchTree.hpp"
#include "RBTree.h"
#include <random>
#include <algorithm>
#include <time.h>

using namespace std;

void BSTTest(int*, int);
void RBTreeTest(int*, int);

int main() {
	srand(time(NULL));
	int n = 1000;
	int* a = new int[n];
	for (int i = 1; i <= n; i++) {
		a[i - 1] = i;
	}
	// random_shuffle(a, a + n - 1);
	cout << "BinaryTree Test: " << endl;
	BSTTest(a, n);
	cout << endl << "RBTree Test: " << endl;
	RBTreeTest(a,n );
	delete[] a;
	return 0;
}

void BSTTest(int* a, int n) {

	BinarySearchTree tree;
	clock_t start = clock();
	for (int i = 0; i < n; i++) {
		tree.insert(new BinaryNode(a[i], "value_" + to_string(a[i])));
		if ((i +1) % (n/10) == 0) {
			cout << "Heigth after " << i + 1 << " insertions: " << tree.height() << endl;
		}
	}
	clock_t end = clock();

	cout << "Insert duration: " << ((end - start) * 1000) / CLOCKS_PER_SEC << endl;
	cout << "Check: " << tree.check() << endl;
	cout << "Heigth: " << tree.height() << endl;

	start = clock();
	for (int i = 1; i <= n; i++) {
		if (i % 2 != 0) tree.remove(i);
	}
	end = clock();

	cout << "Remove duration: " << ((end - start) * 1000) / CLOCKS_PER_SEC << endl;
	cout << "Check: " << tree.check() << endl;
	cout << "New Heigth: " << tree.height() << endl;
	
}

void RBTreeTest(int* a, int n) {

	RBTree tree;
	clock_t start = clock();
	for (int i = 0; i < n; i++) {
		tree.insert(new RBNode(a[i], "value_" + to_string(a[i])));
		if ((i + 1) % (n / 10) == 0) {
			cout << "Heigth after " << i + 1 << " insertions: " << tree.height() << endl;
		}
	}
	clock_t end = clock();

	cout << "Insert duration: " << ((end - start) * 1000) / CLOCKS_PER_SEC << endl;
	cout << "Heigth: " << tree.height() << endl;
	// cout << tree.toString() << endl;
	cout << "Check: " << tree.check() << endl;
	// cout << tree.toString() << endl;

}