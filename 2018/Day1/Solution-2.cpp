#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

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


void process_line(const string& textline, vector<int>& frequencies) {
    stringstream ss(textline);
    int num;
    ss >> num;
    frequencies.push_back(num);
}

int find_duplicate(const vector<int>& frequencies) {
    set<int> memo = {0};
    int curr = 0, idx = 0;

    while(true) {
        curr += frequencies[idx];
        if (memo.count(curr) != 0) {
            return curr;
        }
        memo.insert(curr);
        idx = (idx + 1) % frequencies.size();
    }
}


long process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<int> frequencies;
    while(getline(inputStream, textline)) {
        process_line(textline, frequencies);
    }
    return find_duplicate(frequencies);
}


int main() {
    auto output = process_file();
    cout << "The first duplicate frequency is " << output << endl;
}