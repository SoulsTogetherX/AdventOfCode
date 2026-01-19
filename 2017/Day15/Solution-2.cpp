#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

#define ll long long

const ll GEN_A_FACTOR = 16807;
const ll GEN_B_FACTOR = 48271;
const ll DIV_FACTOR = 2147483647;

const ll PAIRS = 5000000;
const ll mask = 0b1111111111111111;
const ll mask_8 = 0b111;
const ll mask_4 = 0b11;


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

void generate(ll &val, const ll &mul_fac, const ll &div_fac) {
    val = (val * mul_fac) % div_fac;
}
int simulate(ll A_val, ll B_val) {
    int matches = 0;

    for(int i = 0; i < PAIRS; i++) {
        do {
            generate(A_val, GEN_A_FACTOR, DIV_FACTOR);
        } while (A_val & mask_4);
        do {
            generate(B_val, GEN_B_FACTOR, DIV_FACTOR);
        } while (B_val & mask_8);

        if (((A_val ^ B_val) & mask) == 0) {
            matches++;
        }
    }

    return matches;
}

void process_line(const string &textline, ll &val) {
    stringstream ss(textline);
    string temp_s;
    ss >> temp_s >> temp_s >> temp_s >> temp_s >> val;
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    ll A_start, B_start;
    getline(inputStream, textline);
    process_line(textline, A_start);
    getline(inputStream, textline);
    process_line(textline, B_start);

    return simulate(A_start, B_start);
}


int main() {
    auto output = process_file();
    cout << "The judges final count is " << output << endl;
}