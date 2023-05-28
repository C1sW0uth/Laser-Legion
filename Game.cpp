#include "Game.h"

//Function to create an enemies of and their atributes

Enemy* harbinger() {return new Minion("Sonic Harbinger", 30, "ATTACK", 4);}
Enemy* assault() {return new Minion("Assault Trooper", 14, "ATTACK", 5);}
Enemy* calvary() {return new Minion("Arcane Calvary", 10, "ATTACK", 8);}
Enemy* sniper() {return new Minion("Photon Sniper", 6, "ATTACK", 15);}

Enemy* vanguard() {return new Minion("Plasma Vanguard", 14, "SHIELD", 6);}
Enemy* warden() {return new Minion("Chrono Warden", 20, "SHIELD", 4);}
Enemy* sentinel() {return new Minion("Pyro Sentinel", 6, "SHIELD", 14);}

Enemy* medic() {return new Minion("Arcane Siphoner", 12, "HEAL", 6);}
Enemy* regenerator() {return new Minion("Bio-Regenerator", 6, "HEAL", 12);}

Game::Game() {
    round = 1;

    // Set up the levels and enemies for each round
    levels = {
        {},
        {assault()},
        {calvary()},
        {calvary(), vanguard()},
        {warden(), sniper()},
        {assault(), medic()},
        {calvary(), regenerator()},
        {harbinger(), vanguard(), medic()},
        {warden(), assault(), calvary()},
        {harbinger(), calvary(), sentinel(), regenerator()},
        {new Boss("Dr. Cygnus", 40, 10, 4, 2), sniper(), sentinel()},
    };

    // Create all the cards available in the game
    allCards = {
        new Card("Recharge+", 0, "RECHARGE", 2),
        new Card("Recharge+", 0, "RECHARGE", 2),

        new Card("Photon Blast", 1, "ATTACK", 8),
        new Card("Charged Blast", 2, "ATTACK", 14),
        new Card("Charged Blast", 2, "ATTACK", 14),
        new Card("Overcharged Blast", 3, "ATTACK", 30),

        new Card("Double Slash", 0, "MELEE", 10),
        new Card("Double Slash", 0, "MELEE", 10),

        new Card("Barrier", 1, "SHIELD", 6),
        new Card("Barrier", 1, "SHIELD", 6),
        new Card("Force Field", 2, "SHIELD", 10),
        new Card("Force Field", 2, "SHIELD", 10),

        new Card("Repair", 1, "HEAL", 6),
        new Card("Heavy Repair", 2, "HEAL", 10),
        new Card("Reconstruction", 3, "HEAL", 20),
    };

    //Create the original cards available for first round

    playerDeck = {
        new Card("Recharge", 0, "RECHARGE", 1),
        new Card("Recharge", 0, "RECHARGE", 1),

        new Card("Slash", 0, "MELEE", 6),

        new Card("Photon Blast", 1, "ATTACK", 8),
        new Card("Photon Blast", 1, "ATTACK", 8),

        new Card("Repair", 1, "HEAL", 6),

        new Card("Barrier",  1, "SHIELD", 6),
    };
}

//Allow the player to input their name

void Game::setNewPlayer() {
    string playerName;

    while (true) {
        std::cout << "Enter player name (less than 13 characters): ";
        std::getline(std::cin, playerName);
        
        if (playerName.length() < 13) {
            player = new Player(playerName, 50, 3);
            return;
        }
        
        std::cout << "Invalid input! Please enter a name less than 13 characters." << std::endl;
    }
}

//Function to save game into a txt file

void Game::saveGame(const string& filename) {
    ofstream file(filename);
    std::cout << "\n Saving...\n";
    this_thread::sleep_for(chrono::milliseconds(2000));
    if (file.is_open()) {
        file << "Player Name: " << player->getName() << '\n' << '\n';

        file << "Round: " << round+1 << '\n' << '\n';

        file << "All Cards: " << '\n';
        for (const auto& card : allCards)
            file << "\"" << card->getName() << "\"" << ' ' << card->getBulletCost() << ' ' << card->getType() << ' ' << card->getAmount() << '\n';

        file << '\n';

        file << "Player Deck: " << '\n';
        for (const auto& card : playerDeck)
            file << "\"" << card->getName() << "\"" << ' ' << card->getBulletCost() << ' ' << card->getType() << ' ' << card->getAmount() << '\n';
        
        file << '\n';

        file << "Player HP: " << player->getCurrentHealth() << '\n';

        file.close();
        std::cout << "Game saved successfully!" << '\n';
    }
    else {
        std::cout << "Error: Unable to open file" << '\n';
    }
}

//Load the game from a saved txt file

