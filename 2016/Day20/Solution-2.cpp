#include <iostream>
#include <fstream>
#include <sstream>
#include "IntervalMap.h"

using namespace std;

const size_t POSSIBLE_IP_COUNT = 4294967296;


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

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    auto im = IntervalMap<size_t>();
    while(getline(inputStream, textline)) {
        process_line(textline, im);
    }

    size_t ips = 0;
    auto ranges = im.get_ranges();
    for(auto r : im.get_ranges()) {
        ips += r.size();
    }
    return ips;
}


int main() {
    auto output = process_file();
    cout << "The number of blocked IPs is " << output << endl;
    cout << "The number of allowed IPs is " << POSSIBLE_IP_COUNT - output << endl;
}