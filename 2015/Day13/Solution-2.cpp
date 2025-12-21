#include <iostream>
#include <limits>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

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

void process_line(
    string textline,
    unordered_map<string, unordered_map<string, int>> &memo
) {
    stringstream ss(textline);
    string name1, name2, temp, sign;
    int happiness;

    ss >> name1 >> temp >> sign >> happiness >> temp >> temp >> temp >> temp >> temp >> temp >> name2;
    name2.pop_back(); // Remove Period

    if (sign == "lose") happiness = -happiness;

    memo[name1][name2] = happiness;
}
void insert_me(
    unordered_map<string, unordered_map<string, int>> &memo
) {
    unordered_map<string, int> my_interests;

    for(auto it : memo) {
        my_interests[it.first] = 0;
        it.second["me"] = 0;
    }

    memo["me"] = my_interests;
}

const long long max_seating_recursive(
    unordered_map<string, unordered_map<string, int>> memo,
    string curr,
    vector<string> visted
) {
    visted.push_back(curr);
    if (memo.size() == visted.size()) {
        return memo[visted.front()][visted.back()] + memo[visted.back()][visted.front()];
    }

    long long temp, happiness = numeric_limits<long long>::min();
    for(auto it : memo) {
        if (find(visted.begin(), visted.end(), it.first) != visted.end()) {
            continue;
        }

        temp = memo[curr][it.first] + memo[it.first][curr] + max_seating_recursive(memo, it.first, visted);

        if (happiness < temp) {
            happiness = temp;
        }
    }

    return happiness;
}
const long long max_seating(unordered_map<string, unordered_map<string, int>> memo) {
    if (memo.empty()) {
        return 0;
    }

    return max_seating_recursive(memo, memo.begin()->first, vector<string>());
}


long long process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    unordered_map<string, unordered_map<string, int>> memo;

    while(getline(inputStream, textline)) {
        process_line(textline, memo);
    }

    insert_me(memo);
    return max_seating(memo);
}


int main() {
    auto output = process_file();
    cout << "The optimal happiness is " << output << endl;
}