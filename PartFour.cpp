#include "utility.h"

struct Node
{
	string symbol;
	int freq;
	Node * lChild;
	Node * rChild;
	string code;
};

void createTree(string filename, Node* root);
void decodeFile(string encodedFilename, Node * root, string outputFilename);

int main() {
	string inputFile = "coded.txt" ;
	string codetableFile = "codetable.txt" ;
	string outputFile = "decoded.txt";
	Node * root = new Node();

	createTree(codetableFile, root);
	decodeFile(inputFile, root, outputFile);

	return 0;
}

void insertNode(Node* root, string code, string symbol) {
	Node * current = root;
	for (int i = 0; i < code.size(); i++) {
		if (code[i] == '0') {
			//check if lChild is empty
			//if so create a new Node and add;
			//Then update current to lchild;
			if (current->lChild == NULL) {
				Node * child = new Node();
				current->lChild = child;
			}
			current = current->lChild;
		}
		else {
			//check if rChild is empty
			//if so create a new Node and add;
			//Then update current to rchild;
			if (current->rChild == NULL) {
				Node * child = new Node();
				current->rChild = child;
			}
			current = current->rChild;
		}
	}
	current->symbol = symbol;
}

void createTree(string filename, Node * root) {
	ifstream inFile;
	inFile.open(filename);

	if (inFile.is_open()) {
		string line;
		while (getline(inFile, line)) {
			string symbol;
			string code;

			//check if first char is space;
			if (line[0] == ' ') {
				symbol = " ";
				stringstream(line) >> code;
			}
			else {
				stringstream(line) >> symbol >> code;
			}

			insertNode(root, code, symbol);
		}
	}
}

void decodeFile(string encodedFilename, Node * root, string outputFilename) {
	ifstream inFile(encodedFilename);
	ofstream outFile(outputFilename);
	Node * current = root;
	
	if (inFile.is_open() && outFile.is_open()) {
		char bit;
		inFile.get(bit);
		while (!inFile.eof()) {
			if (bit == '0') {
				current = current->lChild;
			}
			else {
				current = current->rChild;
			}
			
			//check if at a leave by seeing if 
			//both children are null
			//if so write the symbol in the output file
			//reset current node to root
			if (current->lChild == NULL and current->rChild == NULL) {
				//check if symbol is LF, and output correct value;
				if (current->symbol == "LF") {
					outFile << endl;
				}
				else {
					outFile << current->symbol;
				}
				current = root;
			}
			
			inFile.get(bit);
		}
	}

	inFile.close();
	outFile.close();
}

