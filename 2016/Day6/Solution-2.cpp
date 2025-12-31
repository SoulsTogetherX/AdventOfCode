#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

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

bool sort_pair(const pair<char, int>& a, const pair<char, int>& b) {
    return a.second < b.second;
}
string get_code(const vector<map<char, int>> memo) {
    string ret;

    for(auto m : memo) {
        vector<pair<char, int>> vec(m.begin(), m.end());

        ret.push_back(min_element(vec.begin(), vec.end(), sort_pair)->first);
    }
    return ret;
}

void process_line(string textline, vector<map<char, int>> &memo) {
    memo.resize(max(memo.size(), textline.size()));

    for(int i = 0; i < textline.length(); i++) {
        memo[i][textline[i]]++;
    }
}

string process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<map<char, int>> memo;
    while(getline(inputStream, textline)) {
        process_line(textline, memo);
    }
    return get_code(memo);
}


int main() {
    auto output = process_file();
    cout << "The corrected message is " << output << endl;
}