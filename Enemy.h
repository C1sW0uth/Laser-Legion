#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h" // Include the header file for the Character class

class Enemy : public Character {
public:
    Enemy(); // Default constructor for the Enemy class
    Enemy(string name, int maxHealth); // Parameterized constructor for the Enemy class

    virtual void useAbility(Character* target) = 0; // Pure virtual function for using the enemy's ability
    virtual string getType() = 0; // Pure virtual function for getting the type of the enemy
    virtual int getAmount() = 0; // Pure virtual function for getting the amount associated with the enemy

};

#endif
