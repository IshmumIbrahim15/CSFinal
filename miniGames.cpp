#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Games
{
public:
    int score;
    string playerName;
    int rockPaperScissors();
    int tictactoe();
    int guessTheNumber();
    int pong();
    int Galaga();
};

int Games::rockPaperScissors()
{
    string moves[] = {"Rock", "Paper", "Scissors"};
    int player1Choice;
    int enemyChoice;

    enemyChoice = rand() % 3;

    cout << "Choose your move: 0 (Rock), 1 (Paper), 2 (Scissors): ";
    cin >> player1Choice;

    while (player1Choice < 0 || player1Choice > 2)
    {
        cout << "Invalid choice. Please select 0 (Rock), 1 (Paper), or 2 (Scissors)." << endl;
        cin >> player1Choice;
    }

    if (player1Choice == enemyChoice)
    {
        cout << "You and the enemy both chose " << moves[player1Choice] << ". It's a tie!" << endl;
    }
    else if ((player1Choice == 0 && enemyChoice == 2) || (player1Choice == 1 && enemyChoice == 0) || (player1Choice == 2 && enemyChoice == 1))
    {
        cout << "You chose " << moves[player1Choice] << ". The enemy chose " << moves[enemyChoice] << ". You win!" << endl;
    }
    else
    {
        cout << "You chose " << moves[player1Choice] << ". The enemy chose " << moves[enemyChoice] << ". Enemy wins!" << endl;
    }

    return 0;
}

int tictactoeLogic(char boxes[])
{
    // Check if X wins
    if (boxes[0] == 'X' && boxes[1] == 'X' && boxes[2] == 'X')
    {
        return 1;
    }
    if (boxes[3] == 'X' && boxes[4] == 'X' && boxes[5] == 'X')
    {
        return 1;
    }
    if (boxes[6] == 'X' && boxes[7] == 'X' && boxes[8] == 'X')
    {
        return 1;
    }
    if (boxes[0] == 'X' && boxes[3] == 'X' && boxes[6] == 'X')
    {
        return 1;
    }
    if (boxes[1] == 'X' && boxes[4] == 'X' && boxes[7] == 'X')
    {
        return 1;
    }
    if (boxes[2] == 'X' && boxes[5] == 'X' && boxes[8] == 'X')
    {
        return 1;
    }
    if (boxes[0] == 'X' && boxes[4] == 'X' && boxes[8] == 'X')
    {
        return 1;
    }
    if (boxes[2] == 'X' && boxes[4] == 'X' && boxes[6] == 'X')
    {
        return 1;
    }

    // Check if O wins
    if (boxes[0] == 'O' && boxes[1] == 'O' && boxes[2] == 'O')
    {
        return 2;
    }
    if (boxes[3] == 'O' && boxes[4] == 'O' && boxes[5] == 'O')
    {
        return 2;
    }
    if (boxes[6] == 'O' && boxes[7] == 'O' && boxes[8] == 'O')
    {
        return 2;
    }
    if (boxes[0] == 'O' && boxes[3] == 'O' && boxes[6] == 'O')
    {
        return 2;
    }
    if (boxes[1] == 'O' && boxes[4] == 'O' && boxes[7] == 'O')
    {
        return 2;
    }
    if (boxes[2] == 'O' && boxes[5] == 'O' && boxes[8] == 'O')
    {
        return 2;
    }
    if (boxes[0] == 'O' && boxes[4] == 'O' && boxes[8] == 'O')
    {
        return 2;
    }
    if (boxes[2] == 'O' && boxes[4] == 'O' && boxes[6] == 'O')
    {
        return 2;
    }

    return 0;
}

int Games::tictactoe()
{
    char boxes[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    string board = string(1, boxes[0]) + " | " + string(1, boxes[1]) + " | " + string(1, boxes[2]) + "\n-----------\n" + string(1, boxes[3]) + " | " + string(1, boxes[4]) + " | " + string(1, boxes[5]) + "\n-----------\n" + string(1, boxes[6]) + " | " + string(1, boxes[7]) + " | " + string(1, boxes[8]);
    while (tictactoeLogic(boxes) == 0)
    {
        cout << board << endl;
        cout << "Player 1, choose a box to place your X (0-8): ";
        int player1Choice;
        cin >> player1Choice;

        while (boxes[player1Choice] != ' ')
        {
            cout << "Box already taken. Choose another box: ";
            cin >> player1Choice;
        }
        boxes[player1Choice] = 'X';
        board = string(1, boxes[0]) + " | " + string(1, boxes[1]) + " | " + string(1, boxes[2]) + "\n-----------\n" + string(1, boxes[3]) + " | " + string(1, boxes[4]) + " | " + string(1, boxes[5]) + "\n-----------\n" + string(1, boxes[6]) + " | " + string(1, boxes[7]) + " | " + string(1, boxes[8]);


        int botChoice = rand() % 9;
        while (boxes[botChoice] != ' ')
       {
            botChoice = rand() % 9;
        }
        boxes[botChoice] = 'O';

        board = string(1, boxes[0]) + " | " + string(1, boxes[1]) + " | " + string(1, boxes[2]) + "\n-----------\n" + string(1, boxes[3]) + " | " + string(1, boxes[4]) + " | " + string(1, boxes[5]) + "\n-----------\n" + string(1, boxes[6]) + " | " + string(1, boxes[7]) + " | " + string(1, boxes[8]);
    }

    cout << board << endl;

    if(tictactoeLogic(boxes) == 1)
    {
        cout << "Player 1 wins!" << endl;
    }
    else if(tictactoeLogic(boxes) == 2)
    {
        cout << "Bot wins!" << endl;
    }
    else
    {
        cout << "It's a tie!" << endl;
    }

    return 0;
}

int Games::pong()
{
    int player1Score = 0;
    int botScore = 0;

    string player1Paddle = "|\n|\n|\n|\n|";
    string botPaddle = "|\n|\n|\n|\n|";
    string ball = "O";
    string wall = "------------------------";
    string floor = "------------------------";
    string ceiling = "------------------------";

    while (player1Score < 5 && botScore < 5)
    {
        cout << wall << endl;
        cout << ceiling << endl;
        cout << player1Paddle << " " << ball << " " << botPaddle << endl;
        cout << floor << endl;
        cout << "Player 1 Score: " << player1Score << " Bot Score: " << botScore << endl;
    }

    return 0;
}


int Games::guessTheNumber(){
    int secretNum = rand() % 100 + 1;
    int playerGuess;

    cout << "Rules: Guess a random number between 1 - 100. You have 5 chances to geuss the right number. Good luck!" << endl;
    cout << "Enter your guess: ";
    cin >> playerGuess;

    int countGuesses = 1;

    while (countGuesses < 5)
    {
        if (playerGuess == secretNum)
        {
            cout << "Congratulations! You guessed the correct number in " << countGuesses << " attempts." << endl;
            break;
        }
        else if (playerGuess < secretNum)
        {
            cout << "Too low! Try again." << endl;
        }
        else
        {
            cout << "Too high! Try again." << endl;
        }

        countGuesses++;
        cout << "Enter your guess: ";
        cin >> playerGuess;
    }

    return 0;
}
