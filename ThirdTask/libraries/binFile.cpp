#include "binFile.h"

int toBinary(string fileName, string fileNameBin){//read from text file and write to binary file
	ifstream fin(fileName);
	fstream fout(fileNameBin, ios::out|ios::binary|ios::trunc);
	if(!fin.is_open() || !fout.is_open()){
		cout << "file doesn't exist" << endl;
		fin.close();
		fout.close();
		return 1;
	}
	while(fin.good()){
		Bank bank;
		vector<string> tokens;
		for (string each; getline(fin, each, ';'); tokens.push_back(each));
		for(int i = 0; i < tokens.size(); i++){
			//cout << tokens.size() << " " << tokens[i] << endl;
			if(i%4 == 0) bank.id = stoi(tokens[i]);
			else if(i%4 == 1) strcpy(bank.name, tokens[i].c_str());
			else if(i%4 == 2) strcpy(bank.city, tokens[i].c_str());
			else if(i%4 == 3){
				bank.commercialOrState = (tokens[i] == "true") ? true : false;
				fout.write((char*)&bank, sizeof(bank));
			}
		}
		
	}
	fin.close();
	fout.close();
	return 0;
}

int getBank(string fileNameBin, Bank &bank, int ind){//get bank by index from binary file
	//returns 0 if bank was found, 1 if file doesn't exist, 2 if bank wasn't found
	fstream fin(fileNameBin, ios::in|ios::binary);
	if(!fin.is_open()){
		cout << "file doesn't exist" << endl;
		fin.close();
		return 1;
	}
	
	fin.seekg(sizeof(Bank)*(ind-1), ios::beg);
	Bank readBank; 
	fin.read((char*)&readBank, sizeof(Bank));
	if(!fin.good()){
		return 2;
	}
	bank = readBank;
	fin.close();
	return 0;
}

int deleteBank(string fileNameBin, int id){//delete bank by id from binary file
	//returns 0 if bank was deleted, 1 if file doesn't exist, 2 if bank wasn't found
	fstream fin(fileNameBin, ios::in|ios::out|ios::binary);
	if(!fin.is_open()){
		cout << "file doesn't exist" << endl;
		fin.close();
		return 1;
	}

	Bank bank;
	fin.seekg(0, ios::beg);
	while(fin.read((char*)&bank, sizeof(bank))){
		cout << bank.id << endl;
		if(bank.id == id){
			bank.id == -1; //means that bank was deleted
			fin.seekp(-sizeof(bank), ios::cur);
			fin.write((char*)&bank, sizeof(bank));
			fin.close();
			return 0;
		}
	}
	fin.close();
	return 2;
}


void testBinF(){
	//test toBinary
	toBinary("bfi.txt", "bfb.txt");
}