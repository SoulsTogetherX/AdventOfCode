#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int RACE_SECONDS = 2503;


struct RainDeer {
    int vs, vl, rd;

    RainDeer(int vs, int vl, int rd) : vs(vs), vl(vl), rd(rd) {}

    int get_speed(int second) {
        if ((second % (vl + rd)) < vl) {
            return vs;
        }
        return 0;
    }
};


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

size_t simulate_deer(vector<RainDeer> deers) {
    vector<int> distances(deers.size(), 0), points(deers.size(), 0);
    int max_index, max_temp;

    for(int i = 0; i < RACE_SECONDS; i++) {
        max_index = -1;
        max_temp = -1;

        for(int j = 0; j < deers.size(); j++) {
            distances[j] += deers[j].get_speed(i);

            if (max_temp < distances[j]) {
                max_index = j;
                max_temp = distances[j];
            }
        }

        points[max_index] += 1;
    }

    sort(points.begin(), points.end());
    return points.back();
}

void process_line(string textline, vector<RainDeer> &deers) {
    int vs, vl, rd;
    string temp;

    stringstream ss(textline);

    ss >> temp >> temp >> temp >> vs >> temp >> temp >> vl >> temp >> temp >> temp >> temp >> temp >> temp >> rd;

    deers.push_back(RainDeer(vs, vl, rd));
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<RainDeer> deers;
    while(getline(inputStream, textline)) {
        process_line(textline, deers);
    }
    return simulate_deer(deers);
}


int main() {
    auto output = process_file();
    cout << "The points of the winning reindeer is " << output << endl;
}