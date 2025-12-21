#include <iostream>
#include <string>
#include <vector>
#include "rooms.h"
#include "player.h"

// Added by ChatGPT
void Rooms::AddExit(const string &label, Rooms *next)
{
    roomItems.push_back(label);
    roomExits.push_back(next);
}

void Rooms::AddItem(string item)
{
    roomItems.push_back(item);
}

void Rooms::Print()
{
    cout << "Room: " << roomName << endl;
    cout << roomDescription << endl;

    cout << "Items here: ";
    if (roomItems.size() == 0)
    {
        cout << "(none)\n";
    }
    else
    {
        cout << "\n";
        for (int i = 0; i < (int)roomItems.size(); i++)
        {
            cout << "  - " << roomItems[i] << "\n";
        }
    }
}

void Rooms::pickupItems(Player *p)
{
    if (roomItems.size() == 0)
    {
        cout << "No items to pick up.\n";
        return;
    }

    cout << "What would you like to pick up? ";
    string itemToPickup;
    getline(cin >> ws, itemToPickup);

    bool found = false;
    for (int i = 0; i < (int)roomItems.size(); i++)
    {
        if (roomItems[i] == itemToPickup)
        {
            p->pickupItem(itemToPickup);
            roomItems.erase(roomItems.begin() + i);
            found = true;
            break;
        }
    }

    if (!found)
        cout << "That item does not exist.\n";
}