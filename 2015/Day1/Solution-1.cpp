#include <iostream>
#include <fstream>

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


int process_floor(string textline) {
    int floor = 0;
    for(char c : textline) {
        floor += (c == '(') - (c == ')');
    }
    return floor;
}

int process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    getline(inputStream, textline);
    return process_floor(textline);
}


int main() {
    auto output = process_file();
    cout << "The exit floor is " << output << endl;
}