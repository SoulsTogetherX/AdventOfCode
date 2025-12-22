#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <set>
#include <regex>

using namespace std;


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

set<string> get_all_chemicals(string inital, unordered_map<string, vector<string>> instructions) {
    set<string> memo;
    auto matches_end = sregex_iterator();

    for(auto it : instructions) {
        regex reg(it.first);
        
        auto matches_begin = sregex_iterator(inital.begin(), inital.end(), reg);
        
        for(string replace_str : it.second) {
            for (sregex_iterator i = matches_begin; i != matches_end; i++) {
                string temp = inital;
                temp.replace(i->position(), it.first.size(), replace_str);
                memo.insert(temp);
            }
        }
    }
    
    return memo;
}
void process_line(string textline, unordered_map<string, vector<string>> &instructions) {
    stringstream ss(textline);
    string name1, name2;

    ss >> name1 >> name2 >> name2;
    instructions[name1].push_back(name2);
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    unordered_map<string, vector<string>> instructions;
    string inital;

    while(getline(inputStream, textline)) {
        if (textline.empty()) {
            getline(inputStream, textline);
            inital = textline;
            break;
        }

        process_line(textline, instructions);
    }

    return get_all_chemicals(inital, instructions).size();
}


int main() {
    auto output = process_file();
    cout << "The number of molecules is " << output << endl;
}