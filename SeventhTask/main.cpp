#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;

string rleCompression(string s) {
	string result = "";
	int count = 1;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == s[i + 1]) {
			count++;
		} else {
			if(count < 5){
				for (int j = 0; j < count; j++) {
					result += s[i];
				}
			} else {
				result += s[i];
				result += "<" + to_string(count) + ">";
			}
			count = 1;
		}
	}
	return result;
}

string rleDeCompression(string s) {
	string result = "";
	int i = 0;
	while (i < s.length()) {
		if (s[i] == '<') {
			int j = i + 1;
			int count = stoi(s.substr(j, s.find('>', j) - j));
			for (int k = 0; k < count-1; k++) {
				result += s[i - 1];
			}
			i = s.find('>', j) + 1;
		} else {
			result += s[i];
			i++;
		}
	}
	return result;
}

int findMatch(string s, int i, int windowSize, int lookAheadSize, int &offset, int &length) {
	int max = 0;
	for (int j = i - windowSize; j < i; j++) {
		if (j < 0) {
			continue;
		}
		int k = 0;
		while (s[i + k] == s[j + k] && k < lookAheadSize) {
			k++;
		}
		if (k > max) {
			max = k;
			offset = i - j;
			length = k;
		}
	}
	return max;
}

struct NodeLZ77{
	int offset;
	int length;
	char next;
};

vector<NodeLZ77> lz77Compression(string s, int windowSize, int lookAheadSize) {
	vector<NodeLZ77> result;
	int i = 0;
	while (i < s.length()) {
		int offset = 0;
		int length = 0;
		int max = findMatch(s, i, windowSize, lookAheadSize, offset, length);
		if (max == 0) {
			NodeLZ77 node;
			node.offset = 0;
			node.length = 0;
			node.next = s[i];
			result.push_back(node);
			i++;
		} else {
			NodeLZ77 node;
			node.offset = offset;
			node.length = length;
			node.next = s[i + length];
			result.push_back(node);
			i += length + 1;
		}
	}
	return result;
}

string lz77DeCompression(vector<NodeLZ77> s) {
	string result = "";
	for (int i = 0; i < s.size(); i++) {
		if (s[i].length == 0) {
			result += s[i].next;
		} else {
			int start = result.length() - s[i].offset;
			for (int j = 0; j < s[i].length; j++) {
				result += result[start + j];
			}
			result += s[i].next;
		}
	}
	return result;
}

struct LZ78Node {
	int index;
	char next;
};

vector<LZ78Node> lz78Compression(string s) {
	vector<LZ78Node> result;
	map<string, int> dictionary;
	string temp = "";
	for (int i = 0; i < s.length(); i++) {
		if(dictionary.find(temp + s[i]) != dictionary.end()){
			temp += s[i];
		}
		else{
			LZ78Node node;
			node.index = dictionary[temp];
			node.next = s[i];
			result.push_back(node);
			dictionary[temp + s[i]] = dictionary.size();
			temp = "";
		}
	}
	if(temp != ""){
		LZ78Node node;
		node.next = temp[temp.length() - 1];
		temp = temp.substr(0, temp.length() - 1);
		node.index = dictionary[temp];
		result.push_back(node);
	}
	return result;
}

string lz78DeCompression(vector<LZ78Node> s) {
	string result = "";
	vector<string> dictionary = {""};
	for (int i = 0; i < s.size(); i++) {
		string temp = dictionary[s[i].index] + s[i].next;
		result += temp;
		dictionary.push_back(temp);
	}
	return result;
}

map<char, int> countCharacters(string s) {
	map<char, int> result;
	for (int i = 0; i < s.length(); i++) {
		if (result.find(s[i]) == result.end()) {
			result[s[i]] = 1;
		} else {
			result[s[i]]++;
		}
	}
	return result;
}

map<char, string> shennonFanoCompressionMap(const map<char, int>& count) {
	map<char, string> result;
	vector<pair<char, int>> temp;
	for (auto it = count.begin(); it != count.end(); it++) {
		temp.push_back(*it);
	}
	sort(temp.begin(), temp.end(), [](pair<char, int> a, pair<char, int> b) {return a.second > b.second; });
	int sum = 0;
	for (int i = 0; i < temp.size(); i++) {
		sum += temp[i].second;
	}
	vector<pair<char, int>> left;
	vector<pair<char, int>> right;
	int sum1 = 0;
	int sum2 = 0;
	for(int i = 0; i < temp.size(); i++){
		if(sum1 <= sum2){
			left.push_back(temp[i]);
			sum1 += temp[i].second;
		}
		else{
			right.push_back(temp[i]);
			sum2 += temp[i].second;
		}
	}
	for (int k = 0; k < left.size(); k++) {
		result[left[k].first] = "0";
	}
	for (int k = 0; k < right.size(); k++) {
		result[right[k].first] = "1";
	}


	//now we go recursive for left and right
	if (left.size() > 1) {
		map<char, int> tempCount;
		for (int i = 0; i < left.size(); i++) {
			tempCount[left[i].first] = left[i].second;
		}
		map<char, string> tempLeaf = shennonFanoCompressionMap(tempCount);
		for (auto it = tempLeaf.begin(); it != tempLeaf.end(); it++) {
			result[it->first] = "0" + it->second;
		}
	}
	if (right.size() > 1) {
		map<char, int> tempCount;
		for (int i = 0; i < right.size(); i++) {
			tempCount[right[i].first] = right[i].second;
		}
		map<char, string> tempLeaf = shennonFanoCompressionMap(tempCount);
		for (auto it = tempLeaf.begin(); it != tempLeaf.end(); it++) {
			result[it->first] = "1" + it->second;
		}
	}
	return result;
}

