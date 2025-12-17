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

size_t parse_line(string textline) {
    stringstream ss(textline);
    size_t l, w, h, ret;
    char chars;

    ss >> l >> chars >> w >> chars >> h >> chars;

    ret = (l*w*h);

    if (l > w) {
        swap(l, w);
    }
    if (w > h) {
        swap(w, h);
    }

    return ret + ((l + w) << 1);
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    size_t sum = 0;
    while(getline(inputStream, textline)) {
        sum += parse_line(textline);
    }

    return sum;
}


int main() {
    auto output = process_file();
    cout << "The amount of wrapping paper needed is " << output << endl;
}