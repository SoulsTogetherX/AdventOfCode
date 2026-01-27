#include <iostream>
#include <fstream>
#include <map>
#include "Point2D.h"

using namespace std;

enum TILE_STATE {
    CLEAN = 0b00,
    WEAKENED = 0b01,
    INFECTED = 0b10,
    FLAGGED = 0b11
};

const int ACTIVITY_BURSTS = 10000000;


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

int simulate_activity(map<Point2D<int>, TILE_STATE>& grid, Point2D<int> curr) {
    int count = 0;
    Point2D<int> dir(0, -1);

    for(int i = 0; i < ACTIVITY_BURSTS; i++) {
        switch(grid[curr]) {
            case CLEAN:
                dir = dir.counterclockwise();
                grid[curr] = WEAKENED;
            break;
            case WEAKENED:
                grid[curr] = INFECTED;
                count += 1;
            break;
            case INFECTED:
                dir = dir.clockwise();
                grid[curr] = FLAGGED;
            break;
            case FLAGGED:
                dir = dir.flip();
                grid.erase(curr);
            break;
        }
        curr += dir;
    }

    return count;
}

void process_line(const string& textline, const int &y_pos, map<Point2D<int>, TILE_STATE>& grid) {
    for(int x_pos = 0; x_pos < textline.size(); x_pos++) {
        if (textline[x_pos] == '#') {
            grid[Point2D(x_pos, y_pos)] = INFECTED;
        }
    }
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    map<Point2D<int>, TILE_STATE> grid;
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