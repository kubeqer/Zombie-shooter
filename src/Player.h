#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include "Movable.h"
#include "Bullet.h"

class MainCharacter : public Movable {
private:
    int HP;
    int maxHP;
    int dmg = 2;

public:
    MainCharacter();

    // reduces the current health points (HP) of the main character by the specified amount.
    void dealDamage(int damage);

    // performs a shooting action for the main character.
    void shoot();

    void increaseHP(int amount);

    //the damage dealt by the main character.
    int damage();

    //simple getters
    int getHP() const;
    int getMaxHP() const;
};
