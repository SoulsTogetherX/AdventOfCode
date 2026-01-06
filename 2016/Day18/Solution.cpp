#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int STEP_NUMBER = 400000;


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

void process_row(const string &textline, vector<bool> &row) {
    row.reserve(textline.length());

    for(char c : textline) {
        row.push_back(c != '^');
    }
}
void print_row(const vector<bool> &row) {
    for(bool safe : row) {
        cout << (safe ? '.' : '^');
    }
    cout << endl;
}

void step_forward(vector<bool> &row) {
    bool left, right;
    vector<bool> copy = row;

    for(int i = 0; i < copy.size(); i++) {
        left = (i == 0) || copy[i - 1];
        right = (i == copy.size() - 1) || copy[i + 1];

        row[i] = (left == right);
    }
}
int count_safe(const vector<bool> &row) {
    int ret = 0;

    for(bool safe : row) {
        ret += safe;
    }

    return ret;
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<bool> row;
    int count = 0;

    getline(inputStream, textline);
    process_row(textline, row);
    
    for(int i = 0; i < STEP_NUMBER; i++) {
        //print_row(row);
        count += count_safe(row);
        step_forward(row);
    }

    return count;
}


int main() {
    auto output = process_file();
    cout << "The number of safe tiles is " << output << endl;
}