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

int process_lines(string line1, string line2, string line3) {
    stringstream ss1(line1), ss2(line2), ss3(line3);
    int s1, s2, s3, count = 0;

    for(int i = 0; i < 3; i++) {
        ss1 >> s1;
        ss2 >> s2;
        ss3 >> s3;

        count += is_triangle_possible(s1, s2, s3);
    }

    return count;
}

size_t process_file() {
    string line1, line2, line3;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    size_t sum = 0;

    while(getline(inputStream, line1)) {
        getline(inputStream, line2);
        getline(inputStream, line3);

        sum += process_lines(line1, line2, line3);
    }

    return sum;
}


int main() {
    auto output = process_file();
    cout << "The number of possible triangles is " << output << endl;
}