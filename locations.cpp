#include <iostream>
#include "locations.h"
using namespace std;

inline int Locations::yourCell(Player *p)
{
    p->inventory[0] = "carving knife";
    p->inventory[1] = "Soap";
    p->inventory[2] = "Cell Key";
    int playerChoice;
    cout << "You are currently in your cell. It's a small, dark room with a wooden bed and a small window." << endl;
    cout << "The door is locked from the outside, and there's no way out." << endl;
    cout << "Luckily, the guards accidentally dropped a key in front of your cell." << endl;
    cout << "You have a carving knife, a piece of bread, and a bar of soap in your inventory." << endl;
    cout << "You can use the carving knife to cut the soap into the same shape as the key." << endl
         << endl;
    cout << "What would you like to do?" << endl;
    cout << "\t1. Cut the soap into the same shape as the key." << endl;
    cout << "\t2. Give the key back" << endl;
    cout << "\t3. Use the key to unlock the door." << endl;
    cout << "\t4. Call the guards and give the key back." << endl;
    cout << "\t5. Do nothing." << endl
         << endl;

    cin >> playerChoice;

    while (playerChoice < 1 || playerChoice > 5)
    {
        cout << "Invalid choice. Please try again." << endl;
        cin >> playerChoice;
    }

    while (playerChoice == 5)
    {
        cout << "You decide to do nothing." << endl;
        cout << "What would you like to do now?" << endl;
        cin >> playerChoice;
    }

    if (playerChoice == 1)
    {
        cout << "You use the carving knife to cut the soap into the same shape as the key." << endl;
        cout << "But you have terrible carving skills, and now your soap and carving knife have both been destroyed." << endl;
        p->inventory[1] = "";
        p->inventory[0] = "";
    }
    else if (playerChoice == 2)
    {
        cout << "You decide to give the key back to the guards." << endl;
        cout << "The guards take the key and lock the door again." << endl;
    }
    else if (playerChoice == 3)
    {
        cout << "You use the soap key to unlock the door." << endl;
        cout << "The door opens, and you step out of your cell and enter the dungeon." << endl;
        dungeon(p);
    }
    else
    {
        cout << "You call the guards and give the key back." << endl;
        cout << "The guards take the key and lock the door again." << endl;
        cout << "The End. Thank you for playing!" << endl;
        return 0;
    }

    return 0;
}

int Locations::dungeon(Player *p)
{
    // The creation of the corridors and where they point to were added by ChatGPT (I was very lazy to create the rooms and corridors manually)
    Rooms *corridorA = new Rooms("CorridorA", "Cold stone walls. You hear water dripping.");
    Rooms *corridorB = new Rooms("CorridorB", "A torch flickers. Shadows move strangely.");
    Rooms *corridorC = new Rooms("CorridorC", "Bones on the ground. Something was here.");
    Rooms *stairs = new Rooms("staircase", "You found a staircase leading up!", true);

    // Link exits (each exit points to a different room)
    corridorA->AddExit("Go left", corridorB);
    corridorA->AddExit("Go right", corridorC);

    corridorB->AddExit("Go forward", corridorC);
    corridorB->AddExit("Go back", corridorA);

    // This is the “one exit leads to a staircase” moment:
    corridorC->AddExit("Open the heavy door", stairs);
    corridorC->AddExit("Go back", corridorB);

    cout << "You are currently in the dungeon. You hear eerie noises around you and see movement in dark corners." << endl;
    cout << "You don't know what's in there, but you can't help but feel a sense of unease." << endl
         << endl;

    cout << "Down the long corridor, you see more paths that lead to different areas of the mazelike dungeon." << endl;

    p->current = corridorA;

    while (p->current != nullptr && p->current->roomName != "Entrance")
    {
        p->current->Print();

        int choice = 0;
        cout << "Choose an exit: ";
        cin >> choice;

        int index = choice - 1;

        if (index < 0 || index >= (int)p->current->roomExits.size())
        {
            cout << "Invalid choice.\n";
        }
        else
        {
            Rooms *next = p->current->roomExits[index];
            if (next == nullptr)
            {
                cout << "That exit is blocked.\n";
            }
            else
            {
                p->current = next;
            }
        }
    }

    if (p->current != nullptr && p->current->roomName != "Entrance")
    {
        cout << "You have left the dungeon." << endl;
        cout << "You have reached the first floor of the castle. Now you must sneak past guards and find the key to leave the castle" << endl;
        firstFloor(p);
    }

    delete corridorA;
    delete corridorB;
    delete corridorC;
    delete stairs;

    return 0;
}

