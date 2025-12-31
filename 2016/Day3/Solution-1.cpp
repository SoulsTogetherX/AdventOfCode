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

bool is_triangle_possible(int s1, int s2, int s3) {
    return s1 + s2 > s3 && s1 + s3 > s2 && s2 + s3 > s1;
}

bool process_line(string textline) {
    stringstream ss(textline);
    int s1, s2, s3;

    ss >> s1 >> s2 >> s3;

    return is_triangle_possible(s1, s2, s3);
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    size_t sum = 0;

    while(getline(inputStream, textline)) {
        sum += process_line(textline);
    }

    return sum;
}


int main() {
    auto output = process_file();
    cout << "The number of possible triangles is " << output << endl;
}