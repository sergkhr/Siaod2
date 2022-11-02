#ifndef __BINARYSEARCHTREE_H__
#define __BINARYSEARCHTREE_H__

#include <iostream>
#include <time.h>

using namespace std;

//binary search tree class for int
class BinarySearchTree{
    private:
        int id;
        int index;
        BinarySearchTree *parent;
        BinarySearchTree *left;
        BinarySearchTree *right;
    public:
        BinarySearchTree(int id, int index);
        ~BinarySearchTree();
         void setParent(BinarySearchTree *parent);
        void setLeft(BinarySearchTree *left);
        void setRight(BinarySearchTree *right);
        BinarySearchTree *getParent();
        BinarySearchTree *getLeft();
        BinarySearchTree *getRight();

        void addNode(int id, int index);
        int findNodeIndex(int id);
        void deleteNode(int id);
        void printTree(int depth = 0);
};

#endif