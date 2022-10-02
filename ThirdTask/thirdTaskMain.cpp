#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <vector>

using namespace std;

struct Bank{
	int id;
	char name[61];
	char city[61];
	bool commercialOrState; //true - commercial, false - state 
};

int hash1(const int id){
    return ((id % 20 + 1) << 2 - 3); //interesting enough???
}
int hash2(const int id, const int tableSize){
    return (id % (tableSize-1) + 1);
}

int main(){

    return 0;
}