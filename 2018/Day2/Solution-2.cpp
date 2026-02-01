#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

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

bool check_difference(const string& s1, const string& s2) {
    bool difference = false;

    for (auto it1 = s1.begin(), it2 = s2.begin(); it1 != s1.end() && it2 != s2.end(); ++it1, ++it2) {
        if (*it1 != *it2) {
            if (difference) {
                return false;
            }
            difference = true;
        }
    }
    return difference;
}

string simulate(vector<string> serials) {
    string s1, s2;

    for(int i = 0; i < serials.size(); i++) {
        s1 = serials[i];
        for(int j = i + 1; j < serials.size(); j++) {
            s2 = serials[j];

            if (check_difference(s1, s2)) {
                s2.erase(mismatch(s2.begin(), s2.end(), s1.begin()).first);
                return s2;
            }
        }
    }
    return "";
}

string process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<string> serials;
    while(getline(inputStream, textline)) {
        serials.push_back(textline);
    }
    return simulate(serials);
}


int main() {
    auto output = process_file();
    cout << "The common letters are " << output << endl;
}