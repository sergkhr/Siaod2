#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <vector>

using namespace std;
struct Bank{
	int id;
	string name;
	string city;
	bool commercialOrState; //true - commercial, false - state 
};

void toBinary(ifstream &fin, fstream &fout){//read from text file and write to binary file
	if(fin.is_open()){
		while(fin.good()){
			Bank bank;
			vector<string> tokens;
   			for (string each; getline(fin, each, ';'); tokens.push_back(each));
			bank.id = stoi(tokens[0]);
			bank.name = tokens[1];
			bank.city = tokens[2];
			bank.commercialOrState = (tokens[3] == "true") ? true : false;
			fout.write((char*)&bank, sizeof(bank));
		}
	}
	fin.close();
	fout.close();
}

void toText(fstream &fin, ofstream &fout){//read from binary file and write to text file
	if(fin.is_open()){
		while(fin.good()){
			Bank bank;
			fin.read((char*)&bank, sizeof(bank));
			fout << bank.id << ";" << bank.name << ";" << bank.city << ";" << bank.commercialOrState << endl;
		}
	}
	fin.close();
	fout.close();
}

void printBinary(fstream &fin){//print from binary file
	if(fin.is_open()){
		while(fin.good()){
			Bank bank;
			fin.read((char*)&bank, sizeof(bank));
			cout << bank.id << ";" << bank.name << ";" << bank.city << ";" << bank.commercialOrState << endl;
		}
	}
	fin.close();
}

Bank getBank(fstream &fin, int id){//get bank by id from binary file
	if(fin.is_open()){
		fin.seekg(sizeof(Bank)*(id-1), ios::beg);
		Bank bank; 
		fin.read((char*)&bank, sizeof(bank));
		return bank;
	}
}

//todo: understand what they mean by "delete by replacing with the last record"
//now the delete function looks like rewriting the record with the id=-1 record
void deleteBank(fstream &fin, int id){//delete bank by id from binary file
	if(fin.is_open()){
		fin.seekg(sizeof(Bank)*(id-1), ios::beg); //does the seekg sizeof(Bank) even work?
		Bank bank; 
		fin.read((char*)&bank, sizeof(bank));
		bank.id = -1;
		fin.seekp(-sizeof(Bank), ios::cur);
		fin.write((char*)&bank, sizeof(bank));
	}
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
				cout << bank.id << ";" << bank.name << ";" << bank.city << ";" << bank.commercialOrState << endl;
			}
		}
	}
	fin.close();
}
