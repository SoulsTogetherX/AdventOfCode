#include <iostream>
#include <fstream>

using namespace std;

const int REPEAT_COUNT = 50;
const string INPUT = "1321131112";


string look_and_say(string input) {
    if (input.empty()) return "";

    string ret = "";
    char current = input[0];
    int count = 1;

    for(int i = 1; i < input.size(); i++) {
        if (input[i] == current) {
            count++;
        } else {
            ret += to_string(count) + current;

            count = 1;
            current = input[i];
        }
    }

    return ret + to_string(count) + current;
}


size_t play_game() {
    string current_str = INPUT;

    //cout << current_str << endl;
    for(int i = 0; i < REPEAT_COUNT; i++) {
        current_str = look_and_say(current_str);
        //cout << current_str << endl;
    }

    return current_str.size();
}


int main() {
    cout << " " << endl;

    auto output = play_game();
    cout << "The length of the game's result is " << output << endl;
}