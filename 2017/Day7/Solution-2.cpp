#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;


struct Node {
    Node *parent = nullptr;
    vector<Node*> children;

    string name;
    int weight, total_weight;

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
    int weight;
    char chars;

    ss >> name >> chars >> weight >> chars;

    tree_map[name].name = name;
    tree_map[name].weight = weight;

    ss >> temp_s;
    while(ss >> temp_s) {
        if (temp_s.back() == ','){
            temp_s.pop_back();
        }

        tree_map[temp_s].parent = &tree_map[name];
        tree_map[name].children.push_back(&tree_map[temp_s]);
    }
}

Node *get_root(map<string, Node> tree_map) {
    Node *curr = &begin(tree_map)->second;

    while(curr->parent) {
        curr = curr->parent;
    }

    return curr;
}

int add_bottom_up(Node *curr) {
    if (curr == nullptr) {
        return 0;
    }

    int total_weight = 0;
    for(auto node : curr->children) {
        total_weight += add_bottom_up(node);
    }

    curr->total_weight = total_weight + curr->weight;
    return curr->total_weight;
}

int cal_better_weight(Node *curr, int ideal) {
    return curr->weight + (ideal - curr->total_weight);
}

int weight_search(Node *curr) {
    if (curr == nullptr || curr->children.empty()) {
        return -1;
    }

    int val, i;

    for(auto child : curr->children) {
        val = weight_search(child);
        if (val != -1) {
            return val;
        }
    }

    val = curr->children[0]->total_weight;
    for(i = 1; i < curr->children.size(); i++) {
        if (val != curr->children[i]->total_weight) {
            // Since there is garanteed to be one, and this is the lowest point there is a difference, there must be at least three children
            // here.

            // If the difference is at the first check, then we need to do another compairson.
            if (i == 1) {
                if (val != curr->children[2]->total_weight) {
                    return cal_better_weight(curr->children[0], curr->children[1]->total_weight);
                }
                return cal_better_weight(curr->children[1], val);
            }
            return cal_better_weight(curr->children[i], val);
        }
    }

    return -1;
}

int find_better_weight(Node *root) {
    add_bottom_up(root);

    return weight_search(root);
}


int process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    map<string, Node> tree_map;

    while(getline(inputStream, textline)) {
        process_line(textline, tree_map);
    }

    return find_better_weight(get_root(tree_map));
}


int main() {
    auto output = process_file();
    cout << "The changed weight needs to be " << output << endl;
}