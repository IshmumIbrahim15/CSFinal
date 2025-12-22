#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include "locations.h"
#include "items.h"
#include "ascii.h"
#include "enemies.h"
using namespace std;

Items itemGenerator;
Ascii picture;

int Locations::yourCell(Player &p)
{
    p.inventory[0] = "carving knife";
    p.inventory[1] = "Soap";
    p.inventory[2] = "Cell Key";
    int playerChoice;

    this_thread::sleep_for(chrono::seconds(1));
    cout << "You are currently in your cell. It's a small, dark room with a wooden bed and a small window." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "The door is locked from the outside, and there's no way out." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Luckily, the guards accidentally dropped a key in front of your cell." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You have a carving knife, a piece of bread, and a bar of soap in your inventory." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You can use the carving knife to cut the soap into the same shape as the key." << endl
         << endl;

    cout << "What would you like to do?" << endl;
    cout << "\t1. Cut the soap into the same shape as the key." << endl;
    cout << "\t2. Call the guards and give the key back." << endl;
    cout << "\t3. Use the key to unlock the door." << endl;
    cout << "\t4. Do nothing." << endl
         << endl;

    cin >> playerChoice;

    if(playerChoice == 9){
        p.checkInventory();
        cout << "What else would you like to do?" << endl;
        cin >> playerChoice;
    }

    while (playerChoice != 3)
    {

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
            this_thread::sleep_for(chrono::seconds(1));
            cout << "\nYou use the carving knife to cut the soap into the same shape as the key." << endl;
            this_thread::sleep_for(chrono::seconds(1));
            cout << "But you have terrible carving skills, and now your soap and carving knife have both been destroyed." << endl;
            p.inventory[1] = "";
            p.inventory[0] = "";
        }
        else if (playerChoice == 2)
        {
            this_thread::sleep_for(chrono::seconds(1));
            cout << "You decide to give the key back to the guards." << endl;
            this_thread::sleep_for(chrono::seconds(1));
            cout << "The guards take the key and lock the door again." << endl;
            this_thread::sleep_for(chrono::seconds(1));
            cout << "The end. Thank you for playing!" << endl;
            return 0;
        }
        cout << "\nWhat would you like to do now?" << endl;
        cin >> playerChoice;
    }

    cout << "You use the key to unlock the door and step out of your cell.\n"
         << endl;
    return dungeon(p);
}

//Made by ChatGpt
vector<Enemy> CreateDungeonEnemies()
{
    vector<Enemy> enemies;

    enemies.push_back(Enemy(
        15, 4,
        "Giant Rat",
        {"bread"},
        "A starving sewer rat with red eyes. It bites anything that moves."));

    enemies.push_back(Enemy(
        22, 6,
        "Cave Spider",
        {"bandage"},
        "A spider the size of a plate. It drops from the ceiling without warning."));

    enemies.push_back(Enemy(
        28, 7,
        "Skeleton Guard",
        {"helmet"},
        "A cursed guard whose armor still clatters as it walks."));

    enemies.push_back(Enemy(
        35, 9,
        "Goblin Jailer",
        {"medkit"},
        "A cruel goblin with a ring of keys and a nasty temper."));

    enemies.push_back(Enemy(
        40, 10,
        "Dungeon Brute",
        {"boots"},
        "A huge prisoner who escaped his chains and now attacks everyone."));

    enemies.push_back(Enemy(
        50, 12,
        "Warden's Hound",
        {"healing potion"},
        "A trained beast that hunts escapees by smell."));

    return enemies;
}

