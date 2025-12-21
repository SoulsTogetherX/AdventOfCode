#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

enum Compounds {
    CHILDREN = 0,
    CATS,
    SAMOYEDS,
    POMERANIANS,
    AKITAS,
    VIZSLAS,
    GOLDFISH,
    TREES,
    CARS,
    PERFUMES,
    LENGTH
};


const vector<int> correct_aunt = {3, 7, 2, 3, 0, 0, 5, 3, 2, 1};
const unordered_map<string, int> compound_map = {
    {"children", CHILDREN},
    {"cats", CATS},
    {"samoyeds", SAMOYEDS},
    {"pomeranians", POMERANIANS},
    {"akitas", AKITAS},
    {"vizslas", VIZSLAS},
    {"goldfish", GOLDFISH},
    {"trees", TREES},
    {"cars", CARS},
    {"perfumes", PERFUMES}
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

void process_line(string textline, vector<vector<int>> &aunts) {
    vector<int> aunt(LENGTH, -1);
    string name = "goldfish";
    int number;

    stringstream ss(textline);

    ss >> name;
    while(ss.peek() != char_traits<char>::eof()) {
        ss >> name >> name >> number;
        name.pop_back();
        
        aunt[compound_map.at(name)] = number;
    }

    aunts.push_back(aunt);
}

int sift_aunts(vector<int> correct, vector<vector<int>> aunts) {
    bool vaild;
    int idx = 0;

    for(int i = 0; i < aunts.size(); i++) {
        auto aunt = aunts[i];

        vaild = true;
        for(int i = 0; i < LENGTH; i++) {
            if (aunt[i] == -1) continue;
            if (i == CATS || i == TREES) {
                if (aunt[i] > correct[i]) {
                    continue;
                }
            } else if (i == POMERANIANS || i == GOLDFISH) {
                if (aunt[i] < correct[i]) {
                    continue;
                }
            } else if (aunt[i] == correct[i]) {
                continue;
            }

            vaild = false;
            break;
        }

        if (vaild) idx = i;
    }

    return idx + 1;
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<vector<int>> aunts;
    while(getline(inputStream, textline)) {
        process_line(textline, aunts);
    }

    return sift_aunts(correct_aunt, aunts);
}


int main() {
    auto output = process_file();
    cout << "The Sue that gave you the gift is number " << output << endl;
}