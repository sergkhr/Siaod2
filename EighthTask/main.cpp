#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

bool areCitiesConnected(const vector<vector<int>>& matrix, int city1, int city2, vector<bool>& visited){
	if (city1 < 0 || city1 >= matrix.size() || city2 < 0 || city2 >= matrix.size()){
		return false;
	}
	if(city1 == city2){
		return true;
	}
	if (matrix[city1][city2] != 0){
		return true;
	}
	visited[city1] = true;
	for (int i = 0; i < matrix.size(); i++){
		if (matrix[city1][i] != 0 && !visited[i]){
			if (areCitiesConnected(matrix, i, city2, visited)){
				return true;
			}
		}
	}
	return false;
}

int deleteRoads(vector<vector<int>>& matrix, const vector<int>& roads){
	int sum = 0;
	for(int i = 0; i < roads.size(); i+=2){
		if(roads[i] == roads[i+1]){
			sum++;
			matrix[roads[i]][roads[i+1]] -= 1;
			continue;
		}
		matrix[roads[i]][roads[i+1]] -= 1; //we delete the road
		matrix[roads[i+1]][roads[i]] -= 1;
		vector<bool> visited(matrix.size(), false);
		if (areCitiesConnected(matrix, roads[i], roads[i+1], visited)){ //we check if it is possible to get from city i to city j without the deleted road
			sum++;
		}
		else{
			matrix[roads[i]][roads[i+1]] += 1; //if it is not, we add the road back;
			matrix[roads[i+1]][roads[i]] += 1;
		}
	}
	return sum;
}

int main(){
	cout << "insert number of cities: ";
	int n;
	cin >> n;
	vector<vector<int>> matrix(n, vector<int>(n));
	cout << "insert number of roads: ";
	int m;
	cin >> m;
	cout << "insert roads (two numbers of cities (cities are numbered from 1 to \"inserted number of cities\")): ";
	vector<int> roads(m*2);
	for (int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			matrix[i][j] = 0;
		}
	}
	for (int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		if(a == b) matrix[a-1][b-1] += 1;
		else{
			matrix[a-1][b-1] += 1;
			matrix[b-1][a-1] += 1;
		}
		roads[i*2] = a-1;
		roads[i*2+1] = b-1;
	}
	cout << "test citiesConnection check(y/n) (n by default): ";
	char c;
	cin >> c;
	if (c == 'y'){
		cout << "insert two cities (from 1 to \"inserted number of cities\"): " << endl;
		int a, b;
		cin >> a >> b;
		vector<bool> visited(matrix.size(), false);
		cout << "are cities connected: " << ((areCitiesConnected(matrix, a-1, b-1, visited))?"yes":"no") << endl;
	}

	cout << "optimisation..." << endl;
	cout << "sum of deleted roads: " << deleteRoads(matrix, roads) << endl;
	for(int j = 0; j < matrix.size(); j++){
		cout << setw(3) << j+1;
	}
	cout << " ";
	for (int i = 0; i < matrix.size(); i++){
		cout << endl << i+1;
		for (int j = 0; j < matrix.size(); j++){
			cout << setw(3) << matrix[i][j];
		}
		cout << endl;
	}
	return 0;
}