int Locations::dungeon(Player &p)
{
    srand(time(nullptr));
    int enemyRandomizer = rand() % 6;
    vector<Enemy> dungeonEnemies = CreateDungeonEnemies();
    //vector created by ChatGPT
    vector<void (Ascii::*)()> enemyImages = {
        &Ascii::printRat,
        &Ascii::printSpider,
        &Ascii::printSkeleton,
        &Ascii::printGoblin,
        &Ascii::printDefault,
        &Ascii::printHound
    };
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

    this_thread::sleep_for(chrono::seconds(1));
    cout << "You are currently in the dungeon. You hear eerie noises around you and see movement in dark corners." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You don't know what's in there, but you can't help but feel a sense of unease." << endl
         << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Down the long corridor, you see more paths that lead to different areas of the mazelike dungeon." << endl;

    p.current = corridorA;

    //This while loop will keep looking until you find the exit, in this case the exit is the staircase
    while (p.current != nullptr && p.current->roomName != "staircase")
    {
        p.current->Print();

        int choice = 0;
        cout << "Choose an exit (1 for first exit, 2 for second, etc.): ";
        cin >> choice;

        int index = choice - 1;

        if (index < 0 || index >= (int)p.current->roomExits.size())
        {
            cout << "Invalid choice.\n";
        }
        else
        {
            Rooms *next = p.current->roomExits[index];
            if (next == nullptr)
            {
                cout << "That exit is blocked.\n";
            }
            else
            {
                (picture.*enemyImages[enemyRandomizer])();
                p.fightEnemy(dungeonEnemies[enemyRandomizer]);
                p.current = next;
            }
        }
    }

    delete corridorA;
    delete corridorB;
    delete corridorC;
    delete stairs;

    this_thread::sleep_for(chrono::seconds(1));
    cout << "You reach the staircase and climb up to the first floor of the castle.\n"
         << endl;
    return firstFloor(p);
}

int Locations::firstFloor(Player &p)
{
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You are currently on the first floor of the castle." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You see a guard patrolling the area, and you can hear the sound of footsteps in the distance." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You need to fight the guard to go to the other rooms." << endl
         << endl;
    this_thread::sleep_for(chrono::seconds(1));

    cout << "What would you like to do?" << endl;
    cout << "\t1. Enter the library." << endl;
    cout << "\t2. Enter the kitchen." << endl;
    cout << "\t3. Enter the armory." << endl;
    cout << "\t4. Enter the bathroom." << endl;
    cout << "\t5. Use the key to open the door to the watch tower." << endl;
    cout << "\t6. Go up to the second floor." << endl;
    cout << "\t7. Do nothing." << endl
         << endl;

    int playerChoice;
    cin >> playerChoice;

    //allows you to check your inventory
    if(playerChoice == 9){
        p.checkInventory();
        cout << "What else would you like to do?" << endl;
        cin >> playerChoice;
    }

    //fighting sequence
    Enemy knight(
        35, 8,
        "Knight",
        {"helmet", "Sword"},
        "A disciplined castle knight in steel armor. Tough, trained, and relentless."
    );

    picture.printKnight();
    p.fightEnemy(knight);

    while (playerChoice < 1 || playerChoice > 7)
    {
        cout << "Invalid choice. Please try again." << endl;
        cin >> playerChoice;
    }

    while (playerChoice == 7)
    {
        cout << "You decide to do nothing." << endl;
        cout << "What would you like to do now?" << endl;
        cin >> playerChoice;
    }

    if (playerChoice == 1)
    {
        cout << "You enter the library.\n" << endl;
        library(p);
    }
    else if (playerChoice == 2)
    {
        cout << "You enter the kitchen.\n" << endl;
        kitchen(p);
    }
    else if (playerChoice == 3)
    {
        cout << "You enter the armory.\n" << endl;
        armory(p);
    }
    else if (playerChoice == 4)
    {
        cout << "You enter the bathroom.\n" << endl;
        bathroom(p);
    }
    else if (playerChoice == 5)
    {
        for (int i = 0; i < 30; i++){
            if(p.inventory[i] == "WatchTower Key"){
                cout << "You use the WatchTower Key to open the door to the watch tower." << endl;
                break;
            }
            else if(i == 29){
                cout << "You don't have a key to open the door to the watch tower." << endl;
                return firstFloor(p);
            }
        }
        watchTower(p);
    }
    else if (playerChoice == 6)
    {
        cout << "You go up to the second floor." << endl;
        secondFloor(p);
    }
    else
    {
        cout << "You decide to do nothing." << endl;
        cout << "The End. Thank you for playing!" << endl;
        return 0;
    }

    return 0;
}

