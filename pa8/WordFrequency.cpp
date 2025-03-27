// Jason Waseq
// jwaseq
// pa8
// WordFrequency.cpp

#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include <algorithm>
#include "Dictionary.h"

using namespace std;

// Function to convert a string to lowercase
string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

int main(int argc, char * argv[]){

   int token_count, line_count;
   size_t begin, end, len;
   ifstream in;
   ofstream out;
   string line;
   string tokenBuffer;
   string token;
   string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789"; // Modified delimiter

   // check command line for correct number of arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }

    Dictionary wordFrequencies; // Declare dictionary here

   // read each line of input file, then count and print tokens 
   line_count = 0;
   while( getline(in, line) )  {
      line_count++;
      len = line.length();
      
      // get tokens in this line
      token_count = 0;
      tokenBuffer = "";

      // get first token
      begin = min(line.find_first_not_of(delim, 0), len);
      end   = min(line.find_first_of(delim, begin), len);
      token = line.substr(begin, end-begin);
      
      while( token!="" ){  // we have a token
        // Convert the word to lowercase
        token = toLower(token);

        // Check if the word is already in the Dictionary
        if (wordFrequencies.contains(token)) {
            // If the word exists, increment its frequency
            wordFrequencies.getValue(token)++;
        } else {
            // If the word is new, add it to the Dictionary with frequency 1
            wordFrequencies.setValue(token, 1);
        }
        token_count++;

         // get next token
         begin = min(line.find_first_not_of(delim, end+1), len);
         end   = min(line.find_first_of(delim, begin), len);
         token = line.substr(begin, end-begin);
      }

   }

      // print tokens in this line

    out << wordFrequencies;


   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}

