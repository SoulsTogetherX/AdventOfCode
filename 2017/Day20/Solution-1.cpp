#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Point3D.h"

using namespace std;


struct Particle {
    Point3D<int> position, velocity, acceleration;
    int index;

    bool operator < (const Particle& p) const {
        int manh_self, manh_other;

        manh_self = acceleration.manhattan_distance();
        manh_other = p.acceleration.manhattan_distance();
        if (manh_self != manh_other) {
            return manh_self < manh_other;
        }

        manh_self = velocity.manhattan_distance();
        manh_other = p.velocity.manhattan_distance();
        if (manh_self != manh_other) {
            return manh_self < manh_other;
        }

        manh_self = position.manhattan_distance();
        manh_other = p.position.manhattan_distance();
        if (manh_self != manh_other) {
            return manh_self < manh_other;
        }

        return false;
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

Point3D<int> parse_coord(stringstream &ss) {
    int x, y, z;

    ss.ignore(1);
    ss >> x;
    ss.ignore(1);
    ss >> y;
    ss.ignore(1);
    ss >> z;
    ss.ignore(1);

    return Point3D<int>(x, y, z);
}
void process_line(const string &textline, vector<Particle> &particles) {
    stringstream ss(textline);
    Particle particle;
    string temp_s;

    ss.ignore(2);
    particle.position = parse_coord(ss);
    ss.ignore(4);
    particle.velocity = parse_coord(ss);
    ss.ignore(4);
    particle.acceleration = parse_coord(ss);

    particle.index = particles.size();
    particles.push_back(particle);
}

size_t process_file() {
    string textline;
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    vector<Particle> particles;
    while(getline(inputStream, textline)) {
        process_line(textline, particles);
    }

    sort(particles.begin(), particles.end());
    return particles[0].index;
}


int main() {
    auto output = process_file();
    cout << "The particle that will be closest to <0,0,0> long term is " << output << endl;
}