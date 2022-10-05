#ifndef __HASHFUNCTIONS_H__
#define __HASHFUNCTIONS_H__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <time.h>
#include <string>
#include <vector>

using namespace std;

int hash1(const int id);
int hash2(const int id, const int tableSize);
int addHash(vector<vector<int>> &hashTable, int &tableSize, const int id, const int index);
int deleteHash(vector<vector<int>> &hashTable, const int tableSize, const int id);
int findByHash(const vector<vector<int>> &hashTable, const int tableSize, const int id);
int resizeHash(vector<vector<int>> &hashTable, int &tableSize);
void testHashT();

#endif