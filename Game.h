#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Enemy.h"
#include "Minion.h"
#include "Character.h"
#include "Card.h"
#include "Boss.h"
#include "System.h"
#include<bits/stdc++.h>

using namespace std;

class Game {
private:
    // File name for saving the game state
    const string SAVEFILE = "GameSave.txt";

    System system; // System object for game-related functionalities
    int round; // Current round number
    vector<vector<Enemy*> > levels; // 2D vector to store enemy configurations for each level

    vector<Card*> allCards; // Vector to store all available cards in the game
    vector<Card*> playerDeck; // Vector to store the player's deck of cards

    Player* player; // Pointer to the player object

    // Private helper functions
    bool startRound(Player* player); // Function to start a round of the game
    void displayStatus(Player* player, vector<Enemy*> enemies, vector<Card*> cards); // Function to display the game status

public:
    Game(); // Constructor

    // Public member functions
    void saveGame(const string& filename); // Function to save the game state to a file
    void loadGame(const string& filename); // Function to load the game state from a file
    void startGame(); // Function to start the game
    void setNewPlayer(); // Function to set up a new player for the game
};

#endif
