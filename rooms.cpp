#include <iostream>
#include <string>
#include <vector>
#include "rooms.h"
#include "player.h"
using namespace std;

Rooms::Rooms(string name, string description, bool exit)
{
    roomName = name;
    roomDescription = description;
}

// Added by ChatGPT
void Rooms::AddExit(string choice, Rooms *next)
{
    roomChoices.push_back(choice);
    roomExits.push_back(next);
}

void Rooms::AddItem(string item)
{
    roomItems.push_back(item);
}

void Rooms::Print()
{
    cout << "<=====#=====#======#=======#=====#=====#=====#=====#=====>\n";
    cout << "\nRoom: " << roomName << endl;
    cout << roomDescription << endl;
    cout << "Exits: ";
    if (roomChoices.size() == 0)
    {
        cout << "(none)\n";
    }
    else
    {
        for (int i = 0; i < (int)roomChoices.size(); i++)
        {
            cout << roomChoices[i];
            if (i < (int)roomChoices.size() - 1)
                cout << ", ";
        }
        cout << "\n";
    }

    cout << "Items here: ";
    if (roomItems.size() == 0)
    {
        cout << "\t(none)\n";
    }
    else
    {
        cout << "\t";
        for (int i = 0; i < (int)roomItems.size(); i++)
        {
            cout << roomItems[i] << ", ";
        }
        cout << "\n";
    }

    cout << "\n<=====#=====#======#=======#=====#=====#=====#=====#=====>\n";
}

void Rooms::pickupItems(Player *p)
{
    if (roomItems.size() == 0)
    {
        cout << "\tNo items to pick up.\n";
        return;
    }

    cout << "\nWhat would you like to pick up? (type 'done' when you are finished) \n" << endl;
    string itemToPickup;

    while(roomItems.size() != 0 && itemToPickup != "done"){
        cout << "\t";
        getline(cin >> ws, itemToPickup);

        bool found = false;
        for (int i = 0; i < roomItems.size(); i++){
            if (itemToPickup == roomItems[i])
            {
                cout << "\t";
                p->pickupItem(roomItems[i]);
                roomItems.erase(roomItems.begin() + i);
                cout << "\nYou picked up the " << itemToPickup << ".\n";
                found = true;
                break;
            }
            else{
                found = false;
            }
        }
        if (!found && itemToPickup != "done")
        {
            cout << "That item is not in this room.\n";
        }
        if (roomItems.size() == 0){
            cout << "You have picked up all the items in this room.\n\n";
            break;
        }
    }
}