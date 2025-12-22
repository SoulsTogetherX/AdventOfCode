#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

enum STATE {
    OFF = 0b00,
    ON = 0b01,
    NEXT_ON = 0b10
};


const int BOARD_SIDE_LEN = 100;
const int STEPS = 100;


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


void animate_board(vector<vector<unsigned char>> &board) {
    int lit;

    for(int r = 0; r < BOARD_SIDE_LEN; r++) {
        for(int c = 0; c < BOARD_SIDE_LEN; c++) {
            lit = 0;
            for(int r2 = r - 1; r2 <= r + 1; r2++) {
                if (r2 < 0) continue;
                if (r2 >= BOARD_SIDE_LEN) continue;

                for(int c2 = c - 1; c2 <= c + 1; c2++) {
                    if (c2 < 0) continue;
                    if (c2 >= BOARD_SIDE_LEN) continue;
                    
                    lit += (board[r2][c2] & ON);
                }
            }

            if (board[r][c] & ON) {
                if (lit == 3 || lit == 4) {
                    board[r][c] |= NEXT_ON;
                }
            } else {
                if (lit == 3) {
                    board[r][c] |= NEXT_ON;
                }
            }
        }
    }

    for(int r = 0; r < BOARD_SIDE_LEN; r++) {
        for(int c = 0; c < BOARD_SIDE_LEN; c++) {
            board[r][c] >>= 1;
        }
    }
}
int print_board(vector<vector<unsigned char>> board) {
    int count = 0;

    for(int r = 0; r < BOARD_SIDE_LEN; r++) {
        for(int c = 0; c < BOARD_SIDE_LEN; c++) {
            cout << ((board[r][c] & ON) ? '#' : '.');
        }
        cout << endl;
    }

    return 0;
}
int count_board(vector<vector<unsigned char>> board) {
    int count = 0;

    for(int r = 0; r < BOARD_SIDE_LEN; r++) {
        for(int c = 0; c < BOARD_SIDE_LEN; c++) {
            count += (board[r][c] & ON);
        }
    }

    return count;
}

void process_line(string textline, vector<vector<unsigned char>> &board) {
    vector<unsigned char> line(BOARD_SIDE_LEN, 0);

    for(int i = 0; i < BOARD_SIDE_LEN; i++) {
        if (textline[i] == '#') {
            line[i] = ON;
        }
    }

    board.push_back(line);
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<vector<unsigned char>> board;
    while(getline(inputStream, textline)) {
        process_line(textline, board);
    }

    for(int i = 0; i < STEPS; i++) {
        animate_board(board);
    }
    print_board(board);
    return count_board(board);
}


int main() {
    auto output = process_file();
    cout << "The number of lit lights is " << output << endl;
}