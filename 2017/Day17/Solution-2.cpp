#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int ROUNDS = 50000000;
const int SECERT = 376;


size_t simulate() {
    int pos = 0, ret;
    for(int i = 1; i < ROUNDS; i++) {
        pos = (pos + SECERT) % i + 1;
        if (pos == 1) {
            ret = i;
        }
    }
    return ret;
}

int main() {
    auto output = simulate();
    cout << "The value after 2017 is " << output << endl;
}