#include "binarySearchTree.h"

BinarySearchTree::BinarySearchTree(int id, int index){
	this->id = id;
	this->index = index;
	this->parent = nullptr;
	this->left = nullptr;
	this->right = nullptr;
}

BinarySearchTree::~BinarySearchTree(){
	if(this->left){
		delete this->left;
	}
	if(this->right){
		delete this->right;
	}
}

void BinarySearchTree::setParent(BinarySearchTree *parent){
	this->parent = parent;
}

void BinarySearchTree::setLeft(BinarySearchTree *left){
	this->left = left;
}

void BinarySearchTree::setRight(BinarySearchTree *right){
	this->right = right;
}

BinarySearchTree *BinarySearchTree::getParent(){
	return this->parent;
}

BinarySearchTree *BinarySearchTree::getLeft(){
	return this->left;
}

BinarySearchTree *BinarySearchTree::getRight(){
	return this->right;
}

void BinarySearchTree::addNode(int id, int index){
	if(id < this->id){
		if(this->left){
			this->left->addNode(id, index);
		}else{
			this->left = new BinarySearchTree(id, index);
			this->left->setParent(this);
		}
	}else{
		if(this->right){
			this->right->addNode(id, index);
		}else{
			this->right = new BinarySearchTree(id, index);
			this->right->setParent(this);
		}
	}
}

int BinarySearchTree::findNodeIndex(int id){
	if(id == this->id){
		return this->index;
	}
	if(id < this->id){
		if(this->left == nullptr){
			return -1;
		}
		else{
			return this->left->findNodeIndex(id);
		}
	}
	else{
		if(this->right == nullptr){
			return -1;
		}
		else{
			return this->right->findNodeIndex(id);
		}
	}
}

void BinarySearchTree::deleteNode(int id){
	if(id == this->id){
		if(this->left == nullptr && this->right == nullptr){
			if(this->parent){
				if(this->parent->getLeft() == this){
					this->parent->setLeft(nullptr);
				}
				else{
					this->parent->setRight(nullptr);
				}
			}
			delete this;
		}
		else if(this->left == nullptr){
			if(this->parent){
				if(this->parent->getLeft() == this){
					this->parent->setLeft(this->right);
					this->right->setParent(this->parent);
				}
				else{
					this->parent->setRight(this->right);
					this->right->setParent(this->parent);
				}
			}
			this->right = nullptr;
			delete this;
		}
		else if(this->right == nullptr){
			if(this->parent){
				if(this->parent->getLeft() == this){
					this->parent->setLeft(this->left);
					this->left->setParent(this->parent);
				}
				else{
					this->parent->setRight(this->left);
					this->left->setParent(this->parent);
				}
			}
			this->left = nullptr;
			delete this;
		}
		else{
			BinarySearchTree *temp = this->right;
			while(temp->getLeft()){
				temp = temp->getLeft();
			}
			this->id = temp->id;
			this->index = temp->index;
			temp->deleteNode(temp->id);
		}
	}
	else if(id < this->id){
		if(this->left == nullptr){
			return;
		}
		else{
			this->left->deleteNode(id);
		}
	}
	else{
		if(this->right == nullptr){
			return;
		}
		else{
			this->right->deleteNode(id);
		}
	}
}

void BinarySearchTree::printTree(int depth){
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