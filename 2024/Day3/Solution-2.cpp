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


void parse_mul(string line, int &sum, bool &enabled) {
    if (!enabled) return;

    stringstream ss(line);
    char chars;
    int a, b;
    
    ss >> chars >> chars >> chars;
    ss >> chars;

    ss >> a;

    ss >> chars;

    ss >> b;
    
    sum +=  a * b;
}
void parse_do_or_dont(string line, bool &enabled) {
    enabled = (line.length() <= 4);
}
void parse_match(string line, int &sum, bool &enabled) {
    if (line[0] == 'm') {
        parse_mul(line, sum, enabled);
        return;
    }
    parse_do_or_dont(line, enabled);
}

void process_line(string line, int &sum, bool &enabled) {
    regex pattern("(mul\\((([1-9][0-9]*)|0),(([1-9][0-9]*)|0)\\))|(do\\(\\))|(don't\\(\\))");
    sregex_iterator begin(line.begin(), line.end(), pattern);
    sregex_iterator end;

    for (sregex_iterator i = begin; i != end; ++i) {
        smatch match = *i;
        parse_match(match.str(), sum, enabled);
        cout << match.str() << " : " << sum << " : " << enabled << endl;
    }
}

int process_file() {
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    string line;
    bool enabled = true;
    int sum = 0;

    while(getline(inputStream, line)) {
        process_line(line, sum, enabled);
    }

    return sum;
}


int main() {
    auto output = process_file();
    cout << "The sum of all multiplications is " << output << endl;
}