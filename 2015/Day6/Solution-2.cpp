#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


const int BOARD_SIZE = 1000;

class Point2D{
    public:
        long x, y;

        Point2D() {};
        Point2D(long x, long y) : x(x), y(y) {};

        string to_string() {
            return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
        }

        bool operator < (const Point2D& p) const {
            return x < p.x ||(x == p.x && y < p.y);
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

void zero_board(unsigned char board[BOARD_SIZE][BOARD_SIZE]) {
    for(int r = 0; r < BOARD_SIZE; r++) {
        for(int c = 0; c < BOARD_SIZE; c++) {
            board[r][c] = 0;
        }
    }
}
void parse_line(string textline, char &op, Point2D &st, Point2D &ed) {
    stringstream ss(textline);
    string temp_s;
    char temp_c;

    ss >> temp_s;
    if (temp_s == "toggle") {
        op = '^';
    } else {
        ss >> temp_s;
        if (temp_s == "on") {
            op = '|';
        } else {
            op = '&';
        }
    }

    ss >> st.x >> temp_c >> st.y >> temp_s >> ed.x >> temp_c >> ed.y;

    if (st.x > ed.x) {
        swap(st.x, ed.x);
    }
    if (st.y > ed.y) {
        swap(st.y, ed.y);
    }
}
void process_line(string textline, unsigned char board[BOARD_SIZE][BOARD_SIZE]) {
    Point2D st, ed;
    char delta;
    char op;
    
    parse_line(textline, op, st, ed);

    if (op == '^') {
        delta = 2;
    } else if (op == '|') {
        delta = 1;
    } else if (op == '&') {
        delta = -1;
    }

    for(int r = st.y; r <= ed.y; r++) {
        for(int c = st.x; c <= ed.x; c++) {
            if (board[r][c] == 0 && delta < 0) {
                continue;
            }

            board[r][c] += delta;
        }
    }
}
long count_bits(unsigned char board[BOARD_SIZE][BOARD_SIZE]) {
    long count = 0;

    for(int r = 0; r < BOARD_SIZE; r++) {
        for(int c = 0; c < BOARD_SIZE; c++) {
            count += board[r][c];
        }
    }

    return count;
}


long process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    unsigned char board[BOARD_SIZE][BOARD_SIZE];
    zero_board(board);

    while(getline(inputStream, textline)) {
        process_line(textline, board);
    }
    return count_bits(board);
}


int main() {
    auto output = process_file();
    cout << "The number of lit lights is " << output << endl;
}