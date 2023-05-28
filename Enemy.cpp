#include "Enemy.h" // Include the header file for the Enemy class

Enemy::Enemy() = default; // Default constructor for the Enemy class
Enemy::Enemy(string name, int maxHealth) : Character(name, maxHealth) {}; // Parameterized constructor for the Enemy class, inheriting from the Character class
