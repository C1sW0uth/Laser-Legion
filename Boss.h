#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"

class Boss : public Enemy {
private:
    int* stat; // Stores the values for attack, shield, and heal abilities of the boss
public:
    // Default constructor
    Boss();

    // Parameterized constructor
    Boss(string name, int maxHealth, int attack, int shield, int heal);

    // Override function for using boss's ability on a target
    void useAbility(Character* target) override;

    // Get the type of the enemy (BOSS in this case)
    string getType() override {
        return "BOSS";
    }

    // Get the amount (not used in this class)
    int getAmount() override {
        return 0;
    }

    // Destructor
    ~Boss() {
        delete stat; // Deallocate the memory for the stat array
    }
};

#endif
