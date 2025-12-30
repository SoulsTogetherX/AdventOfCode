#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const size_t FIRST = 20151125;
const size_t MUL = 252533;
const size_t DIV = 33554393;


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

size_t gen_step(size_t seed) {
    return (seed * MUL) % DIV;
}
size_t process_line(string textline) {
    stringstream ss(textline);
    string temp_s;
    size_t row, col;

    ss >> temp_s >> temp_s >> temp_s >> temp_s >> temp_s >> temp_s >> temp_s >> temp_s >> temp_s >> temp_s >> temp_s >> temp_s >> temp_s >> temp_s >> temp_s >> row >> temp_s >> temp_s >> col;

    size_t num = ((row + col - 1) * (row + col) - 2 * (row - 1)) / 2;
    size_t seed = FIRST;

    for(size_t i = 1; i < num; i++) {
        seed = gen_step(seed);
    }
    return seed;
}


size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    getline(inputStream, textline);
    return process_line(textline);
}


int main() {
    auto output = process_file();
    cout << "The code is " << output << endl;
}