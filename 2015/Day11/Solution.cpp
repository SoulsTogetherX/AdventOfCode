#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

const string START_PASSWORD = "hepxxyzz";


void remove_wrong(string &str) {
    for(int i = 0; i < str.size(); i++) {
        if (str[i] == 'i' || str[i] == 'o' || str[i] == 'l') {
            str[i]++;
        }
    }
}
void increment_password(string &str) {
    int i = str.size() - 1;

    while(i >= 0) {
        if (str[i] != 'z') {
            str[i]++;
            if (str[i] == 'i' || str[i] == 'o' || str[i] == 'l') {
                str[i]++;
            }
            break;
        }
        str[i] = 'a';
        i--;
    }
}
bool vaild_password(string &str) {
    regex reg1(".*(.)\\1.*(.)\\2.*");
    regex reg2(".*(i|o|l).*");
    regex reg3(".*(abc|bcd|cde|def|efg|fgh|ghi|hij|ijk|jkl|klm|lmn|mno|nop|opq|pqr|qrs|rst|stu|tuv|uvw|vwx|wxy|xyz).*");

    return regex_match(str, reg1) && !regex_match(str, reg2) && regex_match(str, reg3);
}

string advance_password(string start) {
    size_t count = 0;

    remove_wrong(start);
    do {
        increment_password(start);
        if (count % 2400 == 0) {
            cout << "Checked: " << start << endl;
        }
        count++;
    } while(!vaild_password(start));

    return start;
}

int main() {
    auto output = advance_password(START_PASSWORD);
    cout << "The next password should be " << output << endl;
}