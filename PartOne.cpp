#include "utility.h"

int main() {
	//map to hold char and freq
	map<char, int> freqTable = {};

	//open the file and read char by char
	ifstream inFile("clear.txt");
	if (inFile.is_open()) {

		char symbol;
		inFile.get(symbol);
		while (!inFile.eof()) {
			//if the symbol doesn't exist in the table... add it
			if (freqTable.count(symbol) <= 0) {
				freqTable.insert(pair<char, int>(symbol, 0));
			}
			//increment count;
			freqTable[symbol]++;

			//move to next symbol
			inFile.get(symbol);
		}
	}

	//open the file to output frequency
	ofstream outFile("freq.txt");
	if (outFile.is_open()) {
		map<char, int>::iterator it = freqTable.begin();
		for (it; it != freqTable.end(); ++it) {
			if (int(it->first) != 10) {
				outFile << it->first << " " << it->second << endl;
			}
			else {
				outFile << "LF " << it->second << endl;
			}
		}
	}
	outFile.close();
	return 0;
}
