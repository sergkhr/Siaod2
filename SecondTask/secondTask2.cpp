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
	ifstream fin(fileName);
	if(!fin.is_open()){
		cout << "file doesn't exist" << endl;
		return 1;
	}


	cout << "input file name for binary file (without .txt)" << endl;
	string fileNameBin;
	cin >> fileNameBin;
	fileNameBin += ".txt";
	fstream finBin(fileNameBin, ios::in|ios::binary);
	if(!finBin.is_open()){
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
	cout << "\ncontents of binary file:" << endl;
	printBinary(fileNameBin);

	cout << "\ninput number of bank (starts from 1)" << endl;
	int num;
	cin >> num;
	Bank bank;
	if(getBank(fileNameBin, bank, num) == 0){
		cout << "id: " << bank.id << endl;
		cout << "name: " << bank.name << endl;
		cout << "city: " << bank.city << endl;
		cout << (bank.commercialOrState? "commercial" : "state") << endl;
	}
	else cout << "no such bank" << endl;

	cout << "\ninput id of bank you want to delete" << endl;
	int id;
	cin >> id;
	if(deleteBank(fileNameBin, id) == 0) cout << "bank deleted" << endl;
	else cout << "no such bank" << endl;
	cout << "\ncontents of binary file:" << endl;
	printBinary(fileNameBin);

	cout << "\ninput the id of the bank that you want to cahnge ownership of" << endl;
	cin >> id;
	if(changeOwnership(fileNameBin, id) == 0) cout << "ownership changed" << endl;
	else cout << "no such bank" << endl;
	cout << "\ncontents of binary file:" << endl;
	printBinary(fileNameBin);

	cout << "\ninput name of the city banks of which you want to print" << endl;
	string city;
	cin >> city;
	printBanksOfCity(fileNameBin ,city);


	fin.close();
	finBin.close();
	foutText.close();
	return 0;
}