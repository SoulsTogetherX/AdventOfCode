#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


struct Scanner {
    int depth, range;

    Scanner(int depth, int range) : depth(depth), range(range) {}

    bool detected_at_offset(int offset) {
        return (depth + offset) % ((range - 1) << 1) == 0;
    }
};


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

int simulate(const vector<Scanner> &scanners) {
    int min_time = 0;
    bool vaild;

    while(true) {
        vaild = true;
        for(auto scanner : scanners) {
            if (scanner.detected_at_offset(min_time)) {
                vaild = false;
                break;
            }
        }

        if (vaild) {
            break;
        }
        min_time++;
    }
    return min_time;
}

void process_line(const string &textline, vector<Scanner> &scanners) {
    stringstream ss(textline);
    int depth, range;
    char chars; 
    
    ss >> depth >> chars >> range;
    scanners.push_back(Scanner(depth, range));
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<Scanner> scanners;
    while(getline(inputStream, textline)) {
        process_line(textline, scanners);
    }

    return simulate(scanners);
}


int main() {
    auto output = process_file();
    cout << "The min delay needed is " << output << endl;
}