void Game::loadGame(const string& filename) {
    // Clear existing card decks
    allCards.clear();
    playerDeck.clear();

    // Open the specified file
    ifstream file(filename);

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            // Check for player name in the file
            if (line.find("Player Name: ") != string::npos) {
                // Extract the player name from the line and create a new Player object
                string playerName = line.substr(13);
                player = new Player(playerName, 50, 3);
            }
            // Check for the current round in the file
            else if (line.find("Round: ") != string::npos) {
                // Extract the round number from the line and update the game's round variable
                string roundStr = line.substr(7);
                int r = stoi(roundStr);
                this->round = r;
            }
            // Check for the list of all cards in the file
            else if (line == "All Cards: ") {
                // Read the lines until an empty line is encountered
                while (getline(file, line) && !line.empty()) {
                    // Parse the card data from the line and create a new Card object
                    istringstream iss(line);
                    string name, type;
                    int cost, amount;
                    iss >> quoted(name) >> cost >> type >> amount;
                    allCards.push_back(new Card(name, cost, type, amount));
                }
            }
            // Check for the player's deck in the file
            else if (line == "Player Deck: ") {
                // Read the lines until an empty line is encountered
                while (getline(file, line) && !line.empty()) {
                    // Parse the card data from the line and create a new Card object
                    istringstream iss(line);
                    string name, type;
                    int cost, amount;
                    iss >> quoted(name) >> cost >> type >> amount;
                    playerDeck.push_back(new Card(name, cost, type, amount));
                }
            }
            // Check for the player's current health in the file
            else if (line == "Player HP: ") {
                // Extract the player's current health from the line and update the player object
                string hpStr = line.substr(11);
                int HP = stoi(hpStr);
                player->setCurrentHealth(HP);
            }
        }
        
        file.close();
        std::cout << "Game loaded successfully! \n\n";
    }
    else {
        std::cout << "Error: Unable to open file \n\n";
    }
}


void Game::displayStatus(Player* player, vector<Enemy*> enemies, vector<Card*> cards) {
    // Display the player's status
    std::cout << '\n' << '\n' << "========================================" << '\n'; 
    std::cout << player->getName() << '\n';
    std::cout << "HP: " << player->getCurrentHealth() << "/" << player->getMaxHealth() << '\t' << "Energy: " << player->getCurrentBullet() << "/" << player->getMaxBullet() << '\n';
    if (player->getShield() > 0)
        std::cout << "Shield: " << player->getShield() << '\n';
        
    // Display the enemies' status
    std::cout << "========================================" << '\n';
    
    for (Enemy* em : enemies) {
        std::cout << em->getName() << '\n';
        std::cout << "HP: " << em->getCurrentHealth() << "/" << em->getMaxHealth() << '\n';
        if (em->getType() == "BOSS")
            std::cout << "Type: BOSS: ?!?" << '\n';
        else
            std::cout << "Type: " << em->getType() << ": " << em->getAmount() << '\n';
        if (em->getShield() > 0)
            std::cout << "Shield: " << em->getShield() << '\n';
        std::cout << '\n';
    }
    
    // Display the available cards
    std::cout << "========================================" << '\n';
    std::cout << "Cards: " << '\n';
    for (int i = 0; i < cards.size(); i++) {
        std::cout << "(" << i << "): " << *cards[i] << '\n';
    }

    // Display the option to end the turn
    std::cout << "(" << cards.size() << "): End turn" << '\n';
}

//A turn of the game

