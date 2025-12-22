#pragma once
#include <string>
#include <iostream>
#include <string>
#include <vector>
#include "enemies.h"
using namespace std;

class Rooms;

class Player
{
public:
    string name = "Hero";
    int score = 0;
    int health = 100;
    int armor = 25;
    int attackPower = 5;

    Rooms *current;
    Player();

    int heal(string item);
    int takeDamage(string damageType);
    int dealDamage(string damageType);

    string inventory[30];
    int pickupItem(string item);
    int displayStats();
    int checkInventory();
    void useItem(string item);
    int fightEnemy(Enemy enemy);
};
