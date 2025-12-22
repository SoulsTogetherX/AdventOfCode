#include <iostream>

using namespace std;

const int TARGET = 29000000;
const int MAX_BATCH = 1000;


// NOTE: DOES NOT WORK ON SMALLER VALUES
int sieve_helper(int target, int min, int max) {
    if (max < min) {
        swap(max, min);
    }

    int length = max - min;
    int memo[length];

    for(int i = 0; i < length; i++) {
        memo[i] = 1;
    }

    for(int i = 2; i <= max; i++) {
        int j = i - (min % i) - 1;

        while(j < length) {
            memo[j] += i;
            if (memo[j] >= target) {
                return j + min + 1;
            }

            j += i;
        }
    }

    return -1;
}
int sieve(int target) {
    int ret;

    target /= 10;
    for(int i = 0;; i++) {
        ret = sieve_helper(target, i * MAX_BATCH, (i + 1) * MAX_BATCH);

        if (ret != -1) {
            return ret;
        }
    }
    return -1;
}

int main() {
    auto output = sieve(TARGET);
    cout << "The lowest house number is " << output << endl;
}