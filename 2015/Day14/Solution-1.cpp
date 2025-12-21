#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int RACE_SECONDS = 2503;


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

size_t cal_distance_from_sec(int vs, int vl, int rd, int s) {
    int repeat_distance = vl + rd;
    int extra_sec = s % repeat_distance;
    int persistent_distance = ceil((double)(s - vl) / (double)(rd + vl));
    bool count_extra = (((s - 1) % repeat_distance) - vl) < 0;

    return (extra_sec * count_extra + vl * persistent_distance) * vs;
}


void process_line(string textline, vector<size_t> &distances) {
    int vs, vl, rd;
    string temp;

    stringstream ss(textline);

    ss >> temp >> temp >> temp >> vs >> temp >> temp >> vl >> temp >> temp >> temp >> temp >> temp >> temp >> rd;

    distances.push_back(cal_distance_from_sec(vs, vl, rd, RACE_SECONDS));
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<size_t> distances;
    while(getline(inputStream, textline)) {
        process_line(textline, distances);
    }

    sort(distances.begin(), distances.end());

    return distances.back();
}


int main() {
    auto output = process_file();
    cout << "The distance of the winning reindeer is " << output << endl;
}