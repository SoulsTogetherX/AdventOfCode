#include <iostream>
#include <fstream>
#include <sstream>
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

bool is_time_vaild(int t, vector<pair<int, int>> disks) {
    for (auto disk : disks) {
        if ((disk.second + t) % disk.first != 0) {
            return false;
        }
    }
    return true;
}

void process_line(string textline, vector<pair<int, int>> &disks) {
    stringstream ss(textline);
    string temp_s;
    char chars;
    int idx, positions, start;

    ss >> temp_s >> chars >> idx >> temp_s >> positions >> temp_s >> temp_s >> temp_s >> temp_s >> temp_s >> temp_s >> temp_s >> start;
    disks.push_back(pair<int, int>(positions, (start + idx) % positions));
}

size_t process_disks(vector<pair<int, int>> disks) {
    pair<int, int> max_pos_disk = *max_element(disks.begin(), disks.end(), [](pair<int, int>& d1, pair<int, int>& d2) {
        return d1.first > d2.first;
    });

    int t = max_pos_disk.first - max_pos_disk.second;
    for(int i = 0;;i++) {
        if (is_time_vaild(i, disks)) {
            return i;
        }
    }

    return -1;
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<pair<int, int>> disks;

    while(getline(inputStream, textline)) {
        process_line(textline, disks);
    }
    process_line("Disc #7 has 11 positions; at time=0, it is at position 0.", disks);

    return process_disks(disks);
}


int main() {
    auto output = process_file();
    cout << "The min time to drop the capsule is " << output << endl;
}