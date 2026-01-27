#include <iostream>
#include <fstream>
#include <map>
#include "Point2D.h"

using namespace std;


const int ACTIVITY_BURSTS = 10000;


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

int simulate_activity(map<Point2D<int>, bool>& grid, Point2D<int> curr) {
    int count = 0;
    Point2D<int> dir(0, -1);

    for(int i = 0; i < ACTIVITY_BURSTS; i++) {
        if (grid[curr]) {
            dir = dir.clockwise();
        } else {
            dir = dir.counterclockwise();
        }

        grid[curr] = !grid[curr];
        count += grid[curr];
        curr += dir;
    }

    return count;
}

void process_line(const string& textline, const int &y_pos, map<Point2D<int>, bool>& grid) {
    for(int x_pos = 0; x_pos < textline.size(); x_pos++) {
        if (textline[x_pos] == '#') {
            grid[Point2D(x_pos, y_pos)] = true;
        }
    }
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    map<Point2D<int>, bool> grid;
    int width, height = 0;

    while(getline(inputStream, textline)) {
        process_line(textline, height, grid);
        height++;
    }
    width = textline.size();

    return simulate_activity(grid, Point2D<int>(width >> 1, height >> 1));
}


int main() {
    auto output = process_file();
    cout << "The number of infected tiles is " << output << endl;
}