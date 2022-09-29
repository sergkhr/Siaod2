#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include "functions2.cpp"

using namespace std;

int main(){
	cout << "input file name (without .txt)" << endl;
	string fileName;
	cin >> fileName;
	fileName += ".txt";


	cout << "input file name for binary file (without .txt)" << endl;
	string fileNameBin;
	cin >> fileNameBin;
	fileNameBin += ".txt";
	fstream finoutBin(fileNameBin, ios::in|ios::out|ios::binary);
	if(!finoutBin.is_open()){
		cout << "file doesn't exist" << endl;
		return 1;
	}

	cout << "input file name for text file (without .txt)" << endl;
	string fileNameText;
	cin >> fileNameText;
	fileNameText += ".txt";
	ofstream foutText(fileNameText);
	if(!foutText.is_open()){
		cout << "file doesn't exist" << endl;
		return 1;
	}

	toBinary(fileName, fileNameBin);
	toText(fileNameBin, fileNameText);
	printBinary(fileNameBin);
	cout << "input id of bank" << endl;
	int id;
	cin >> id;
	Bank bank;
	if(getBank(finoutBin, bank, id)){
		cout << "id: " << bank.id << endl;
		cout << "name: " << bank.name << endl;
		cout << "city: " << bank.city << endl;
		cout << (bank.commercialOrState? "commercial" : "state") << endl;
	}
	else cout << "no such bank" << endl;
	


	fin.close();
	finoutBin.close();
	foutText.close();
	return 0;
}