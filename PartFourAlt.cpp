#include "utility.h"

struct Node
{
	string symbol;
	int freq;
	Node * lChild;
	Node * rChild;
	string code;
};

void createTreeAlt(string filename, Node* root);
void decodeFileBinary(string encodedFilename, Node * root, string outputFilename);

int main() {
	string inputFile = "codedalt.txt" ;
	string codetableFile = "codetable.txt" ;
	string outputFile = "decodedalt.txt";
	Node * root = new Node();

	createTreeAlt(codetableFile, root);
	decodeFileBinary(inputFile, root, outputFile);
	return 0;
}

void insertNodeAlt(Node* root, string code, string symbol) {
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

void createTreeAlt(string filename, Node * root) {
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

			insertNodeAlt(root, code, symbol);
		}
	}
}

void decodeFileBinary(string encodedFilename, Node * root, string outputFilename) {
	ifstream inFile(encodedFilename, ios::in|ios::binary);
	ofstream outFile(outputFilename);
	Node * current = root;
	
	if (inFile.is_open() && outFile.is_open()) {
		char charByte;
		while (inFile.read(&charByte, 1)) {
			bitset<8> byte(charByte);
			//loop through each bit and choose left or right child
			for (int i = 7; i >= 0; i--) {
				if (byte[i] == false) {
					current = current->lChild;
				}
				else {
					current = current->rChild;
				}

				//check if at a lea by seeing if 
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
			}
		}
	}

	inFile.close();
	outFile.close();
}