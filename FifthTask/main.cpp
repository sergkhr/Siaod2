#include <iostream>
#include <chrono>
#include "libraries/binFile.h"
#include "libraries/binarySearchTree.h"
#include "libraries/randomizedBinarySearchTree.h"

using namespace std;

BinarySearchTree *createBinaryTreeOutOfFile(string fileNameBin){
	ifstream fin("../../" + fileNameBin, ios::binary);
	if (!fin.is_open()){
		cout << "Error opening file " << fileNameBin << endl;
		fin.close();
		return nullptr;
	}
	Bank bank;
	fin.read((char*)&bank, sizeof(Bank));

	BinarySearchTree *tree = new BinarySearchTree(bank.id, 0);
	int index = 1;
	while (fin.good()){
		fin.read((char*)&bank, sizeof(Bank));
		if (fin.good()){
			tree->addNode(bank.id, index);
			index++;
		}
	}
	fin.close();
	return tree;
}

RandomizedBinarySearchTree *createRandomizedTreeOutOfFile(string fileNameBin, double &averageTurns){
	ifstream fin("../../" + fileNameBin, ios::binary);
	if (!fin.is_open()){
		cout << "Error opening file " << fileNameBin << endl;
		fin.close();
		return nullptr;
	}
	Bank bank;
	fin.read((char*)&bank, sizeof(Bank));

	RandomizedBinarySearchTree *tree = new RandomizedBinarySearchTree(bank.id, 0);
	int index = 1;
	long long countTurns = 0;
	while (fin.good()){
		fin.read((char*)&bank, sizeof(Bank));
		if (fin.good()){
			tree = RandomizedBinarySearchTree::addNode(tree, bank.id, index, countTurns);
			index++;
			countTurns++;
		}
	}
	averageTurns = (double)countTurns / (double)index;
	fin.close();
	return tree;
}

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
		long long countTurns = 0;
		tree = RandomizedBinarySearchTree::addNode(tree, 100, 1, countTurns);
		tree = RandomizedBinarySearchTree::addNode(tree, 110, 2, countTurns);
		tree = RandomizedBinarySearchTree::addNode(tree, 130, 3, countTurns);
		tree = RandomizedBinarySearchTree::addNode(tree, 122, 11, countTurns);
		tree = RandomizedBinarySearchTree::addNode(tree, 140, 4, countTurns);
		tree = RandomizedBinarySearchTree::addNode(tree, 150, 5, countTurns);
		tree = RandomizedBinarySearchTree::addNode(tree, 160, 6, countTurns);
		tree = RandomizedBinarySearchTree::addNode(tree, 145, 7, countTurns);
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



	cout << "is it big file for testing time? (y/n) (n by default)" << endl;
	char bigFile;
	cin >> bigFile;
	cin.ignore(INT_MAX, '\n');
	if(bigFile != 'y' && bigFile != 'n') bigFile = 'n';
	if(bigFile == 'n'){
		cout << "Enter file name for initial text file (without .txt): " << endl;
		string fileName;
		getline(cin, fileName);
		fileName += ".txt";
		ifstream fin("../../" + fileName);
		if(!fin.is_open()){
			cout << "Error opening file" << endl;
			return 1;
		}
		fin.close();

		cout << "Enter file name for binary file (without .bin): " << endl;
		string fileNameBin;
		getline(cin, fileNameBin);
		fileNameBin += ".txt";
		ifstream finBin("../../" + fileNameBin);
		if(!finBin.is_open()){
			cout << "Error opening file" << endl;
			return 1;
		}
		finBin.close();

		toBinary(fileName, fileNameBin);
		cout << "binary file contents: " << endl;
		Bank bank;
		int iter = 0;
		while(getBank(fileNameBin, bank, iter) == 0){
			//print bank
			cout << "id: " << bank.id;
			cout << ", name: " << bank.name;
			cout << ", city: " << bank.city;
			cout << ", commercialOrState: " << bank.commercialOrState << endl;
			iter++;
		}
		cout << endl;


		cout << "do you want to search in file using linear search? (y/n n by default)" << endl;
		cin >> c;
		if (c == 'y'){
			cout << "enter id to get bank: " << endl;
			int id;
			cin >> id;
			Bank bank;
			bank.id = -1;
			linearSearch(fileNameBin, bank, id);
			if(bank.id == -1){
				cout << "no bank with such id" << endl;
			}
			else{
				cout << "id: " << bank.id;
				cout << ", name: " << bank.name;
				cout << ", city: " << bank.city;
				cout << ", commercialOrState: " << bank.commercialOrState << endl;
			}
		}

		
		cout << "do you want to search in file using binary search tree? (y/n n by default)" << endl;
		cin >> c;
		if (c == 'y'){
			cout << "enter id to get bank: " << endl;
			int id;
			cin >> id;
			BinarySearchTree *tree = createBinaryTreeOutOfFile(fileNameBin);
			int index = tree->findNodeIndex(id);
			Bank bank;
			bank.id = -1;
			getBank(fileNameBin, bank, index);
			if(bank.id == -1){
				cout << "no bank with such id" << endl;
			}
			else{
				cout << "id: " << bank.id;
				cout << ", name: " << bank.name;
				cout << ", city: " << bank.city;
				cout << ", commercialOrState: " << bank.commercialOrState << endl;
			}
		}


		cout << "do you want to search in file using randomized binary search tree? (y/n n by default)" << endl;
		cin >> c;
		if (c == 'y'){
			cout << "enter id to get bank: " << endl;
			int id;
			cin >> id;
			double averageTurns = 0;
			RandomizedBinarySearchTree *tree = createRandomizedTreeOutOfFile(fileNameBin, averageTurns);
			cout << "average turns: " << averageTurns << endl;
			int index = tree->findNodeIndex(id);
			Bank bank;
			bank.id = -1;
			getBank(fileNameBin, bank, index);
			if(bank.id == -1){
				cout << "no bank with such id" << endl;
			}
			else{
				cout << "id: " << bank.id;
				cout << ", name: " << bank.name;
				cout << ", city: " << bank.city;
				cout << ", commercialOrState: " << bank.commercialOrState << endl;
			}
		}
		
	}
	else{ //big file for testing time
		cout << "Enter file name for binary file (without .bin): " << endl;
		string fileNameBin;
		getline(cin, fileNameBin);
		fileNameBin += ".txt";
		ifstream finBin("../../" + fileNameBin);
		if(!finBin.is_open()){
			cout << "Error opening file" << endl;
			return 1;
		}
		finBin.close();


		cout << "do you want to search in file using linear search? (y/n n by default)" << endl;
		cin >> c;
		if(c == 'y'){
			for(int i = 0; i < 3; i++){
				cout << "Enter id to get bank (from 1 to 200000 (1-250 are the last ones in bigFile.txt)): " << endl;
				int id;
				cin >> id;
				Bank bank;
				auto start = chrono::high_resolution_clock::now();
				linearSearch(fileNameBin, bank, id);
				auto end = chrono::high_resolution_clock::now();
				auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
				cout << "id: " << bank.id;
				cout << ", name: " << bank.name;
				cout << ", city: " << bank.city;
				cout << ", commercialOrState: " << bank.commercialOrState << endl;
				cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
			}
		}

		cout << "do you want to search in file using binary search tree? (y/n n by default)" << endl;
		cin >> c;
		if(c == 'y'){
			auto treeBuildingStart = chrono::high_resolution_clock::now();
			BinarySearchTree *tree = createBinaryTreeOutOfFile(fileNameBin);
			auto treeBuildingEnd = chrono::high_resolution_clock::now();
			auto treeBuildingTime = chrono::duration_cast<chrono::milliseconds>(treeBuildingEnd - treeBuildingStart);
			cout << "tree building time: " << treeBuildingTime.count() << " ms" << endl;

			for(int i = 0; i < 3; i++){
				cout << "Enter id to get bank (from 1 to 200000 (1-250 are the last ones in bigFile.txt)): " << endl;
				int id;
				cin >> id;
				Bank bank;
				auto start = chrono::high_resolution_clock::now();
				int index = tree->findNodeIndex(id);
				bank.id = -1;
				getBank(fileNameBin, bank, index);
				auto end = chrono::high_resolution_clock::now();
				auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
				cout << "id: " << bank.id;
				cout << ", name: " << bank.name;
				cout << ", city: " << bank.city;
				cout << ", commercialOrState: " << bank.commercialOrState << endl;
				cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
			}
		}

		cout << "do you want to search in file using randomized binary search tree? (y/n n by default)" << endl;
		cin >> c;
		if(c == 'y'){
			auto treeBuildingStart = chrono::high_resolution_clock::now();
			double averageTurns = 0;
			RandomizedBinarySearchTree *tree = createRandomizedTreeOutOfFile(fileNameBin, averageTurns);
			auto treeBuildingEnd = chrono::high_resolution_clock::now();
			auto treeBuildingTime = chrono::duration_cast<chrono::milliseconds>(treeBuildingEnd - treeBuildingStart);
			cout << "tree building time: " << treeBuildingTime.count() << " ms" << endl;
			cout << "average turns: " << averageTurns << endl;

			for(int i = 0; i < 3; i++){
				cout << "Enter id to get bank (from 1 to 200000 (1-250 are the last ones in bigFile.txt)): " << endl;
				int id;
				cin >> id;
				Bank bank;
				auto start = chrono::high_resolution_clock::now();
				int index = tree->findNodeIndex(id);
				bank.id = -1;
				getBank(fileNameBin, bank, index);
				auto end = chrono::high_resolution_clock::now();
				auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
				cout << "id: " << bank.id;
				cout << ", name: " << bank.name;
				cout << ", city: " << bank.city;
				cout << ", commercialOrState: " << bank.commercialOrState << endl;
				cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
			}
		}
	}

	return 0;
}