int Locations::firstFloor(Player *p)
{
    cout << "You are currently on the first floor of the castle." << endl;
    cout << "You see a guard patrolling the area, and you can hear the sound of footsteps in the distance." << endl;
    cout << "You need to find a way to sneak past the guard and reach the watch tower." << endl
         << endl;

    cout << "What would you like to do?" << endl;
    cout << "\t1. Enter the library." << endl;
    cout << "\t2. Enter the kitchen." << endl;
    cout << "\t3. Enter the armory." << endl;
    cout << "\t4. Use the key to open the door to the watch tower." << endl;
    cout << "\t5. Do nothing." << endl
         << endl;

    int playerChoice;
    cin >> playerChoice;

    while (playerChoice < 1 || playerChoice > 5)
    {
        cout << "Invalid choice. Please try again." << endl;
        cin >> playerChoice;
    }

    while (playerChoice == 5)
    {
        cout << "You decide to do nothing." << endl;
        cout << "What would you like to do now?" << endl;
        cin >> playerChoice;
    }

    if (playerChoice == 1)
    {
        cout << "You enter the library." << endl;
        library(p);
    }
    else if (playerChoice == 2)
    {
        cout << "You enter the kitchen." << endl;
        kitchen(p);
    }
    else if (playerChoice == 3)
    {
        cout << "You enter the armory." << endl;
        armory(p);
    }
    else if (playerChoice == 4)
    {
        cout << "You use the key to open the door to the watch tower." << endl;
        cout << "The door opens, and you step into the watch tower." << endl;
        watchTower(p);
    }
    else
    {
        cout << "You decide to do nothing." << endl;
        cout << "The End. Thank you for playing!" << endl;
        return 0;
    }

    return 0;
}

int Locations::library(Player *p)
{
    cout << "You are currently in the library." << endl;
    cout << "The books are lined up neatly on the shelves, and the air is filled with the scent of old paper." << endl;
    cout << "You see a small window that leads to the outside world, but it's too high to reach." << endl
         << endl;

    cout << "What would you like to do?" << endl;
    cout << "\t1. Look for a book and catch up on some reading." << endl;
    cout << "\t2. Try to climb out of the window." << endl;
    cout << "\t3. Leave the library." << endl;
    cout << "\t4. Enter some of the rooms." << endl;
    cout << "\t5. Do nothing." << endl
         << endl;

    int playerChoice;
    cin >> playerChoice;

    while (playerChoice < 1 || playerChoice > 5)
    {
        cout << "Invalid choice. Please try again." << endl;
        cin >> playerChoice;
    }

    while (playerChoice == 5)
    {
        cout << "You decide to do nothing." << endl;
        cout << "What would you like to do now?" << endl;
        cin >> playerChoice;
    }

    if (playerChoice == 1)
    {
        cout << "You look for a book and catch up on some reading." << endl;
        cout << "After a while, you decide to keep looking around" << endl;
        firstFloor(p);
    }
    else if (playerChoice == 2)
    {
        cout << "You try to climb out of the window." << endl;
        cout << "But the window is too high, and you fall back into the library." << endl;
        cout << "You are now back in the library." << endl;
    }
    else if (playerChoice == 3)
    {
        cout << "You leave the library." << endl;
        firstFloor(p);
    }
    else if (playerChoice == 4)
    {
        Rooms *entrance = new Rooms("Entrance Hall", "A quiet entrance with a big directory sign.");
        Rooms *readingRoom = new Rooms("Reading Room", "Rows of tables, lamps, and people whispering.", true);
        Rooms *shelves = new Rooms("Book Shelves", "Tall shelves. It feels like a maze.");
        Rooms *archive = new Rooms("Archives", "Old documents behind glass. A lockbox sits on a desk.");
        Rooms *cafe = new Rooms("Library Cafe", "Smells like coffee. Someone left food on a table.", true);

        entrance->AddItem("library map");
        readingRoom->AddItem("armory key");
        shelves->AddItem("dusty bookmark");
        archive->AddItem("silver key");
        cafe->AddItem("bread");

        entrance->AddExit("Go to Reading Room", readingRoom);
        entrance->AddExit("Go to Library Cafe", cafe);

        readingRoom->AddExit("Go to Entrance Hall", entrance);
        readingRoom->AddExit("Go to Book Shelves", shelves);
        cafe->AddExit("Go to Entrance Hall", entrance);

        shelves->AddExit("Go to Reading Room", readingRoom);
        shelves->AddExit("Go to Archives", archive);
        archive->AddExit("Go back to Book Shelves", shelves);

        p->current = entrance;

        // made by chatGPT
        bool exited = false;

        while (exited == false)
        {
            if (p->current == nullptr)
            {
                std::cout << "Error: player is not in a room.\n";
                break;
            }

            p->current->Print();

            // NEW: ask to pick up items
            p->current->pickupItems(p);

            int choice = 0;
            cout << "Choose an exit: ";
            cin >> choice;

            int index = choice - 1;

            if (index < 0 || index >= (int)p->current->roomExits.size())
            {
                cout << "Invalid choice.\n";
            }
            else
            {
                Rooms *next = p->current->roomExits[index];

                if (next == nullptr)
                {
                    cout << "That exit is blocked.\n";
                }
                else
                {
                    if (next == entrance)
                    {
                        p->current = next; // optional
                        exited = true;
                    }
                    else
                    {
                        p->current = next;
                    }
                }
            }
        }

        cout << "You have left the library." << endl;
        firstFloor(p);
    }

    return 0;
}
