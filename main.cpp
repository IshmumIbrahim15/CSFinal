//Story: You have been caught in an alien spaceship, and you need to escape through hordes of enemies and obstacles
// in this mazelike ship. User your decision making skills and quick thinking to get off the ship alive!

#include <iostream>
using namespace std;
#include "rockPaperScissors.cpp"

int main() {
    cout << "Welcome to the Alien Spaceship Escape Adventure!" << endl;
    cout << "You find yourself trapped in a maze-like alien spaceship filled with enemies and obstacles." << endl;
    cout << "Your goal is to navigate through the ship and find your way to freedom." << endl;

    string choice1;
    cout << "You enter a dimly lit corridor. Do you want to go 'left' or 'right'? ";
    cin >> choice1;

    if (choice1 == "left") {
        string choice2;
        cout << "You encounter a hostile alien! Do you want to 'fight' or 'run'? ";
        cin >> choice2;

        if (choice2 == "fight") {
            cout << "You bravely fight the alien and manage to defeat it! You continue down the corridor." << endl;
            cout << "To determine the outcome of the fight, let's play a game of rock, paper, and scissors!" << endl;
            rockPaperScissors();
        } else if (choice2 == "run") {
            cout << "You run away safely but end up back at the start of the corridor." << endl;
        } else {
            cout << "Invalid choice. The alien attacks you while you hesitate. Game over!" << endl;
            return 0;
        }
    } else if (choice1 == "right") {
        string choice2;
        cout << "You find a locked door. Do you want to 'pick' the lock or 'search' for a key? ";
        cin >> choice2;

        if (choice2 == "pick") {
            cout << "You successfully pick the lock and enter a new area of the ship." << endl;
        } else if (choice2 == "search") {
            cout << "You find a key hidden under a crate and unlock the door!" << endl;
        } else {
            cout << "Invalid choice. You waste time and get caught by patrolling aliens. Game over!" << endl;
            return 0;
        }
    } else {
        cout << "Invalid choice. You wander aimlessly until you are captured by aliens. Game over!" << endl;
        return 0;
    }

    cout << "Congratulations! You have navigated through part of the alien spaceship." << endl;
    cout << "More challenges await you as you continue your escape!" << endl;

    return 0;
}