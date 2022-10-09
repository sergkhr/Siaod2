#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <vector>
#include <cstring>

using namespace std;
struct Bank{
	int id;
	char name[61];
	char city[61];
	bool commercialOrState; //true - commercial, false - state 
};

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

int toText(string fileNameBin, string fileName){//read from binary file and write to text file
	fstream fin(fileNameBin, ios::in|ios::out|ios::binary);
	ofstream fout(fileName);
	
	if(!fin.is_open() || !fout.is_open()){
		cout << "file doesn't exist" << endl;
		fin.close();
		fout.close();
		return 1;
	}
	Bank bank;
	while(fin.read((char*)&bank, sizeof(bank))){
		fout << bank.id << ";" << bank.name << ";" << bank.city << ";" << (bank.commercialOrState? "true" : "false") << endl;
	}
	fin.close();
	fout.close();
	return 0;
}

int printBinary(string fileNameBin){//print from binary file
	fstream fin(fileNameBin, ios::in|ios::out|ios::binary);
	if(!fin.is_open()){
		cout << "file doesn't exist" << endl;
		fin.close();
		return 1;
	}
	Bank bank;
	while(fin.read((char*)&bank, sizeof(bank))){
		cout << bank.id << ";" << bank.name << ";" << bank.city << ";" << (bank.commercialOrState? "true" : "false") << endl;
	}
	fin.close();
	return 0;
}

int getBank(string fileNameBin, Bank &bank, int ind){//get bank by ind from binary file
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
	
	fin.seekg(-sizeof(Bank), ios::end);
	Bank lastBank; 
	fin.read((char*)&lastBank, sizeof(lastBank));

	Bank bank;
	fin.seekg(0, ios::beg);
	while(fin.read((char*)&bank, sizeof(bank))){
		if(bank.id == id){
			fin.seekp(-sizeof(bank), ios::cur);
			fin.write((char*)&lastBank, sizeof(lastBank));
			fin.close();
			return 0;
		}
	}
	fin.close();
	return 2;
}

int changeOwnership(string fileNameBin, int id){//change bank commercialOrState by id from binary file
	//returns 0 if bank was changed, 1 if file doesn't exist, 2 if bank wasn't found
	fstream finoutBin(fileNameBin, ios::in|ios::out|ios::binary);
	if(!finoutBin.is_open()){
		cout << "file doesn't exist" << endl;
		finoutBin.close();
		return 1;
	}

	Bank bank;
	finoutBin.seekg(0, ios::beg);
	while(finoutBin.read((char*)&bank, sizeof(bank))){
		if(bank.id == id){
			bank.commercialOrState = !bank.commercialOrState;
			finoutBin.seekp(-sizeof(bank), ios::cur);
			finoutBin.write((char*)&bank, sizeof(bank));
			finoutBin.close();
			return 0;
		}
	}
	finoutBin.close();
	return 2;
}

int printBanksOfCity(string fileNameBin, string city){//print commercial banks of city from binary file
	fstream fin(fileNameBin, ios::in|ios::binary);
	if(!fin.is_open()){
		cout << "file doesn't exist" << endl;
		fin.close();
		return 1;
	}
	while(fin.good()){
		Bank bank;
		fin.read((char*)&bank, sizeof(bank));
		if(bank.city == city && bank.commercialOrState){//banks of city and commercial
			cout << bank.id << ";" << bank.name << ";" << bank.city << ";" << (bank.commercialOrState? "commercial" : "state") << endl;
		}
	}
	fin.close();
	return 0;
}
