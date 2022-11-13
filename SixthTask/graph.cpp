#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Graph {
private:
	vector<vector<int>> adjMatrix;
public:
	Graph(int n) {
		adjMatrix.resize(n, vector<int>(n, 0));
	}

	void addEdge(int from, int to, int weight) {
		adjMatrix[from][to] = weight;
		adjMatrix[to][from] = weight;
	}

	void readGraph() {//the task wants method of reading graph from keyboard
		cout << "Enter number of vertices and number of edges" << endl;
		int n;
		cin >> n;
		adjMatrix.resize(n, vector<int>(n, 0));
		int m;
		cin >> m;
		cout << "Enter edges (<from number> <to number> <weight>) (numbers are from 1 to n)" << endl;
		for (int i = 0; i < m; i++) {
			//even though in memory we store graph as matrix, we will read it as list of edges
			//because the task wanted us to use addEdge method
			int from, to, weight;
			cin >> from >> to >> weight;
			addEdge(from-1, to-1, weight);
		}
	}

	void removeEdge(int from, int to) {
		adjMatrix[from][to] = 0;
		adjMatrix[to][from] = 0;
	}

	void printGraph() {
		cout << setw(3) << "#";
		for (int j = 0; j < adjMatrix[0].size(); j++){
			cout << setw(3) << j+1;
		}
		cout << endl;
		for (int i = 0; i < adjMatrix.size(); i++) {
			cout << setw(3) << i+1;
			for (int j = 0; j < adjMatrix[i].size(); j++) {
				cout << setw(3) << adjMatrix[i][j];
			}
			cout << endl;
		}
	}

	int findSum(int from) {
		vector<int> dist(adjMatrix.size(), INT_MAX);
		vector<bool> visited(adjMatrix.size(), false);
		dist[from] = 0;
		for (int i = 0; i < adjMatrix.size(); i++) {
			int min = INT_MAX;
			int minIndex = -1; //closest vertex
			for (int j = 0; j < adjMatrix.size(); j++) {
				if (!visited[j] && dist[j] < min) {
					min = dist[j];
					minIndex = j;
				}
			}
			visited[minIndex] = true;
			for (int j = 0; j < adjMatrix.size(); j++) {
				if (!visited[j] && adjMatrix[minIndex][j] != 0 && dist[minIndex] != INT_MAX && dist[minIndex] + adjMatrix[minIndex][j] < dist[j]) {
					dist[j] = dist[minIndex] + adjMatrix[minIndex][j];
				}
			}
		}
		int sum = 0;
		for (int i = 0; i < dist.size(); i++) {
			sum += dist[i];
		}
		return sum;
	}

	int findMedian() {
		int min = INT_MAX;
		int minIndex = -1;
		for (int i = 0; i < adjMatrix.size(); i++) {
			int sum = findSum(i);
			if (sum < min) {
				min = sum;
				minIndex = i;
			}
		}
		return minIndex;
	}

	void findShortestPath(int from, int to, vector<int>& path) {
		vector<int> dist(adjMatrix.size(), INT_MAX);
		vector<int> prev(adjMatrix.size(), -1);
		vector<bool> visited(adjMatrix.size(), false);
		dist[from] = 0;
		for (int i = 0; i < adjMatrix.size(); i++) {
			int min = INT_MAX;
			int minIndex = -1; //closest vertex
			for (int j = 0; j < adjMatrix.size(); j++) {
				if (!visited[j] && dist[j] < min) {
					min = dist[j];
					minIndex = j;
				}
			}
			visited[minIndex] = true;
			for (int j = 0; j < adjMatrix.size(); j++) {
				if (!visited[j] && adjMatrix[minIndex][j] != 0 && dist[minIndex] != INT_MAX && dist[minIndex] + adjMatrix[minIndex][j] < dist[j]) {
					dist[j] = dist[minIndex] + adjMatrix[minIndex][j];
					prev[j] = minIndex;
				}
			}
		}
		path.clear();
		int current = to;
		while (current != -1) {
			path.push_back(current);
			current = prev[current];
		}
	}

	void findKShortestPaths(int from, int to, int k, vector<vector<int>>& paths) {
		paths.clear();
		vector<int> path;
		findShortestPath(from, to, path);
		paths.push_back(path);
		for (int i = 1; i < k; i++) {
			int min = INT_MAX;
			int minIndex = -1;
			for (int j = 0; j < paths[i - 1].size() - 1; j++) {
				int from = paths[i - 1][j];
				int to = paths[i - 1][j + 1];
				removeEdge(from, to);
				int sum = findSum(from);
				if (sum < min) {
					min = sum;
					minIndex = j;
				}
				addEdge(from, to, adjMatrix[from][to]);
			}
			vector<int> newPath;
			for (int j = 0; j <= minIndex; j++) {
				newPath.push_back(paths[i - 1][j]);
			}
			findShortestPath(paths[i - 1][minIndex], to, path);
			for (int j = 1; j < path.size(); j++) {
				newPath.push_back(path[j]);
			}
			paths.push_back(newPath);
		}
	}

};

int main(){
	Graph g(0);
	g.readGraph();
	g.printGraph();
	cout << "Median is " << g.findMedian() + 1 << endl;
	cout << "insert numbers of vertexes to find shortest path between them" << endl;
	int from, to;
	cin >> from >> to;
	vector<int> path;
	g.findShortestPath(from - 1, to - 1, path);
	cout << "Shortest path is: ";
	for (int i = path.size() - 1; i >= 0; i--) {
		cout << path[i] + 1 << " ";
	}
	cout << endl;
	return 0;
}