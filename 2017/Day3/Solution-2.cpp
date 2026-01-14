#include <iostream>
#include <fstream>
#include <map>
#include "Point2D.h"

using namespace std;

const int SECERT = 289326;


int spiral_to(int secert) {
    size_t step = 1, curr = 1;
    map<Point2D<int>, int> memo;
    Point2D<int> curr_p(0, 0), dir(1, 0);
    bool swap = false;
    
    memo[Point2D(0, 0)] = 1;

    while(true) {
        for(int i = 0; i < step; i++) {
            curr = 0;
            curr_p += dir;
            
            for(int x = curr_p.x - 1; x <= curr_p.x + 1; x++) {
                for(int y = curr_p.y - 1; y <= curr_p.y + 1; y++) {
                    curr += memo[Point2D(x, y)];
                }
            }

            if (curr > secert) {
                return curr;
            }

            memo[curr_p] = curr;
        }

        dir = dir.rotate_clockwise_90();
        if (swap) {
            step++;
        }
        swap = !swap;
    }

    return -1;
}

int main() {
    cout << endl << endl;
    auto output = spiral_to(SECERT);
    cout << "The first value higher than secert is " << output << endl;
}