//Story: The king falsely accused you of stealing his chicken leg at the dinner table and now you are locked in a dungeon full of 
//scary monsters, creepy insects, and dangerous criminals, awaiting your execution. You must escape from the dungeon 
//, out of the castle, and out of the kingdom before the king executes you. To escape, you must defeat enemies, play games, and
// use your wits to find your way out. Good luck!

#include <iostream>
#include "player.h"
#include "locations.h"
#include "ascii.h"
using namespace std;


int main() {
    Player p;
    Ascii printImages;
    cout << "The king falsely accused you of stealing his chicken leg at the dinner table and now you are locked in a dungeon full of " << endl;
    cout << "scary monsters, creepy insects, and dangerous criminals, awaiting your execution. You must escape from the dungeon " << endl;
    cout << ", out of the castle, and out of the kingdom before the king executes you. To escape, you must defeat enemies, play games, and" << endl;
    cout << "use your wits to find your way out. Good luck!" << endl << endl;

    printImages.printKnight();

    cout << "Welcome to the dungeon escape game!" << endl;
    cout << "You are locked in a dungeon full of scary monsters, creepy insects, and dangerous criminals." << endl;
    cout << "You must escape from the dungeon, out of the castle, and out of the kingdom before the king executes you." << endl;
    cout << "To escape, you must defeat enemies, play games, and use your wits to find your way out." << endl;
    cout << "Good luck!" << endl;

    cout << "(Remember, if you want to look at your inventory, type 9)" << endl;

    Locations location;
    location.armory(p);
    return 0;
}