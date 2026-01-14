#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

const int PATTERN_CHECK = 100;

enum INSTRUCTION_TYPE {
    CPY,
    INC,
    DEC,
    JNZ,
    TGL,
    OUT,
    MUL
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

    void toggle_instruction() {
        switch (type) {
            case INC:
            case DEC:
            case TGL:
            case OUT:
                type = type == INC ? DEC : INC;
            break;
            case CPY:
            case JNZ:
            case MUL:
                type = type == JNZ ? CPY : JNZ;
            break;
        }
    }

    void on_run(map<string, unsigned int> &registers, vector<Instruction> &instructions, int &curr_pos, int &value, bool &unchecked) {
        switch (type) {
            case CPY:
                if (!v2.is_register) {
                    break;
                }

                v2.set_value(registers, v1.get_value(registers));
                break;
            case INC:
                if (!v1.is_register) {
                    break;
                }

                v1.set_value(registers, v1.get_value(registers) + 1);
                break;
            case DEC:
                if (!v1.is_register) {
                    break;
                }

                v1.set_value(registers, v1.get_value(registers) - 1);
                break;
            case TGL:{
                int edit_pos = curr_pos + v1.get_value(registers);
                if (edit_pos >= instructions.size()) {
                    break;
                }
                instructions[edit_pos].toggle_instruction();
            }
                break;
            case OUT:
                value = v1.get_value(registers);
                unchecked = true;
                break;
            case JNZ:
                if (v1.get_value(registers) == 0) {
                    break;
                }
                curr_pos += v2.get_value(registers);
                return;
            case MUL:
                if (!v2.is_register) {
                    break;
                }
                v2.set_value(registers, v1.get_value(registers) * v2.get_value(registers));
                break;
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

int simulate_program(map<string, unsigned int> &registers, vector<Instruction> instructions) {
    int pos = 0, start = 0, count = 0, value;
    bool unchecked, pattern;

    while(true) {
        cout << "Checking: " << start << endl;
        //cout << "Pattern: ";

        pos = 0;
        count = 0;
        registers.clear();
        registers["a"] = start;

        while(true) {
            unchecked = false;
            instructions[pos].on_run(registers, instructions, pos, value, unchecked);

            if (unchecked) {
                //cout << value << " ";

                if (value != 0 && value != 1) {
                    //cout << endl;
                    break;
                } else if (count == 0) {
                    pattern = (value == 1);
                } else if (pattern != (value == 1)) {
                    //cout << endl;
                    break;
                }

                if (count >= PATTERN_CHECK) {
                    //cout << endl;
                    return start;
                }

                pattern = !pattern;
                count++;
            }
            if (pos >= instructions.size()) {
                //cout << endl;
                break;
            }
        }

        start++;
    }

    return -1;
}

Value get_value(string str) {
    stringstream token(str);
    int i_temp;

    if (token >> i_temp) {
        return Value(i_temp);
    }
    return Value(str);
}

void process_line(string textline, int pos, vector<Instruction> &instructions) {
    stringstream token, ss(textline);
    Instruction instruct;
    string s_temp;
    int i_temp;

    ss >> s_temp;
    if (s_temp == "inc") {
        ss >> s_temp;
        instruct.v1 = get_value(s_temp);

        instruct.type = INC;
        instruct.pos = pos;
    } else if (s_temp == "dec") {
        ss >> s_temp;
        instruct.v1 = get_value(s_temp);

        instruct.type = DEC;
        instruct.pos = pos;
    } else if (s_temp == "cpy") {
        ss >> s_temp;
        instruct.v1 = get_value(s_temp);

        ss >> s_temp;
        instruct.v2 = get_value(s_temp);

        instruct.type = CPY;
        instruct.pos = pos;
    } else if (s_temp == "jnz") {
        ss >> s_temp;
        instruct.v1 = get_value(s_temp);

        ss >> s_temp;
        instruct.v2 = get_value(s_temp);

        instruct.type = JNZ;
        instruct.pos = pos;
    } else if (s_temp == "mul") {
        ss >> s_temp;
        instruct.v1 = get_value(s_temp);

        ss >> s_temp;
        instruct.v2 = get_value(s_temp);

        instruct.type = MUL;
        instruct.pos = pos;
    } else if (s_temp == "tgl") {
        ss >> s_temp;
        instruct.v1 = get_value(s_temp);

        instruct.type = TGL;
        instruct.pos = pos;
    } else if (s_temp == "out") {
        ss >> s_temp;
        instruct.v1 = get_value(s_temp);

        instruct.type = OUT;
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

    return simulate_program(registers, instructions);;
}


int main() {
    auto output = process_file();
    cout << "The smallest possible number needed is " << output << endl;
}
