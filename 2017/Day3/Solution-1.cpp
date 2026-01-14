#include <iostream>
#include <fstream>
#include "Point2D.h"

using namespace std;

const int SECERT = 289326;


int spiral_to(int secert) {
    size_t step = 1, curr = 1;
    Point2D<int> curr_p(0, 0), dir(1, 0);
    bool swap = false;
    
    while(secert > curr + step) {
        curr += step;
        curr_p += dir * step;
        dir.rotate_clockwise_90();

        if (swap) {
            step++;
        }
        swap = !swap;
    }

    curr_p += dir * (secert - curr);

    return curr_p.manhattan_distance();
}

int main() {
    auto output = spiral_to(SECERT);
    cout << "The Manhattan Distance is " << output << endl;
}