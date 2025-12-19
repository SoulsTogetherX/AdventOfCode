#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>

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


void parse_line(string textline, unordered_map<string, unordered_map<string, int>> &distance_memo) {
    stringstream ss(textline);
    string loc1, loc2, temp;
    int distance;

    ss >> loc1 >> temp >> loc2 >> temp >> distance;

    distance_memo[loc1][loc2] = distance;
    distance_memo[loc2][loc1] = distance;
}
void simply_distances_recsurive(
    unordered_map<string, unordered_map<string, int>> distance_memo,
    string curr,
    size_t &min_distance,
    size_t distance
) {
    //cout << distance << " " << curr << endl;
    if (min_distance < distance) return;
    if (distance_memo.size() == 1) {
        min_distance = distance;
        return;
    }

    unordered_map<string, int> memo = distance_memo[curr];
    distance_memo.erase(curr);

    for(auto loc_memo : distance_memo) {
        distance_memo[loc_memo.first].erase(curr);
    }
    for(auto loc : memo) {
        simply_distances_recsurive(distance_memo, loc.first, min_distance, distance + loc.second);
    }
}
size_t simply_distances(unordered_map<string, unordered_map<string, int>> distance_memo) {
    size_t min_distance = -1;
    
    for(auto loc : distance_memo) {
        simply_distances_recsurive(distance_memo, loc.first, min_distance, 0);
        //cout << endl;
    }

    return min_distance;
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    unordered_map<string, unordered_map<string, int>> distance_memo;
    while(getline(inputStream, textline)) {
        parse_line(textline, distance_memo);
    }

    return simply_distances(distance_memo);
}


int main() {
    auto output = process_file();
    cout << "The shortest route is " << output << endl;
}