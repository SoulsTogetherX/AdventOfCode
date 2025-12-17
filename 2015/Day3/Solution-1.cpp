#include <iostream>
#include <fstream>
#include <set>

using namespace std;


class Point2D{
    public:
        long x, y;

        Point2D(long x, long y) : x(x), y(y) {};

        bool operator < (const Point2D& p) const {
            return x < p.x ||(x == p.x && y < p.y);
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

size_t process_line(string textline) {
    Point2D curr(0, 0);
    set<Point2D> visited;

    visited.insert(curr);
    for(char c : textline) {
        curr.x += (c == '>') - (c == '<');
        curr.y += (c == '^') - (c == 'v');
        visited.insert(curr);
    }

    return visited.size();
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    getline(inputStream, textline);
    return process_line(textline);
}


int main() {
    auto output = process_file();
    cout << "The number of houses Santa visited is " << output << endl;
}