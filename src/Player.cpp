#include "Player.h"
MainCharacter::MainCharacter() {
    HP = 10;
    maxHP = 10;
    position = {0,0};
    velocity = {0,0};
    framesPerMove = 15;
}

void MainCharacter::dealDamage(int damage){
    HP -= damage;
}
void MainCharacter::shoot() {
}

void MainCharacter::increaseHP(int amount) {
    HP += amount;
}

int MainCharacter::damage() {
    return dmg;
}

int MainCharacter::getHP() const {
    return HP;
}
int MainCharacter::getMaxHP() const {
    return maxHP;
}
