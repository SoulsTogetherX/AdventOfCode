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
    const char search_char = 'A';
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

    bool match_found;
    char top_left, top_right, bottom_left, bottom_right;
    int max_x = grid[0].length(), max_y = grid.size();
    int x, y;

    x = coord.x;
    y = coord.y;
    if (x <= 0 || y <= 0 || x >= max_x - 1 || y >= max_y - 1) {
        return;
    }

    top_left = grid[y - 1][x - 1];
    bottom_right = grid[y + 1][x + 1];

    top_right = grid[y - 1][x + 1];
    bottom_left = grid[y + 1][x - 1];

    match_found = (top_left == 'S' && bottom_right == 'M') || (top_left == 'M' && bottom_right == 'S');
    match_found &= (top_right == 'S' && bottom_left == 'M') || (top_right == 'M' && bottom_left == 'S');

    //cout << match_found << " (" << x << ", " << y << ") " << top_left << " " << bottom_right << " " << top_right << " " << bottom_left << endl;

    sum += match_found;
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