#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "Point3D.h"

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
size_t process_file() {
    string dir;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    map<string, Point3D<>> directions = {
        {"n", Point3D<>(1, -1, 0)},
        {"ne", Point3D<>(1, 0, -1)},
        {"nw", Point3D<>(0, -1, 1)},
        {"s", Point3D<>(-1, 1, 0)},
        {"se", Point3D<>(0, 1, -1)},
        {"sw", Point3D<>(-1, 0, 1)}
    };
    Point3D<> pt;
    int temp, max_distance = 0;

    while(getline(inputStream, dir, ',')) {
        pt += directions[dir];

        temp = pt.manhattan_distance() >> 1;
        if (temp > max_distance) {
            max_distance = temp;
        }
    }

    return max_distance;
}


int main() {
    auto output = process_file();
    cout << "The farthest distance is " << output << endl;
}