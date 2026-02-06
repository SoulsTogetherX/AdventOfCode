#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "Point2D.h"

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

void process_line(const string& textline, map<Point2D<int>, int>& points) {
    stringstream ss(textline);
    string temp_s;
    char temp_c;
    int x, y, width, height;

    ss >> temp_s >> temp_s >> x >> temp_c >> y >> temp_c >> width >> temp_c >> height;

    for(int r = y; r < y + height; r++) {
        for(int c = x; c < x + width; c++) {
            points[Point2D<int>(c, r)] += 1;
        }
    }
}

size_t count_overlaps(const map<Point2D<int>, int>& points) {
    size_t ret = 0;

    for(auto it = points.begin(); it != points.end(); ++it) {
        ret += (it->second >= 2);
    }

    return ret;
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    map<Point2D<int>, int> points;
    while(getline(inputStream, textline)) {
        process_line(textline, points);
    }
    return count_overlaps(points);
}


int main() {
    auto output = process_file();
    cout << "The amount of overlapping fabric is " << output << endl;
}