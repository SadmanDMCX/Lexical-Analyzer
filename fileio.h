#include <iostream>
#include <fstream>

using namespace std;

namespace fileio {

    class FileIO {
    public:
        string ReadFile() {
            string fileName = "input.txt";
            string line = "", totalLine = "";

            fstream infile;
            infile.open(fileName.c_str(), ios::in);

            while (!infile.eof()) {
                getline(infile, line);
                totalLine += line + "\n";
            }

            infile.close();
            return totalLine;
        }
        void WriteFile(string data) {
            string filename = "output.txt";

            fstream outfile;
            outfile.open(filename.c_str(), ios::out);
            outfile << data;
            outfile.close();
        }
    } fio;

}

