#pragma once
#include <string>
#include <vector>
#include "rooms.h"
using namespace std;

class Items
{
public:
    vector<string> weapons = {"Training stick", "Wooden club", "Dagger", "Sword","Warhammer", "Spear", "Longsword","MythicGreatsword"};
    vector<string> items = {
        "bread",
        "bandage",
        "medkit",
        "cake",
        "healing potion",
        "gems",
        "helmet",
        "chestplate",
        "leggings",
        "boots"};

    int weaponProbability()
    {
        int r = (rand() % 100) + 1; // 1..100

        if (r <= 5){
            return 7;
        }
        if (r <= 20){
            return 6;
        }
        if (r <= 35){
            return 5;
        }
        if (r <= 50){
            return 4;
        }
        if (r <= 65){
            return 3;
        }
        if (r <= 75){
            return 2; 
        }
        if (r <= 90){
            return 1;
        }
        return 0;     
    }

    int itemProbability()
    {
        int r = (rand() % 100) + 1;

        if (r <= 5){
            return 9;
        }
        if (r <= 20){
            return 8; 
        }
        if (r <= 35){
            return 7;
        }
        if (r <= 50){
            return 6;
        }
        if (r <= 65){
            return 5;
        }
        if (r <= 75){
            return 4;
        }
        if (r <= 90){
            return 3;
        }
        if (r <= 95){
            return 2;
        }
        if (r <= 99){
            return 1;
        }
        return 0;     
    }

    void fillRoomWithRandomItems(Rooms *room, const vector<string> &loot, int itemRange)
    {
        int count = (rand() % itemRange) + 1;

        for (int i = 0; i < count; i++)
        {
            int index = rand() % loot.size();
            room->AddItem(loot[index]);
        }
    }

    int getWeaponDamage(string weapon)
    {
        if (weapon == "Training stick")
        {
            return 5;
        }
        else if (weapon == "Wooden club")
        {
            return 7;
        }
        else if (weapon == "Dagger")
        {
            return 9;
        }
        else if (weapon == "Sword")
        {
            return 12;
        }
        else if (weapon == "Warhammer")
        {
            return 15;
        }
        else if (weapon == "Spear")
        {
            return 17;
        }
        else if (weapon == "Longsword")
        {
            return 20;
        }
        else if (weapon == "MythicGreatsword")
        {
            return 25;
        }

        return 0;
    }

    int getArmorDefense(const string &armorPiece)
    {
        if (armorPiece == "helmet")
        {
            return 10;
        }
        else if (armorPiece == "boots")
        {
            return 12;
        }
        else if (armorPiece == "leggings")
        {
            return 18;
        }
        else if (armorPiece == "chestplate")
        {
            return 25;
        }

        return 0;
    }
};