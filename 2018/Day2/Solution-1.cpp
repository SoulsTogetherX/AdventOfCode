#include <iostream>
#include <fstream>
#include <vector>
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

void process_line(const string& textline, int& double_c, int& triple_c) {
    map<char, int> memo;
    bool found_double, found_triple;

    for(char c : textline) {
        memo[c]++;
    }

    for(auto it = memo.begin(); it != memo.end(); it++) {
        found_double |= (it->second == 2);
        found_triple |= (it->second == 3);
    }

    double_c += found_double;
    triple_c += found_triple;
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    int double_c = 0, triple_c = 0;
    while(getline(inputStream, textline)) {
        process_line(textline, double_c, triple_c);
    }
    return double_c * triple_c;
}


int main() {
    auto output = process_file();
    cout << "The checksum is " << output << endl;
}