bool Game::startRound(Player* player) {
    // Display the current round number
    std::cout << "Round: " << round << '\n';
    this_thread::sleep_for(chrono::milliseconds(2000));
    
    // Retrieve the enemies and player's cards for the current round
    vector<Enemy*> enemies = levels[round];
    vector<Card*> cards;

    while(true) {
        // Shuffle the player's deck
        shuffle(playerDeck.begin(), playerDeck.end(), mt19937{random_device{}()});
        
        // Clear the previous cards and select new cards from the shuffled deck
        cards.clear();
        for (int i = 0; i < 4; i++) cards.push_back(playerDeck[i]);

        while (true) {
            // Display the game status
            displayStatus(player, enemies, cards);

            // Prompt the player to choose a card to play
            int choice = cards.size();
            while (true) {
                std::cout << "Choose card to play: \n";
                choice = system.getInputInRange(0, (int)cards.size());
                
                // Check if the player has enough energy to play the chosen card
                if (choice != cards.size() && cards[choice]->getBulletCost() > player->getCurrentBullet())
                    std::cout << "Not enough Energy Orbs!\n";
                else
                    break;
                    
                std::cout << '\n';
            }

            if (choice == cards.size())
                break;
            else {
                std::cout << '\n';

                // Play the chosen card based on its type
                if (cards[choice]->getType() == "ATTACK") {
                    // Prompt the player to choose a target
                    std::cout << "Choose target: \n";
                    int target = system.getInputInRange(0, enemies.size()-1);

                    // Use the card's ability on the chosen target
                    cards[choice]->use(player, enemies[target]);
                    
                    // Check if the target enemy is defeated
                    if (enemies[target]->isDead()) {
                        std::cout << enemies[target]->getName() << " defeated!" << '\n';
                        this_thread::sleep_for(chrono::milliseconds(1000));
                        // Remove the defeated enemy from the enemies vector
                        enemies.erase(enemies.begin() + target);
                    }
                }
                else if (cards[choice]->getType() == "MELEE") {
                    // Use the card's ability on the first enemy in the vector
                    cards[choice]->use(player, enemies[0]);
                    
                    // Check if the first enemy is defeated
                    if (enemies[0]->isDead()) {
                        std::cout << enemies[0]->getName() << " defeated!" << '\n';
                        this_thread::sleep_for(chrono::milliseconds(1000));
                        // Remove the defeated enemy from the enemies vector
                        enemies.erase(enemies.begin());
                    }                
                }
                else {
                    // Use the card's ability on the player
                    cards[choice]->use(player, player);
                }

                // Remove the played card from the cards vector
                cards.erase(cards.begin() + choice);
            }

            // Check if all enemies are defeated
            if (enemies.empty())
                return true;

            this_thread::sleep_for(chrono::milliseconds(2000));
        }
        
        std::cout << '\n';
        
        // Enemy's turn
        for (Enemy* em : enemies) {
            // Use the enemy's ability based on its type
            if (em->getType() == "ATTACK" || em->getType() == "BOSS")
                em->useAbility(player);
            else
                em->useAbility(enemies[0]);
            
            // Check if the player is defeated
            if (player->isDead())
                return false;

            this_thread::sleep_for(chrono::milliseconds(1000));
        }

        this_thread::sleep_for(chrono::milliseconds(1000));

        // Player's recharge
        std::cout << player->getName() << " RECHARGE once" << '\n';
        player->reload(1);
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

//Main loop of the game

void Game::startGame() {
    // Loop through each round in the game
    for (; round < levels.size(); round++) {
        // Start the current round and check if the player is defeated
        if (!startRound(player)) {
            // Player is defeated
            std::cout << "YOU DIED" << '\n';
            this_thread::sleep_for(chrono::milliseconds(1000));
            std::cout << "GAME OVER" << '\n';
            this_thread::sleep_for(chrono::milliseconds(3000));
            return;
        }

        // Player successfully completes the round
        std::cout << " \nCONGRATS! \n";
        this_thread::sleep_for(chrono::milliseconds(1000));
        std::cout << "ROUND " << round << " WON!" << '\n';
        this_thread::sleep_for(chrono::milliseconds(1000));
        std::cout << '\n' << "You healed for 5, reloaded to full, and all shields were removed" << '\n';
        this_thread::sleep_for(chrono::milliseconds(2000));

        // Reset player's shield, heal, and energy
        player->setShield(0);
        player->getHeal(5);
        player->reload(3);

        // Offer new cards to the player
        std::cout << '\n' << "You can pick 1 of 4 new cards to add to your deck:" << '\n';
        shuffle(allCards.begin(), allCards.end(), mt19937{random_device{}()});
        for (int i = 0; i < 4; i++) 
            std::cout << "(" << i << "): " << *allCards[i] << '\n';

        // Prompt the player to choose a card
        int choice = system.getInputInRange(0, 3);
        this_thread::sleep_for(chrono::milliseconds(1000));
        std::cout << "Nice! " << allCards[choice]->getName() << " has been added to your deck \n\n";

        // Add the chosen card to the player's deck and remove it from the available cards
        playerDeck.push_back(allCards[choice]);
        allCards.erase(allCards.begin() + choice);
        this_thread::sleep_for(chrono::milliseconds(2000));

        // Prompt the player to save the game state
        std::cout << "Do you want to save the current game state? (Y/N)";
        std::string saveInput;

        while (true) {
            // Retrieve the player's input and convert it to lowercase
            getline(std::cin, saveInput);
            saveInput[0] = tolower(saveInput[0]);

            // Check if the input is valid (either 'y' or 'n')
            if (saveInput.length() == 1 && (saveInput[0] == 'y' || saveInput[0] == 'n')) {
                if (saveInput[0] == 'y') {
                    // Save the game state
                    saveGame(SAVEFILE);
                    break;
                }
                else if (saveInput[0] == 'n') {
                    break;
                }
            }

            std::cout << "Invalid input. Please enter 'y' or 'n' \n";
        }
        cout << '\n';
    }
    return;
}
