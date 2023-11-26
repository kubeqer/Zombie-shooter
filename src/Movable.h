#pragma once
#include <SFML/Graphics.hpp>

class Movable {
protected:
    sf::Vector2i position{0,0};
    sf::Vector2i velocity{0,0};
    int framesPerMove = 0;
    int framesToMove = 0;

public:
    virtual void outsideMap();
    void setVelocity(sf::Vector2i v);
    void unsetVelocity(sf::Vector2i v);
    sf::Vector2i Position();
    void updatePos();
    void unUpdatePos();
};