string shennonFanoCompression(map<char, string> code, string s) {
	string result = "";
	for (int i = 0; i < s.length(); i++) {
		result += code[s[i]];
	}
	return result;
}

string shennonFanoDeCompression(map<char, string> code, string s) {
	string result = "";
	string temp = "";
	for (int i = 0; i < s.length(); i++) {
		temp += s[i];
		for (auto it = code.begin(); it != code.end(); it++) {
			if (it->second == temp) {
				result += it->first;
				temp = "";
				break;
			}
		}
	}
	return result;
}

struct HaffmanBinaryTreeNode {
	char c;
	int count;
	HaffmanBinaryTreeNode* left;
	HaffmanBinaryTreeNode* right;
	HaffmanBinaryTreeNode(char c, int count) {
		this->c = c;
		this->count = count;
		this->left = nullptr;
		this->right = nullptr;
	}
	HaffmanBinaryTreeNode(HaffmanBinaryTreeNode* left, HaffmanBinaryTreeNode* right) {
		this->c = 0;
		this->count = left->count + right->count;
		this->left = left;
		this->right = right;
	}
	~HaffmanBinaryTreeNode() {
		if (this->left != nullptr) {
			delete this->left;
		}
		if (this->right != nullptr) {
			delete this->right;
		}
	}
};

void haffmanCompressionMapRecursive(HaffmanBinaryTreeNode* node, map<char, string>& result, string code = "") {
	if (node->left == nullptr && node->right == nullptr) {
		result[node->c] = code;
		return;
	}
	haffmanCompressionMapRecursive(node->left, result, code + "0");
	haffmanCompressionMapRecursive(node->right, result, code + "1");
}

map<char, string> haffmanCompressionMap(const map<char, int>& count) {
	map<char, string> result;
	vector<HaffmanBinaryTreeNode*> temp;
	for (auto it = count.begin(); it != count.end(); it++) {
		temp.push_back(new HaffmanBinaryTreeNode(it->first, it->second));
	}
	while (temp.size() > 1) {
		sort(temp.begin(), temp.end(), [](HaffmanBinaryTreeNode* a, HaffmanBinaryTreeNode* b) {return a->count > b->count; }); //haha press f to pay respect to efficiency
		HaffmanBinaryTreeNode* left = temp.back();
		temp.pop_back();
		HaffmanBinaryTreeNode* right = temp.back();
		temp.pop_back();
		temp.push_back(new HaffmanBinaryTreeNode(left, right));
	}
	HaffmanBinaryTreeNode* root = temp.back();
	temp.pop_back();
	//now we have haffman tree
	//we go recursive and fill map
	haffmanCompressionMapRecursive(root, result);
	delete root;
	return result;
}

string haffmanCompression(map<char, string> code, string s) {
	string result = "";
	for (int i = 0; i < s.length(); i++) {
		result += code[s[i]] + " ";
	}
	return result;
}

string haffmanDeCompression(map<char, string> code, string s) {
	string result = "";
	string temp = "";
	for (int i = 0; i < s.length(); i++) {
		if(s[i] == ' ') continue;
		temp += s[i];
		for (auto it = code.begin(); it != code.end(); it++) {
			if (it->second == temp) {
				result += it->first;
				temp = "";
				break;
			}
		}
	}
	return result;
}



