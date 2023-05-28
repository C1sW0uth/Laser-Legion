#ifndef CHARACTER_H
#define CHARACTER_H

#include<bits/stdc++.h>

using namespace std;

class Character {
protected:
    string name; // Name of the character
    int maxHealth; // Maximum health of the character
    int currentHealth; // Current health of the character
    int shield; // Shield value of the character
public:
    // Default constructor
    Character();

    // Parameterized constructor
    Character(string name, int maxHealth);

    // Function to apply damage to the character
    void takeDamage(int amount);

    // Function to apply healing to the character
    void getHeal(int amount);

    // Function to increase the shield value of the character
    void getShield(int amount);

    // Function to check if the character is dead (no health remaining)
    bool isDead();

    // Get the name attribute of the character
    string getName();

    // Get the maxHealth attribute of the character
    int getMaxHealth();

    // Get the currentHealth attribute of the character
    int getCurrentHealth();

    // Get the shield attribute of the character
    int getShield();

    // Set the shield attribute of the character
    void setShield(int shield);

    // Set the currentHealth attribute of the character
    void setCurrentHealth(int health);
};

#endif
