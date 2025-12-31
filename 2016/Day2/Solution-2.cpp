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

int process_line(Point2D &curr, string textline) {
    stringstream ss(textline);
    char chars;

    Point2D dir;
    while(ss >> chars) {
        if (chars == 'L') {
            dir = Point2D(-1, 0);
        } else if (chars == 'R') {
            dir = Point2D(1, 0);
        } else if (chars == 'U') {
            dir = Point2D(0, -1);
        } else if (chars == 'D') {
            dir = Point2D(0, 1);
        }

        if ((curr + dir - Point2D(2, 2)).mat_distance() < 3) {
            curr += dir;
        }
    }

    string map[5] = {
        "  1  ",
        " 234 ",
        "56789",
        " ABC ",
        "  D  "
    };
    return map[curr.y][curr.x];
}


string process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    string code = "";
    Point2D curr(0, 2);

    while(getline(inputStream, textline)) {
        code += process_line(curr, textline);
    }

    return code;
}


int main() {
    auto output = process_file();
    cout << "The code is " << output << endl;
}