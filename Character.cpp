#include "Character.h"

// Default constructor
Character::Character() = default;

// Parameterized constructor
Character::Character(string name, int maxHealth)
    : name(name), maxHealth(maxHealth), currentHealth(maxHealth), shield(0) {}

// Function to apply damage to the character
void Character::takeDamage(int amount) {
    // Calculate the amount of damage to be reduced by the shield
    int shieldReduct = min(amount, shield);

    // Reduce the shield value and the remaining damage
    shield -= shieldReduct;
    amount -= shieldReduct;

    // Reduce the current health by the remaining damage
    currentHealth -= amount;
}

// Function to apply healing to the character
void Character::getHeal(int amount) {
    // Increase the current health by the healing amount
    currentHealth += amount;

    // Make sure the current health doesn't exceed the maximum health
    currentHealth = min(currentHealth, maxHealth);
}

// Function to increase the shield value of the character
void Character::getShield(int amount) {
    shield += amount;
}

// Function to check if the character is dead
bool Character::isDead() {
    return currentHealth <= 0;
}

// Get the name attribute of the character
string Character::getName() {
    return name;
}

// Get the maxHealth attribute of the character
int Character::getMaxHealth() {
    return maxHealth;
}

// Get the currentHealth attribute of the character
int Character::getCurrentHealth() {
    return currentHealth;
}

// Get the shield attribute of the character
int Character::getShield() {
    return shield;
}

// Set the shield attribute of the character
void Character::setShield(int shield) {
    this->shield = shield;
}

// Set the currentHealth attribute of the character
void Character::setCurrentHealth(int health) {
    this->currentHealth = health;
}
