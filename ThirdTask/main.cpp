#include <iostream>
#include <iomanip>
#include <fstream>
#include <time.h>
#include <string>
#include <vector>
#include <chrono>
#include "libraries/hashBinFile.h"

using namespace std;

int main(){
	//testHashT();
	//testBinF();

	// fstream fout("../../bigFile.txt", ios::out|ios::binary);
	// Bank bank;
	// for(int i = 0; i < 200000; i++){
	// 	bank.id = (i + 250) % 200000 + 1;
	// 	string tmpName = "test bank" + to_string(i);
	// 	string tmpCity = "test city";
	// 	strcpy(bank.name, tmpName.c_str());
	// 	strcpy(bank.city, tmpCity.c_str());
	// 	bank.commercialOrState = true;
	// 	if((i / 100) % 2 == 0){
	// 		bank.commercialOrState = false;
	// 	}
	// 	fout.write((char*)&bank, sizeof(Bank));
	// }
	// fout.close();

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

		int simpleNums[6] = {13, 19, 53, 601, 12289, 1046527}; //simple numbers for hash table size the last one is 1 046 527 for 1 million test
		int hashElements = 0; //this is the way to store how much elements we have stored and deleted (kind of a hack, but it's fiiiiiine)
		int deletedElements = 0;
		int hashSize = simpleNums[0];
		// hash table: (id, index)
		vector<vector<int>> hashTable(hashSize, {-1, -1});

		hashFile(fileNameBin, hashTable, hashSize, hashElements, deletedElements);
		cout << "hash table contents: " << endl;
		for(int i = 0; i < hashSize; i++){
			cout << "hashTable[" << i << "]: " << hashTable[i][0] << ", " << hashTable[i][1] << endl;
		}
		cout << "enter id to get bank: " << endl;
		int id;
		cin >> id;
		bank = getRecordById(fileNameBin, id, hashTable, hashSize);
		if(bank.id == -1){
			cout << "no bank with such id" << endl;
		}
		else{
			cout << "id: " << bank.id;
			cout << ", name: " << bank.name;
			cout << ", city: " << bank.city;
			cout << ", commercialOrState: " << bank.commercialOrState << endl;
		}
		cout << "enter id to delete bank: " << endl;
		cin >> id;
		deleteRecordById(fileNameBin, id, hashTable, hashSize, deletedElements);
		
		cout << "binary file contents: " << endl;
		iter = 0;
		while(getBank(fileNameBin, bank, iter) == 0){
			//print bank
			cout << "id: " << bank.id;
			cout << ", name: " << bank.name;
			cout << ", city: " << bank.city;
			cout << ", commercialOrState: " << bank.commercialOrState << endl;
			iter++;
		}
	}
	else{
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

		int simpleNums[6] = {13, 19, 53, 601, 12289, 1046527}; //simple numbers for hash table size the last one is 1 046 527 for 1 million test
		int hashElements = 0; //this is the way to store how much elements we have stored and deleted (kind of a hack, but it's fiiiiiine)
		int deletedElements = 0;
		int hashSize = simpleNums[0];
		// hash table: (id, index)
		vector<vector<int>> hashTable(hashSize, {-1, -1});

		auto hashingStart = chrono::high_resolution_clock::now();
		hashFile(fileNameBin, hashTable, hashSize, hashElements, deletedElements);
		auto hashingEnd = chrono::high_resolution_clock::now();
		auto hashingTime = chrono::duration_cast<chrono::milliseconds>(hashingEnd - hashingStart);
		cout << "hashing time (it probably did some rehashing because hashTable started from capcity of 13 elements): " << hashingTime.count() << " ms" << endl;

		for(int i = 0; i < 3; i++){
			cout << "Enter id to get bank (from 1 to 200000 (1-250 are the last ones)): " << endl;
			int id;
			cin >> id;
			Bank bank;
			auto start = chrono::high_resolution_clock::now();
			bank = getRecordById(fileNameBin, id, hashTable, hashSize);
			auto end = chrono::high_resolution_clock::now();
			auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
			cout << "id: " << bank.id;
			cout << ", name: " << bank.name;
			cout << ", city: " << bank.city;
			cout << ", commercialOrState: " << bank.commercialOrState << endl;
			cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
		}
	}

	return 0;
}
