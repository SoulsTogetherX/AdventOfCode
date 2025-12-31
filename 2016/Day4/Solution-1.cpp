#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
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

bool is_digit(char digit) {
    return '0' <= digit && digit <= '9';
}
bool sort_pair(const pair<char, int>& a, const pair<char, int>& b) {
    return a.second > b.second || (a.second == b.second && a.first < b.first);
}

int process_line(string textline) {
    stringstream ss(textline);
    map<char, int> memo;
    int temp_i, idx;
    char chars;

    while(!is_digit(ss.peek())) {
        ss >> chars;
        if (chars != '-') {
            memo[chars]++;
        }
    }

    ss >> temp_i >> chars >> chars;

    vector<pair<char, int>> vec(memo.begin(), memo.end());
    sort(vec.begin(), vec.end(), sort_pair);

    idx = 0;
    while(chars != ']') {
        if (vec[idx].first != chars) {
            return 0;
        }
        ss >> chars;
        idx++;
    }

    return temp_i;
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    size_t sum = 0;

    while(getline(inputStream, textline)) {
        sum += process_line(textline);
    }

    return sum;
}


int main() {
    auto output = process_file();
    cout << "The sum of vaild sector IDs is " << output << endl;
}