#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


struct coordinate {
    int x, y;

    coordinate(int x_pos, int y_pos) {
        x = x_pos;
        y = y_pos;
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

void process_line(vector<string> &grid, vector<coordinate> &coordinates, string textline) {
    const char search_char = 'X';
    int y_pos = grid.size();
    grid.push_back(textline);

    size_t x_pos = textline.find(search_char, 0);
    while (x_pos != std::string::npos) {
        coordinates.push_back(coordinate(x_pos, y_pos));
        x_pos = textline.find(search_char, x_pos + 1);
    }
}

void process_matches(vector<string> grid, coordinate coord, size_t &sum) {
    if (grid.empty()) return;

    const char pattern[] = "XMAS";
    const int pattern_length = 4;

    bool word_found;
    int max_x = grid[0].length(), max_y = grid.size();
    int x, y;

    for(int y_inc = -1; y_inc <= 1; y_inc++) {
        for(int x_inc = -1; x_inc <= 1; x_inc++) {
            if (y_inc == 0 && x_inc == 0) continue;

            word_found = true;
            x = coord.x;
            y = coord.y;
            for(int idx = 1; idx < pattern_length; idx++) {
                x += x_inc;
                y += y_inc;

                if (x < 0 || y < 0 || x >= max_x || y >= max_y || pattern[idx] != grid[y][x]) {
                    word_found = false;
                    break;
                }
            }

            sum += word_found;
            //cout << sum << " : " << word_found << " (" << coord.x << ", " << coord.y << ")" << " (" << x_inc << ", " << y_inc << ")" << endl;
        }
    }
}

void process_grid(vector<string> grid, vector<coordinate> coordinates, size_t &sum) {
    for(auto coord = coordinates.begin(); coord != coordinates.end(); coord++) {
        process_matches(grid, *coord, sum);
    }
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    size_t sum = 0;
    vector<string> grid;
    vector<coordinate> coordinates;

    while(getline(inputStream, textline)) {
        process_line(grid, coordinates, textline);
    }
    process_grid(grid, coordinates, sum);

    return sum;
}


int main() {
    auto output = process_file();
    cout << "The number of times 'XMAS' appears is " << output << endl;
}