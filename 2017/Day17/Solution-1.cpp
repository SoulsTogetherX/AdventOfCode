#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int ROUNDS = 2018;
const int SECERT = 376;


size_t simulate() {
    vector<int> buffer = {0};
    buffer.reserve(ROUNDS);

    int pos = 0;
    for(int i = 1; i < ROUNDS; i++) {
        pos = (pos + SECERT) % i + 1;
        buffer.insert(begin(buffer) + pos, i);
    }
    
    return buffer[(pos + 1) % buffer.size()];
}

int main() {
    auto output = simulate();
    cout << "The value after 2017 is " << output << endl;
}