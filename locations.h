#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "rooms.h"
#include "player.h"
using namespace std;


class Locations{
    public:
        int yourCell(Player *p);
        int dungeon(Player *p);
        int firstFloor(Player *p);
        int library(Player* p);
        int watchTower(Player *p);
        int kitchen(Player *p);
        int armory(Player *p);
        int hospital(Player *p);
        int bathroom(Player *p);
        int shower(Player *p);
        int bedroom1(Player *p);
        int bedroom2(Player *p);
        int kingsRoom(Player *p);
        int balcony(Player *p);
};