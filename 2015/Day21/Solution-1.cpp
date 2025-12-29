#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


enum ITEM_TYPE {
    WEAPON = 0b0001,
    ARMOUR = 0b0010,
    RING_1 = 0b0100,
    RING_2 = 0b1000,
    RINGS = 0b1100,
    ALL = 0b1111
};

struct Entity {
    int hp, atk, def;
    Entity() {hp = 0; atk = 0; def = 0;}
    Entity(int hp, int atk, int def) : hp(hp), atk(atk), def(def) {}

    bool operator <= (Entity &e) {
        int delta_p = max(atk - e.def, 1);
        int delta_e = max(e.atk - def, 1);

        return hp * delta_p <= e.hp * delta_e;
    }
};

struct Item {
    string name;
    int price, atk_delta, def_delta;

    Item() {price = price; atk_delta = atk_delta; def_delta = def_delta;}
    Item(int price, int atk_delta, int def_delta, string name) : price(price), atk_delta(atk_delta), def_delta(def_delta), name(name) {}

    bool operator<(Item &i) {
        return price < i.price;
    }
};


vector<Item> weapons = {
    Item(8, 4, 0, "Dagger"),
    Item(10, 5, 0, "Shortsword"),
    Item(25, 6, 0, "Warhammer"),
    Item(40, 7, 0, "Longsword"),
    Item(74, 8, 0, "Greataxe")
};
vector<Item> armors = {
    Item(13, 0, 1, "Leather"),
    Item(31, 0, 2, "Chainmail"),
    Item(53, 0, 3, "Splintmail"),
    Item(75, 0, 4, "Bandedmail"),
    Item(102, 0, 5, "Platemail")
};
vector<Item> rings = {
    Item(25, 1, 0, "Damage +1"),
    Item(50, 2, 0, "Damage +2"),
    Item(100, 3, 0, "Damage +3"),
    Item(20, 0, 1, "Defense +1"),
    Item(40, 0, 2, "Defense +2"),
    Item(80, 0, 3, "Defense +3")
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


Entity parse_enemy(ifstream &inputStream) {
    string temp;
    stringstream ss;
    int hp, atk, def;

    getline(inputStream, temp);
    ss = stringstream(temp);
    ss >> temp >> temp >> hp;

    getline(inputStream, temp);
    ss = stringstream(temp);
    ss >> temp >> atk;

    getline(inputStream, temp);
    ss = stringstream(temp);
    ss >> temp >> def;

    return Entity(hp, atk, def);
}

void brute_helper(
    Entity enemy,
    Entity player,
    int r_idx,
    char type_tracker,
    size_t curr_price,
    size_t &min_price
) {
    if (curr_price >= min_price) {
        return;
    }
    if (enemy <= player) {
        min_price = curr_price;
        return;
    }

    if (!(type_tracker & WEAPON)) {
        type_tracker |= WEAPON;

        for(int i = 0; i < weapons.size(); i++) {
            auto item = weapons[i];

            brute_helper(
                enemy,
                Entity(player.hp, player.atk + item.atk_delta, player.def + item.def_delta),
                r_idx,
                type_tracker,
                curr_price + item.price,
                min_price
            );
        }
        return;
    }
    if (!(type_tracker & ARMOUR)) {
        type_tracker |= ARMOUR;

        // No armour
        brute_helper(enemy, player, r_idx, type_tracker, curr_price, min_price);
        
        for(int i = 0; i < armors.size(); i++) {
            auto item = armors[i];

            brute_helper(
                enemy,
                Entity(player.hp, player.atk + item.atk_delta, player.def + item.def_delta),
                r_idx,
                type_tracker,
                curr_price + item.price,
                min_price
            );
        }
        return;
    }
    if ((type_tracker & RINGS) < RINGS) {
        if (type_tracker & RING_1) {
            type_tracker |= RINGS;
        } else {
            type_tracker |= RING_1;
        }

        for(int i = r_idx; i < rings.size(); i++) {
            auto item = rings[i];

            brute_helper(
                enemy,
                Entity(player.hp, player.atk + item.atk_delta, player.def + item.def_delta),
                i + 1,
                type_tracker,
                curr_price + item.price,
                min_price
            );
        }
        return;
    }
}
size_t brute_force(Entity enemy, Entity player) {
    size_t min_price = -1;

    brute_helper(enemy, player, 0, 0, 0, min_price);

    return min_price;
}

size_t process_file() {
    ifstream inputStream;
    inputStream = open_file(FILE_NAME);

    Entity enemy = parse_enemy(inputStream);
    Entity player = Entity(100, 0, 0);

    return brute_force(enemy, player);
}


int main() {
    auto output = process_file();
    cout << "The min price is " << output << endl;
}