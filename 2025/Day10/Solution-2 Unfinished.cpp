#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;


class Button {
    private:
        vector<int> toggles;

    public:

        Button(vector<int> toggles = vector<int>()) {
            this->toggles = toggles;

        }

        vector<int> get_toggles() {
            return toggles;
        }
        int get_prioity() {
            return toggles.size();
        }

        bool operates_on(int idx) {
            for(auto i : toggles) {
                if (i == idx) return true;
            }
            return false;
        }
        void reduce(vector<int> &joltage, int mul = 0) {
            for(auto i : toggles) {
                joltage[i] += mul;
            }
        }

        bool operator < (const Button &b) const {
            return toggles.size() < b.toggles.size();
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

void parse_line(string textline, vector<Button> &buttons, vector<int> &joltage) {
    stringstream ss(textline);
    int temp;
    char chars;

    ss >> chars;
    while(true) {
        ss >> chars;
        if (chars == ']') {
            break;
        }
    }

    while(true) {
        ss >> chars;
        if (chars != '(') break;

        vector<int> toggles;
        while(true) {
            ss >> temp >> chars;
            toggles.push_back(temp);

            if (chars == ')') break;
        }
        buttons.push_back(Button(toggles));
    }

    while(true) {
        ss >> temp >> chars;
        joltage.push_back(temp);
        if (chars == '}') break;
    }
}

vector<Button> filter_buttons(vector<Button> buttons, int joltage_idx = 0) {
    vector<Button> ret;

    for(auto b : buttons) {
        if (b.operates_on(joltage_idx)) {
            ret.push_back(b);
        }
    }

    return ret;
}
void permutation_recusive(
    vector<int> joltage,
    vector<Button> buttons,
    int joltage_idx,
    size_t depth,
    size_t &min_depth
) {
    if (depth > min_depth) {
        return;
    }
    if (joltage_idx >= joltage.size()) {
        min_depth = depth;
        return;
    }

    vector<int> base_joltage = joltage;
    vector<Button> relevant_buttons = filter_buttons(buttons, joltage_idx);
    Button button;
    int base_depth = depth, b_idx;
    bool vaild;

    for(int button_idx = 0; button_idx < relevant_buttons.size(); button_idx++) {
        joltage = base_joltage;
        depth = base_depth;
        b_idx = button_idx;
        
        vaild = true;
        while(joltage[joltage_idx] != 0) {
            if (b_idx >= relevant_buttons.size() || depth > min_depth) {
                vaild = false;
                break;
            }
            button = relevant_buttons[b_idx];

            unsigned int op_num = -1;
            for(auto idx : button.get_toggles()) {
                op_num = (joltage[idx] < op_num) ? joltage[idx] : op_num;
            }

            button.reduce(joltage, -op_num);
            depth += op_num;
            
            b_idx++;
        }

        if (vaild) {
            permutation_recusive(joltage, buttons, joltage_idx + 1, depth, min_depth);
        }
    }
}
size_t permutation(vector<int> joltage, vector<Button> buttons) {
    size_t min_depth = -1;
    vector<Button> safe_buttons = buttons;

    sort(safe_buttons.begin(), safe_buttons.end());
    permutation_recusive(joltage, safe_buttons, 0, 0, min_depth);

    return min_depth;
}


void process_line(string textline, size_t &sum) {
    vector<Button> buttons;
    vector<int> joltage;
    
    parse_line(textline, buttons, joltage);

    size_t min_depth = permutation(joltage, buttons);
    if (min_depth == -1) {
        cout << "No solution found for '" << textline << "'" << endl << endl;
    } else {
        cout << to_string(min_depth) << "-length solution found for '" << textline << "'" << endl << endl;
    }

    sum += min_depth;
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    size_t sum = 0;
    while(getline(inputStream, textline)) {
        process_line(textline, sum);
    }

    return sum;
}

int main() {
    size_t output = process_file();
    cout << "The fewest number of button presses is " << output << endl;
}