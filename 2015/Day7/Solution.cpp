#include <cstdint>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;


const string OUTPUT_WIRE = "a";


class Input {
    protected:
        bool type;
        uint16_t num;
        string signal_name;

    public:
        Input() {}
        Input(string signal_name) : signal_name(signal_name) { type = false; }
        Input(uint16_t num) : num(num) { type = true; }

        string to_string() {
            return type ? std::to_string(num) : signal_name;
        }

        bool can_access(unordered_map<string, uint16_t> signals) {
            return type || signals.count(signal_name);
        }
        uint16_t access(unordered_map<string, uint16_t> signals) {
            return type ? num : signals[signal_name];
        }
};

class Operation {
    protected:
        bool binary;
        string op_name, out_name;
        Input input1, input2;

    public:
        Operation(
            bool binary,
            string op_name,
            string out_name,
            Input input1,
            Input input2
        ) : binary(binary), op_name(op_name), out_name(out_name), input1(input1), input2(input2) {}

        string to_string() {
            if (binary) {
                return input1.to_string() + " " + op_name + " " + input2.to_string() + " " + out_name;
            }
            return op_name + " " + input1.to_string() + " " + out_name;
        }

        bool operate(unordered_map<string, uint16_t> &signals) {
            if (!input1.can_access(signals) || (binary && !input2.can_access(signals))) return false;

            if (op_name == "SET") {
                signals[out_name] = input1.access(signals);
                return true;
            } else if (op_name == "NOT") {
                signals[out_name] = ~input1.access(signals);
                return true;
            } else if (op_name == "AND") {
                signals[out_name] = input1.access(signals) & input2.access(signals);
                return true;
            } else if (op_name == "OR") {
                signals[out_name] = input1.access(signals) | input2.access(signals);
                return true;
            } else if (op_name == "XOR") {
                signals[out_name] = input1.access(signals) ^ input2.access(signals);
                return true;
            } else if (op_name == "LSHIFT") {
                signals[out_name] = input1.access(signals) << input2.access(signals);
                return true;
            } else if (op_name == "RSHIFT") {
                signals[out_name] = input1.access(signals) >> input2.access(signals);
                return true;
            }
             
            return false;
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

Input parse_input(string str) {
    char* p;
    uint16_t converted = strtol(str.c_str(), &p, 10);
    if (*p) {
        //cout << "s " << str << endl;
        return Input(str);
    }
    //cout << "i " << str << endl;
    return Input(converted);
}
void parse_line(string textline, vector<Operation> &operations) {
    stringstream ss(textline);
    string s_temp, op;
    Input input1, input2;

    ss >> s_temp;
    if (s_temp == "NOT") {
        ss >> s_temp;
        input1 = parse_input(s_temp);

        ss >> s_temp >> s_temp;
        //cout << "op " << "NOT" << endl << "o " << s_temp << endl << endl;
        operations.push_back(
            Operation(false, "NOT", s_temp, input1, Input())
        );
        return;
    }

    input1 = parse_input(s_temp);

    ss >> s_temp;
    if (s_temp == "->") {
        ss >> s_temp;
        //cout << "op " << "SET" << endl << "o " << s_temp << endl << endl;
        operations.push_back(
            Operation(false, "SET", s_temp, input1, Input())
        );
        return;
    }

    op = s_temp;
    ss >> s_temp;
    input2 = parse_input(s_temp);

    ss >> s_temp >> s_temp;
    //cout << "op " << op << endl << "o " << s_temp << endl << endl;
    operations.push_back(
        Operation(true, op, s_temp, input1, input2)
    );
}
void emulate_circuit(unordered_map<string, uint16_t> &signals, vector<Operation> operations) {
    vector<Operation> new_ops;

    while(!operations.empty()) {
        new_ops.clear();

        for(auto op : operations) {
            if (!op.operate(signals)) {
                new_ops.push_back(op);
                continue;
            }
            cout << op.to_string() << endl;
        }

        operations = new_ops;
    }
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    unordered_map<string, uint16_t> signals;
    vector<Operation> operations;

    while(getline(inputStream, textline)) {
        parse_line(textline, operations);
    }

    emulate_circuit(signals, operations);
    return signals[OUTPUT_WIRE];
}


int main() {
    auto output = process_file();
    cout << "The final signal is " << output << endl;
}