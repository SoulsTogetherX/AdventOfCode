#include <iostream>
#include <fstream>
#include <algorithm>


using namespace std;


const int FILL_LENGTH = 35651584;
const string SECERT = "01110110101001000";


void convert_bit(string &secert) {
    for(int i = 0; i < secert.size(); i++) {
        secert[i] -= '0';
    }
}
void string_bit(string &secert) {
    for(int i = 0; i < secert.size(); i++) {
       secert[i] += '0';
    }
}

void flip_bit(string &secert) {
    for(int i = 0; i < secert.size(); i++) {
        secert[i] ^= 0b1;
    }
}

void get_data(string &a, int fill_len) {
    a.reserve(fill_len);

    while(a.length() < FILL_LENGTH) {
        string b = a;
        reverse(b.begin(), b.end());
        flip_bit(b);

        a.push_back('\0');
        a += b;
    }

    a.resize(fill_len);
}
void get_checksum(string &data) {
    int len = data.length();

    do {
        for(int i = 0; i < len; i += 2) {
            data[i / 2] = data[i] == data[i + 1];
        }
        len /= 2;
    } while(len % 2 == 0);

    data.resize(len);
}
string process_input(string data, int fill_len) {
    convert_bit(data);
    get_data(data, fill_len);
    get_checksum(data);
    string_bit(data);
    return data;
}


int main() {
    cout << " " << endl;

    auto output = process_input(SECERT, FILL_LENGTH);
    cout << "The checksum is " << output << endl;
}