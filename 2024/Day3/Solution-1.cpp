#include <iostream>
#include <fstream>
#include <regex>

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


int parse_mul(string num) {
    stringstream ss(num);
    char chars;
    int a, b;
    
    ss >> chars >> chars >> chars;
    ss >> chars;

    ss >> a;

    ss >> chars;

    ss >> b;
    
    return a * b;
}

int process_line(string line) {
    regex pattern("mul\\((([1-9][0-9]*)|0),(([1-9][0-9]*)|0)\\)");
    sregex_iterator begin(line.begin(), line.end(), pattern);
    sregex_iterator end;

    int sum = 0;
    for (sregex_iterator i = begin; i != end; ++i) {
        smatch match = *i;
        sum += parse_mul(match.str());
    }
    return sum;
}

int process_file() {
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    string textline;
    int sum = 0;

    while(getline(inputStream, textline)) {
        sum += process_line(textline);
    }

    return sum;
}


int main() {
    auto output = process_file();
    cout << "The sum of all multiplications is " << output << endl;
}