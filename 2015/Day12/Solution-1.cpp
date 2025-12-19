#include <iostream>
#include <fstream>
#include <sstream>
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

size_t parse_input(string textline) {
    size_t sum = 0;
    size_t current;

    textline = regex_replace(textline, regex("[^-0-9]+"), " ");

    stringstream ss(textline);
    while(ss >> current) {
        sum += current;
    }
    return sum;
}


size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    getline(inputStream, textline);
    return parse_input(textline);
}


int main() {
    auto output = process_file();
    cout << "The sum of all appearing numbers is " << output << endl;
}