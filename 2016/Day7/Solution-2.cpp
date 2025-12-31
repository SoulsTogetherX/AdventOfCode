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


bool process_line(string textline) {
    regex reg("((^|\\])\\w*(\\w)(?!\\3)(\\w)\\3(\\w|\\[\\w*\\])*\\[\\w*\\4\\3\\4)|(\\[\\w*(\\w)(?!\\7)(\\w)\\7\\w*\\](\\w|\\[\\w*\\])*\\8\\7\\8)");

    return regex_search(textline, reg);
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
    cout << "The number of IPs is " << output << endl;
}