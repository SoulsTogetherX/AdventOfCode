#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const int HARD_MODE_DEC = 1;

const int MAGE_HP = 50;
const int MAGE_MP = 500;


struct Simulation {
    enum SPELL_TYPE {
        MAGIC_MISSILE = 0,
        DRAIN = 1,
        SHEILD = 2,
        POISON = 3,
        RECHARGE = 4,
        ALL = 5
    };

    const int MAGIC_MISSILE_DAMAGE = 4;
    const int MAGIC_MISSILE_COST = 53;

    const int DRAIN_DAMAGE = 2;
    const int DRAIN_HP_RECOVER = 2;
    const int DRAIN_COST = 73;

    const int SHEILD_DURATION = 6;
    const int SHEILD_DEFENCE = 7;
    const int SHEILD_COST = 113;

    const int POISON_DURATION = 6;
    const int POISON_DAMAGE = 3;
    const int POISON_COST = 173;

    const int RECHARGE_DURATION = 5;
    const int RECHARGE_MP_RECOVER = 101;
    const int RECHARGE_COST = 229;


    int boss_hp = 0, boss_atk = 0;
    int mage_hp = 0, mage_mp = 0;

    int sheild_d, poison_d, recharge_d;


    Simulation() {
        sheild_d = 0; poison_d = 0; recharge_d = 0;
    }
    void set_boss_stats(int b_hp, int b_atk) {
        boss_hp = b_hp;
        boss_atk = b_atk;
    }
    void set_mage_stats(int m_hp, int m_mp) {
        mage_hp = m_hp;
        mage_mp = m_mp;
    }


    void apply_status() {
        if (sheild_d > 0) {
            sheild_d -= 1;
        }
        if (poison_d > 0) {
            poison_d -= 1;
            boss_hp -= POISON_DAMAGE;
        }
        if (recharge_d > 0) {
            recharge_d -= 1;
            mage_mp += RECHARGE_MP_RECOVER;
        }
    }
    bool can_cast_spell(SPELL_TYPE type) {
        switch (type) {
            case MAGIC_MISSILE:
                return mage_mp >= MAGIC_MISSILE_COST;
            case DRAIN:
                return mage_mp >= DRAIN_COST;
            case SHEILD:
                return mage_mp >= SHEILD_COST && sheild_d == 0;
            case POISON:
                return mage_mp >= POISON_COST && poison_d == 0;
            case RECHARGE:
                return mage_mp >= RECHARGE_COST && recharge_d == 0;
        }
    }
    int cast_spell(SPELL_TYPE type) {
        switch (type) {
            case MAGIC_MISSILE:
                mage_mp -= MAGIC_MISSILE_COST;
                boss_hp -= MAGIC_MISSILE_DAMAGE;
                return MAGIC_MISSILE_COST;
            case DRAIN:
                mage_mp -= DRAIN_COST;
                mage_hp += DRAIN_HP_RECOVER;
                boss_hp -= DRAIN_DAMAGE;
                return DRAIN_COST;
            case SHEILD:
                mage_mp -= SHEILD_COST;
                sheild_d = SHEILD_DURATION;
                return SHEILD_COST;
            case POISON:
                mage_mp -= POISON_COST;
                poison_d = POISON_DURATION;
                return POISON_COST;
            case RECHARGE:
                mage_mp -= RECHARGE_COST;
                recharge_d = RECHARGE_DURATION;
                return RECHARGE_COST;
        }
        return 0;
    }

    
    void sim_boss_turn() {
        mage_hp -= max(boss_atk - ((sheild_d > 0) ? SHEILD_DEFENCE : 0), 1);
    }

    bool is_mage_dead() {
        return mage_hp <= 0;
    }
    bool is_boss_dead() {
        return boss_hp <= 0;
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

void parse_enemy(ifstream &inputStream, Simulation &Sim) {
    string temp;
    stringstream ss;
    int hp, atk;

    getline(inputStream, temp);
    ss = stringstream(temp);
    ss >> temp >> temp >> hp;

    getline(inputStream, temp);
    ss = stringstream(temp);
    ss >> temp >> atk;

    Sim.set_boss_stats(hp, atk);
}

void brute_helper(Simulation sim, Simulation::SPELL_TYPE type, size_t curr_mp, size_t &min_mp) {
    // Player Turn (Second Half)
    curr_mp += sim.cast_spell(type);
    if (curr_mp >= min_mp) {
        return;
    }
    if (sim.is_boss_dead()) {
        min_mp = curr_mp;
        return;
    }
    
    // Boss Turn
    sim.apply_status();
    if (sim.is_boss_dead()) {
        min_mp = curr_mp;
        return;
    }

    sim.sim_boss_turn();
    
    // Player Turn (First Half)
    sim.mage_hp -= 1;
    if (sim.is_mage_dead()) {
        return;
    }

    sim.apply_status();
    if (sim.is_boss_dead()) {
        min_mp = curr_mp;
        return;
    }

        // Makes Spell Decisiton
    for(int m = 0; m < Simulation::ALL; m++) {
        auto type = (Simulation::SPELL_TYPE)m;

        if (!sim.can_cast_spell(type)) continue;

        brute_helper(sim, (Simulation::SPELL_TYPE)type, curr_mp, min_mp);
    }
}
size_t brute_force(Simulation sim) {
    size_t min_mp = -1;

    sim.mage_hp -= 1;
    for(int m = 0; m < Simulation::ALL; m++) {
        auto type = (Simulation::SPELL_TYPE)m;

        if (!sim.can_cast_spell(type)) continue;

        brute_helper(sim, (Simulation::SPELL_TYPE)type, 0, min_mp);
    }

    return min_mp;
}

size_t process_file() {
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    Simulation sim;
    parse_enemy(inputStream, sim);
    sim.set_mage_stats(MAGE_HP, MAGE_MP);

    return brute_force(sim);
}


int main() {
    auto output = process_file();
    cout << "The min mana needed to defeat the boss is " << output << endl;
}