int Locations::library(Player &p)
{
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You are currently in the library." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "The books are lined up neatly on the shelves, and the air is filled with the scent of old paper." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You see a small window that leads to the outside world, but it's too high to reach." << endl
         << endl;
    this_thread::sleep_for(chrono::seconds(1));

    cout << "What would you like to do?" << endl;
    cout << "\t1. Look for a book and catch up on some reading." << endl;
    cout << "\t2. Try to climb out of the window." << endl;
    cout << "\t3. Leave the library." << endl;
    cout << "\t4. Enter some of the rooms." << endl;
    cout << "\t5. Do nothing." << endl
         << endl;

    int playerChoice;
    cin >> playerChoice;

    if(playerChoice == 9){
        p.checkInventory();
        cout << "What else would you like to do?" << endl;
        cin >> playerChoice;
    }

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

    while (playerChoice != 3 && playerChoice != 4)
    {
        if (playerChoice == 1)
        {
            cout << "You look for a book and catch up on some reading." << endl;
            cout << "After a while, you decide to keep looking around" << endl;
            cout << "What would you like to do now?" << endl;
            cin >> playerChoice;
        }
        if (playerChoice == 2)
        {
            cout << "You try to climb out of the window." << endl;
            cout << "But the window is too high, and you fall back into the library." << endl;
            cout << "You are now back in the library." << endl;
            cout << "What would you like to do now?" << endl;
            cin >> playerChoice;
        }
    }

    if (playerChoice == 3)
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

        p.current = entrance;

        // made by chatGPT
        bool exited = false;

        while (exited == false)
        {
            if (p.current == nullptr)
            {
                std::cout << "Error: player is not in a room.\n";
                break;
            }

            p.current->Print();
            p.current->pickupItems(&p);

            int choice = 0;
            cout << "Choose an exit(1 for first exit, 2 for second, etc.): ";
            cin >> choice;

            int index = choice - 1;

            if (index < 0 || index >= (int)p.current->roomExits.size())
            {
                cout << "Invalid choice.\n";
            }
            else
            {
                Rooms *next = p.current->roomExits[index];

                if (next == nullptr)
                {
                    cout << "That exit is blocked.\n";
                }
                else
                {
                    if (next == entrance)
                    {
                        p.current = next; // optional
                        exited = true;
                    }
                    else
                    {
                        p.current = next;
                    }
                }
            }
        }

        cout << "\nYou have left the library." << endl;
        firstFloor(p);
    }

    return 0;
}

