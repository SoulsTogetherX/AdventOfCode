#include <iostream>
#include <fstream>
#include <sstream>

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


long process_line(const string& textline) {
    stringstream ss(textline);
    long num;

    ss >> num;
    return num;
}


long process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    long sum = 0;
    while(getline(inputStream, textline)) {
        sum += process_line(textline);
    }
    return sum;
}


int main() {
    auto output = process_file();
    cout << "The frequency is " << output << endl;
}