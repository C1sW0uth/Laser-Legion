#include "Minion.h"

Minion::Minion() = default; // Default constructor

Minion::Minion(string name, int maxHealth, string type, int amount) : Enemy(name, maxHealth), type(type), amount(amount) {};
// Parameterized constructor that initializes the Minion object with the provided values

void Minion::useAbility(Character* target) {
    cout << name << " " << type << " " << target->getName() << " for " << amount << '\n';

    if (type == "ATTACK") {
        target->takeDamage(amount); // Apply damage to the target character
    }
    else if (type == "SHIELD") {
        target->getShield(amount); // Apply shield to the target character
    }
    else if (type == "HEAL") {
        target->getHeal(amount); // Heal the target character
    }
}
// Implementation of the useAbility() function inherited from the Enemy class.
// Performs the specified ability on the target character based on the Minion's type and amount.

string Minion::getType() {
    return type; // Returns the type of the Minion
}

int Minion::getAmount() {
    return amount; // Returns the amount associated with the Minion
}
