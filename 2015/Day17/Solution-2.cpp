#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
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

void bottom_up_helper(vector<int> cups, int fill_limit, map<int, int> &memo, int filled, int cup_idx, int depth) {
    if (fill_limit == filled) {
        memo[depth]++;
        return;
    }
    if (fill_limit < filled) {
        return;
    }

    for(int j = cup_idx + 1; j < cups.size(); j++) {
        bottom_up_helper(cups, fill_limit, memo, filled + cups[j], j, depth + 1);
    }
}
int bottom_up(int fill_limit, vector<int> cups) {
    map<int, int> memo;

    sort(cups.begin(), cups.end(), greater<int>());
    bottom_up_helper(cups, fill_limit, memo, 0, -1, 0);

    return memo.begin()->second;
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