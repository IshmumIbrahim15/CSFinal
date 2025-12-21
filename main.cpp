//Story: The king falsely accused you of stealing his chicken leg at the dinner table and now you are locked in a dungeon full of 
//scary monsters, creepy insects, and dangerous criminals, awaiting your execution. You must escape from the dungeon 
//, out of the castle, and out of the kingdom before the king executes you. To escape, you must defeat enemies, play games, and
// use your wits to find your way out. Good luck!

#include <iostream>
#include "player.h"
#include "locations.h"
using namespace std;


int main() {
    Player p;

    cout << "Welcome to the dungeon escape game!" << endl;
    cout << "You are locked in a dungeon full of scary monsters, creepy insects, and dangerous criminals." << endl;
    cout << "You must escape from the dungeon, out of the castle, and out of the kingdom before the king executes you." << endl;
    cout << "To escape, you must defeat enemies, play games, and use your wits to find your way out." << endl;
    cout << "Good luck!" << endl;

    Locations location;
    location.yourCell(&p);
    return 0;
}