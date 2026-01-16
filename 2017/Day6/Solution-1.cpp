#include <iostream>
#include <fstream>
#include <sstream>
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

void process_line(const string &textline, vector<int> &blocks) {
    stringstream ss(textline);
    int temp_i;

    while(ss >> temp_i) {
        blocks.push_back(temp_i);
    }
}

bool check_memory(const vector<vector<int>> &memory, const vector<int> &blocks) {
    bool check;

    for(vector<int> m_blocks : memory) {
        check = true;
        for(int i = 0; i < m_blocks.size(); i++) {
            if (m_blocks[i] != blocks[i]) {
                check = false;
                break;
            }
        }

        if (check) {
            return true;
        }
    }

    return false;
}
int index_of_largest(const vector<int> &blocks) {
    if (blocks.empty()) {
        return 0;
    }

    int max_val = blocks[0], max_idx = 0;

    for(int i = 1; i < blocks.size(); i++) {
        if (max_val < blocks[i]) {
            max_idx = i;
            max_val = blocks[i];
        }
    }

    return max_idx;
}
void distribute_blocks(const int &idx, vector<int> &blocks) {
    if (blocks.empty()) {
        return;
    }

    int remainding = blocks[idx] % blocks.size();
    int dividing = blocks[idx] / blocks.size();

    blocks[idx] = 0;
    for(int i = idx + 1; i <= blocks.size() + idx; i++) {
        blocks[i % blocks.size()] += dividing;

        if (remainding > 0) {
            blocks[i % blocks.size()]++;
            remainding--;
        }
    }
}

int simulate(vector<int> blocks) {
    vector<vector<int>> memory;
    int steps = 0;

    memory.push_back(blocks);
    while (true) {
        steps++;
        distribute_blocks(index_of_largest(blocks), blocks);
        if (check_memory(memory, blocks)) {
            return steps;
        }
        memory.push_back(blocks);
    }
}


int process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<int> blocks;

    getline(inputStream, textline);
    process_line(textline, blocks);

    return simulate(blocks);
}


int main() {
    auto output = process_file();
    cout << "The number of cycles before repeat is " << output << endl;
}