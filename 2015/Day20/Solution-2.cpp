#include <iostream>

using namespace std;

const int TARGET = 29000000;
const int MAX_BATCH = 1000;
const int MAX_HOUSES = 50;
const int HOUSE_MUL = 11;


// NOTE: DOES NOT WORK ON SMALLER VALUES
int sieve_helper(int target, int min, int max) {
    if (max < min) {
        swap(max, min);
    }

    int length = max - min;
    int memo[length];

    for(int i = 0; i < length; i++) {
        memo[i] = HOUSE_MUL * ((i + min) < MAX_HOUSES);
    }

    for(int i = 2; i <= max; i++) {
        int j = i - (min % i) - 1;
        int h = (min + j) / i;

        while(j < length && h < MAX_HOUSES) {
            memo[j] += i * HOUSE_MUL;
            if (memo[j] >= target) {
                return j + min + 1;
            }

            j += i;
            h++;
        }
    }

    return -1;
}
int sieve(int target) {
    int ret;

    for(int i = 0;; i++) {
        ret = sieve_helper(target, i * MAX_BATCH, (i + 1) * MAX_BATCH);

        if (ret != -1) {
            return ret;
        }
    }
    return -1;
}

int main() {
    cout << " " << endl;

    auto output = sieve(TARGET);
    cout << "The lowest house number is " << output << endl;
}