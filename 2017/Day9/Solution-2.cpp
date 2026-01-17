#include <iostream>
#include <fstream>
#include <vector>

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


int parse_garbage(int &idx, const string &textline) {
    int total = 0;

    if (textline[idx] != '<') {
        cout << "Debug 1 - Invaild character '" << textline[idx] << "' at " << idx << "." << endl;
        exit(1);
    }
    idx++;

    while(textline[idx] != '>') {
        if (textline[idx] == '!') {
            idx += 2;
            continue;
        }
        idx++;
        total++;
    }
    idx++;

    return total;
}
int parse_group(int &idx, const string &textline) {
    int total = 0;

    if (textline[idx] != '{') {
        cout << "Debug 2 - Invaild character '" << textline[idx] << "' at " << idx << "." << endl;
        exit(1);
    }
    idx++;

    while(textline[idx] != '}') {
        if (textline[idx] == '{') {
            total += parse_group(idx, textline);
        } else if (textline[idx] == '<') {
            total += parse_garbage(idx, textline);
        } else {
            cout << "Debug 3 - Invaild character '" << textline[idx] << "' at " << idx << "." << endl;
            exit(1);
        }

        if (textline[idx] == '}') {
            break;
        } else if (textline[idx] == ',') {
            idx++;
            continue;
        }

        cout << "Debug 4 - Invaild character '" << textline[idx] << "' at " << idx << "." << endl;
        exit(1);
    }

    idx++;
    return total;
}
int parse_line(const string &textline) {
    int idx = 0;
    if (textline[idx] == '{') {
        return parse_group(idx, textline);
    }
    if (textline[idx] == '<') {
        return parse_garbage(idx, textline);
    }
    return 0;
}


size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    getline(inputStream, textline);
    return parse_line(textline);
}


int main() {
    auto output = process_file();
    cout << "The number of no-canceled garbage characters is " << output << endl;
}