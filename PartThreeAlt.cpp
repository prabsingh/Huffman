#include "utility.h"

/*
Team 7
Prabhdeep Singh
Christopher Goebel
*/

void readCodeTableAlt(string filename, map<string, string> & charCodeMap);
void encodeFileBinary(string inputFilename, map<string, string> & codetable, string outputFilename);

int main() {
	string inputFile = "clear.txt";
	string codeTableFile = "codetable.txt";
	string outputFile = "codedalt.txt";
	map<string, string> charCodeMap;
	
	readCodeTableAlt(codeTableFile, charCodeMap);
	encodeFileBinary(inputFile, charCodeMap, outputFile);
}

//Given filename and a map
//Read the file line by line, populate the map
//with the char and corresponding code;
void readCodeTableAlt(string filename, map<string, string> & charCodeMap) {
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
void encodeFileBinary(string inputFilename, map<string, string> & codetable, string outputFilename) {
	ifstream inFile(inputFilename);
	ofstream outFile(outputFilename, ios::out|ios::binary);

	if (inFile.is_open() && outFile.is_open()) {
		int pos = 7;
		bitset<8> byte;

		char symbol;
		inFile.get(symbol);
		while (!inFile.eof()) {
			string temp(1, symbol);

			if (int(symbol) == 10) {
				temp = "LF";
			}

			string code = codetable[temp];
			
			//for each bit of the code
			//add to the byte
			for (int i = 0; i < code.size(); i++) {			
				if (code[i] == '1') {
					byte.set(pos);
				}
				pos--;

				//if reached the end of the byte then write the byte to file
				//reset byte to all 0
				//reset pos to begin of byte
				if (pos < 0) {
					outFile.write((char *)(&byte),1);
					byte.reset();
					pos = 7;
				}
			}
			
			inFile.get(symbol);
		}
		
		//output the last byte if there is something written to it
		if (pos != 7) {
			outFile.write((char *)(&byte), 1);
		}
	}

	inFile.close();
	outFile.close();
}
