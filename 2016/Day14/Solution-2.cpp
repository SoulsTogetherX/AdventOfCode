#include <iostream>
#include <format>
#include <iomanip>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

using namespace std;


const string SECERT = "yjdafjpo";
const int PRIMARY_SAME_REQUIREMENT = 3;
const int SECONDARY_SAME_REQUIREMENT = 5;
const int KEY_REQUIREMENT = 64;
const int REPEAT_REQUIREMENT = 2017;
const int DISTANCE_REQUIREMENT = 1000;


void MD5(const char *input, unsigned char md_value[EVP_MAX_MD_SIZE], unsigned int &md_len) {
    EVP_MD_CTX *mdctx;

    mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        perror("EVP_MD_CTX_new error");
        return;
    }
    if (EVP_DigestInit_ex(mdctx, EVP_md5(), NULL) != 1) {
        perror("EVP_DigestInit_ex error");
        EVP_MD_CTX_free(mdctx);
        return;
    }
    if (EVP_DigestUpdate(mdctx, input, strlen(input)) != 1) {
        perror("EVP_DigestUpdate error");
        EVP_MD_CTX_free(mdctx);
        return;
    }
    if (EVP_DigestFinal_ex(mdctx, md_value, &md_len) != 1) {
        perror("EVP_DigestFinal_ex error");
        EVP_MD_CTX_free(mdctx);
        return;
    }

    EVP_MD_CTX_free(mdctx);
}

string format_hex_padded(unsigned int value) {
    ostringstream oss;
    oss << hex << setw(2) << setfill('0') << value;
    return oss.str();
}
string convert_to_hex(unsigned char md_value[EVP_MAX_MD_SIZE], unsigned int md_len) {
    string ret;

    for(int i = 0; i < md_len; i++) {
        ret += format_hex_padded(md_value[i]);
    }

    return ret;
}

bool check_same_primary(string check, char &found) {
    if (check.length() < PRIMARY_SAME_REQUIREMENT || PRIMARY_SAME_REQUIREMENT <= 1) {
        return false;
    }
    int count = 1;

    for(int i = 1; i < check.size(); i++) {
        if (check[i - 1] != check[i]) {
            count = 1;
            continue;
        }

        count++;
        if (count == PRIMARY_SAME_REQUIREMENT) {
            found = check[i];
            return true;
        }
    }
    
    found = '\0';
    return false;
}
bool check_same_secondary(string check, char search) {
    if (check.length() < SECONDARY_SAME_REQUIREMENT) {
        return false;
    }
    int count = 0;

    for(int i = 0; i < check.size(); i++) {
        if (check[i] != search) {
            count = 0;
            continue;
        }

        count++;
        if (count == SECONDARY_SAME_REQUIREMENT) {
            return true;
        }
    }
    return false;
}
void purge_invaild(vector<int> &search, int curr) {
    int len = search.size();

    for(int i = 0; i < len;) {
        auto s = search[i];
        if (s + DISTANCE_REQUIREMENT < curr) {
            len--;
            swap(search[i], search.back());
            search.pop_back();
        } else {
            i++;
        }
    }
}

void find_keys(size_t &i, map<char, vector<int>> &search, vector<int> &keys) {
    string secert;

    char temp;
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;

    for(;; i++) {
        secert = SECERT + to_string(i);

        for (int j = 0; j < REPEAT_REQUIREMENT; j++) {
            MD5(secert.c_str(), md_value, md_len);
            secert = convert_to_hex(md_value, md_len);
        }

        for(auto it : search) {
            if (!it.second.empty() && check_same_secondary(secert, it.first)) {
                purge_invaild(it.second, i);
                cout << "Found secondary match at " << i << " with " << it.first << " in " << secert << " with " << it.second.size() << " matches" << endl;
                
                keys.insert(keys.end(), it.second.begin(), it.second.end());
                it.second.clear();

                if (keys.size() >= KEY_REQUIREMENT) {
                    return;
                }
            }
        }
        if (check_same_primary(secert, temp)) {
            search[temp].push_back(i);
        }
    }

    return;
}

size_t find_keys() {
    size_t i = 0;
    map<char, vector<int>> search;
    vector<int> keys;

    find_keys(i, search, keys);
    sort(keys.begin(), keys.end());
    return keys[KEY_REQUIREMENT - 1];
}

int main() {
    cout << " " << endl;

    auto output = find_keys();
    cout << "The index to create the 64th key is " << output << endl;
}