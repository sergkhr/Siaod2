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

	int findSumToAllVertexes(int from) {
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
			int sum = findSumToAllVertexes(i);
			if (sum < min) {
				min = sum;
				minIndex = i;
			}
		}
		return minIndex;
	}

	int findShortestPath(int from, int to, vector<int>& path) { //returns weight of path
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
		return dist[to];
	}

	
	void findKShortestPaths(int from, int to, int k, vector<vector<int>>& paths) {//it's absolutely broken now
		paths.clear();
		vector<int> path;
		int weight = findShortestPath(from, to, path);
		paths.push_back(path);
		vector<vector<int>> A; //path candidates (paths with one edge removed)
		vector<int> C; //weights of path candidates
		for (int i = 1; i < k; i++) {
			for (int j = 0; j < path.size() - 1; j++) {
				int removedEdgeFrom = path[j];
				int removedEdgeTo = path[j + 1];
				int removedEdgeWeight = adjMatrix[removedEdgeFrom][removedEdgeTo];
				vector<int> newPath;
				int weight = 0;
				for (int l = 0; l < j; l++) {
					newPath.push_back(path[l]);
					weight += adjMatrix[path[l]][path[l + 1]];
				}
				removeEdge(removedEdgeFrom, removedEdgeTo);
				vector<int> newPath2;
				weight += findShortestPath(removedEdgeFrom, to, newPath2);
				for (int l = 0; l < newPath2.size(); l++) {
					newPath.push_back(newPath2[l]);
				}
				A.push_back(newPath);
				C.push_back(weight);
				addEdge(removedEdgeFrom, removedEdgeTo, removedEdgeWeight);
			}

			for (int j = 0; j < A.size(); j++) {
				for (int t = 0; t < A[j].size(); t++) {
					cout << A[j][t] << " ";
				}
				cout << "weight: " << C[j] << endl;
			}
			cout << endl;
			int min = INT_MAX;
			int minIndex = -1;
			for (int j = 0; j < C.size(); j++) {
				bool alreadyInPaths = false;
				for (int l = 0; l < paths.size(); l++) {
					if (paths[l] == A[j]) {
						alreadyInPaths = true;
						break;
					}
				}
				if (C[j] < min && !alreadyInPaths) {
					min = C[j];
					minIndex = j;
				}
			}
			paths.push_back(A[minIndex]);
			path = A[minIndex];
			A.clear();
			C.clear();
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

	//yen's algorithm absolutely broken now
	// cout << "insert numbers of vertexes to find k shortest paths between them (also insert k)" << endl;
	// int k;
	// cin >> from >> to >> k;
	// vector<vector<int>> paths;
	// g.findKShortestPaths(from - 1, to - 1, k, paths);
	// for (int i = 0; i < paths.size(); i++) {
	// 	cout << "Path " << i + 1 << ": ";
	// 	for (int j = paths[i].size() - 1; j >= 0; j--) {
	// 		cout << paths[i][j] + 1 << " ";
	// 	}
	// 	cout << endl;
	// }
	return 0;
}