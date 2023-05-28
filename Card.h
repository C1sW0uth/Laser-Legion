#ifndef CARD_H
#define CARD_H

#include<bits/stdc++.h>
#include "Character.h"
#include "Player.h"
using namespace std;

class Card {
private:
    string name; // Name of the card
    string type; // Type of the card (e.g., ATTACK, SHIELD, HEAL)
    int amount; // Amount associated with the card (e.g., damage amount, shield amount)
    int bulletCost; // Bullet cost required to use the card
public:
    // Default constructor
    Card();

    // Parameterized constructor
    Card(string name, int bulletCost, string type, int amount);

    // Function to use the card's effect on a target
    void use(Player* player, Character* target);

    // Get the name attribute of the card
    string getName();

    // Get the type attribute of the card
    string getType();

    // Get the amount attribute of the card
    int getAmount();

    // Get the bullet cost attribute of the card
    int getBulletCost();

    // Print out the card's information
    friend ostream& operator <<(ostream& os, const Card& card) {
        os << std::left << std::setw(25) 
        << card.name << card.type
        << "\t for " << card.amount 
        << "\t Cost: " << card.bulletCost;
        return os;
    }
};

#endif
