#pragma once
#include "Movable.h"

class Bullet : public Movable {
    int dmg = 0;
    bool friendly = true;

public:
    Bullet(int _dmg, sf::Vector2i _pos, sf::Vector2i _vel, int _framesPerMove, bool _friendly);
    Bullet();

    void outsideMap() override;

    bool isBullet();
    int damage();
    bool isFriendly();
};