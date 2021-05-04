#include <iostream>
#include <ostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <getopt.h>
using namespace std;

void print_usage(char* name) {
	fprintf(stderr, "Usage: %s [-o outFile] charString inFile", name);
}

int main(int argc, char** argv) {

    int opt;
    int o_flag = 0;
    char* outFileName;

    while ((opt = getopt(argc, argv, "o:")) != -1) {
        switch (opt) {
            case 'o':
                o_flag = 1;
                outFileName = optarg;
                break;
            case '?':
                print_usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (o_flag) {
        if (argc != 5) {
            print_usage(argv[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        if (argc != 3) {
            print_usage(argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    string removeChars(argv[optind]);
    int nextByte;

    ifstream toRead;
    toRead.open(argv[optind + 1], ios::binary); // open the input file to read from

    if (o_flag) {
        string outFile(outFileName);
        ofstream toWrite;
        toWrite.open(outFile, ios::binary); // open the output file to write to
        while ((nextByte = toRead.get()) != EOF) {
            if (removeChars.find((char)nextByte) == string::npos) {
                toWrite.put((char)nextByte);
            }
        }
        toWrite.flush();
        toWrite.close();
    } else {
        while ((nextByte = toRead.get()) != EOF) {
            if (removeChars.find((char)nextByte) == string::npos) {
                cout.put((char)nextByte);
            }
        }
    }

    toRead.close();

    return 0;
}