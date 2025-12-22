#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "items.h"
using namespace std;

extern Items createItems; 

class Enemy
{
public:
    int enemyHealth;
    int enemyDamage;
    string enemyName;
    string description;
    vector<string> enemyItems;

    Enemy();
    Enemy(int health, int damage, string name, vector<string> items, string enemyDescription);

    void displayEnemyInfo();
    void takeDamage(int damage);

    void dropItems();
};