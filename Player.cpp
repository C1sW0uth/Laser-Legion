#include "Player.h"

Player::Player() = default; // Default constructor

Player::Player(string name, int maxHealth, int maxBullet) {
    this->name = name;
    this->maxHealth = maxHealth;
    currentHealth = maxHealth;
    this->maxBullet = maxBullet;
    currentBullet = maxBullet;

    isCrit = 0;
}
// Parameterized constructor that initializes a Player object with the provided values.
// It sets the player's name, maximum health, current health, maximum bullet count, current bullet count,
// and initializes the isCrit flag to 0.

int Player::getMaxBullet() {
    return maxBullet; // Returns the maximum bullet count of the player
}

int Player::getCurrentBullet() {
    return currentBullet; // Returns the current bullet count of the player
}

void Player::reload(int amount) {
    currentBullet += amount; // Increase the current bullet count by the specified amount
    currentBullet = min(currentBullet, maxBullet); // Ensure that the current bullet count does not exceed the maximum bullet count
}

void Player::setCurrentBullet(int bullet) {
    if (bullet >= 0 && bullet <= maxBullet)
        currentBullet = bullet; // Set the current bullet count to the specified value if it is within the valid range
    else
        cout << "Error setting bullet!" << '\n'; // Display an error message if the specified bullet count is invalid
}
