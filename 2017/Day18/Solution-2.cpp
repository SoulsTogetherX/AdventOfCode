#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include "EasyInterpreter.h"


using namespace std;

#define ll long long


enum INSTRUCTION_NAMES {
    snd = 0,
    set = 1,
    add = 2,
    mul = 3,
    mod = 4,
    rcv = 5,
    jgz = 6
};

std::vector<ll> program_0_queue;
std::vector<ll> program_1_queue;


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

bool instruction_code(
    const int& instruction_type,
    const std::vector<shared_ptr<Value<char, ll>>>& arguments,
    std::map<char, ll>& registers,
    int &pc,
    const int &id
) {
    switch (instruction_type) {
        case snd:
            registers['\0']++;

            if (id == 0) {
                    // Program 1
                program_1_queue.push_back(arguments[0]->get_value(registers));
                break;
            }
                // Program 0
            program_0_queue.push_back(arguments[0]->get_value(registers));
        break;
        case set:
            arguments[0]->set_value(registers, arguments[1]->get_value(registers));
        break;
        case add:
            arguments[0]->set_value(registers, arguments[0]->get_value(registers) + arguments[1]->get_value(registers));
        break;
        case mul:
            arguments[0]->set_value(registers, arguments[0]->get_value(registers) * arguments[1]->get_value(registers));
        break;
        case mod:
            arguments[0]->set_value(registers, arguments[0]->get_value(registers) % arguments[1]->get_value(registers));
        break;
        case rcv:
            if (id == 0) {
                    // Program 0
                if (program_0_queue.empty()) {
                    return false;
                }
                arguments[0]->set_value(registers, program_0_queue.front());
                program_0_queue.erase(program_0_queue.begin());
                break;
            }
                // Program 1
            if (program_1_queue.empty()) {
                return false;
            }
            arguments[0]->set_value(registers, program_1_queue.front());
            program_1_queue.erase(program_1_queue.begin());
        break;
        case jgz:
            if (arguments[0]->get_value(registers) > 0) {
                pc += arguments[1]->get_value(registers);
                return false;
            }
        break;
    }
    return true;
}
bool instruction_code_0(
    const int& instruction_type,
    const std::vector<shared_ptr<Value<char, ll>>>& arguments,
    std::map<char, ll>& registers,
    int &pc
) {
    return instruction_code(instruction_type, arguments, registers, pc, 0);
}
bool instruction_code_1(
    const int& instruction_type,
    const std::vector<shared_ptr<Value<char, ll>>>& arguments,
    std::map<char, ll>& registers,
    int &pc
) {
    return instruction_code(instruction_type, arguments, registers, pc, 1);
}

void process_val(const string &str, Instruction<char, ll> &instr) {
    stringstream token(str);
    int i_temp;

    if (token >> i_temp) {
        instr.add_constant(i_temp);
        return;
    }
    instr.add_register(str[0]);
}

void process_line(const string &textline, Program<char, ll> &program_0, Program<char, ll> &program_1) {
    stringstream ss(textline);
    string temp_s;
    Instruction<char, ll> instruct(snd);

    ss >> temp_s;
    if (temp_s == "snd") {
        // snd X plays a sound with a frequency equal to the value of X.
        instruct = Instruction<char, ll>(snd);

        ss >> temp_s;
        process_val(temp_s, instruct);
    } else if (temp_s == "set") {
        // set X Y sets register X to the value of Y.
        instruct = Instruction<char, ll>(set);

        ss >> temp_s;
        process_val(temp_s, instruct);
        ss >> temp_s;
        process_val(temp_s, instruct);
    } else if (temp_s == "add") {
        // add X Y increases register X by the value of Y.
        instruct = Instruction<char, ll>(add);

        ss >> temp_s;
        process_val(temp_s, instruct);
        ss >> temp_s;
        process_val(temp_s, instruct);
    } else if (temp_s == "mul") {
        // mul X Y sets register X to the result of multiplying the value contained in register X by the value of Y.
        instruct = Instruction<char, ll>(mul);

        ss >> temp_s;
        process_val(temp_s, instruct);
        ss >> temp_s;
        process_val(temp_s, instruct);
    } else if (temp_s == "mod") {
        // mod X Y sets register X to the remainder of dividing the value contained in register X by the value of Y (that is, it sets X to the result of X modulo Y).
        instruct = Instruction<char, ll>(mod);

        ss >> temp_s;
        process_val(temp_s, instruct);
        ss >> temp_s;
        process_val(temp_s, instruct);
    } else if (temp_s == "rcv") {
        // rcv X recovers the frequency of the last sound played, but only when the value of X is not zero. (If it is zero, the command does nothing.)
        instruct = Instruction<char, ll>(rcv);

        ss >> temp_s;
        process_val(temp_s, instruct);
    } else if (temp_s == "jgz") {
        // jgz X Y jumps with an offset of the value of Y, but only if the value of X is greater than zero. (An offset of 2 skips the next instruction, an offset of -1 jumps to the previous instruction, and so on.)
        instruct = Instruction<char, ll>(jgz);

        ss >> temp_s;
        process_val(temp_s, instruct);
        ss >> temp_s;
        process_val(temp_s, instruct);
    }

    program_0.add_instruction(instruct);
    program_1.add_instruction(instruct);
}

bool is_running(Program<char, ll> program, int id) {
    if (program.get_current_instruction_type() != rcv) {
        return true;
    }
    if (id == 0) {
        if (!program_0_queue.empty()) {
            return true;
        }
    } else {
        if (!program_0_queue.empty()) {
            return true;
        }
    }
    return false;
}
int simulate(Program<char, ll> program_0, Program<char, ll> program_1) {
    while (is_running(program_0, 0) || is_running(program_1, 1)) {
        program_0.simulate_step();
        program_1.simulate_step();
    }
    return program_1.get_register('\0');
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    Program<char, ll> program_0(0, instruction_code_0);
    Program<char, ll> program_1(0, instruction_code_1);

    program_0.set_register('p', 0);
    program_1.set_register('p', 1);

    while(getline(inputStream, textline)) {
        process_line(textline, program_0, program_1);
    }
    return simulate(program_0, program_1);
}


int main() {
    auto output = process_file();
    cout << "The program 1 send a value " << output << " times" << endl;
}