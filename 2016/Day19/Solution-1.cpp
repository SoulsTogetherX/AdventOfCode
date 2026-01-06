#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


const int SECERT = 3012210;


size_t sieve_elfs(int elf_num) {
    size_t st = 0, curr = 0, skip = 2;

    while(skip < elf_num) {
        while(curr < elf_num) {
            curr += skip;
        }
        if (curr - elf_num > st) {
            st += skip;
        }
        skip <<= 1;

        curr = st;
    }

    return curr + 1;
}


int main() {
    cout << " " << endl;

    auto output = sieve_elfs(SECERT);
    cout << "The elf with all the presents is " << output << endl;
}