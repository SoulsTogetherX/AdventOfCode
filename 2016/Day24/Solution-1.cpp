#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "Point2D.h"

using namespace std;

const char WALL_ASCII = '#';
const char EMPTY_ASCII = '.';


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

void process_line(const string &textline, vector<vector<bool>> &grid, vector<Point2D<int>> &points) {
    char temp;
    int row_number = grid.size();

    vector<bool> row;
    row.reserve(textline.length());

    for(int i = 0; i < textline.size(); i++) {
        temp = textline[i];

        if (temp == WALL_ASCII) {
            row.push_back(false);
        } else if (temp == EMPTY_ASCII) {
            row.push_back(true);
        } else {
            if (temp == '0') {
                points.insert(begin(points), Point2D<int>(i, row_number));
            } else {
                points.push_back(Point2D<int>(i, row_number));
            }
            row.push_back(true);
        }
    }

    grid.push_back(row);
}

template<typename T>
void print_array2D(const vector<vector<T>> &array) {
    for(auto row : array) {
        for(auto col : row) {
            cout << col << "\t";
        }
        cout << endl;
    }
}

vector<vector<unsigned int>> get_memo(const vector<Point2D<int>> &points, const vector<vector<bool>> &grid) {
    if (points.empty() || grid.empty()) {
        return vector<vector<unsigned int>>();
    }

    auto memo = vector<vector<unsigned int>>(points.size(), vector<unsigned int>(points.size(), 0));
    unsigned int steps;

    Point2D<int> curr, check;
    Point2D<int> lower(0, 0), upper(grid[0].size(), grid.size());
    set<Point2D<int>> visited;
    vector<Point2D<int>> open, closed;

    for(int i = 0; i < points.size(); i++) {
        Point2D<int> p = points[i];

        steps = 0;
        open.clear();
        closed = {p};
        visited = {p};

        while(!closed.empty()) {
            swap(open, closed);

            while(!open.empty()) {
                curr = open.back();
                open.pop_back();

                for(int j = 0; j < points.size(); j++) {
                    if (points[j] == curr) {
                        memo[i][j] = steps;
                    }
                }

                check = curr + Point2D<int>(0, 1);
                if (check.y < upper.y && grid[check.y][check.x] && visited.count(check) == 0) {
                    visited.insert(check);
                    closed.push_back(check);
                }

                check = curr + Point2D<int>(0, -1);
                if (check.y >= lower.y && grid[check.y][check.x] && visited.count(check) == 0) {
                    visited.insert(check);
                    closed.push_back(check);
                }

                check = curr + Point2D<int>(1, 0);
                if (check.x < upper.x && grid[check.y][check.x] && visited.count(check) == 0) {
                    visited.insert(check);
                    closed.push_back(check);
                }

                check = curr + Point2D<int>(-1, 0);
                if (check.x >= lower.x && grid[check.y][check.x] && visited.count(check) == 0) {
                    visited.insert(check);
                    closed.push_back(check);
                }
            }

            steps++;
        }
    }

    return memo;
}

void brute_force_helper(
    const vector<vector<unsigned int>> &memo, 
    set<unsigned int> idxs,
    unsigned int curr_idx,
    size_t distance,
    size_t &min_distance
) {
    if (distance >= min_distance) {
        return;
    }

    idxs.erase(curr_idx);
    if (idxs.empty()) {
        min_distance = distance;
        return;
    }

    for(auto idx : idxs) {
        brute_force_helper(memo, idxs, idx, distance + memo[curr_idx][idx], min_distance);
    }
}
size_t brute_force(const vector<vector<unsigned int>> &memo) {
    set<unsigned int> idxs;
    size_t min_distance = -1;

    for(int i = 0; i < memo.size(); i++) {
        idxs.insert(i);
    }

    brute_force_helper(memo, idxs, 0, 0, min_distance);
    return min_distance;
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<vector<bool>> grid;
    vector<Point2D<int>> points;

    while(getline(inputStream, textline)) {
        process_line(textline, grid, points);
    }

    auto memo = get_memo(points, grid);
    print_array2D(memo);

    return brute_force(memo);
}


int main() {
    auto output = process_file();
    cout << "The smallest path takes " << output << " steps." << endl;
}