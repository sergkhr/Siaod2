#include "hashBinFile.h"

int hashRecord(string fileNameBin, int ind, vector<vector<int>> &hashTable, int &tableSize){
	fstream fin("../../" + fileNameBin, ios::in|ios::binary);
	if(!fin.is_open()){
		cout << "file doesn't exist" << endl;
		fin.close();
		return 1;
	}

	fin.seekg(sizeof(Bank)*(ind), ios::beg);
	Bank readBank; 
	fin.read((char*)&readBank, sizeof(Bank));
	if(!fin.good()){
		return 2; //index out of bounds
	}
	int id = readBank.id;
	return addHash(hashTable, tableSize, id, ind);
}


int hashFile(string fileName, vector<vector<int>> &hashTable, int &tableSize){
	//returns 0 if file was hashed, 1 if file doesn't exist
	fstream fin("../../" + fileName, ios::in|ios::binary);
	if(!fin.is_open()){
		cout << "file doesn't exist" << endl;
		fin.close();
		return 1;
	}

	Bank bank;
	fin.seekg(0, ios::beg);
	int ind = 0;
	while(fin.read((char*)&bank, sizeof(bank))){
		int id = bank.id;
		addHash(hashTable, tableSize, id, ind);
		ind++;
	}
	fin.close();
	return 0;
}

int deleteRecordById(string fileName, int id, vector<vector<int>> &hashTable, const int &tableSize){
	//returns 0 if bank was deleted, 1 if file doesn't exist, 2 if bank wasn't found
	fstream fin("../../" + fileName, ios::in|ios::out|ios::binary);
	if(!fin.is_open()){
		cout << "file doesn't exist" << endl;
		fin.close();
		return 1;
	}

	int ind = findByHash(hashTable, tableSize, id);
	if(ind == -1){
		return 2;
	}
	
	deleteHash(hashTable, tableSize, id);
	Bank bank;
	fin.seekg(sizeof(Bank)*(ind), ios::beg);
	fin.read((char*)&bank, sizeof(Bank));
	bank.id = -1;
	fin.seekp(-sizeof(bank), ios::cur);
	fin.write((char*)&bank, sizeof(bank));

	fin.close();
	return 0;
}

Bank getRecordById(string fileName, int id, vector<vector<int>> &hashTable, int &tableSize){
	fstream fin("../../" + fileName, ios::in|ios::binary);
	if(!fin.is_open()){
		cout << "file doesn't exist" << endl;
		fin.close();
		Bank b; b.id = -2; return b; // id == -2 is file not found
	}

	int ind = findByHash(hashTable, tableSize, id);
	if(ind == -1){
		Bank b; b.id = -1; return b;
	}

	Bank bank;
	fin.seekg(sizeof(Bank)*(ind), ios::beg);
	fin.read((char*)&bank, sizeof(Bank));
	
	fin.close();
	return bank;
}