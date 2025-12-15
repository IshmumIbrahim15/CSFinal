#include <iostream>
using namespace std;

int main() {
    string moves[] = {"Rock", "Paper", "Scissors"};
    int player1Choice;
    int enemyChoice;

    int enemyChoice = rand() % 3;

    cin >> player1Choice;

    while (player1Choice < 0 || player1Choice > 2) {
        cout << "Invalid choice. Please select 0 (Rock), 1 (Paper), or 2 (Scissors)." << endl;
        cin >> player1Choice;
    }

    if (player1Choice == enemyChoice) {
        cout << "You and the enemy both chose " << moves[player1Choice] << ". It's a tie!" << endl;
    } else if ((player1Choice == 0 && enemyChoice == 2) || (player1Choice == 1 && enemyChoice == 0) || (player1Choice == 2 && enemyChoice == 1)) {
        cout << "You chose " << moves[player1Choice] << ". The enemy chose " << moves[enemyChoice] << ". You win!" << endl;
    } else {
        cout << "You chose " << moves[player1Choice] << ". The enemy chose " << moves[enemyChoice] << ". Enemy wins!" << endl;
    }

    return 0;
}