//The watchtower is kind of optional but it gives loot, although the loot might not always be useful
int Locations::watchTower(Player &p)
{
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You are currently in the watch tower." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "The tower is high up, and you can see the entire castle from here." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You can also see the surrounding area, but it's too far away to make out any details." << endl
         << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You see guards patrolling the area, shielding the chests that lay behind them." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You can also see a small window that gives you a better view of the outside world." << endl
         << endl;

    cout << "What would you like to do?" << endl;
    cout << "\t1. Try to steal a chest from the guards." << endl;
    cout << "\t2. Try to sneak past the guards to view the window." << endl;
    cout << "\t3. Leave the watch tower." << endl;
    cout << "\t4. Do nothing." << endl
         << endl;

    int playerChoice;
    cin >> playerChoice;

    if(playerChoice == 9){
        p.checkInventory();
        cout << "What else would you like to do?" << endl;
        cin >> playerChoice;
    }

    while (playerChoice < 1 || playerChoice > 4)
    {
        cout << "Invalid choice. Please try again." << endl;
        cin >> playerChoice;
    }

    while (playerChoice == 4)
    {
        cout << "You decide to do nothing." << endl;
        cout << "What would you like to do now?" << endl;
        cin >> playerChoice;
    }

    if (playerChoice == 1)
    {
        int stealChance = (rand() % 2) + 1;
        if(stealChance == 1)
        {
            cout << "You try to steal a chest from the guards." << endl;
            cout << "You successfully steal a chest." << endl;
            for (int i = 0; i < 5; i++)
            {
                int item = itemGenerator.itemProbability();
                p.pickupItem(itemGenerator.items[item]);
                cout << "You received: " << itemGenerator.items[item] << "\n";
            }
                cout << "You leave the watch tower." << endl;
            firstFloor(p);
        }
        else
        {

            Enemy knight(
                35, 8,
                "Knight",
                {"helmet", "Sword"},
                "A disciplined castle knight in steel armor. Tough, trained, and relentless."
            );

            picture.printKnight();
            p.fightEnemy(knight);
            return 0;
        }
    }
    else if (playerChoice == 2)
    {
        int sneakChance = (rand() % 3) + 1;
        if(sneakChance == 1)
        {
            cout << "You try to sneak past the guards." << endl;
            cout << "You successfully sneak past the guards and hide behind a barrel that is close to the window." << endl;
            cout << "You look through window and see the King in his room with his closest guards handing them a key to open the castle doors." << endl;
            return 0;
        }
        else
        {
            cout << "You try to sneak past the guards." << endl;
            cout << "But the guards notice you and chase you out of the watch tower." << endl;
            cout << "You leave the watch tower." << endl;
            firstFloor(p);
        }
    }

    else if (playerChoice == 3)
    {
        cout << "You leave the watch tower." << endl;
        firstFloor(p);
    }
    return firstFloor(p);
}

int Locations::kitchen(Player &p)
{
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You are currently in the kitchen." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "The kitchen is filled with the aroma of food and the sound of clinking dishes." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "There are many different types of food and drinks available, but you can't help but feel a sense of unease." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You see a guard patrolling the area, and you can hear the sound of footsteps in the distance." << endl
         << endl;

    cout << "What would you like to do?" << endl;
    cout << "\t1. Try to steal some food and drinks." << endl;
    cout << "\t2. Leave the kitchen." << endl;
    cout << "\t3. Do nothing." << endl
         << endl;

    int playerChoice;
    cin >> playerChoice;

    if(playerChoice == 9){
        p.checkInventory();
        cout << "What else would you like to do?" << endl;
        cin >> playerChoice;
    }

    while (playerChoice < 1 || playerChoice > 3)
    {
        cout << "Invalid choice. Please try again." << endl;
        cin >> playerChoice;
    }

    while (playerChoice == 3)
    {
        cout << "You decide to do nothing." << endl;
        cout << "What would you like to do now?" << endl;
        cin >> playerChoice;
    }

    if (playerChoice == 1)
    {
        int stealChance = (rand() % 2) + 1;
        if (stealChance == 2)
        {
            cout << "You try to steal some food and drinks." << endl;
            cout << "But the guard notices you and catches you in the act." << endl;
            //fighting scene

            return 0;
        }
        else
        {
            cout << "You try to steal some food and drinks." << endl;
            cout << "You successfully steal some food and drinks." << endl;
            p.pickupItem("Bread");
            p.pickupItem("Water"); 
            p.pickupItem("WatchTower Key");
            cout << "You leave the kitchen." << endl;
            firstFloor(p);
        }
        firstFloor(p);
    }
    else if (playerChoice == 2)
    {
        cout << "You leave the kitchen." << endl;
        firstFloor(p);
    }
    return firstFloor(p);
}

