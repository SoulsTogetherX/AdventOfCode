#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

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


int process_file() {
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<int> vec;
    unordered_map<int, int> map;
    int buffer;

    while(inputStream.peek() != EOF) {
        inputStream >> buffer;
        vec.push_back(buffer);

        inputStream >> buffer;
        map.insert_or_assign(buffer, map[buffer] + 1);
    }

    int similarity = 0;
    for (auto i = vec.begin(); i != vec.end(); i++) {
        similarity += *i * map[*i];
    }

    return similarity;
}



int main() {
    auto output = process_file();
    cout << "The sum of similarity score is " << output << endl;
}