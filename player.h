#pragma once
#include <string>
#include <iostream>
using namespace std;

class Rooms; // forward declare (no need to include locations.h here)

class Player
{
public:
    std::string name;
    int score = 0;
    int health = 50;
    int armor = 25;

    Rooms *current;
    Player();

    int heal(std::string item);
    int takeDamage(std::string damageType);
    int dealDamage(std::string damageType);

    std::string inventory[100];
    int pickupItem(std::string item);
    int useItem();
    int displayStats();
};
