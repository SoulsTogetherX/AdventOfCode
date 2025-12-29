#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

enum INSTRUCTION_TYPE {
    HLF,
    TPL,
    INC,
    JMP,
    JIE,
    JIO
};

struct Instruction {
    string reg;
    INSTRUCTION_TYPE type;
    int pos, value;

    void on_run(map<string, unsigned int> &registers, int &curr_pos) {
        switch (type) {
            case HLF:
                registers[reg] /= 2;
                break;
            case TPL:
                registers[reg] *= 3;
                break;
            case INC:
                registers[reg]++;
                break;
            case JMP:
                curr_pos += value;
                return;
            case JIE:
                if (!(registers[reg] % 2)) {
                    curr_pos += value;
                    return;
                }
            case JIO:
                if (registers[reg] == 1) {
                    curr_pos += value;
                    return;
                }
        }
        curr_pos++;
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

void simulate_program(map<string, unsigned int> &registers, vector<Instruction> instructions) {
    int pos = 0;

    while(true) {
        instructions[pos].on_run(registers, pos);
        cout << "a: " << registers["a"] << " b: " << registers["b"] << endl;
        if (pos >= instructions.size()) return;
    }
}

void process_line(string textline, int pos, vector<Instruction> &instructions) {
    stringstream ss(textline);
    Instruction instruct;
    string s_temp;
    int i_temp;

    ss >> s_temp;
    if (s_temp == "hlf") {
        ss >> s_temp;

        instruct.type = HLF;
        instruct.pos = pos;
        instruct.reg = s_temp;
    } else if (s_temp == "tpl") {
        ss >> s_temp;

        instruct.type = TPL;
        instruct.pos = pos;
        instruct.reg = s_temp;
    } else if (s_temp == "inc") {
        ss >> s_temp;

        instruct.type = INC;
        instruct.pos = pos;
        instruct.reg = s_temp;
    } else if (s_temp == "jmp") {
        ss >> i_temp;

        instruct.type = JMP;
        instruct.pos = pos;
        instruct.value = i_temp;
    } else if (s_temp == "jie") {
        ss >> s_temp >> i_temp;
        s_temp.pop_back();

        instruct.type = JIE;
        instruct.pos = pos;
        instruct.reg = s_temp;
        instruct.value = i_temp;
    } else if (s_temp == "jio") {
        ss >> s_temp >> i_temp;
        s_temp.pop_back();

        instruct.type = JIO;
        instruct.pos = pos;
        instruct.reg = s_temp;
        instruct.value = i_temp;
    }

    instructions.push_back(instruct);
}

unsigned int process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    map<string, unsigned int> registers;
    vector<Instruction> instructions;

    registers["a"] = 1;

    size_t index = 0;
    while(getline(inputStream, textline)) {
        process_line(textline, index, instructions);
        index++;
    }

    simulate_program(registers, instructions);

    return registers["b"];
}


int main() {
    auto output = process_file();
    cout << "The value of b at the end is " << output << endl;
}