#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

enum INSTRUCTION_TYPE {
    CPY,
    INC,
    DEC,
    JNZ
};

struct Value {
    string reg;
    int value;
    bool is_register;

    Value() {}
    Value(int val) : value(val), is_register(false) {}
    Value(string name) : reg(name), is_register(true) {}

    void set_value(map<string, unsigned int> &registers, int val) {
        if (is_register) {
            registers[reg] = val;
            return;
        }
        value = val;
    }
    int get_value(map<string, unsigned int> &registers) {
        if (is_register) {
            return registers[reg];
        }
        return value;
    }
};

struct Instruction {
    INSTRUCTION_TYPE type;
    Value v1, v2;
    int pos;

    void on_run(map<string, unsigned int> &registers, int &curr_pos) {
        switch (type) {
            case CPY:
                v2.set_value(registers, v1.get_value(registers));
                break;
            case INC:
                v1.set_value(registers, v1.get_value(registers) + 1);
                break;
            case DEC:
                v1.set_value(registers, v1.get_value(registers) - 1);
                break;
            case JNZ:
                if (v1.get_value(registers) == 0) {
                    break;
                }
                curr_pos += v2.get_value(registers);
                return;
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
        //cout << "a: " << registers["a"] << " b: " << registers["b"] << endl;
        if (pos >= instructions.size()) return;
    }
}

void process_line(string textline, int pos, vector<Instruction> &instructions) {
    stringstream token, ss(textline);
    Instruction instruct;
    string s_temp;
    int i_temp;

    ss >> s_temp;
    if (s_temp == "inc") {
        ss >> s_temp;

        instruct.type = INC;
        instruct.pos = pos;
        instruct.v1 = Value(s_temp);
    } else if (s_temp == "dec") {
        ss >> s_temp;

        instruct.type = DEC;
        instruct.pos = pos;
        instruct.v1 = Value(s_temp);
    } else if (s_temp == "cpy") {
        ss >> s_temp;
        token = stringstream(s_temp);
        if (token >> i_temp) {
            instruct.v1 = Value(i_temp);
        } else {
            instruct.v1 = Value(s_temp);
        }

        ss >> s_temp;
        token = stringstream(s_temp);
        if (token >> i_temp) {
            instruct.v2 = Value(i_temp);
        } else {
            instruct.v2 = Value(s_temp);
        }

        instruct.type = CPY;
        instruct.pos = pos;
    } else if (s_temp == "jnz") {
        ss >> s_temp;
        token = stringstream(s_temp);
        if (token >> i_temp) {
            instruct.v1 = Value(i_temp);
        } else {
            instruct.v1 = Value(s_temp);
        }

        ss >> s_temp;
        token = stringstream(s_temp);
        if (token >> i_temp) {
            instruct.v2 = Value(i_temp);
        } else {
            instruct.v2 = Value(s_temp);
        }

        instruct.type = JNZ;
        instruct.pos = pos;
    }

    instructions.push_back(instruct);
}

unsigned int process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    map<string, unsigned int> registers;
    vector<Instruction> instructions;

    size_t index = 0;
    while(getline(inputStream, textline)) {
        process_line(textline, index, instructions);
        index++;
    }

    simulate_program(registers, instructions);

    return registers["a"];
}


int main() {
    auto output = process_file();
    cout << "The value of a at the end is " << output << endl;
}