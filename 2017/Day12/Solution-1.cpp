#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

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

void process_line(const string &textline, vector<vector<int>> &connections) {
    stringstream ss(textline);
    vector<int> pipes;
    int temp; char chars;

    ss >> temp >> chars >> chars >> chars;
    while(ss >> temp) {
        pipes.push_back(temp);
        ss >> chars;
    }

    connections.push_back(pipes);
}

int count_connected(const vector<vector<int>> &connections, const int &from) {
    vector<int> open, closed;
    set<int> memo;
    int temp;

    open.push_back(from);
    while(!open.empty()) {
        swap(open, closed);

        while(!closed.empty()) {
            temp = closed.back();
            closed.pop_back();

            if (memo.count(temp)) {
                continue;
            }
            memo.insert(temp);
            open.insert(open.end(), connections[temp].begin(), connections[temp].end());
        }
    }

    return memo.size();
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<vector<int>> connections;

    while(getline(inputStream, textline)) {
        process_line(textline, connections);
    }

    return count_connected(connections, 0);
}


int main() {
    auto output = process_file();
    cout << "The number of programs connected to zero is " << output << endl;
}