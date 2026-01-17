#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

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

void process_line(const string &textline, map<string, int> &registers) {
    stringstream ss(textline);
    string name_1, name_2, operation, compair;
    int number_1, number_2;

    ss >> name_1 >> operation >> number_1 >> name_2 >> name_2 >> compair >> number_2;

    if (compair == "<") {
        if (registers[name_2] >= number_2) {
            return;
        }
    } else if (compair == "<=") {
        if (registers[name_2] > number_2) {
            return;
        }
    } else if (compair == ">") {
        if (registers[name_2] <= number_2) {
            return;
        }
    } else if (compair == ">=") {
        if (registers[name_2] < number_2) {
            return;
        }
    } else if (compair == "==") {
        if (registers[name_2] != number_2) {
            return;
        }
    } else if (compair == "!=") {
        if (registers[name_2] == number_2) {
            return;
        }
    }

    if (operation == "inc") {
        registers[name_1] += number_1;
    } else if (operation == "dec") {
        registers[name_1] -= number_1;
    }
}

void largest_register_value(const map<string, int> &registers, int &largest_val) {
    for(auto it : registers) {
        if (largest_val < it.second) {
            largest_val = it.second;
        }
    }
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    int largest_val = 0;
    map<string, int> registers;

    while(getline(inputStream, textline)) {
        process_line(textline, registers);
        largest_register_value(registers, largest_val);
    }

    return largest_val;
}


int main() {
    auto output = process_file();
    cout << "The largest register value is " << output << endl;
}