// Jason Waseq
// jwaseq
// pa6
// Arithmetic.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "BigInteger.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    ofstream outputFile(argv[2]);

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open input file " << argv[1] << endl;
        return 1;
    }

    if (!outputFile.is_open()) {
        cerr << "Error: Could not open output file " << argv[2] << endl;
        inputFile.close();
        return 1;
    }

    string stringA, stringB;
    inputFile >> stringA >> stringB;

    BigInteger A(stringA);
    BigInteger B(stringB);

    outputFile << A << "\n\n";
    outputFile << B << "\n\n";
    outputFile << A + B << "\n\n";
    outputFile << A - B << "\n\n";
    outputFile << A - A << "\n\n";
    outputFile << 3 * A - 2 * B << "\n\n";
    outputFile << A * B << "\n\n";
    outputFile << A * A << "\n\n";
    outputFile << B * B << "\n\n";
    outputFile << 9 * A * A * A * A + 16 * B * B * B * B * B << "\n\n";

    inputFile.close();
    outputFile.close();

    return 0;
}

