#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

class Point2D{
    public:
        long x, y;

        Point2D() : x(0), y(0) {};
        Point2D(long x, long y) : x(x), y(y) {};

        string to_string() {
            return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
        }

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


const int FAV_NUMBER = 1350;
const int TARGET = 50;


bool is_wall(Point2D coord) {
    size_t temp = coord.x*coord.x + 3*coord.x + 2*coord.x*coord.y + coord.y + coord.y*coord.y;
    temp += FAV_NUMBER;

    int bit_count = 0;
    while(temp) {
        bit_count += (temp & 0b1);
        temp >>= 1;
    }

    return bit_count % 2;
}

void print_layout(Point2D p1, Point2D p2) {
    if (p1.x > p2.x) {
        swap(p1.x, p2.x);
    }
    if (p1.y > p2.y) {
        swap(p1.y, p2.y);
    }

    for(int r = p1.y; r <= p2.y; r++) {
        for(int c = p1.x; c <= p2.x; c++) {
            if (is_wall(Point2D(c, r))) {
                cout << "#";
                continue;
            }
            cout << ".";
        }
        cout << endl;
    }
}

size_t unique_tiles(int target_steps) {
    set<Point2D> memo;
    vector<Point2D> visiting, next;
    Point2D curr;
    size_t step = 0;

    next.push_back(Point2D(1, 1));

    while(!next.empty()) {
        swap(next, visiting);
        next.clear();
        
        for(auto v : visiting) {
            curr = v + Point2D(1, 0);
            if (!memo.count(curr)) {
                if (!is_wall(curr)) {
                    next.push_back(curr);
                    memo.insert(curr);
                }
            }

            curr = v + Point2D(-1, 0);
            if (!memo.count(curr) && curr.x >= 0) {
                if (!is_wall(curr)) {
                    next.push_back(curr);
                    memo.insert(curr);
                }
            }
            
            curr = v + Point2D(0, 1);
            if (!memo.count(curr)) {
                if (!is_wall(curr)) {
                    next.push_back(curr);
                    memo.insert(curr);
                }
            }
            
            curr = v + Point2D(0, -1);
            if (!memo.count(curr) && curr.y >= 0) {
                if (!is_wall(curr)) {
                    next.push_back(curr);
                    memo.insert(curr);
                }
            }
        }

        step++;
        if (target_steps == step) {
            break;
        }
    }

    return memo.size();
}

int main() {
    cout << " " << endl;
    
    auto output = unique_tiles(TARGET);
    cout << "The number of unique tiles in 50 steps is " << output << endl;
}