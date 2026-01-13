#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Point2D.h"

using namespace std;

struct Node {
    Point2D<int> coord;
    int size, used, avail, percent;

    Node(
        Point2D<int> coord,
        int size,
        int used,
        int avail,
        int percent
    ) : coord(coord), size(size), used(used), avail(avail), percent(percent) {}
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

void process_line(string textline, vector<Node> &nodes) {
    stringstream ss(textline);
    int x, y, size, used, avail, percent;
    char chars;

    ss.seekg(16);
    ss >> x >> chars >> chars >> y >> size >> chars >> used >> chars >> avail >> chars >> percent;

    nodes.push_back(Node(Point2D(x, y), size, used, avail, percent));
}

size_t count_viable_pairs(vector<Node> nodes) {
    size_t sum = 0;

    for(int i = 0; i < nodes.size(); i++) {
        for(int j = 0; j < nodes.size(); j++) {
            sum += (nodes[i].used != 0 && i != j && nodes[i].used <= nodes[j].avail);
        }
    }

    return sum;
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<Node> nodes;

    getline(inputStream, textline);
    getline(inputStream, textline);
    while(getline(inputStream, textline)) {
        process_line(textline, nodes);
    }

    return count_viable_pairs(nodes);
}


int main() {
    auto output = process_file();
    cout << "The number of vaild viable is " << output << endl;
}