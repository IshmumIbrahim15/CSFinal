#include "player.h"
#include "locations.h"
#include "miniGames.h"
#include "items.h"
#include <iostream>
#include <ctime>
#include <limits>
using namespace std;

Items getItems;
Games miniGames;

Player::Player() : current(nullptr) {}

int Player::heal(string item)
{
    if (item == "Bread")
    {
        if (health + 5 > 100)
        {
            health = 50;
            return health;
        }
        health += 5;
        return health;
    }
    if (item == "Meat")
    {
        if (health + 10 > 100)
        {
            health = 100;
            return health;
        }
        health += 10;
        return health;
    }
    if (item == "bandage")
    {
        if (health + 5 > 100)
        {
            health = 100;
            return health;
        }
        health += 5;
        return health;
    }
    if (item == "Potion")
    {
        if (health + 10 > 100)
        {
            health = 100;
            return health;
        }
        {
            health = 50;
            return health;
        }
        health += 10;
        return health;
    }
    if (item == "MedKit")
    {
        if (health + 20 > 100)
        {
            health = 100;
            return health;
        }
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
    return attackPower;
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
    for (int i = 0; i < 30; i++)
    {
        if (inventory[i] == "")
        {
            inventory[i] = item;
            return 1;
        }
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

int Player::checkInventory()
{
    for (int i = 0; i < 30; i++)
    {
        if (inventory[i] != "")
        {
            cout << "\t- " <<inventory[i] << endl;
        }
    }

    cout << "Would you like to use an item? (y/n): ";
    char userChoice;
    cin >> userChoice;

    //ChatGpt
    // eat the rest of the line so future getline works
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    userChoice = (char)tolower(userChoice);

    if (userChoice == 'y')
    {
        cout << "What item would you like to use? ";
        string userItem;
        getline(cin, userItem);  

        useItem(userItem);
    }

    return 0;
}

void Player::useItem(string item)
{
    for (int i = 0; i < 30; i++)
    {
        if (inventory[i] == item)
        {
            if (item == "Meat" || item == "bandage" || item == "Potion" || item == "MedKit")
            {
                heal(item);
                inventory[i] = "";
            }
        }

        if (item == "helmet" || item == "chestplate" || item == "leggings" || item == "boots")
        {
            armor += getItems.getArmorDefense(item);
            inventory[i] = "";
        }

        for (int j = 0; j < getItems.weapons.size(); j++)
        {
            if (item == getItems.weapons[j])
            {
                if (attackPower > getItems.getWeaponDamage(item)){
                    cout << "You already have a better weapon." << endl;
                }
                attackPower = getItems.getWeaponDamage(item);
                inventory[i] = "";
            }
        }
    }
    cout << "That item can't be used!" << endl;
}

int Player::fightEnemy(Enemy enemy)
{
    cout << "You have encountered a " << enemy.enemyName << "!" << endl;
    cout << "You must play minigames to defeat it." << endl;
    cout << endl;

    char lookAtInventory;
    srand(time(nullptr));
    int gameRes;

    while (health > 0 && enemy.enemyHealth > 0)
    {
        cout << "YOUR STATS: "<< endl;
        displayStats();

        cout << "\nENEMY STATS: " << endl;
        enemy.displayEnemyInfo();

        cout << "Would you like to check your inventory? (y/n): " << endl;
        cin >> lookAtInventory;
        if(lookAtInventory == 'y'){
            checkInventory();
        }

        int gameRandomizer = rand() % 3;
        if (gameRandomizer == 0)
        {
            cout << "You must play the rock paper scissors minigame to defeat the enemy." << endl;
            gameRes = miniGames.rockPaperScissors();
            if( gameRes == 1){
                enemy.enemyHealth -= attackPower;
                cout << "You have dealt " << attackPower << " damage to the " << enemy.enemyName << "!" << endl;
            }
            else if(gameRes == 2){
                health -= enemy.enemyDamage;
                cout << "The " << enemy.enemyName << " has dealt " << enemy.enemyDamage << " damage to you!" << endl;
            }
            else if(gameRes == 0){
                enemy.enemyHealth -= 5;
                health -= 5;
                cout << "You and the " << enemy.enemyName << " have tied." << endl;
            }
        }

        else if (gameRandomizer == 1)        {
            gameRes = miniGames.guessTheNumber();
            cout << "You must play the guessTheNumber minigame to defeat the enemy." << endl;
            if (gameRes == 1)
            {
                enemy.enemyHealth -= attackPower;
                cout << "You have dealt " << attackPower << " damage to the " << enemy.enemyName << "!" << endl;
            }
            else
            {
                health -= enemy.enemyDamage;
                cout << "The " << enemy.enemyName << " has dealt " << enemy.enemyDamage << " damage to you!" << endl;
            }
        }

        else if (gameRandomizer == 2)
        {
            cout << "You must play the tictactoe minigame to defeat the enemy." << endl;
            gameRes = miniGames.tictactoe();
            if (gameRes == 1)
            {
                enemy.enemyHealth -= attackPower;
                cout << "You have dealt " << attackPower << " damage to the " << enemy.enemyName << "!" << endl;
            }
            else if (gameRes == 2)
            {
                health -= enemy.enemyDamage;
                cout << "The " << enemy.enemyName << " has dealt " << enemy.enemyDamage << " damage to you!" << endl;
            }
            else if (gameRes == 0)
            {
                enemy.enemyHealth -= 5;
                health -= 5;
                cout << "You and the " << enemy.enemyName << " have tied." << endl;
            }
        }
    }
    if (enemy.enemyHealth <= 0)
    {
        cout << "You have defeated the " << enemy.enemyName << "!" << endl;
        for(unsigned int i = 0; i < enemy.enemyItems.size(); i++){
            cout << "You recieved " << enemy.enemyItems[i] << "!" << endl;
            pickupItem(enemy.enemyItems[i]);
        }
        return 1;
    }
    else
    {
        cout << "You have been defeated by the " << enemy.enemyName << "!" << endl;
        return 0;
    }
}