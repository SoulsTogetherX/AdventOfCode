#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

const int ROUNDS = 64;
const int DIV_LENGTH = 16;
const int HASH_SIZE = 256;

const int ROW_NUMBER = 128;
const int COL_NUMBER = 128;
const string SECERT = "uugsqrei";


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

string knot_hash(string lengths) {
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

int count_used_in_hex(const string &hex_str) {
    map<char, int> used = {
        {'0', 0}, //0b0000
        {'1', 1}, //0b0001
        {'2', 1}, //0b0010
        {'3', 2}, //0b0011
        {'4', 1}, //0b0100
        {'5', 2}, //0b0101
        {'6', 2}, //0b0110
        {'7', 3}, //0b0111
        {'8', 1}, //0b1000
        {'9', 2}, //0b1001
        {'a', 2}, //0b1010
        {'b', 3}, //0b1011
        {'c', 2}, //0b1100
        {'d', 3}, //0b1101
        {'e', 3}, //0b1110
        {'f', 4}  //0b1111
    };

    int used_amount = 0;
    for(char c : knot_hash(hex_str)) {
        used_amount += used[c];
    }
    return used_amount;
}

int process_secert() {
    int used_amount = 0;
    for(int i = 0; i < ROW_NUMBER; i++) {
        used_amount += count_used_in_hex(SECERT + "-" + to_string(i));
    }
    return used_amount;
}

int main() {
    auto output = process_secert();
    cout << "The number of used squares is " << output << endl;
}