#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

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


void process_line(const string& textstring, vector<pair<int, int>>& components) {
    stringstream ss(textstring);
    int p1, p2;
    char discard;

    ss >> p1 >> discard >> p2;
    components.push_back(pair<int ,int>(p1, p2));
}

void find_max_bridge_helper(
    vector<pair<int, int>> components,
    const int& remove_idx,
    const int& next,
    const int& strength,
    int& max_stength
) {
    if (remove_idx != -1) {
        swap(components[remove_idx], components.back());
        components.pop_back();
    }

    for(int i = 0; i < components.size(); i++) {
        auto c = components[i];

        if (c.first == next) {
            find_max_bridge_helper(components, i, c.second, strength + c.first + c.second, max_stength);
        } else if (c.second == next) {
            find_max_bridge_helper(components, i, c.first, strength + c.first + c.second, max_stength);
        }
    }

    if (strength > max_stength) {
        max_stength = strength;
    }
}
int find_max_bridge(vector<pair<int, int>> components) {
    int max_stength = -1;
    find_max_bridge_helper(components, -1, 0, 0, max_stength);
    return max_stength;
}


size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<pair<int, int>> components;

    while(getline(inputStream, textline)) {
        process_line(textline, components);
    }

    return find_max_bridge(components);
}


int main() {
    auto output = process_file();
    cout << "The max strength bridge is " << output << endl;
}