#include <iostream>
#include <format>
#include <iomanip>
#include <sstream>

#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>


#define BUFF_SIZE 4096

using namespace std;

const string SECERT = "bgvyzdsv";
const int ZERO_REQUIREMENT = 5;


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
    oss << hex << uppercase << setw(2) << setfill('0') << value;
    return oss.str();
}
string convert_to_hex(unsigned char md_value[EVP_MAX_MD_SIZE], unsigned int md_len) {
    string ret;

    for(int i = 0; i < md_len; i++) {
        ret += format_hex_padded(md_value[i]);
    }

    return ret;
}
bool check_zeros(string check) {
    if (check.length() < ZERO_REQUIREMENT) return false;

    for(int i = 0; i < ZERO_REQUIREMENT; i++) {
        if (check[i] != '0') return false;
    }

    return true;
}

size_t find_lowest_five_zero() {
    string secert;

    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;

    for(size_t i = 0;; i++) {
        secert = SECERT + to_string(i);

        MD5(secert.c_str(), md_value, md_len);
        if (md_len >= ZERO_REQUIREMENT && check_zeros(convert_to_hex(md_value, md_len))) {
            return i;
        }

        if (i % 10000 == 0 && i > 0) {
            printf("%d to %d checked.\n", i - 10000, i);
        }
    }

    return -1;
}

int main() {
    cout << " " << endl;

    auto output = find_lowest_five_zero();
    cout << "The lowest addon to create a 5 zero MD5 hash is " << output << endl;
}