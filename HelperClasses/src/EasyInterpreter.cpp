#include "EasyInterpreter.h"

#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <memory>


// Values for Instructions
template<typename R, typename C>
C Value<R, C>::get_value(const std::map<R, C>&) const {
    assert(false && "Called the abstract 'Value' function 'get_value'.");
    return C();
}
template<typename R, typename C>
void Value<R, C>::set_value(std::map<R, C>&, const C&) {
    assert(false && "Called the abstract 'Value' function 'set_value'.");

}

    // Register
template<typename R, typename C>
Register<R, C>::Register(R name) : reg_name(name) {}

template<typename R, typename C>
C Register<R, C>::get_value(const std::map<R, C>& registers) const {
    if (registers.count(reg_name)) {
        return registers.at(reg_name);
    }
    return 0;
}
template<typename R, typename C>
void Register<R, C>::set_value(std::map<R, C>& registers, const C& val) {
    registers[reg_name] = val;
}

    // Constants
template<typename R, typename C>
Constant<R, C>::Constant(C val) : value(val) {}

template<typename R, typename C>
C Constant<R, C>::get_value(const std::map<R, C>& registers) const {
    return value;
}
template<typename R, typename C>
void Constant<R, C>::set_value(std::map<R, C>& registers, const C& val) {
    assert(false && "Attempted to set a 'Constant' value.");
}


// Instructions
template<typename R, typename C>
Instruction<R, C>::Instruction(const int& type) : instruction_type(type) {}

template<typename R, typename C>
void Instruction<R, C>::add_register(const R& name) {
    arguments.push_back(std::shared_ptr<Register<R, C>>(new Register<R, C>(name)));
}
template<typename R, typename C>
void Instruction<R, C>::add_constant(const C& val) {
    arguments.push_back(std::shared_ptr<Constant<R, C>>(new Constant<R, C>(val)));
}

template<typename R, typename C>
bool Instruction<R, C>::enact_code(std::map<R, C>& registers, int& pc, typename AliasWrapper<R, C>::Instr processor) {
   return processor(instruction_type, arguments, registers, pc);
}


// Program
template<typename R, typename C>
Program<R, C>::Program(
    const int& pc,
    const typename AliasWrapper<R, C>::Instr& processor
) : program_counter(pc), instruction_code(processor) {}

template<typename R, typename C>
bool Program<R, C>::simulate_step() {
    if (0 <= program_counter && program_counter < instructions.size()) {
        if (instructions[program_counter].enact_code(registers, program_counter, instruction_code)) {
            program_counter++;
        }
        return true;
    }
    return false;
}


template<typename R, typename C>
bool Program<R, C>::is_finished() {
    return 0 > program_counter || program_counter >= instructions.size();
}
template<typename R, typename C>
int Program<R, C>::get_program_counter() {
    return program_counter;
}
template<typename R, typename C>
int Program<R, C>::get_current_instruction_type() {
    return instructions[program_counter].get_instruction_type();
}

template<typename R, typename C>
void Program<R, C>::add_instruction(const Instruction<R, C>& instruct) {
    instructions.push_back(instruct);
}

template<typename R, typename C>
void Program<R, C>::set_register(const R& name, const C& val) {
    registers[name] = val;
}
template<typename R, typename C>
C Program<R, C>::get_register(const R& name) const {
    if (registers.count(name)) {
        return registers.at(name);
    }
    return 0;
}
template<typename R, typename C>
std::vector<R> Program<R, C>::get_register_names() const {
    std::vector<R> keys;
    for (const auto& it : registers) {
        keys.push_back(it.first);
    }
    return keys;
}



template class Value<char, long long>;
template class Register<char, long long>;
template class Constant<char, long long>;
template class Instruction<char, long long>;
template class Program<char, long long>;

template class Value<std::string, long long>;
template class Register<std::string, long long>;
template class Constant<std::string, long long>;
template class Instruction<std::string, long long>;
template class Program<std::string, long long>;