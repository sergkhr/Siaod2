#ifndef __RANDOMIZEDBINARYSEARCHTREE_H__
#define __RANDOMIZEDBINARYSEARCHTREE_H__

#include <iostream>
#include <time.h>
#include <random>
#include <ctime>

using namespace std;

class RandomizedBinarySearchTree{
private:
	int id;
	int index;
	int size;
	RandomizedBinarySearchTree *left;
	RandomizedBinarySearchTree *right;
public:
	RandomizedBinarySearchTree(int id, int index);
	~RandomizedBinarySearchTree();
	void setLeft(RandomizedBinarySearchTree *left);
	void setRight(RandomizedBinarySearchTree *right);
	void setSize(int size);
	void setId(int id);
	RandomizedBinarySearchTree *getLeft();
	RandomizedBinarySearchTree *getRight();
	int getSize();
	int getId();
	static void fixSize(RandomizedBinarySearchTree *node);

	static RandomizedBinarySearchTree *rotateLeft(RandomizedBinarySearchTree *root);
	static RandomizedBinarySearchTree *rotateRight(RandomizedBinarySearchTree *root);
	static RandomizedBinarySearchTree *addNodeToRoot(RandomizedBinarySearchTree *root, int id, int index);

	static RandomizedBinarySearchTree *addNode(RandomizedBinarySearchTree *root, int id, int index);
	int findNodeIndex(int id);

	static RandomizedBinarySearchTree *merge(RandomizedBinarySearchTree *left, RandomizedBinarySearchTree *right);

	static RandomizedBinarySearchTree *deleteNode(RandomizedBinarySearchTree *root, int id);
	void printTree(int depth = 0);
};

#endif