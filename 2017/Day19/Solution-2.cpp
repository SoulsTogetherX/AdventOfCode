#include <iostream>
#include <fstream>
#include <vector>
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


int process_path(const vector<string> &path) {
    if (path.empty()) {
        return 0;
    }

    Point2D<int> curr, dir(0, 1);
    Point2D<int> lower(0, 0), upper(path[0].size(), path.size());
    int ret = 1;
    char temp;

    for(int i = 0; i < upper.x; i++) {
        if (path[0][i] == '|') {
            curr.x = i;
            break;
        }
    }

    while(true) {
        curr += dir;
        
        if (!curr.has_lower_bound(lower) || !curr.has_supremum(upper)) {
            break;
        }

        temp = path[curr.y][curr.x];
        if (temp == ' ') {
            break;
        }

        ret++;
        if (temp == '-' || temp == '|') {
            continue;
        }
        if (temp == '+') {
            if (dir.x == 0) {
                if (curr.x <= 0 || path[curr.y][curr.x - 1] == ' ') {
                    dir = Point2D(1, 0);
                    continue;
                }
                dir = Point2D(-1, 0);
            } else {
                if (curr.y <= 0 || path[curr.y - 1][curr.x] == ' ') {
                    dir = Point2D(0, 1);
                    continue;
                }
                dir = Point2D(0, -1);
            }
            continue;
        }
    }

    return ret;
}

int process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<string> path;
    while(getline(inputStream, textline)) {
        path.push_back(textline);
    }

    return process_path(path);
}

int main() {
    auto output = process_file();
    cout << "The number of steps needed is " << output << endl;
}