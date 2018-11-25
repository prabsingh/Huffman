#include "utility.h"

void readCodeTable(string filename, map<string, string> & charCodeMap);
void encodeFile(string inputFilename, map<string, string> & codetable, string outputFilename);

int main() {
	string inputFile = "clear.txt";
	string codeTableFile = "codetable.txt";
	string outputFile = "coded.txt";
	map<string, string> charCodeMap;

	readCodeTable(codeTableFile, charCodeMap);
	encodeFile(inputFile, charCodeMap, outputFile);

	return 0;
}

//Given filename and a map
//Read the file line by line, populate the map
//with the char and corresponding code;
void readCodeTable(string filename, map<string, string> & charCodeMap) {
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

			charCodeMap.insert(pair<string, string>(symbol, code));
		}
	}
}

//Given inputFile, map, outputFile
//Reads the inputfile, char by char and finds the corresponding code
//in the map. Then outputs the code to the outputFile 
void encodeFile(string inputFilename, map<string, string> & codetable, string outputFilename) {
	ifstream inFile(inputFilename);
	ofstream outFile(outputFilename);
	
	if (inFile.is_open() && outFile.is_open()) {
		char symbol;
		inFile.get(symbol);
		while (!inFile.eof()) {
			string temp(1, symbol);

			if (int(symbol) == 10) {
				temp = "LF";
			}

			string code = codetable[temp];
			outFile << code;

			inFile.get(symbol);
		}
	}

	inFile.close();
	outFile.close();
}
