#include <iostream>

using namespace std;

#define ll long long


ll comphended_program() {
    ll a = 1, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0;
	b = 93;
	c = 93;

	if (a != 0) {
		b = b * 100 + 100000;
		c = b + 17000;
	}

	do {
		f = 1;
		d = 2;
		e = 2;
		for (d=2; d*d <= b; d++) {
			if (b % d == 0) {
				f = 0;
				break;
			}
		}
		if (f == 0) {
			h++;
        }
		g = b - c;
		b += 17;
	} while (g != 0); 

    return h;
}

int main() {
    auto output = comphended_program();
    cout << "There are " << output << " composite numbers in range." << endl;
}