#include "utility.h"

struct Node
{
	string symbol;
	int freq;
	Node * lChild;
	Node * rChild;
	string code;
};

struct compare {
	bool operator()(Node* a, Node* b) {
		return a->freq > b->freq;
	}
};

void readFreqFile(vector<Node *> & nodeVec, string filename);
void assignCode(Node* n, string curCode);
void outputCodeTable(vector<Node *> & nodeVec, string filename);
Node* createTree(vector<Node *> & symbolVec);

int main() {
	vector<Node *> originalList;
	string freqFilename = "freq.txt";
	
	readFreqFile(originalList, freqFilename);
	Node * root = createTree(originalList);
	assignCode(root, "");

	string outFileName = "codetable.txt";
	outputCodeTable(originalList, outFileName);

	return 0;
}


void readFreqFile(vector<Node *> & nodeVec, string filename) {
	ifstream inFile;
	inFile.open(filename);
	
	if (inFile.is_open()) {
		string value;
		while (getline(inFile, value)) {
			Node* nextValue = new Node();
			//check if first character is space since delimeter is space
			//
			if (value[0] != ' ') {
				stringstream(value) >> nextValue->symbol >> nextValue->freq;
			}
			else {
				nextValue->symbol = ' ';
				stringstream(value) >> nextValue->freq;
			}
			nodeVec.push_back(nextValue);
		}
	}

	inFile.close();
}

void assignCode(Node* n, string curCode) {
	//if at a leaf then assign code
	//else continue traversing tree
	if (n->lChild == NULL && n->rChild == NULL) {
		n->code = curCode;
	}
	else {
		//for left child add 0
		//for right child add 1
		assignCode(n->lChild, curCode + "0");
		assignCode(n->rChild, curCode + "1");
	}
}

void outputCodeTable(vector<Node *> & nodeVec, string filename) {
	ofstream outFile("codetable.txt");
	for (int i = 0; i < nodeVec.size(); i++) {
		outFile << nodeVec[i]->symbol << " " << nodeVec[i]->code << endl;
	}
	outFile.close();
}

Node* createTree(vector<Node*> & symbolVec) {
	priority_queue<Node* ,vector<Node* >, compare> queue;
	for (Node* n : symbolVec) {
		queue.push(n);
	}

	while (queue.size() > 1) {
		Node * parent = new Node();
		
		parent->lChild = queue.top();
		parent->freq = queue.top()->freq;
		queue.pop();
		
		parent->rChild = queue.top();
		parent->freq += queue.top()->freq;
		queue.pop();
		
		queue.push(parent);
	}
	return queue.top();
}