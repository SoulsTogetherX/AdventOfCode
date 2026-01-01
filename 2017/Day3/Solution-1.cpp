#include <iostream>
#include <fstream>

using namespace std;

const int SECERT = 289326;

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

        Point2D rotate_clockwise() {
            swap(x, y);
            y *= -1;
            return *this;
        }
        Point2D rotate_counterclockwise() {
            swap(x, y);
            x *= -1;

            return *this;
        }
        Point2D rotate_180() {
            x *= -1;
            y *= -1;

            return *this;
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


int spiral_to(int secert) {
    size_t step = 1, curr = 1;
    Point2D curr_p(0, 0), dir(1, 0);
    bool swap = false;
    
    while(secert > curr + step) {
        curr += step;
        curr_p += dir * step;
        dir.rotate_clockwise();

        if (swap) {
            step++;
        }
        swap = !swap;
    }

    curr_p += dir * (secert - curr);

    return curr_p.mat_distance();
}

int main() {
    auto output = spiral_to(SECERT);
    cout << "The Manhattan Distance is " << output << endl;
}