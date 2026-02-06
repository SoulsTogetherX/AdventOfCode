#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Rectangle.h"

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

void process_line(const string& textline, vector<Rectangle<int>>& rectangles) {
    stringstream ss(textline);
    string temp_s;
    char temp_c;
    int x, y, width, height;

    ss >> temp_s >> temp_s >> x >> temp_c >> y >> temp_c >> width >> temp_c >> height;

    rectangles.push_back(Rectangle(x, y, width, height));
}

int get_non_overlapping_id(const vector<Rectangle<int>>& rectangles) {
    bool overlap;
    
    for(int i = 0; i < rectangles.size(); i++) {
        overlap = false;
        for(int j = 0; j < rectangles.size(); j++) {
            if (j == i) continue;

            overlap = rectangles[i].intersects(rectangles[j]);
            if (overlap) {
                break;
            }
        }
        
        if (!overlap) {
            return i + 1;
        }
    }

    return -1;
}


size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<Rectangle<int>> rectangles;

    while(getline(inputStream, textline)) {
        process_line(textline, rectangles);
    }

    return get_non_overlapping_id(rectangles);
}


int main() {
    auto output = process_file();
    cout << "The non-overlaping id is " << output << endl;
}