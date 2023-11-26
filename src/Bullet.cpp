#include "Bullet.h"
Bullet::Bullet(int _dmg, sf::Vector2i _pos, sf::Vector2i _vel, int _framesPerMove, bool _friendly) {
    dmg = _dmg;
    position = _pos;
    velocity = _vel;
    framesPerMove = _framesPerMove;
    friendly = _friendly;
}
Bullet::Bullet() {}

void Bullet::outsideMap() {}

bool Bullet::isBullet() {
    return dmg;
}
int Bullet::damage() {
    return dmg;
}
bool Bullet::isFriendly() {
    return friendly;
}