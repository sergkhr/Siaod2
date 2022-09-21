#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include "functions.cpp"

using namespace std;


//variant 29
int main(){
	srand(time(NULL));
	cout << "input file name (without .txt)" << endl;
	string fileName;
	cin >> fileName;
	fileName += ".txt";
	ifstream fin(fileName);

	if (!fin.is_open()){ //generatin file
		cout << "file doesn't exist, do you want to create it (y/n)" << endl;
		char answer;
		cin >> answer;
		if (answer == 'y'){
			cout << "input file size" << endl;
			int size;
			cin >> size;
			generateFile(fileName, size);
		}
		else if(answer == 'n'){
			return 0;
		}
		else{
			cout << "we assume that is a \"no\"" << endl;
			return 0;
		}
	}
	else{
		cout << "file exists, do you want to regenerate it (y/n)" << endl;
		char answer;
		cin >> answer;
		if (answer == 'y'){
			cout << "input file size" << endl;
			int size;
			cin >> size;
			generateFile(fileName, size);
		}
		else if(answer == 'n');
		else cout << "we assume that is a \"no\"" << endl;
	}

	if(fin.is_open()){
		readFile(fileName);
	}

	cout << "do you want to add a line in the end of file (y/n)" << endl;
	char answer;
	cin >> answer;
	if (answer == 'y'){
		cout << "input line" << endl;
		string toAdd;
		cin >> toAdd;
		if(fin.is_open()){
			addToFile(fileName, toAdd);
			readFile(fileName);
		}
	}
	else if(answer == 'n'){
		cout << "ok" << endl;
	}
	else{
		cout << "we assume that is a \"no\"" << endl;
	}

	cout << "input a number to find" << endl;
	int number;
	while(!(cin >> number)){
		cout << "input a number to find" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
	}
	if(fin.is_open()){
		findNumber(fileName, number);
	}

	if(fin.is_open()){
		cout << "number of numbers in file: " << numbersCount(fileName);
	}
	else{
		cout << "can't count - file doesn't exist" << endl;
	}

	if(fin.is_open()){
		fibbonachiFile(fileName);
	}
	else{
		cout << "can't create fibbonachi file - file doesn't exist" << endl;
	}
	return 0;
}