#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const int HASH_SIZE = 256;


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

void print_hash(unsigned char (&hash)[]) {
    for(int i = 0; i < HASH_SIZE; i++) {
        cout << (unsigned int)hash[i] << " ";
    }
    cout << endl;
}

void reverse_subsection(unsigned char (&hash)[], int st, int ed) {
    int mid = (ed - st) / 2;
    int hash_len = HASH_SIZE;

    st = st % hash_len;
    ed = ed % hash_len;

    for(int i = 0; i <= mid; i++) {
        swap(hash[st], hash[ed]);

        st = (st + 1) % hash_len;
        ed = ((ed - 1) + hash_len) % hash_len;
    }
}

int process_line(const string &textline) {
    stringstream ss(textline);
    unsigned char hash[HASH_SIZE];

    int pos = 0, skip = 0, len;
    char chars;

    for(int i = 0; i < HASH_SIZE; i++) {
        hash[i] = i;
    }

    while(ss >> len) {
        reverse_subsection(hash, pos, pos + len - 1);
        pos = (pos + skip + len) % HASH_SIZE;

        ss >> chars;
        skip++;
    }

    return hash[0] * hash[1];
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
    cout << "The multiplication of the first two elements is " << output << endl;
}