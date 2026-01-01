#include <iostream>
#include <fstream>

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

size_t process_line(string textline) {
    int sum = 0;

    if (textline.back() == textline.front()) {
        sum += textline.back() - '0';
    }
    for(int i = 1; i < textline.length(); i++) {
        if (textline[i - 1] == textline[i]) {
            sum += textline[i] - '0';
        }
    }

    return sum;
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
    cout << "The captcha's solution is " << output << endl;
}