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

size_t process_string(string textline) {
    regex reg("(\\\\\\\\)|(\\\\\")|(\\\\x[0-9a-fA-F]{2})");
    return textline.size() - (regex_replace(textline, reg, ".").size() - 2);
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    size_t sum = 0;
    while(getline(inputStream, textline)) {
        sum += process_string(textline);
    }
    return sum;
}


int main() {
    auto output = process_file();
    cout << "The number of times 'XMAS' appears is " << output << endl;
}