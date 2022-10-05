#include "hashFunctions.h"

int hash1(const int id){
	return (((id % 20 + 1) << 2) - 3); //interesting enough???
}
int hash2(const int id, const int tableSize){
	return (id % (tableSize-1) + 1);
}
int addHash(vector<vector<int>> &hashTable, int &tableSize, const int id, const int index){
	int hash = hash1(id) % tableSize;
	int step = hash2(id, tableSize);
	for(int i = 0; i < tableSize; i++){
		if(hashTable[hash][1] < 0){ //-1 means empty, -2 means deleted
			hashTable[hash][0] = id;
			hashTable[hash][1] = index;
			return 0; //0 means success
		}
		hash = (hash + step) % tableSize;
	}
	return resizeHash(hashTable, tableSize); //resize if full
}
int deleteHash(vector<vector<int>> &hashTable, const int tableSize, const int id){
	int hash = hash1(id) % tableSize;
	int step = hash2(id, tableSize);
	for(int i = 0; i < tableSize; i++){
		if(hashTable[hash][1] == -1){ //-1 means empty
			return -1; //-1 means not found
		}
		if(hashTable[hash][0] == id){ 
			hashTable[hash][1] = -2; //-2 means deleted   deleted != empty so search should be fine
			return 0; //0 means success
		}
		hash = (hash + step) % tableSize;
	}
	return -1; //-1 means not found
}
int findByHash(const vector<vector<int>> &hashTable, const int tableSize, const int id){
	int hash = hash1(id) % tableSize;
	int step = hash2(id, tableSize);
	for(int i = 0; i < tableSize; i++){
		if(hashTable[hash][1] == -1){ //-1 means empty
			return -1; //-1 means not found
		}
		if(hashTable[hash][0] == id){ 
			return hashTable[hash][1]; //return index
		}
		hash = (hash + step) % tableSize;
	}
	return -1; //-1 means not found
}
int resizeHash(vector<vector<int>> &hashTable, int &tableSize){
	int oldTableSize = tableSize;
	int simpleNums[6] = {13, 19, 53, 601, 12289, 1046527};
	for(int i = 0; i < 6; i++){
		if(simpleNums[i] > tableSize){
			tableSize = simpleNums[i];
			break;
		}
		if(i == 5){
			return -1; //error too much data
		}
	}
	vector<vector<int>> newHashTable(tableSize, {-1, -1});
	for(int i = 0; i < oldTableSize; i++){
		if(hashTable[i][1] >= 0){ // >= 0 means not empty or deleted
			addHash(newHashTable, tableSize, hashTable[i][0], hashTable[i][1]);
		}
	}
	hashTable = newHashTable;
	return 0;
}


void testHashT(){
	srand(time(NULL));
	int simpleNums[6] = {13, 19, 53, 601, 12289, 1046527}; //simple numbers for hash table size the last one is 1 046 527 for 1 million test
	int hashSize = simpleNums[0];
	// hash table: (id, index)
	vector<vector<int>> hashTable(hashSize, {-1, -1});
	int a[15];
	for(int i = 0; i < 15; i++){
		a[i] = rand() % 100;
	}
	cout << "hash table for 15 random id's" << endl;
	for(int i = 0; i < hashSize; i++){
		if(addHash(hashTable, hashSize, a[i], i) == -1) cout << "Table is full" << endl;
	}
	for(int i = 0; i < hashSize; i++){
		cout << setw(4) << hashTable[i][0] << ":" << setw(2) << hashTable[i][1];
	}
	cout << endl;
	cout << "delete " << a[2] << endl;
	deleteHash(hashTable, hashSize, a[2]);
	for(int i = 0; i < hashSize; i++){
		cout << setw(4) << hashTable[i][0] << ":" << setw(2) << hashTable[i][1];
	}
	cout << endl;
	cout << "adding more" << endl;
	for(int i = hashSize; i < 15; i++){
		if(addHash(hashTable, hashSize, a[i], i) == -1) cout << "Table is full" << endl;
	}
	for(int i = 0; i < hashSize; i++){
		cout << setw(4) << hashTable[i][0] << ":" << setw(2) << hashTable[i][1];
	}
    cout << endl;
    cout << "pick what to delete" << endl;
    int delId;
    cin >> delId;
    if(!deleteHash(hashTable, hashSize, delId)) cout << "deleted" << endl;
    else cout << "not found" << endl;
    cout << "pick what to find" << endl;
    int findId;
    cin >> findId;
    int findIndex = findByHash(hashTable, hashSize, findId);
    if(findIndex >= 0) cout << "found at index " << findIndex << endl;
    else cout << "not found" << endl;
	return;
}