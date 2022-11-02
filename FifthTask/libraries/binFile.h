#ifndef __BINFILE_H__
#define __BINFILE_H__

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

int toBinary(string fileName, string fileNameBin);//read from text file and write to binary file
int getBank(string fileNameBin, Bank &bank, int ind);//get bank by index from binary file
int linearSearch(string fileNameBin, Bank &bank, int id);
int deleteBankById(string fileNameBin, int id);
int deleteBankByIndex(string fileNameBin, int ind);
int addBank(string fileNameBin, const Bank &bank, int ind = -1);

void testBinF();

#endif