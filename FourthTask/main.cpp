#include <iostream>
#include <string>

using namespace std;


class BinaryTree {
private:
	char data;
	BinaryTree *left;
	BinaryTree *right;
public:
	BinaryTree(char data) {
		this->data = data;
		left = nullptr;
		right = nullptr;
	}
	BinaryTree(char data, BinaryTree *left){
		this->data = data;
		this->left = left;
		right = nullptr;
	}
	BinaryTree(char data, BinaryTree *left, BinaryTree *right) {
		this->data = data;
		this->left = left;
		this->right = right;
	}

	~BinaryTree() {
		delete left;
		delete right;
	}
	void setLeft(BinaryTree *left) {
		this->left = left;
	}
	void setRight(BinaryTree *right) {
		this->right = right;
	}
	BinaryTree *getLeft() {
		return left;
	}
	BinaryTree *getRight() {
		return right;
	}
	char getData() {
		return data;
	}

	void addRightNodeRec(const string& s, int it){
		if(it >= s.size()){
			return;
		}
		if(it+1 >= s.size()){
			right = new BinaryTree(s[it]);
			return;
		}
		right = new BinaryTree( s[it+1], new BinaryTree(s[it]) ); //adding a block of a left operand and an operator
		right->addRightNodeRec(s, it+2);
		return;
	}

	bool isExpression(){
		if(data == '+' || data == '-' || data == '*' || data == '/'){ //it's an operator
			if(left == nullptr || right == nullptr){
				return false; //if at least one of the operands is missing and the data is an operator then it's not an expression
			}
			//operator and both operands are present, they must be expressions
			return (left->isExpression() && right->isExpression());
		}
		//not an operator
		if(left == nullptr && right == nullptr){
			return true; //operand can't have operands so it's an expression
		}
		return false;
	}

	bool containsMultiply(){
		if(data == '*'){
			return true;
		}
		if(left != nullptr && left->containsMultiply()){
			return true;
		}
		if(right != nullptr && right->containsMultiply()){
			return true;
		}
		return false;
	}

	void printTree() {
		printTree(0);
	}
	void printTree(int level) {
		if (right != nullptr) {
			right->printTree(level + 1);
		}
		for (int i = 0; i < level; i++) {
			cout << "|   ";
		}
		cout << "|" <<data << endl;
		if (left != nullptr) {
			left->printTree(level + 1);
		}
	}

	string buildExpression(string s = ""){
		if(left != nullptr){
			s = left->buildExpression(s);
		}
		s += data;
		if(right != nullptr){
			s = right->buildExpression(s);
		}
		return s;
	}
};

int main()
{
	setlocale(LC_ALL, "");
	cout << "insert math thingy (without any spaces and using only +-*/ and digits)" << endl;
	string s;
	getline(cin, s);
	if(s.length() == 0){
		cout << "seriosly?" << endl;
		return 0;
	}
	if(s.length() == 1){
		BinaryTree *tree = new BinaryTree(s[0]);
		tree->printTree();
		delete tree;
		return 0;
	}
	BinaryTree *tree = new BinaryTree(s[1], new BinaryTree(s[0]));
	tree->addRightNodeRec(s, 2);
	tree->printTree();
	cout << endl;
	tree->isExpression() ? cout << "it's an expression" << endl : cout << "it's not an expression" << endl;
	cout << endl;
	cout << "expression: " << tree->buildExpression() << endl;
	tree->containsMultiply() ? cout << "contains *" << endl : cout << "doesn't contain *" << endl;
	delete tree;
	return 0;
}