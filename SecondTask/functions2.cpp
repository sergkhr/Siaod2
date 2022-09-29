#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <vector>
#include <bits/stdc++.h> 

using namespace std;
struct Bank{
	int id;
	char name[61];
	char city[61];
	bool commercialOrState; //true - commercial, false - state 
};

int toBinary(string fileName, string fileNameBin){//read from text file and write to binary file
	ifstream fin(fileName);
	fstream fout(fileNameBin, ios::in|ios::out|ios::binary);
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
		bank.id = stoi(tokens[0]);
		strcpy(bank.name, tokens[1].c_str());
		strcpy(bank.city, tokens[2].c_str());
		bank.commercialOrState = (tokens[3] == "true") ? true : false;
		fout.write((char*)&bank, sizeof(bank));
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
	
	while(fin.good()){
		Bank bank;
		fin.read((char*)&bank, sizeof(bank));
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
	while(fin.good()){
		Bank bank;
		fin.read((char*)&bank, sizeof(bank));
		cout << bank.id << ";" << bank.name << ";" << bank.city << ";" << (bank.commercialOrState? "commercial" : "state") << endl;
	}
	fin.close();
	return 0;
}

int getBank(string fileNameBin, Bank &bank, int id){//get bank by id from binary file
	fstream fin(fileNameBin, ios::in|ios::out|ios::binary);
	if(!fin.is_open()){
		cout << "file doesn't exist" << endl;
		fin.close();
		return 1;
	}
	
	fin.seekg(sizeof(Bank)*(id-1), ios::beg);
	Bank readBank; 
	fin.read((char*)&bank, sizeof(bank));
	if(!fin.good()){
		return false;
	}
	bank = readBank;
	fin.close();
	return 0;
}

int deleteBank(string fileNameBin, int id){//delete bank by id from binary file
	fstream fin(fileNameBin, ios::in|ios::out|ios::binary);
	if(!fin.is_open()){
		cout << "file doesn't exist" << endl;
		fin.close();
		return 1;
	}
	
	fin.seekg(sizeof(Bank), ios::end);
	Bank bank; 
	fin.read((char*)&bank, sizeof(bank));//now bank contains the last record
	fin.seekp(sizeof(Bank)*(id-1), ios::beg);
	fin.write((char*)&bank, sizeof(bank));//teacher said that we have to open file in writing without appending mode to delete, will have to check

	Bank bank;
	fin.seekg(0, ios::beg);
	do{
		fin.read((char*)&bank, sizeof(bank));
		if(bank.id == id){

		}
	}while(fin.good());
}

void changeBankCom(fstream &fin, int id){//change bank commercialOrState by id from binary file
	if(fin.is_open()){
		fin.seekg(sizeof(Bank)*(id-1), ios::beg);
		Bank bank; 
		fin.read((char*)&bank, sizeof(bank));
		bank.commercialOrState = !bank.commercialOrState;
		fin.seekp(-sizeof(Bank), ios::cur);
		fin.write((char*)&bank, sizeof(bank));
	}
}

void printBanksOfCity(fstream &fin, string city){//print banks of city from binary file
	if(fin.is_open()){
		while(fin.good()){
			Bank bank;
			fin.read((char*)&bank, sizeof(bank));
			if(bank.city == city && bank.commercialOrState){//banks of city and commercial
				cout << bank.id << ";" << bank.name << ";" << bank.city << ";" << (bank.commercialOrState? "commercial" : "state") << endl;
			}
		}
	}
}