int Locations::armory(Player &p)
{
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You are currently in the armory." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "The armory is filled with weapons and armor." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You see a Upper guardsman patrolling the area as he stomps his massive feet with his heavy boots" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You can see the guardsman is holding a key to the kings room right next to his massive sword and shield" << endl<<endl;

    cout << "What would you like to do?" << endl;
    cout << "\t1. Fight the guardsman to steal his keys." << endl;
    cout << "\t2. Try to sneak past the guardsman to grab the armor and weapons behind him." << endl;
    cout << "\t3. Leave the armory." << endl;
    cout << "\t4. Do nothing." << endl
         << endl;

    int playerChoice;
    cin >> playerChoice;

    while (playerChoice < 1 || playerChoice > 4)
    {
        cout << "Invalid choice. Please try again." << endl;
        cin >> playerChoice;
    }

    while (playerChoice == 4)
    {
        cout << "You decide to do nothing." << endl;
        cout << "What would you like to do now?" << endl;
        cin >> playerChoice;
    }

    if (playerChoice == 1)
    {
        Enemy upperKnight(
            60, 12,
            "Upper Knight",
            {"chestplate", "Shield", "KingsRoomKey"},
            "An elite knight with heavier armor and stronger attacks. A serious threat."
        );

        picture.printUpperKnight();
        p.fightEnemy(upperKnight);
        return firstFloor(p);
    }
    else if (playerChoice == 2)
    {
        int sneakChance = (rand() % 10) + 1;
        if (sneakChance == 1)
        {
            cout << "You try to sneak past the guardsman." << endl;
            cout << "You successfully sneak past the guardsman and grab the armor and weapons behind him." << endl;
            p.pickupItem("Sword");
            p.pickupItem("Shield");
            cout << "You leave the armory." << endl;
            firstFloor(p);
        }
        else
        {
            cout << "You try to sneak past the guardsman." << endl;
            cout << "But the guardsman notices you and chases you out of the armory." << endl;
            cout << "You leave the armory." << endl;
            firstFloor(p);
        }
    }
    else if (playerChoice == 3)
    {
        cout << "You leave the armory." << endl;
        firstFloor(p);
    }
    return firstFloor(p);
}

