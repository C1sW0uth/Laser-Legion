#include "Card.h"

// Default constructor
Card::Card() = default;

// Parameterized constructor
Card::Card(string name, int bulletCost, string type, int amount) : name(name), bulletCost(bulletCost), type(type), amount(amount) {};

// Function to use the card's effect on a target
void Card::use(Player* player, Character* target) {
    cout << player->getName() << " used " << name << " on " << target->getName() << '\n';
    player->setCurrentBullet(player->getCurrentBullet() - bulletCost);

    // Check the type of the card and perform the corresponding action
    if (type == "ATTACK" || type == "MELEE") {
        target->takeDamage(amount);
    }
    else if (type == "SHIELD") {
        player->getShield(amount);
    }
    else if (type == "HEAL") {
        player->getHeal(amount);
    }
    else if (type == "RECHARGE") {
        player->reload(amount);
    }
    else if (type == "ALL") {
        // Handle the case when the card type is "ALL"
        // Add the desired behavior here
    }
}

// Get the amount attribute of the card
int Card::getAmount() {
    return amount;
}

// Get the bullet cost attribute of the card
int Card::getBulletCost() {
    return bulletCost;
}

// Get the name attribute of the card
string Card::getName() {
    return name;
}

// Get the type attribute of the card
string Card::getType() {
    return type;
}
