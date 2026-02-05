#include <iostream>
#include <fstream>
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

int shrink_sequence(string sequence) {
    if (sequence.empty()) {
        return 0;
    }

    string new_sequence;
    int diff = 'A' - 'a';
    char temp;
    
    while(true) {
        new_sequence.clear();
        new_sequence.reserve(sequence.size());

        new_sequence.push_back(sequence[0]);
        for(int i = 1; i < sequence.size(); i++) {
            temp = sequence[i];

            if (!new_sequence.empty() && (new_sequence.back() == temp - diff || new_sequence.back() == temp + diff)) {
                new_sequence.pop_back();
                continue;
            }
            new_sequence.push_back(temp);
        }

        if (new_sequence.size() == sequence.size()) {
            break;
        }
        swap(new_sequence, sequence);
    }

    return sequence.size();
}


size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    getline(inputStream, textline);
    return shrink_sequence(textline);
}


int main() {
    auto output = process_file();
    cout << "The number of remaining units is " << output << endl;
}