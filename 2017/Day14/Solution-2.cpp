#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <bitset>
#include "Point2D.h"


using namespace std;


const int ROUNDS = 64;
const int DIV_LENGTH = 16;
const int HASH_SIZE = 256;

const int ROW_NUMBER = 128;
const int COL_NUMBER = 128;
const string SECERT = "uugsqrei";


string format_hex_padded(const string& input) {
    stringstream ss;
    ss << hex;
    
    for (char c : input) {
        ss << setw(2) << setfill('0') << static_cast<unsigned int>(static_cast<unsigned char>(c));
    }
    
    return ss.str();
}

void reverse_subsection(unsigned char (&hash)[], int st, int ed) {
    int mid = (ed - st) / 2;
    int hash_len = HASH_SIZE;

    st = st % hash_len;
    ed = ed % hash_len;

    for(int i = 0; i <= mid; i++) {
        swap(hash[st], hash[ed]);

        st = (st + 1) % hash_len;
        ed = ((ed - 1) + hash_len) % hash_len;
    }
}

string knot_hash(string lengths) {
    string ret;
    int pos = 0, skip = 0;
    unsigned char hash[HASH_SIZE];
    char chars;

    ret.resize(HASH_SIZE / DIV_LENGTH);
    lengths.push_back(17);
    lengths.push_back(31);
    lengths.push_back(73);
    lengths.push_back(47);
    lengths.push_back(23);

    for(int i = 0; i < HASH_SIZE; i++) {
        hash[i] = i;
    }

    for(int i = 0; i < ROUNDS; i++){
        for(unsigned int len : lengths) {
            reverse_subsection(hash, pos, pos + len - 1);
            pos = (pos + skip + len) % HASH_SIZE;

            skip++;
        }
    }

    for(int i = 0; i < HASH_SIZE; i++) {
        ret[i / DIV_LENGTH] ^= hash[i];
    }
    return format_hex_padded(ret);
}

bitset<COL_NUMBER> get_row_bits(const string &hex_str) {
    map<char, int> used = {
        {'0', 0}, //0b0000
        {'1', 1}, //0b0001
        {'2', 2}, //0b0010
        {'3', 3}, //0b0011
        {'4', 4}, //0b0100
        {'5', 5}, //0b0101
        {'6', 6}, //0b0110
        {'7', 7}, //0b0111
        {'8', 8}, //0b1000
        {'9', 9}, //0b1001
        {'a', 10}, //0b1010
        {'b', 11}, //0b1011
        {'c', 12}, //0b1100
        {'d', 13}, //0b1101
        {'e', 14}, //0b1110
        {'f', 15}  //0b1111
    };

    bitset<COL_NUMBER> ret;
    for(char c : knot_hash(hex_str)) {
        ret <<= 4;
        ret |= used[c];
    }
    return ret;
}

void clear_region(vector<bitset<COL_NUMBER>> &grid, const Point2D<> &start) {
    if (grid.empty()) {
        return;
    }

    vector<Point2D<>> open = {start};
    Point2D<> curr;
    
    while(!open.empty()) {
        curr = open.back();
        open.pop_back();

        if (grid[curr.y][curr.x] != 1) {
            continue;
        }

        grid[curr.y][curr.x] = 0;

        if (curr.x + 1 < grid[0].size()) {
            open.push_back(curr + Point2D<>(1, 0));
        }
        if (curr.x - 1 >= 0) {
            open.push_back(curr + Point2D<>(-1, 0));
        }
        if (curr.y + 1 < grid.size()) {
            open.push_back(curr + Point2D<>(0, 1));
        }
        if (curr.y - 1 >= 0) {
            open.push_back(curr + Point2D<>(0, -1));
        }
    }
}
int count_regions(vector<bitset<COL_NUMBER>> grid) {
    int region_count = 0;

    for(int r = 0; r < ROW_NUMBER; r++) {
        for(int c = 0; c < COL_NUMBER; c++) {
            if (grid[r][c]) {
                region_count++;
                clear_region(grid, Point2D(c, r));
            }
        }
    }

    return region_count;
}

int process_secert() {
    vector<bitset<COL_NUMBER>> grid;
    grid.reserve(ROW_NUMBER);

    for(int i = 0; i < ROW_NUMBER; i++) {
        grid.push_back(get_row_bits(SECERT + "-" + to_string(i)));
    }

    return count_regions(grid);
}

int main() {
    auto output = process_secert();
    cout << "The number regions is " << output << endl;
}