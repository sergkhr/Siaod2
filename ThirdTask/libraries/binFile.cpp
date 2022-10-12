#include "binFile.h"

int toBinary(string fileName, string fileNameBin){//read from text file and write to binary file
	ifstream fin("../../" + fileName);
	fstream fout("../../" + fileNameBin, ios::out|ios::binary|ios::trunc);
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

int addBank(string fileNameBin, const Bank &bank, int ind){
	fstream fout("../../" + fileNameBin, ios::in|ios::out|ios::binary);
	if(!fout.is_open()){
		cout << "file doesn't exist" << endl;
		fout.close();
		return 1;
	}
	if(ind == -1){
		fout.seekp(0, ios::end);
		fout.write((char*)&bank, sizeof(bank));
		fout.close();
		return 0;
	}
	fout.seekp((ind)*sizeof(bank), ios::beg);
	// if(fout.write((char*)&bank, sizeof(bank))){
	// 	fout.close();
	// 	return 0;
	// }
	fout.write((char*)&bank, sizeof(bank));
	fout.close();
	return 0; 
}

int getBank(string fileNameBin, Bank &bank, int ind){//get bank by index from binary file starting from 1
	//returns 0 if bank was found, 1 if file doesn't exist, 2 if bank wasn't found
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
		return 2;
	}
	bank = readBank;
	fin.close();
	return 0;
}

int deleteBankById(string fileNameBin, int id){//delete bank by id from binary file
	//returns 0 if bank was deleted, 1 if file doesn't exist, 2 if bank wasn't found
	fstream fin("../../" + fileNameBin, ios::in|ios::out|ios::binary);
	if(!fin.is_open()){
		cout << "file doesn't exist" << endl;
		fin.close();
		return 1;
	}

	Bank bank;
	fin.seekg(0, ios::beg);
	while(fin.read((char*)&bank, sizeof(bank))){
		if(bank.id == id){
			bank.id = -1; //means that bank was deleted
			fin.seekp(-sizeof(bank), ios::cur);
			fin.write((char*)&bank, sizeof(bank));
			fin.close();
			return 0;
		}
	}
	fin.close();
	return 2;
}

int deleteBankByIndex(string fileNameBin, int ind){
	//returns 0 if bank was deleted, 1 if file doesn't exist, 2 if bank wasn't found
	fstream fin("../../" + fileNameBin, ios::in|ios::out|ios::binary);
	if(!fin.is_open()){
		cout << "file doesn't exist" << endl;
		fin.close();
		return 1;
	}

	fin.seekg(sizeof(Bank)*(ind), ios::beg);
	Bank readBank; 
	fin.read((char*)&readBank, sizeof(Bank));
	if(!fin.good()){
		return 2;
	}
	readBank.id = -1; //means that bank was deleted
	fin.seekp(-sizeof(readBank), ios::cur);
	fin.write((char*)&readBank, sizeof(readBank));
	fin.close();
	return 0;
}

void testBinF(){
	//test toBinary
	toBinary("bfi.txt", "bfb.txt");
	cout << "binary file contents:" << endl;
	for(int i = 1; i <= 4; i++){
		Bank bank;
		getBank("bfb.txt", bank, i-1);
		cout << bank.id << " " << bank.name << " " << bank.city << " " << bank.commercialOrState << endl;
	}
	//test getBank
	cout << "insert index from 1 to pick bank" << endl;
	int ind;
	cin >> ind;
	Bank bank;
	getBank("bfb.txt", bank, ind-1);
	cout << bank.id << " " << bank.name << " " << bank.city << " " << bank.commercialOrState << endl;

	//test deleteBank by id
	cout << "insert id to delete bank" << endl;
	int id;
	cin >> id;
	deleteBankById("bfb.txt", id);
	cout << "binary file contents:" << endl;
	for(int i = 1; i <= 4; i++){
		Bank bank;
		getBank("bfb.txt", bank, i-1);
		cout << bank.id << " " << bank.name << " " << bank.city << " " << bank.commercialOrState << endl;
	}

	//test deleteBank by index
	cout << "insert index to delete bank" << endl;
	cin >> ind;
	deleteBankByIndex("bfb.txt", ind-1);
	cout << "binary file contents:" << endl;
	for(int i = 1; i <= 4; i++){
		Bank bank;
		getBank("bfb.txt", bank, i-1);
		cout << bank.id << " " << bank.name << " " << bank.city << " " << bank.commercialOrState << endl;
	}

	//test adding
	bank.id = 1337;
	string tmpName = "test bank";
	string tmpCity = "test city";
	strcpy(bank.name, tmpName.c_str());
	strcpy(bank.city, tmpCity.c_str());
	bank.commercialOrState = true;

	cout << endl << "bank that is being added " << bank.id << ";" << bank.name << ";" << bank.city << ";" << bank.commercialOrState << endl;
	cout << "adding in the end and to pos 2" << endl;
	addBank("bfb.txt", bank, 2-1);
	addBank("bfb.txt", bank);
	cout << "binary file contents:" << endl;
	for(int i = 1; i <= 5; i++){
		Bank bank;
		getBank("bfb.txt", bank, i-1);
		cout << bank.id << " " << bank.name << " " << bank.city << " " << bank.commercialOrState << endl;
	}
}