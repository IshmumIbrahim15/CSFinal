#include "player.h"
#include "locations.h"
#include <iostream>
using namespace std;

Player::Player() : current(nullptr) {}

int Player::heal(string item)
{
    if (item == "Meat")
    {
        if (health + 5 > 50)
        {
            health = 50;
            return health;
        }
        health += 5;
        return health;
    }
    if (item == "bandage")
    {
        if (health + 5 > 50)
        {
            health = 50;
            return health;
        }
        health += 5;
        return health;
    }
    if (item == "Potion")
    {
        if (health + 10 > 50)
        {
            health = 50;
            return health;
        }
        health += 10;
        return health;
    }
    if (item == "MedKit")
    {
        if (health + 20 > 50)
        {
            health = 50;
            return health;
        }
        health += 20;
        return health;
    }
    return health;
}

int Player::dealDamage(string damageType)
{
    if (damageType == "knife")
    {
        return 10;
    }
    if (damageType == "gun")
    {
        return 20;
    }
    if (damageType == "fists")
    {
        return 5;
    }
    return 0;
}

int Player::takeDamage(string damageType)
{
    if (damageType == "knife")
    {
        health -= 10;
        return health;
    }
    if (damageType == "gun")
    {
        health -= 20;
        return health;
    }
    if (damageType == "fire")
    {
        health -= 5;
        return health;
    }
    return health;
}

int Player::pickupItem(string item)
{
    for (int i = 0; i < 100; i++)
    {
        if (inventory[i] == "")
        {
            inventory[i] = item;
            return 1;
        }
    }
    return 0;
}

int Player::useItem()
{
    string item;
    cout << "Enter the item you want to use: ";
    cin >> item;

    if (item == "Meat" || item == "bandage" || item == "Potion" || item == "MedKit")
    {
        heal(item);
        return 1;
    }
    return 0;
}

int Player::displayStats()
{
    cout << "Name: " << name << endl;
    cout << "Score: " << score << endl;
    cout << "Health: " << health << endl;
    cout << "Armor: " << armor << endl;

    cout << "Inventory: ";
    for (int i = 0; i < 10; i++)
    {
        cout << inventory[i] << ", ";
    }
    cout << endl;
    return 0;
}