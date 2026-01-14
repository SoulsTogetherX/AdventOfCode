#include <iostream>
#include <fstream>
#include <sstream>
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

bool process_line(const string &textline) {
    stringstream ss(textline);
    vector<string> strs;
    string temp_s;

    while(ss >> temp_s) {
        sort(begin(temp_s), end(temp_s));
        strs.push_back(temp_s);
    }

    sort(begin(strs), end(strs));
    for(int i = 1; i < strs.size(); i++) {
        if (strs[i - 1] == strs[i]) {
            return false;
        }
    }

    return true;
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
    cout << "The number vaild passphrases is " << output << endl;
}