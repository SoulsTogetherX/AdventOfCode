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

int process_line(const string &textline) {
    stringstream ss(textline);
    int depth, range;
    char chars; 
    
    ss >> depth >> chars >> range;

    if (depth % ((range - 1) << 1) == 0) {
        return depth * range;
    }
    return 0;
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    size_t total_severity = 0;
    while(getline(inputStream, textline)) {
       total_severity += process_line(textline);
    }
    return total_severity;
}


int main() {
    auto output = process_file();
    cout << "The total severity is " << output << endl;
}