#include "Enemies.h"
Bullet Enemy::shotBullet() {
        return bToShoot;
    }

    int Enemy::damage() {
        return meleeDamage;
    }

    int Enemy::bulletDamage() {
        return 0;
    }

    void Enemy::takeDamage(int damage) {
        HP -= damage;
    }

    bool Enemy::isAlive() {return HP > 0;}

    void Enemy::shoot(sf::Vector2i playerPos) {
        if(shootCooldown > 0) {
            shootCooldown--;
            return;
        }

        bool xequal = position.x == playerPos.x;
        bool yequal = position.y == playerPos.y;
        if(xequal || yequal)
        {
            sf::Vector2i vel{0,0};

            if(yequal)
                vel.x = SIGN(playerPos.x - position.x);
            else
                vel.y = SIGN(playerPos.y - position.y);

            bToShoot = Bullet(bulletDamage(), position, vel, 14, false);
            shootCooldown = framesPerShoot;
        }
    }
    void Enemy::clearBullet() {bToShoot = Bullet();}

    Zombie::Zombie(int x, int y) {
        HP = 4;
        position = sf::Vector2i(x,y);
        framesPerMove = 60;
        meleeDamage = 3;
    }

    sf::Color Zombie::bodyColor() {
        return sf::Color(20, 40, 20);
    }
    sf::Color Zombie::headColor() {
        return sf::Color(0, 100, 0);
    }

    void Zombie::ai(sf::Vector2i playerPos) {
        velocity = sf::Vector2i{0,0};
        if(abs(playerPos.x - position.x) > abs(playerPos.y - position.y)) {
            velocity.x = SIGN(playerPos.x - position.x);
        }
        else {
            velocity.y = SIGN(playerPos.y - position.y);
        }
    }

    Dres::Dres(int x, int y) {
        HP = 5;
        position = sf::Vector2i(x,y);
        framesPerMove = 35;
        framesPerShoot = 100;
        meleeDamage = 2;
    }

    sf::Color Dres::bodyColor() {
        return sf::Color(60, 30, 20);
    }
    sf::Color Dres::headColor() {
        return sf::Color(0, 100, 100);
    }

    int Dres::bulletDamage() {return 1;}

    void Dres::attack() {
        std::cout << "Dres atakuje!" << std::endl;
    }

    void Dres::ai(sf::Vector2i playerPos) {
        velocity = sf::Vector2i{0,0};

        int dx = playerPos.x - position.x;
        int dy = playerPos.y - position.y;

        if((dx*dx + dy*dy) > 400*400)
        {
            if(abs(playerPos.x - position.x) > abs(playerPos.y - position.y)) {
                velocity.x = SIGN(playerPos.x - position.x);
            }
            else {
                velocity.y = SIGN(playerPos.y - position.y);
            }
            return;
        }

        if(abs(playerPos.x - position.x) > abs(playerPos.y - position.y)) {
            velocity.y = SIGN(playerPos.y - position.y);
        }
        else {
            velocity.x = SIGN(playerPos.x - position.x);
        }

        shoot(playerPos);
    }

    Koxy::Koxy(int x, int y) {
        HP = 12;
        position = sf::Vector2i(x,y);
        framesPerMove = 20;
        framesPerShoot = 60;
    }

    sf::Color Koxy::bodyColor() {
        return sf::Color(80, 20, 80);
    }
    sf::Color Koxy::headColor() {
        return sf::Color(100, 0, 0);
    }

    int Koxy::bulletDamage() {
    return 2;
}

    void Koxy::attack() {
        std::cout << "Koxy atakuje!" << std::endl;
    }

    void Koxy::ai(sf::Vector2i playerPos) {
        velocity = sf::Vector2i{0,0};
        int dx = playerPos.x - position.x;
        int dy = playerPos.y - position.y;

        if((dx*dx + dy*dy) >= 280*280)
        {
            if(abs(playerPos.x - position.x) > abs(playerPos.y - position.y)) {
                velocity.x = SIGN(playerPos.x - position.x);
            }
            else {
                velocity.y = SIGN(playerPos.y - position.y);
            }
            return;
        }

        if(abs(playerPos.x - position.x) > abs(playerPos.y - position.y)) {
            velocity.y = SIGN(playerPos.y - position.y);
        }
        else {
            velocity.x = SIGN(playerPos.x - position.x);
        }

        shoot(playerPos);
    }