int Locations::hospital(Player &p)
{
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You are currently in the hospital lobby." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "The hospital is filled with the sound of medical equipment and the smell of antiseptic." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "There are many different types of medical equipment and supplies available, but you can't help but feel a sense of unease." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "There are a number of patients in the hospital, and you can see that some of them are in a lot of pain except for one." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "There a many medics and nurses around the hospital." << endl
         << endl;

    cout << "What would you like to do?" << endl;
    cout << "\t1. Explore the Rooms" << endl;
    cout << "\t2. Talk to a patient for information." << endl;
    cout << "\t3. Leave the hospital." << endl;
    cout << "\t4. Do nothing." << endl
         << endl;

    int playerChoice;
    cin >> playerChoice;
    if(playerChoice == 9){
        p.checkInventory();
        cout << "What else would you like to do?" << endl;
        cin >> playerChoice;
    }

    while (playerChoice < 1 || playerChoice > 4)
    {
        cout << "Invalid choice. Please try again." << endl;
        cin >> playerChoice;
    }

    while (playerChoice == 4)
    {
        cout << "You decide to do nothing." << endl;
        cout << "What would you like to do now?" << endl;
        cin >> playerChoice;
    }

    if (playerChoice == 1)
    {
        Rooms *lobby = new Rooms("Hospital Lobby", "Quiet lobby with a front desk and dusty chairs.");
        Rooms *waitingRoom = new Rooms("Waiting Room", "Old magazines and a broken clock ticking loudly.");
        Rooms *triage = new Rooms("Triage", "Curtains, stretchers, and a faint smell of antiseptic.");
        Rooms *supplyCloset = new Rooms("Supply Closet", "Shelves of medical supplies. Dim light flickers.");
        Rooms *patientWard = new Rooms("Patient Ward", "Rows of beds. Some are overturned.");
        Rooms *operatingRm = new Rooms("Operating Room", "Cold tools on a tray. Something feels off.");
        Rooms *pharmacy = new Rooms("Pharmacy", "Locked cabinets and medicine bottles scattered.");
        Rooms *exitHall = new Rooms("Exit Hall", "A hallway leading back out of the hospital.");

        lobby->AddExit("Go to Waiting Room", waitingRoom);
        lobby->AddExit("Go to Triage", triage);
        lobby->AddExit("Leave Hospital", exitHall);

        waitingRoom->AddExit("Return to Lobby", lobby);

        triage->AddExit("Return to Lobby", lobby);
        triage->AddExit("Go to Patient Ward", patientWard);
        triage->AddExit("Go to Supply Closet", supplyCloset);

        supplyCloset->AddExit("Return to Triage", triage);

        patientWard->AddExit("Return to Triage", triage);
        patientWard->AddExit("Go to Operating Room", operatingRm);
        patientWard->AddExit("Go to Pharmacy", pharmacy);

        operatingRm->AddExit("Return to Patient Ward", patientWard);
        pharmacy->AddExit("Return to Patient Ward", patientWard);

        exitHall->AddExit("Go to Lobby", lobby);

        itemGenerator.fillRoomWithRandomItems(lobby, itemGenerator.items, 4);
        itemGenerator.fillRoomWithRandomItems(waitingRoom, itemGenerator.items, 4);
        itemGenerator.fillRoomWithRandomItems(triage, itemGenerator.items, 4);
        itemGenerator.fillRoomWithRandomItems(supplyCloset, itemGenerator.items, 4);
        itemGenerator.fillRoomWithRandomItems(patientWard, itemGenerator.items, 4);
        itemGenerator.fillRoomWithRandomItems(operatingRm, itemGenerator.items, 4);
        itemGenerator.fillRoomWithRandomItems(pharmacy, itemGenerator.items, 4);

        itemGenerator.fillRoomWithRandomItems(exitHall, itemGenerator.items, 4);

        bool done = false;
        while (!done && p.current != nullptr)
        {
            p.current->Print();
            p.current->pickupItems(&p);

            int choice;
            cout << "Choose an exit (1, 2, 3...): ";
            cin >> choice;

            int index = choice - 1;
            if (index < 0 || index >= (int)p.current->roomExits.size())
            {
                cout << "Invalid choice.\n";
            }
            else
            {
                p.current = p.current->roomExits[index];

                // optional: stop if they reach Exit Hall
                if (p.current != nullptr && p.current->roomName == "Exit Hall")
                {
                    done = true;
                }
            }
        }

        return 0;
    }
    else if (playerChoice == 2)
    {
        this_thread::sleep_for(chrono::seconds(1));
        cout << "You decide to talk to a patient for information." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "The patient is in a lot of pain, but they seem well enough to talk." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "You ask how to defeat the upper guardsman in the armory" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "The patient tells you that the upper guardsman is very strong and has a shield that can block most attacks." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "The only way to defeat him is to find a way to destroy his shield." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "You can find a mythic sword in one of the bedrooms inside a chest that must be unlocked with a silver key." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        cout<< "You thank the patient and leave the hospital." << endl;
        return 0;
    }
    else if (playerChoice == 3)
    {
        cout << "You leave the hospital." << endl;
        firstFloor(p);
    }

    return 0;
}
int Locations::bathroom(Player &p)
{
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You are currently in the bathroom." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "The bathroom is clean and well-maintained." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "There is a shower, a toilet, and a sink." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "There is a guard taking a shower, and you can hear the sound of water running." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You see his pile of clothes on the floor next to the shower." << endl << endl;
    this_thread::sleep_for(chrono::seconds(1));

    cout << "What would you like to do?" << endl;
    cout << "\t1. Try to loot the guard's clothes." << endl;
    cout << "\t2. Leave the bathroom." << endl;
    cout << "\t3. Do nothing." << endl<< endl;
    
    int playerChoice;
    cin >> playerChoice;

    if(playerChoice == 9){
        p.checkInventory();
        cout << "What else would you like to do?" << endl;
        cin >> playerChoice;
    }

    while (playerChoice < 1 || playerChoice > 3)
    {
        cout << "Invalid choice. Please try again." << endl;
        cin >> playerChoice;
    }

    while (playerChoice == 3)
    {
        cout << "You decide to do nothing." << endl;
        cout << "What would you like to do now?" << endl;
        cin >> playerChoice;
    }

    if (playerChoice == 1)
    {
        cout << "You try to loot the guard's clothes and find both bedroom keys." << endl;
        p.pickupItem("bedroom1 key");
        p.pickupItem("bedroom2 key");
        cout << "You leave the bathroom." << endl;
        return firstFloor(p);
    }
    else if (playerChoice == 2)
    {
        cout << "You leave the bathroom." << endl;
        firstFloor(p);
    }


    return firstFloor(p);
}
int Locations::secondFloor(Player &p)
{
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You are currently on the second floor." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "The second floor is a long hallway with doors leading to the bedrooms and the king's room." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "There is a upper guard standing in front of the door to the king's room." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "There is also a guard standing in front of the door to bedroom 1." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "There is also a guard standing in front of the door to bedroom 2." << endl;
    this_thread::sleep_for(chrono::seconds(1));

    cout << "What would you like to do?" << endl
         << endl;


    cout << "\t1. Go to bedroom 1." << endl;
    cout << "\t2. Go to bedroom 2." << endl;
    cout << "\t3. Go to the king's room." << endl;
    cout << "\t4. Go back down to the first floor." << endl;

    int playerChoice;
    cin >> playerChoice;

    if(playerChoice == 9){
        p.checkInventory();
        cout << "What else would you like to do?" << endl;
        cin >> playerChoice;
    }

    while (playerChoice < 1 || playerChoice > 4)
    {
        cout << "\nInvalid choice. Please try again." << endl;
        cin >> playerChoice;
    }

    if (playerChoice == 1)
    {
        cout << "\nYou fight the guard in front of bedroom 1." << endl;
        Enemy knight(
                35, 8,
                "Knight",
                {"helmet", "Sword"},
                "A disciplined castle knight in steel armor. Tough, trained, and relentless."
        );

        picture.printKnight();
        p.fightEnemy(knight);
        bedroom1(p);
        return 0;
    }
    else if (playerChoice == 2)
    {
        cout << "\nYou fight the guard in front of bedroom 2." << endl;
        Enemy knight(
                35, 8,
                "Knight",
                {"helmet", "Sword"},
                "A disciplined castle knight in steel armor. Tough, trained, and relentless."
        );

        picture.printKnight();
        p.fightEnemy(knight);
        bedroom2(p);
        return 0;
    }
    else if (playerChoice == 3)
    {
        cout << "\nYou fight the upper guard in front of the king's room." << endl;
        Enemy upperKnight(
            60, 12,
            "Upper Knight",
            {"chestplate", "Shield", "KingsRoomKey"},
            "An elite knight with heavier armor and stronger attacks. A serious threat."
        );

        picture.printUpperKnight();
        p.fightEnemy(upperKnight);
        for(int i = 0; i < 30; i++){
            if(p.inventory[i] == "KingsRoomKey"){
                cout << "You use the KingsRoomKey to open the door to the king's room." << endl;
                break;
            }
            else if(i == 29){
                cout << "You don't have a key to open the door to the king's room." << endl;
                return secondFloor(p);
            }
        }
        kingsRoom(p);
        return 0;
    }
    else if (playerChoice == 4)
    {
        cout << "\nYou go back down to the first floor." << endl;
        firstFloor(p);
        return 0;
    }

    return firstFloor(p);
}

