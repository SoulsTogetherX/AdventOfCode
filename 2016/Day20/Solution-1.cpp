#include <iostream>
#include <fstream>
#include <sstream>
#include "IntervalMap.h"

using namespace std;


const string FILE_NAME = "input.txt";
ifstream open_file(string filename) {
    ifstream inputStream;

    cout << endl;

    inputStream.open(filename);
    if (inputStream.fail()) {
        cout << "Failed to open file '" << filename << "'." << endl;
        exit(1);
    }
    if (!inputStream.is_open()) {
        cout << "File '" << filename << "' didn't open." << endl;
        exit(1);
    }

    cout << "File '" << filename << "' opened successfully." << endl;

    return inputStream;
}

void process_line(string textline, IntervalMap<size_t>& im) {
    stringstream ss(textline);
    size_t st, ed;
    char chars;

    ss >> st >> chars >> ed;

    im.insert_range(Range<size_t>(st, ed + 1));
}

long process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    auto im = IntervalMap<size_t>();
    while(getline(inputStream, textline)) {
        process_line(textline, im);
    }

    for(auto r : im.get_ranges()) {
        cout << r << endl;
    }
    cout << endl << endl << endl;

    if (im.lower_bound() <= 0) {
        return im.get_ranges()[0].get_upper();
    }
    return 0;
}


int main() {
    auto output = process_file();
    cout << "The lowest-valued IP is " << output << endl;
}