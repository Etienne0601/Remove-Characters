#include <iostream>
#include <ostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <getopt.h>
using namespace std;

void print_usage(char* name) {
	fprintf(stderr, "Usage: %s [-e] [-o outFile] [charString] inFile", name);
}

void print_section(string::const_iterator & itr, string::const_iterator & end, ostream & out) {
    // we have to go forward until we see a pipe,
    // then backward to erase all the trailing spaces

    string::const_iterator writeItr(itr);
    int i = 0;
    int lastCharPos = 0;

    // keep going until we reach the end of this section
    while (*itr != '|') {
        if (*itr != ' ') {
            lastCharPos = i;
        }
        ++i;
        ++itr;
    }

    // now itr is pointing to the '|' character
    itr += 2;

    // now write all the relevant characters to the output stream
    for (i = 0; i <= lastCharPos; ++i) {
        out.put(*writeItr);
        ++writeItr;
    }
}

int main(int argc, char** argv) {

    int opt;
    int o_flag = 0;
    int e_flag = 0;
    char* outFileName;

    while ((opt = getopt(argc, argv, "eo:")) != -1) {
        switch (opt) {
            case 'o':
                o_flag = 1;
                outFileName = optarg;
                break;
            case 'e':
                e_flag = 1;
                break;
            case '?':
                print_usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // with the e flag we don't have a charString argument

    // check for correct number of command line args
    if (e_flag) {
        if (argc != (optind + 1)) {
            print_usage(argv[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        if (argc != (optind + 2)) {
            print_usage(argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    string removeChars;
    string outFile;
    string lineStr;
    ofstream toWrite;
    int nextByte;

    ifstream toRead;

    // open the input file
    if (e_flag) {
        toRead.open(argv[optind], ios::binary);
    } else {
        toRead.open(argv[optind + 1], ios::binary); // open the input file to read from
        removeChars = string(argv[optind]);
    }


    if (o_flag) {
        outFile = string(outFileName);
        toWrite.open(outFile, ios::binary); // open the output file to write to
    }

    if (e_flag) {
        if (o_flag) {
            // write to file

            getline(toRead, lineStr); // read a line

            while (!toRead.eof()) {

                string::const_iterator itr = lineStr.cbegin();
                string::const_iterator end = lineStr.cend();
                
                // we can first do the name of the website/app
                print_section(itr, end, toWrite);
                toWrite.put(',');
                int countPipes = 1;

                // iterate through sections of the line stored in lineStr
                while (countPipes < 3) {
                    print_section(itr, end, toWrite);
                    ++countPipes;
                    toWrite.put(',');
                }
                print_section(itr, end, toWrite);
                toWrite.put('\n');

                getline(toRead, lineStr); // read a line

            }
        } else {
            // write to cout

            getline(toRead, lineStr); // read a line

            while (!toRead.eof()) {

                string::const_iterator itr = lineStr.cbegin();
                string::const_iterator end = lineStr.cend();
                
                // we can first do the name of the website/app
                print_section(itr, end, cout);
                cout.put(',');
                int countPipes = 1;

                // iterate through sections of the line stored in lineStr
                while (countPipes < 3) {
                    print_section(itr, end, cout);
                    ++countPipes;
                    cout.put(',');
                }
                print_section(itr, end, cout);
                cout.put('\n');

                getline(toRead, lineStr); // read a line

            }

        }
    } else {
        if (o_flag) {
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
    }

    toRead.close();

    return 0;
}