int Locations::bedroom1(Player &p)
{
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You are currently in bedroom 1." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "The bedroom is a small room with a bed, a desk, and a chair." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "There is a nobleman holding a sword in the bedroom." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "The nobleman seems to be weak but you must not be too confident." << endl
         << endl;
    this_thread::sleep_for(chrono::seconds(1));

    cout << "What would you like to do?" << endl;
    cout << "\t1. Fight the nobleman." << endl;
    cout << "\t2. Go back to the second floor." << endl;

    int playerChoice;
    cin >> playerChoice;

    if(playerChoice == 9){
        p.checkInventory();
        cout << "What else would you like to do?" << endl;
        cin >> playerChoice;
    }

    while (playerChoice < 1 || playerChoice > 2)
    {
        cout << "\nInvalid choice. Please try again." << endl;
        cin >> playerChoice;
    }

    if (playerChoice == 1)
    {
        Enemy nobleman(
            25, 6,
            "Nobleman",
            {"Silver Key", "Gold Coin"},
            "A wealthy noble who fights out of desperation. Not as skilled, but unpredictable."
        );

        p.fightEnemy(nobleman);

        return secondFloor(p);
    }
    else if (playerChoice == 2)
    {
        cout << "\nYou go back to the second floor." << endl;
        secondFloor(p);
        return 0;
    }
    return secondFloor(p);
}

