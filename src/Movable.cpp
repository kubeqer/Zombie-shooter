#include "Movable.h"
void Movable::outsideMap() {
    unUpdatePos();
}

void Movable::setVelocity(sf::Vector2i v) {
    if(v.x)
        velocity.x = v.x;
    if(v.y)
        velocity.y = v.y;
}

void Movable::unsetVelocity(sf::Vector2i v) {
    if(v.x == velocity.x)
        velocity.x = 0;
    if(v.y == velocity.y)
        velocity.y = 0;
}

sf::Vector2i Movable::Position() {
    return position;
}

void Movable::updatePos() {
    //speed control
    if(framesToMove > 0) {
        framesToMove--;
        return;
    }
    if(velocity == sf::Vector2i{0,0}) return;
    //cooldown
    framesToMove = framesPerMove;

    position += 40 * velocity;
    if(position.x >= 800 || position.y >= 800 || position.x < 0 || position.y < 0)
        outsideMap();
}
void Movable::unUpdatePos() {
    position -= 40 * velocity;
}