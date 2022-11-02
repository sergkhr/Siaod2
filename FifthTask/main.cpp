#include <iostream>
#include "libraries/binFile.h"
#include "libraries/binarySearchTree.h"
#include "libraries/randomizedBinarySearchTree.h"

using namespace std;

int main() {
	srand(time(NULL));
	cout << "do you want to test binaray search tree? (y/n n by default)" << endl;
	char c;
	cin >> c;
	if (c == 'y'){
		BinarySearchTree *tree = new BinarySearchTree(120, 0);
		tree->addNode(100, 1);
		tree->addNode(110, 2);
		tree->addNode(130, 3);
		tree->addNode(122, 11);
		tree->addNode(140, 4);
		tree->addNode(150, 5);
		tree->addNode(160, 6);
		tree->addNode(145, 7);
		tree->printTree();
		cout << "insert search id" << endl;
		int id;
		cin >> id;
		cout << "index of " << id << " is " << tree->findNodeIndex(id) << endl;
		cout << "insert id to delete" << endl;
		cin >> id;
		tree->deleteNode(id);
		tree->printTree();
		delete tree;
	}

	cout << "do you want to test randomized binaray search tree? (y/n n by default)" << endl;
	cin >> c;
	if (c == 'y'){
		RandomizedBinarySearchTree *tree = new RandomizedBinarySearchTree(120, 0);
		tree = RandomizedBinarySearchTree::addNode(tree, 100, 1);
		tree = RandomizedBinarySearchTree::addNode(tree, 110, 2);
		tree = RandomizedBinarySearchTree::addNode(tree, 130, 3);
		tree = RandomizedBinarySearchTree::addNode(tree, 122, 11);
		tree = RandomizedBinarySearchTree::addNode(tree, 140, 4);
		tree = RandomizedBinarySearchTree::addNode(tree, 150, 5);
		tree = RandomizedBinarySearchTree::addNode(tree, 160, 6);
		tree = RandomizedBinarySearchTree::addNode(tree, 145, 7);
		tree->printTree();
		cout << "insert search id" << endl;
		int id;
		cin >> id;
		cout << "index of " << id << " is " << tree->findNodeIndex(id) << endl;
		cout << "insert id to delete" << endl;
		cin >> id;
		tree = RandomizedBinarySearchTree::deleteNode(tree, id);
		tree->printTree();
		delete tree;
	}
	return 0;
}
