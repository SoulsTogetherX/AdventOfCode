#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

const int DIVIDES = 3;


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


void print_group(vector<int> group) {
    for(auto g : group) {
        cout << g << ", ";
    }
    cout << endl;
}
size_t cal_entanglement(vector<int> group) {
    size_t mul = 1;
    for(auto g : group) {
        mul *= (size_t)g;
    }
    return mul;
}
void find_group_helper(
    vector<int> presents,
    vector<int> group,
    int s_target,
    int target,
    int idx,
    size_t &min_size,
    size_t &min_entanglement
) {
    auto present = presents[idx];
    if (target < present) {
        return;
    }

    group.push_back(present);
    if (group.size() > min_size) {
        return;
    }

    presents.erase(presents.begin() + idx);
    if (target == present) {
        size_t ent = cal_entanglement(group);
        if (group.size() < min_size) {
            min_size = group.size();
            min_entanglement = ent;
        } else if (ent < min_entanglement) {
            min_entanglement = ent;
        }
        return;
    }

    target -= present;

    for(int i = idx; i < presents.size(); i++) {
        find_group_helper(presents, group, s_target, target, i, min_size, min_entanglement);
    }
}

size_t quantum_entanglement(vector<int> presents) {
    size_t min_size = -1, min_entanglement = -1;
    int target = 0;

    for(auto p : presents) {
        target += p;
    }
    if (target % 3 != 0) {
        cout << "Impossible task" << endl;
        return - 1;
    }

    target /= DIVIDES;
    sort(presents.begin(), presents.end(), std::greater<int>());

    for(int i = 0; i < presents.size(); i++) {
        find_group_helper(presents, vector<int>(), target, target, i, min_size, min_entanglement);
    }
    return min_entanglement;
}

void process_line(string textline, vector<int> &presents) {
    stringstream ss(textline);
    int temp_i;

    ss >> temp_i;
    presents.push_back(temp_i);
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<int> presents;
    while(getline(inputStream, textline)) {
        process_line(textline, presents);
    }

    return quantum_entanglement(presents);
}


int main() {
    auto output = process_file();
    cout << "The min quantum entanglement is " << output << endl;
}