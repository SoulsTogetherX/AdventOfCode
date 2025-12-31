#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


class Point2D{
    public:
        long x, y;

        Point2D() : x(0), y(0) {};
        Point2D(long x, long y) : x(x), y(y) {};

        Point2D abs() {
            x = std::abs(x);
            y = std::abs(y);

            return *this;
        }
        long dot(const Point2D p) const {
            return x * p.x + y * p.y;
        }
        long mat_distance() const {
            return std::abs(x) + std::abs(y);
        }


        Point2D operator * (const long factor) const {
            return Point2D(x * factor, y * factor);
        }
        Point2D operator *= (const long factor) {
            x *= factor;
            y *= factor;

            return *this;
        }

        Point2D operator / (const long factor) const {
            return Point2D(x / factor, y / factor);
        }
        Point2D operator /= (const long factor) {
            x /= factor;
            y /= factor;

            return *this;
        }

        Point2D operator + (const Point2D& p) const {
            return Point2D(x + p.x, y + p.y);
        }
        Point2D operator += (const Point2D& p) {
            x += p.x;
            y += p.y;

            return *this;
        }

        Point2D operator - (const Point2D& p) const {
            return Point2D(x - p.x, y - p.y);
        }
        Point2D operator -= (const Point2D& p) {
            x -= p.x;
            y -= p.y;

            return *this;
        }

        bool operator == (const Point2D& p) const {
            return x == p.x && y == p.y;
        }
        bool operator != (const Point2D& p) const {
            return x != p.x || y != p.y;
        }

        bool operator < (const Point2D& p) const {
            return x < p.x || (x == p.x && y < p.y);
        }
        bool operator <= (const Point2D& p) const {
            return x < p.x || (x == p.x && y <= p.y);
        }

        bool operator > (const Point2D& p) const {
            return x >= p.x && (x != p.x || y > p.y);
        }
        bool operator >= (const Point2D& p) const {
            return x >= p.x || (x != p.x || y >= p.y);
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
    stringstream ss(textline);
    char chars;
    int steps;

    Point2D dir(0, 1), curr(0, 0);

    while(ss >> chars) {
        ss >> steps;

        if (chars == 'R') {
            swap(dir.x, dir.y);
            dir.x *= -1;
        } else if (chars == 'L') {
            swap(dir.x, dir.y);
            dir.y *= -1;
        }

        curr += dir * steps;

        ss >> chars;
    }

    return curr.mat_distance();
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
    cout << "The number of blocks away the HQ is " << output << endl;
}