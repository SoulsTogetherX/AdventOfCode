#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;


struct Node {
    Node *parent = nullptr;
    vector<Node*> connections;

    string name;
    int value;

    bool operator < (const Node& n) const {
        return name < n.name;
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

void process_line(const string &textline, map<string, Node> &tree_map) {
    stringstream ss(textline);
    string name, temp_s;
    int value;
    char chars;

    ss >> name >> chars >> value >> chars;

    tree_map[name].name = name;

    ss >> temp_s;
    while(ss >> temp_s) {
        if (temp_s.back() == ','){
            temp_s.pop_back();
        }

        tree_map[temp_s].parent = &tree_map[name];
        tree_map[name].connections.push_back(&tree_map[temp_s]);
    }
}

string get_root(map<string, Node> tree_map) {
    Node curr = begin(tree_map)->second;

    while(curr.parent) {
        curr = *curr.parent;
    }

    return curr.name;
}


string process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    map<string, Node> tree_map;

    while(getline(inputStream, textline)) {
        process_line(textline, tree_map);
    }

    return get_root(tree_map);
}


int main() {
    auto output = process_file();
    cout << "The root of the tree is " << output << endl;
}