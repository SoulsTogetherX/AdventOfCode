#include <iostream>
#include <fstream>
#include <sstream>
#include "EasyInterpreter.h"


using namespace std;

#define ll long long


enum INSTRUCTION_NAMES {
    set,
    sub,
    mul,
    jnz
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

bool instruction_code(
    const int& instruction_type,
    const std::vector<shared_ptr<Value<char, ll>>>& arguments,
    std::map<char, ll>& registers,
    int &pc
) {
    switch (instruction_type) {
        case set:
            arguments[0]->set_value(registers, arguments[1]->get_value(registers));
        break;
        case sub:
            arguments[0]->set_value(registers, arguments[0]->get_value(registers) - arguments[1]->get_value(registers));
        break;
        case mul:
            registers['\0']++;
            arguments[0]->set_value(registers, arguments[0]->get_value(registers) * arguments[1]->get_value(registers));
        break;
        case jnz:
            if (arguments[0]->get_value(registers) != 0) {
                pc += arguments[1]->get_value(registers);
                return false;
            }
        break;
    }
    return true;
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

void process_line(const string &textline, Program<char, ll> &program) {
    stringstream ss(textline);
    string temp_s;
    Instruction<char, ll> instruct(0);

    ss >> temp_s;
    if (temp_s == "set") {
        // set X Y sets register X to the value of Y.
        instruct = Instruction<char, ll>(set);

        ss >> temp_s;
        process_val(temp_s, instruct);
        ss >> temp_s;
        process_val(temp_s, instruct);
    } else if (temp_s == "sub") {
        // sub X Y decreases register X by the value of Y.
        instruct = Instruction<char, ll>(sub);

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
    } else if (temp_s == "jnz") {
        // jnz X Y jumps with an offset of the value of Y, but only if the value of X is not zero. (An offset of 2 skips the next instruction, an offset of -1 jumps to the previous instruction, and so on.)
        instruct = Instruction<char, ll>(jnz);

        ss >> temp_s;
        process_val(temp_s, instruct);
        ss >> temp_s;
        process_val(temp_s, instruct);
    }

    program.add_instruction(instruct);
}

int simulate(Program<char, ll> program) {
    while(program.simulate_step());
    return program.get_register('\0');
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    Program<char, ll> program(0, instruction_code);
    while(getline(inputStream, textline)) {
        process_line(textline, program);
    }
    return simulate(program);
}


int main() {
    auto output = process_file();
    cout << "The mul instruction was invoked " << output << " times." << endl;
}