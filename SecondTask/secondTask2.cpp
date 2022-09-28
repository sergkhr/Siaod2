#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include "functions.cpp"

using namespace std;

struct Bank{
	int id;
	string name;
	string city;
	bool commercialOrState; //true - commercial, false - state 
};
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
	// ofstream foutBin(fileNameBin, ios::out|ios::binary);
	// ifstream finBin(fileNameBin, ios::in|ios::binary);
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

	return 0;
}