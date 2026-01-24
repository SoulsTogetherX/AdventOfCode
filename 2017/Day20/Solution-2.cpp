#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Point3D.h"

using namespace std;


const int SIM_STEPS = 10000; // Brute Forcing this because...whatever.


struct Particle {
    Point3D<int> position, velocity, acceleration;
    
    void simulate() {
        velocity += acceleration;
        position += velocity;
    }
    bool operator != (const Particle& p) const {
        return position != p.position;
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

int simulate(vector<Particle> particles) {
    vector<Particle> new_particles;
    for(int i = 0; i < SIM_STEPS; i++) {
        for (auto it = particles.begin(); it != particles.end(); it++) {
            (*it).simulate();
        }
        
        new_particles.clear();
        for (auto it = particles.begin(); it != particles.end(); it++) {
            if ((it == particles.begin() || *it != *(it - 1)) && (it + 1 == particles.end() || *it != *(it + 1))) {
                new_particles.push_back(*it);
            }
        }
        particles = new_particles;
    }
    return particles.size();
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
    return simulate(particles);
}


int main() {
    auto output = process_file();
    cout << "The remaining number of particles is " << output << endl;
}