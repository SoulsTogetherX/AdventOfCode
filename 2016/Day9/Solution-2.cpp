#include <iostream>
#include <fstream>
#include <sstream>
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


size_t decompress_length(string textline) {
    stringstream ss(textline);
    regex reg("\\(([1-9][0-9]*|0)x([1-9][0-9]*|0)\\)");
    size_t A, B, length = 0;
    char chars;

    auto it = sregex_iterator(textline.begin(), textline.end(), reg);
    auto it_end = sregex_iterator();

    for(size_t i = 0; i < textline.size(); i++) {
        ss >> chars;
        if (it != it_end && i == it->position()) {
            ss >> A >> chars >> B;
            
            i = static_cast<size_t>(ss.tellg());
            length += B * decompress_length(textline.substr(i + 1, A));

            i += A;
            ss.seekg(i + 1);

            while(it != it_end && i >= it->position()) {
                it++;
            }
        } else {
            length++;
        }
    }

    return length;
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    getline(inputStream, textline);
    return decompress_length(textline);
}


int main() {
    auto output = process_file();
    cout << "The length of the decrypted message is " << output << endl;
}