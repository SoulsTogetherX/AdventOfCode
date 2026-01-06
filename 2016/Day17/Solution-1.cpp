#include <iostream>
#include <format>
#include <iomanip>
#include <sstream>
#include <set>

#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

using namespace std;


enum DIRECTIONS {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3
};


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


const string SECERT = "pxxbnzuo";

const Point2D START = Point2D(1, 1);
const Point2D END = Point2D(4, 4);
const Point2D LOWER_BOUND = Point2D(1, 1);
const Point2D UPPER_BOUND = Point2D(4, 4);



void MD5(const char *input, unsigned char md_value[EVP_MAX_MD_SIZE], unsigned int &md_len) {
    EVP_MD_CTX *mdctx;

    mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        perror("EVP_MD_CTX_new error");
        return;
    }
    if (EVP_DigestInit_ex(mdctx, EVP_md5(), NULL) != 1) {
        perror("EVP_DigestInit_ex error");
        EVP_MD_CTX_free(mdctx);
        return;
    }
    if (EVP_DigestUpdate(mdctx, input, strlen(input)) != 1) {
        perror("EVP_DigestUpdate error");
        EVP_MD_CTX_free(mdctx);
        return;
    }
    if (EVP_DigestFinal_ex(mdctx, md_value, &md_len) != 1) {
        perror("EVP_DigestFinal_ex error");
        EVP_MD_CTX_free(mdctx);
        return;
    }

    EVP_MD_CTX_free(mdctx);
}

string format_hex_padded(unsigned int value) {
    ostringstream oss;
    oss << hex << setw(2) << setfill('0') << value;
    return oss.str();
}
string convert_to_hex(unsigned char md_value[EVP_MAX_MD_SIZE], unsigned int md_len) {
    string ret;

    for(int i = 0; i < md_len; i++) {
        ret += format_hex_padded(md_value[i]);
    }

    return ret;
}

unsigned char md_value[EVP_MAX_MD_SIZE];
unsigned int md_len;
void get_MD5(string &secert) {
    MD5(secert.c_str(), md_value, md_len);
    secert = convert_to_hex(md_value, md_len);
}

bool is_door_open(char door) {
    return door > 'a';
}
bool in_bounds(Point2D curr) {
    return LOWER_BOUND.x <= curr.x && curr.x <= UPPER_BOUND.x && LOWER_BOUND.y <= curr.y && curr.y <= UPPER_BOUND.y;
}

void find_path_recusive(Point2D curr, string path, string &best_path, unsigned int distance, unsigned int &min_distance) {
    if (distance >= min_distance) {
        return;
    }
    if (curr == END) {
        best_path = path;
        min_distance = distance;
        return;
    }
    distance += 1;

    Point2D next;
    string md5 = path;
    get_MD5(md5);
    
    next = curr + Point2D(0, -1);
    if (in_bounds(next) && is_door_open(md5[UP])) {
        find_path_recusive(next, path + "U", best_path, distance, min_distance);
    }
    next = curr + Point2D(0, 1);
    if (in_bounds(next) && is_door_open(md5[DOWN])) {
        find_path_recusive(next, path + "D", best_path, distance, min_distance);
    }
    next = curr + Point2D(-1, 0);
    if (in_bounds(next) && is_door_open(md5[LEFT])) {
        find_path_recusive(next, path + "L", best_path, distance, min_distance);
    }
    next = curr + Point2D(1, 0);
    if (in_bounds(next) && is_door_open(md5[RIGHT])) {
        find_path_recusive(next, path + "R", best_path, distance, min_distance);
    }
}

string find_shortest_path() {
    string best_path = SECERT;
    unsigned int min_distance = -1;

    find_path_recusive(START, SECERT, best_path, 0, min_distance);
    return best_path.substr(SECERT.length());
}

int main() {
    cout << " " << endl;

    auto output = find_shortest_path();
    cout << "The shortest path is " << output << endl;
}