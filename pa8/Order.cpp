// Jason Waseq
// jwaseq
// pa8
// Order.cpp

#include <iostream>
#include <fstream>
#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return 1;
    }

    ifstream inFile(argv[1]);
    if (!inFile.is_open()) {
        cerr << "Unable to open input file: " << argv[1] << endl;
        return 1;
    }

    ofstream outFile(argv[2]);
    if (!outFile.is_open()) {
        cerr << "Unable to open output file: " << argv[2] << endl;
        inFile.close();
        return 1;
    }

    Dictionary dict;

    string line;
    int lineNumber = 1;
    while (getline(inFile, line)) {
        dict.setValue(line, lineNumber);
        lineNumber++;
    }

    outFile << dict.to_string() << endl;

    outFile << dict.pre_string() << endl;

    inFile.close();
    outFile.close();

    return 0;
}

