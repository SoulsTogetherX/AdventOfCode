#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

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

size_t simulate(vector<int> jumps) {
    size_t steps = 0;
    int pos = 0, jump;

    while(0 <= pos && pos < jumps.size()) {
        steps++;
        jump = jumps[pos];

        if (jump >= 3) {
            jumps[pos]--;
        } else {
            jumps[pos]++;
        }

        pos += jump;
    }

    return steps;
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<int> jumps;
    while(getline(inputStream, textline)) {
        jumps.push_back(stoi(textline));
    }

    return simulate(jumps);
}


int main() {
    auto output = process_file();
    cout << "The number of steps needed to exit is " << output << endl;
}