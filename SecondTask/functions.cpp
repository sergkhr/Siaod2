#include <iostream>
#include <fstream>
#include <time.h>
#include <string>

using namespace std;

int generateFile(string fileName, int size){
	ofstream fout(fileName);
	// if (!fout.is_open()){
	// 	cout << "file doesn't exist" << endl;
	// 	return 1;
	// }
	for (int i = 0; i < size; i++){
		fout << rand() % 100 << " ";
		if((i+1) % 4 == 0) fout << "\n";
	}
	fout << "\n";
	fout.close();
	return 0;
}

int readFile(string fileName){
	ifstream fin(fileName);
	if (!fin.is_open()){
		cout << "file doesn't exist" << endl;
		return 1;
	}
	while (fin.good()){
		string tmp;
		getline(fin, tmp);
		cout << tmp << endl;
	}
	fin.close();
	return 0;
}

int addToFile(string fileName, string toAdd){
	ofstream fout(fileName, ios::app);
	if (!fout.is_open()){
		cout << "file doesn't exist" << endl;
		return 1;
	}
	fout << toAdd << endl;
	fout.close();
	return 0;
}

int findNumber(string fileName, int number){
	ifstream fin(fileName);
	if (!fin.is_open()){
		cout << "file doesn't exist" << endl;
		return 1;
	}
	int count = 0; 
	while (fin.good()){
		string tmp;
		getline(fin, tmp);
		string word = "";
		for (int i = 0; i < tmp.length(); i++){
			if (tmp[i] != ' '){
				word += tmp[i];
			}
			else{
				try{ //checking if the word is a number
					int num = stoi(word);
					if (num != number){
						count++;
					}
					else{
						count++;
						cout << "number " << number << " is on " << count << " position" << endl;
						return 0;
					}
				}
				catch(std::invalid_argument const& ex){
					
				}
				word = "";
			}
		}
	}
	cout << "there are no such number in the file" << endl;
	fin.close();
	return 0;
}

int numbersCount(string fileName){
	ifstream fin(fileName);
	int count = 0;
	while (fin.good()){
		string tmp;
		getline(fin, tmp);
		string word = "";
		for (int i = 0; i < tmp.length(); i++){
			if (tmp[i] != ' '){
				word += tmp[i];
			}
			else{
				try{ //checking if the word is a number
					int num = stoi(word);
					count++;
				}
				catch(std::invalid_argument const& ex){
					
				}
				word = "";
			}
		}
	}
	
	fin.close();
	return (count);
}

int fibbonachiFile(string fileName){
	ofstream fout(fileName.substr(0, fileName.length() - 4) + "_fibbonachi.txt");
	ifstream fin(fileName);
	if (!fin.is_open()){
		cout << "file doesn't exist" << endl;
		return 1;
	}
	int a = 0, b = 0, c = 1;
	int j = 0;
	while(fin.good()){
		string tmp;
		getline(fin, tmp);
		string word = "";
		for (int i = 0; i < tmp.length(); i++){
			if (tmp[i] != ' '){
				word += tmp[i];
			}
			else{
				try{ //checking if the word is a number
					int num = stoi(word);
					fout << num << " ";
					j++;
					if(j >= c){
						fout << "\n";
						a = b;
						b = c;
						c = a + b;
						j = 0;
					}
				}
				catch(std::invalid_argument const& ex){
					
				}
				word = "";
			}
		}
	}
	fout.close();
	return 0;
}