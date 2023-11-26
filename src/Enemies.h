#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Movable.h"
#include "Bullet.h"

#define SIGN(x) ((x) > 0 ? 1 : ((x) == 0 ? 0 : -1))

class Enemy : public Movable {
protected:
    int HP;
    int meleeDamage;
    Bullet bToShoot;

    int shootCooldown = 0;
    int framesPerShoot;

public:

    virtual void ai(sf::Vector2i playerPos) = 0;

    virtual Bullet shotBullet();

    virtual sf::Color bodyColor() = 0;
    virtual sf::Color headColor() = 0;

    int damage();

    virtual int bulletDamage();

    void takeDamage(int damage);

    bool isAlive();

    void shoot(sf::Vector2i playerPos);
    void clearBullet();
};


class Zombie : public Enemy {
public:
    Zombie(int x, int y);

    sf::Color bodyColor();
    sf::Color headColor();

    void ai(sf::Vector2i playerPos);
};

class Dres : public Enemy {
public:
    Dres(int x, int y);

    sf::Color bodyColor();
    sf::Color headColor();

    int bulletDamage() override;

    void attack();

    void ai(sf::Vector2i playerPos) override;
};

class Koxy : public Enemy {
public:
    Koxy(int x, int y);

    sf::Color bodyColor() override;
    sf::Color headColor() override;

    int bulletDamage() override;
    void attack();

    void ai(sf::Vector2i playerPos) override;
};
