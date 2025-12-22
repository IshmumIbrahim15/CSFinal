#include "enemies.h"
#include "ascii.h"

Items createItems;

Enemy::Enemy()
{
    enemyHealth = 0;
    enemyDamage = 0;
    enemyName = "";
    description = "";
}

Enemy::Enemy(int health, int damage, string name, vector<string> items, string enemyDescription)
{
    enemyHealth = health;
    enemyDamage = damage;
    enemyName = name;
    description = enemyDescription;
    enemyItems = items;
}

void Enemy::displayEnemyInfo()
{
    cout << "Enemy Name: " << enemyName << endl;
    cout << "Description: " << description << endl;
    cout << "Health: " << enemyHealth << endl;
    cout << "Damage: " << enemyDamage << endl;
    cout << "Items: ";
    for (string item : enemyItems)
    {
        cout << item << " ";
    }
    cout << endl;
}

void Enemy::takeDamage(int damage)
{
    enemyHealth -= damage;
    if (enemyHealth < 0)
    {
        enemyHealth = 0;
    }
}

void Enemy::dropItems()
{
    cout << "The enemy dropped the following items:\n";
    int itemCount = (rand() % 5) + 1;

    for (int i = 0; i < itemCount; i++)
    {
        int index = rand() % createItems.items.size();
        string dropped = createItems.items[index];
        cout << "  - " << dropped << "\n";
        enemyItems.push_back(dropped);
    }
    cout << endl;
}