int main() {
	cout << "insert string that is to be compressed via rle algorithm (no spaces and <> symbols): ";
	string s;
	cin >> s;
	cin.clear();
	cin.ignore(10000, '\n');
	string compressed = rleCompression(s);
	cout << "rle compressed string: " << compressed << endl;
	string decompressed = rleDeCompression(compressed);
	cout << "rle decompressed string: " << decompressed << endl;
	cout << "rle compressing  string: " << s << endl;
	cout << "compression ratio (more = better): " << (double)(s.size() * sizeof(char)) / (double)(compressed.size() * sizeof(char)) << endl;
	cout << endl;


	cout << "insert string that is to be decompressed via lz77 algorithm (no spaces and <> symbols): ";
	cin >> s;
	cin.clear();
	cin.ignore(10000, '\n');
	cout << "insert window size: ";
	int windowSize;
	cin >> windowSize;
	cin.clear();
	cin.ignore(10000, '\n');
	cout << "insert look ahead size: ";
	int lookAheadSize;
	cin >> lookAheadSize;
	cin.clear();
	cin.ignore(10000, '\n');
	vector<NodeLZ77> compressedVec = lz77Compression(s, windowSize, lookAheadSize);
	cout << "lz77 compressed string: ";
	for (int i = 0; i < compressedVec.size(); i++) {
		cout << "<" << compressedVec[i].offset << "," << compressedVec[i].length << "," << compressedVec[i].next << ">";
	}
	cout << endl;
	decompressed = lz77DeCompression(compressedVec);
	cout << "lz77 decompressed string: " << decompressed << endl;
	cout << "lz77 compressing  string: " << s << endl;
	cout << "compression ratio (more = better): " << (double)(s.size()*sizeof(char)) / (double)sizeof(compressedVec) << endl; 
	cout << endl;

	cout << "insert string that is to be decompressed via lz78 algorithm (no spaces and <> symbols): ";
	cin >> s;
	cin.clear();
	cin.ignore(10000, '\n');
	vector<LZ78Node> compressedVec2 = lz78Compression(s);
	cout << "lz78 compressed string: ";
	for (int i = 0; i < compressedVec2.size(); i++) {
		cout << "<" << compressedVec2[i].index << "," << compressedVec2[i].next << ">";
	}
	cout << endl;
	decompressed = lz78DeCompression(compressedVec2);
	cout << "lz78 decompressed string: " << decompressed << endl;
	cout << "lz78 compressing  string: " << s << endl;
	cout << "compression ratio (more = better): " << (double)(s.size()*sizeof(char)) / (double)sizeof(compressedVec2) << endl;
	cout << endl;


	cout << "insert string that is to be compressed via shennon fano algorithm: " << endl;
	getline(cin, s);

	//s = rleDeCompression("a<50>b<39>c<18>d<49>e<35>f<24>"); //test from wiki
	
	map<char, int> count = countCharacters(s);
	map<char, string> compressedMap = shennonFanoCompressionMap(count);
	//print the compressed map
	for (auto it = compressedMap.begin(); it != compressedMap.end(); it++) {
		cout << it->first << " " << it->second;
		cout << " total symbols: " << count[it->first] << endl;
	}
	cout << endl;
	compressed = shennonFanoCompression(compressedMap, s);
	cout << "shennon fano compressed   string: " << compressed << endl;
	decompressed = shennonFanoDeCompression(compressedMap, compressed);
	cout << "shennon fano decompressed string: " << decompressed << endl;
	cout << "shennon fano compressing  string: " << s << endl;
	//here we compare the string as a sequence of chars (every char is 1 byte)
	//with the compressed string as a sequence of bits (every bit is 1/8 byte)
	//that's why s is multiplyed by 8 and compressed by 1
	cout << "compression ratio (more = better): " << (double)(s.size()*8) / (double)(compressed.size()) << endl;
	cout << endl;

	cout << "insert string that is to be compressed via haffman algorithm: " << endl;
	getline(cin, s);
	count = countCharacters(s);
	compressedMap = haffmanCompressionMap(count);
	//print the compressed map
	for (auto it = compressedMap.begin(); it != compressedMap.end(); it++) {
		cout << it->first << " " << it->second;
		cout << " total symbols: " << count[it->first] << " probability: " << (double)count[it->first] / (double)s.size() << endl;
	}
	cout << endl;
	cout << "average length of code: ";
	double averageLength = 0;
	for (auto it = compressedMap.begin(); it != compressedMap.end(); it++) {
		averageLength += it->second.size();
	}
	averageLength /= compressedMap.size();
	cout << averageLength << endl;
	cout << "dispersion of code: ";
	double dispersion = 0;
	for (auto it = compressedMap.begin(); it != compressedMap.end(); it++) {
		dispersion += (it->second.size() - averageLength) * (it->second.size() - averageLength);
	}
	dispersion /= compressedMap.size();
	cout << dispersion << endl;
	cout << endl;
	compressed = haffmanCompression(compressedMap, s);
	cout << "haffman compressed   string: " << compressed << endl;
	decompressed = haffmanDeCompression(compressedMap, compressed);
	cout << "haffman decompressed string: " << decompressed << endl;
	cout << "haffman compressing  string: " << s << endl;
	int spaces = 0;
	for (int i = 0; i < compressed.size(); i++) {
		if (compressed[i] == ' ') {
			spaces++;
		}
	}
	cout << "compression ratio (more = better): " << (double)(s.size() * 8) / (double)(compressed.size() - spaces) << endl;
	cout << endl;

	return 0;
}