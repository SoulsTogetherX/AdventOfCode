#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const int MAX_LEVEL_GAP = 3;


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

vector<int> get_line_values(string line) {
    stringstream ss(line);
    vector<int> vec;
    int buffer;

    while (ss >> buffer) {
        vec.push_back(buffer);
    }

    return vec;
}

bool is_ascending(vector<int> vec) {
    int prev = *vec.begin();
    for (auto i = vec.begin() + 1; i != vec.end(); i++) {
        if (prev >= *i) {
            return false;
        }
        prev = *i;
    }

    return true;
}
bool is_decending(vector<int> vec) {
    int prev = *vec.begin();
    for (auto i = vec.begin() + 1; i != vec.end(); i++) {
        if (prev <= *i) {
            return false;
        }
        prev = *i;
    }

    return true;
}
bool distance_check(vector<int> vec) {
    int prev = *vec.begin();
    for (auto i = vec.begin() + 1; i != vec.end(); i++) {
        if (abs(prev - *i) > MAX_LEVEL_GAP) {
            return false;
        }
        prev = *i;
    }

    return true;
}

bool process_line(string line) {
    vector<int> vec = get_line_values(line);
    if (!(is_ascending(vec) || is_decending(vec))) {
        return false;
    }
    return distance_check(vec);
}

int process_file() {
    string textline;
    ifstream inputStream;
    int safe_reports = 0;

    inputStream = open_file(FILE_NAME);
    
    while(getline(inputStream, textline)) {
        safe_reports += process_line(textline);
        cout << textline << " : " << process_line(textline) << endl;
    }

    return safe_reports;
}


int main() {
    auto output = process_file();
    cout << "The number of safe reports is " << output << endl;
}