#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

void print_usage() {
	cerr << "Usage: remove-chars [chars] [inFile] [outFile]" << endl;
}

int main(int argc, char** argv) {

    if (argc != 4) {
        print_usage();
        exit(EXIT_FAILURE);
    }

    string removeChars(argv[1]);
    int nextByte;

    ifstream toRead;
    toRead.open(argv[2], ios::binary); // open the input file to read from

    ofstream toWrite;
    toWrite.open(argv[3], ios::binary); // open the output file to write to


    while((nextByte = toRead.get()) != EOF) {
        if (removeChars.find((char)nextByte) == string::npos) {
            toWrite.put((char)nextByte);
        }
    }

    toWrite.flush();

    toRead.close();
    toWrite.close();

    return 0;
}