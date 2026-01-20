#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

const int program_number = 'p' - 'a' + 1;


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

string create_program_line(const int &program_count) {
    string ret;
    ret.reserve(program_count);

    for(int i = 0; i < program_count; i++) {
        ret.push_back('a' + i);
    }
    return ret;
}

void process_line(const string &textline, string &programs) {
    stringstream ss(textline);
    char temp_c1, temp_c2;
    int temp_i1, temp_i2;

    while(ss >> temp_c1) {
        switch(temp_c1) {
            case 's':
                ss >> temp_i1 >> temp_c1;
                rotate(programs.begin(), programs.begin() + (programs.size() - temp_i1), programs.end());
            break;
            case 'x':
                ss >> temp_i1 >> temp_c1 >> temp_i2 >> temp_c1;
                swap(programs[temp_i1], programs[temp_i2]);
            break;
            case 'p':
                ss >> temp_c1 >> temp_c2 >> temp_c2;
            
                iter_swap(find(begin(programs), end(programs), temp_c1), find(begin(programs), end(programs), temp_c2));
                ss >> temp_c1;
            break;
        }
    }
}

string process_file() {
    string instuctions;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    string programs = create_program_line(program_number);
    while(getline(inputStream, instuctions)) {
        process_line(instuctions, programs);
    }
    return programs;
}


int main() {
    auto output = process_file();
    cout << "When finished, the programs look like " << output << endl;
}