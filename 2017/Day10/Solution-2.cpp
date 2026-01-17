#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

const int ROUNDS = 64;
const int DIV_LENGTH = 16;
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

string format_hex_padded(const string& input) {
    stringstream ss;
    ss << hex;
    
    for (char c : input) {
        ss << setw(2) << setfill('0') << static_cast<unsigned int>(static_cast<unsigned char>(c));
    }
    
    return ss.str();
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

string process_line(string lengths) {
    string ret;
    int pos = 0, skip = 0;
    unsigned char hash[HASH_SIZE];
    char chars;

    ret.resize(HASH_SIZE / DIV_LENGTH);
    lengths.push_back(17);
    lengths.push_back(31);
    lengths.push_back(73);
    lengths.push_back(47);
    lengths.push_back(23);

    for(int i = 0; i < HASH_SIZE; i++) {
        hash[i] = i;
    }

    for(int i = 0; i < ROUNDS; i++){
        for(unsigned int len : lengths) {
            reverse_subsection(hash, pos, pos + len - 1);
            pos = (pos + skip + len) % HASH_SIZE;

            skip++;
        }
    }

    for(int i = 0; i < HASH_SIZE; i++) {
        ret[i / DIV_LENGTH] ^= hash[i];
    }
    return format_hex_padded(ret);
}

string process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<unsigned char> lengths;

    getline(inputStream, textline);
    return process_line(textline);
}


int main() {
    auto output = process_file();
    cout << "The dense hash is " << output << endl;
}