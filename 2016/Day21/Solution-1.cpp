#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;


const string START_PASSWORD = "bdgheacf";


enum INSTRUCTION_TYPE {
    SWAP_P,
    SWAP_L,
    ROTATE_R,
    ROTATE_L,
    ROTATE_P,
    REVERSE,
    MOVE
};

struct Instruction {
    INSTRUCTION_TYPE type;
    int v1, v2;

    void on_run(string &curr_string) {
        switch (type) {
            case SWAP_P:
                swap(curr_string[v1], curr_string[v2]);
                break;
            case SWAP_L:
                for(int i = 0; i < curr_string.size(); i++) {
                    if (curr_string[i] == v1) {
                        curr_string[i] = v2;
                    } else if (curr_string[i] == v2) {
                        curr_string[i] = v1;
                    }
                }
                break;
            case ROTATE_L: {
                size_t rotate_count = v1 % curr_string.length();
                curr_string = curr_string.substr(rotate_count) + curr_string.substr(0, rotate_count);
            }
                break;
            case ROTATE_R: {
                size_t rotate_count = v1 % curr_string.length();
                curr_string = curr_string.substr(curr_string.length() - rotate_count) + curr_string.substr(0, curr_string.length() - rotate_count);
            }
                break;
            case ROTATE_P: {
                size_t idx = curr_string.find((char)v1);
                size_t rotate_count = (idx + 1 + (idx >= 4)) % curr_string.length();

                curr_string = curr_string.substr(curr_string.length() - rotate_count) + curr_string.substr(0, curr_string.length() - rotate_count);
            }
                break;
            case REVERSE:
                reverse(begin(curr_string) + v1, begin(curr_string) + v2 + 1);
                break;
            case MOVE:
                char temp = curr_string[v1];
                curr_string.erase(begin(curr_string) + v1);
                curr_string.insert(begin(curr_string) + v2, temp);
                break;
        }
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

void simulate_program(vector<Instruction> instructions, string &password) {
    for (auto instr : instructions) {
        instr.on_run(password);
        //cout << password << endl;
    }
}

void process_line(string textline, int pos, vector<Instruction> &instructions) {
    stringstream token, ss(textline);
    Instruction instruct;
    string s_temp;
    int i_temp;
    char c_temp;

    ss >> s_temp;
    if (s_temp == "swap") {
        ss >> s_temp;
        if (s_temp == "position") {
            ss >> i_temp;

            instruct.type = SWAP_P;
            instruct.v1 = i_temp;

            ss >> s_temp >> s_temp >> i_temp;
            instruct.v2 = i_temp;

        } else if (s_temp == "letter") {
            ss >> c_temp;

            instruct.type = SWAP_L;
            instruct.v1 = c_temp;

            ss >> s_temp >> s_temp >> c_temp;
            instruct.v2 = c_temp;
        }
    } else if (s_temp == "rotate") {
        ss >> s_temp;
        if (s_temp == "based") {
            ss >> s_temp >> s_temp >> s_temp >> s_temp >> c_temp;
            instruct.type = ROTATE_P;
            instruct.v1 = c_temp;
        } else {
            ss >> i_temp;
            instruct.type = (s_temp == "right") ? ROTATE_R : ROTATE_L;
            instruct.v1 = i_temp;
        }
    } else if (s_temp == "reverse") {
        instruct.type = REVERSE;
        ss >> s_temp >> i_temp;
        instruct.v1 = i_temp;

        ss >> s_temp >> i_temp;
        instruct.v2 = i_temp;
    } else if (s_temp == "move") {
        instruct.type = MOVE;
        
        ss >> s_temp >> i_temp;
        instruct.v1 = i_temp;

        ss >> s_temp >> s_temp >> i_temp;
        instruct.v2 = i_temp;
    }

    instructions.push_back(instruct);
}

string process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<Instruction> instructions;
    string password = START_PASSWORD;

    size_t index = 0;
    while(getline(inputStream, textline)) {
        process_line(textline, index, instructions);
        index++;
    }

    simulate_program(instructions, password);

    return password;
}


int main() {
    auto output = process_file();
    cout << "The scrambled password " << output << endl;
}