int Locations::bedroom2(Player &p)
{
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You are currently in bedroom 2." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "The bedroom is a small room with a bed, a desk, and a chair." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "There is a nobleman holding a sword in the bedroom." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You see a chest behind the nobleman that is locked." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "The nobleman seems to be weak but you must not be too confident." << endl
         << endl;
    this_thread::sleep_for(chrono::seconds(1));

    cout << "What would you like to do?" << endl;
    cout << "\t1. Fight the nobleman." << endl;
    cout << "\t2. Go back to the second floor." << endl;

    int playerChoice;
    cin >> playerChoice;

    if(playerChoice == 9){
        p.checkInventory();
        cout << "What else would you like to do?" << endl;
        cin >> playerChoice;
    }

    while (playerChoice < 1 || playerChoice > 2)
    {
        cout << "\nInvalid choice. Please try again." << endl;
        cin >> playerChoice;
    }

    if (playerChoice == 1)
    {
        Enemy nobleman(
            25, 6,
            "Nobleman",
            {"Silver Key", "Gold Coin"},
            "A wealthy noble who fights out of desperation. Not as skilled, but unpredictable."
        );
        cout << "\nYou fight the nobleman and defeat him." << endl;
        cout << "\n You unlock the chest with a silver key and find the MythicGreatSword." << endl;
        
        p.fightEnemy(nobleman);
        cout << "\nYou fight the nobleman and defeat him." << endl;
        for(int i = 0; i < 30; i++){
            if(p.inventory[i] == "silver key"){
                cout << "You unlocked the chest and found a mythical sword!." << endl;
                p.pickupItem("MythicGreatSword");
                picture.printMythicSword();
            }
        }
        secondFloor(p);
    }
    else if (playerChoice == 2)
    {
        cout << "\nYou go back to the second floor." << endl;
        secondFloor(p);
        return 0;
    }

    return firstFloor(p);
}

int Locations::kingsRoom(Player &p)
{
    this_thread::sleep_for(chrono::seconds(1));
    cout << "You are currently in the king's room." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "The room is large and ornate, with a throne at the center." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "There is a guard standing near the throne." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "The guard seems to be strong and well-armed." << endl
         << endl;
    this_thread::sleep_for(chrono::seconds(1));

    cout << "What would you like to do?" << endl;
    cout << "\t1. Fight the guard." << endl;
    cout << "\t2. Go back to the second floor." << endl;

    int playerChoice;
    cin >> playerChoice;

    if(playerChoice == 9){
        p.checkInventory();
        cout << "What else would you like to do?" << endl;
        cin >> playerChoice;
    }

    while (playerChoice < 1 || playerChoice > 2)
    {
        cout << "\nInvalid choice. Please try again." << endl;
        cin >> playerChoice;
    }

    if (playerChoice == 1)
    {
        Enemy upperKnight(
            60, 12,
            "Upper Knight",
            {"chestplate", "Shield", "KingsRoomKey"},
            "An elite knight with heavier armor and stronger attacks. A serious threat."
        );

        picture.printUpperKnight();
        p.fightEnemy(upperKnight);

        cout << "\nYou fight the guard and defeat him." << endl;
        cout << "\nYou use the Kings Room Key to unlock the King's room and steal the key to escape the castle" << endl;
        cout << "\n The end. Thank you for playing.";
        return 0;
    }
    else if (playerChoice == 2)
    {
        cout << "\nYou go back to the second floor." << endl;
        secondFloor(p);
        return 0;
    }

    return firstFloor(p);
}
