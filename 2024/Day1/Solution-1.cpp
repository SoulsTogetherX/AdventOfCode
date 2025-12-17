#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

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


int process_file() {
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<int> v1, v2;
    int buffer;

    while(inputStream.peek() != EOF) {
        inputStream >> buffer;
        v1.push_back(buffer);

        inputStream >> buffer;
        v2.push_back(buffer);
    }

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    int difference = 0;
    for (auto i = v1.begin(), j = v2.begin(); i != v1.end() && j != v2.end(); i++, j++) {
        difference += abs(*i - *j);
    }

    return difference;
}


int main() {
    auto output = process_file();
    cout << "The sum of differences is " << output << endl;
}