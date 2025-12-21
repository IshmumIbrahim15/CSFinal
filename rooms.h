#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Player;

class Rooms
{
public:
    string roomName;
    string roomDescription;
    vector<string> roomItems;
    vector<Rooms *> roomExits;
    void AddExit(const string &label, Rooms *next);
    void AddItem(string item);
    void Print();
    void pickupItems(Player *p);
    

    // Added by ChatGPT
    Rooms(string name, string description, bool exit = false)
    {
        roomName = name;
        roomDescription = description;
    }
};