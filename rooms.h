#pragma once

#include <string>
#include <vector>
using namespace std;

class Player;  // forward declaration

class Rooms
{
public:
    string roomName;
    string roomDescription;

    vector<string> roomItems;
    vector<Rooms*> roomExits;
    vector<string> roomChoices;

    bool isExit;

    Rooms(string name, string description, bool exit = false);

    void AddExit(string choice, Rooms* next);
    void AddItem(string item);

    void Print();
    void pickupItems(Player* p);
};