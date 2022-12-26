#include "randomizedBinarySearchTree.h"

RandomizedBinarySearchTree::RandomizedBinarySearchTree(int id, int index){
	this->id = id;
	this->index = index;
	this->size = 1;
	this->left = nullptr;
	this->right = nullptr;
}

RandomizedBinarySearchTree::~RandomizedBinarySearchTree(){
	if (this->left){
		delete this->left;
	}
	if (this->right){
		delete this->right;
	}
}

void RandomizedBinarySearchTree::setLeft(RandomizedBinarySearchTree *left){
	this->left = left;
}

void RandomizedBinarySearchTree::setRight(RandomizedBinarySearchTree *right){
	this->right = right;
}

void RandomizedBinarySearchTree::setSize(int size){
	this->size = size;
}

void RandomizedBinarySearchTree::setId(int id){
	this->id = id;
}

RandomizedBinarySearchTree *RandomizedBinarySearchTree::getLeft(){
	return this->left;
}

RandomizedBinarySearchTree *RandomizedBinarySearchTree::getRight(){
	return this->right;
}

int RandomizedBinarySearchTree::getSize(){
	return this->size;
}

int RandomizedBinarySearchTree::getId(){
	return this->id;
}

void RandomizedBinarySearchTree::fixSize(RandomizedBinarySearchTree *node){
	if(node){
		int leftSize = 0;
		int rightSize = 0;
		if (node->getLeft()){
			leftSize = node->getLeft()->getSize();
		}
		if (node->getRight()){
			rightSize = node->getRight()->getSize();
		}
		node->setSize(leftSize + rightSize + 1);
	}
}

RandomizedBinarySearchTree *RandomizedBinarySearchTree::rotateLeft(RandomizedBinarySearchTree *root){
	RandomizedBinarySearchTree *newRoot = root->getRight();
	root->setRight(newRoot->getLeft());
	newRoot->setLeft(root);
	fixSize(root);
	fixSize(newRoot);
	return newRoot;
}

RandomizedBinarySearchTree *RandomizedBinarySearchTree::rotateRight(RandomizedBinarySearchTree *root){
	RandomizedBinarySearchTree *newRoot = root->getLeft();
	root->setLeft(newRoot->getRight());
	newRoot->setRight(root);
	fixSize(root);
	fixSize(newRoot);
	return newRoot;
}

RandomizedBinarySearchTree *RandomizedBinarySearchTree::addNodeToRoot(RandomizedBinarySearchTree *root, int id, int index, long long &countTurns){
	if (!root){
		return new RandomizedBinarySearchTree(id, index);
	}
	if (id < root->getId()){
		root->setLeft(addNodeToRoot(root->getLeft(), id, index, countTurns));
		root = rotateRight(root);
		countTurns++;
	}
	else{
		root->setRight(addNodeToRoot(root->getRight(), id, index, countTurns));
		root = rotateLeft(root);
		countTurns++;
	}
	//fixsize is done when we rotate
	return root;
}

RandomizedBinarySearchTree *RandomizedBinarySearchTree::addNode(RandomizedBinarySearchTree *root, int id, int index, long long &countTurns){
	if (!root){
		return new RandomizedBinarySearchTree(id, index);
	}
	if (rand() % (root->getSize() + 1) == 0){
		return addNodeToRoot(root, id, index, countTurns);
	}
	if (id < root->getId()){
		root->setLeft(addNode(root->getLeft(), id, index, countTurns));
	}
	else{
		root->setRight(addNode(root->getRight(), id, index, countTurns));
	}
	fixSize(root);
	return root;
}

int RandomizedBinarySearchTree::findNodeIndex(int id){
	if (this->id == id){
		return this->index;
	}
	if (this->id > id){
		if (this->left){
			return this->left->findNodeIndex(id);
		}
		else{
			return -1;
		}
	}
	else{
		if (this->right){
			return this->right->findNodeIndex(id);
		}
		else{
			return -1;
		}
	}
}

RandomizedBinarySearchTree *RandomizedBinarySearchTree::merge(RandomizedBinarySearchTree *left, RandomizedBinarySearchTree *right){
	if (!left){
		return right;
	}
	if (!right){
		return left;
	}
	if (rand() % (left->getSize() + right->getSize()) < left->getSize()){
		left->setRight(merge(left->getRight(), right));
		fixSize(left);
		return left;
	}
	else{
		right->setLeft(merge(left, right->getLeft()));
		fixSize(right);
		return right;
	}
}

RandomizedBinarySearchTree *RandomizedBinarySearchTree::deleteNode(RandomizedBinarySearchTree *root, int id){
	if (!root) return root;
	if (root->getId() == id){
		RandomizedBinarySearchTree *newRoot = merge(root->getLeft(), root->getRight());
		root->setLeft(nullptr);
		root->setRight(nullptr);
		delete root;
		return newRoot;
	}
	if (root->getId() > id){
		root->setLeft(deleteNode(root->getLeft(), id));
	}
	else{
		root->setRight(deleteNode(root->getRight(), id));
	}
	return root;
}

void RandomizedBinarySearchTree::printTree(int depth){
	if(this->right){
		this->right->printTree(depth + 1);
	}
	for(int i = 0; i < depth; i++){
		cout << "    ";
	}
	cout << this->id << endl;
	if(this->left){
		this->left->printTree(depth + 1);
	}
}