#ifndef __EASY_INTERPRETER__HEADER__
#define __EASY_INTERPRETER__HEADER__


#include <vector>
#include <map>
#include <memory>
#include <functional>


// Values for Instructions
template<typename R, typename C>
class Value {
    public:
        virtual C get_value(const std::map<R, C>&) const;
        virtual void set_value(std::map<R, C>&, const C&);
};

template<typename R, typename C>
class Register : public Value<R, C> {
    R reg_name;

    public:
        Register(R);

        C get_value(const std::map<R, C>&) const;
        void set_value(std::map<R, C>&, const C&);
};

template<typename R, typename C>
class Constant : public Value<R, C> {
    C value;

    public:
        Constant(C);

        C get_value(const std::map<R, C>&) const;
        void set_value(std::map<R, C>&, const C&);
};

template<typename R, typename C>
struct AliasWrapper {
    typedef std::function<bool(const int&, const std::vector<std::shared_ptr<Value<R, C>>>&, std::map<R, C>&, int&)> Instr;
};


// Instructions
template<typename R, typename C>
class Instruction {
    int instruction_type;
    std::vector<std::shared_ptr<Value<R, C>>> arguments;

    public:
        Instruction(const int&);

        void add_register(const R&);
        void add_constant(const C&);

        int get_instruction_type() {
            return instruction_type;
        }

        bool enact_code(std::map<R, C>&, int&, typename AliasWrapper<R, C>::Instr);
};

// Program
template<typename R, typename C>
class Program {
    std::vector<Instruction<R, C>> instructions;
    std::map<R, C> registers;
    typename AliasWrapper<R, C>::Instr instruction_code;
    int program_counter = 0;
    
    public:
        Program(const int&, const typename AliasWrapper<R, C>::Instr&);

        bool is_finished();
        int get_program_counter();
        int get_current_instruction_type();

        bool simulate_step();
        void add_instruction(const Instruction<R, C>& instruct);

        void set_register(const R&, const C&);
        C get_register(const R&) const;
        std::vector<R> get_register_names() const;
};

#endif