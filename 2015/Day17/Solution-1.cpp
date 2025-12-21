#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;


const int FILL_AMOUNT = 150;


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

int bottom_up_helper(vector<int> cups, int fill_limit, int filled, int cup_idx) {
    if (fill_limit == filled) {
        return 1;
    }
    if (fill_limit < filled) {
        return 0;
    }

    int total = 0;
    for(int j = cup_idx + 1; j < cups.size(); j++) {
        total += bottom_up_helper(cups, fill_limit, filled + cups[j], j);
    }

    return total;
}
int bottom_up(int fill_limit, vector<int> cups) {
    sort(cups.begin(), cups.end(), greater<int>());
    return bottom_up_helper(cups, fill_limit, 0, -1);
}

void process_line(string textline, vector<int> &cups) {
    stringstream ss(textline);
    int temp;

    while(ss >> temp) {
        cups.push_back(temp);
    }
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<int> cups;
    while(getline(inputStream, textline)) {
        process_line(textline, cups);
    }

    return bottom_up(FILL_AMOUNT, cups);
}


int main() {
    auto output = process_file();
    cout << "The number of combinations is " << output << endl;
}