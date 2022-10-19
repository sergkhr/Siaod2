#ifndef __HASH_BIN_FILE_H__
#define __HASH_BIN_FILE_H__

#include "hashFunctions.h"
#include "binFile.h"

using namespace std;

int hashRecord(string fileName, int ind, vector<vector<int>> &hashTable, int &tableSize, int &hashElements, int &deletedElements);
int hashFile(string fileName, vector<vector<int>> &hashTable, int &tableSize, int &hashElements, int &deletedElements);
int deleteRecordById(string fileName, int id, vector<vector<int>> &hashTable, int &tableSize, int &deletedElements);
Bank getRecordById(string fileName, int id, vector<vector<int>> &hashTable, int &tableSize);


#endif