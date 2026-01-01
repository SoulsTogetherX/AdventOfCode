#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>

using namespace std;

const int PIXEL_WIDTH = 6;
const int SCREEN_WIDTH = 50;
const int SCREEN_HEIGHT = 6;


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

void print_screen(bitset<SCREEN_WIDTH> screen[SCREEN_HEIGHT]) {
    for(int i = 0; i < SCREEN_HEIGHT; i++) {
        cout << screen[i] << endl;
    }
}
void print_code(bitset<SCREEN_WIDTH> screen[SCREEN_HEIGHT]) {
    for(int r = 0; r < SCREEN_HEIGHT; r++) {
        for(int c = 0; c < SCREEN_WIDTH; c++) {
            if (c % PIXEL_WIDTH == 0) {
                cout << " ";
            }
            cout << (screen[r][SCREEN_WIDTH - c - 1] ? '#' : ' ');
        }
        cout << endl;
    }
}
int count_lit(bitset<SCREEN_WIDTH> screen[SCREEN_HEIGHT]) {
    int lit = 0;

    for(int i = 0; i < SCREEN_HEIGHT; i++) {
        lit += screen[i].count();
    }

    return lit;
}

void process_line(string textline, bitset<SCREEN_WIDTH> (&screen)[SCREEN_HEIGHT]) {
    stringstream ss(textline);
    string temp_s;
    char temp_c;
    int A, B;

    ss >> temp_s;
    if (temp_s == "rect") {
        // rect AxB
        ss >> A >> temp_c >> B;
        B = min(B, SCREEN_HEIGHT);

        bitset<SCREEN_WIDTH> temp;
        temp.set();
        temp >>= A;
        temp.flip();

        for(int i = 0; i < B; i++) {
            screen[i] |= temp;
        }
    } else {
        ss >> temp_s;
        if (temp_s == "row") {
            // rotate row y=A by B
            ss >> temp_c >> temp_c >> A >> temp_s >> B;

            B %= SCREEN_WIDTH;
            screen[A] = (screen[A] >> B) | (screen[A] << (SCREEN_WIDTH - B));
        } else {
            // rotate column x=A by B
            ss >> temp_c >> temp_c >> A >> temp_s >> B;
            A = SCREEN_WIDTH - A - 1;

            bitset<SCREEN_HEIGHT> temp;
            for(int i = 0; i < SCREEN_HEIGHT; i++) {
                temp.set(i, screen[i][A]);
            }

            temp = (temp << B) | (temp >> (SCREEN_HEIGHT - B));

            for(int i = 0; i < SCREEN_HEIGHT; i++) {
                screen[i][A] = temp[i];
            }
        }
    }
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    bitset<SCREEN_WIDTH> screen[SCREEN_HEIGHT] = {0};

    print_screen(screen);
    cout << endl;
    
    while(getline(inputStream, textline)) {
        process_line(textline, screen);

        cout << textline << endl;
        print_screen(screen);
        cout << endl;
    }

    print_code(screen);
    return count_lit(screen);
}


int main() {
    auto output = process_file();
    cout << "The number of lit lights is " << output << endl;
}