#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Enemies.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

#define greater(x, y) ((x) > (y) ? (x) : (y))
#define smaller(x, y) ((x) > (y) ? (y) : (x))

enum class State{
    playing, lost, menu
};

class GameBoard {
private:
    std::vector<sf::Vector2i> obstaclesPosition;

    std::vector<Enemy*> enemies;
    std::vector<Bullet> bullets;

    MainCharacter player;
    int kills = 0;

    sf::RenderWindow& w;
    sf::Font font;

    int spawnCooldown = 180;
    int spawnNumber = 0;

    State gameState = State::menu;

public:

    GameBoard(sf::RenderWindow& window);
    void restart();
    void pressed(sf::Event::KeyEvent key);
    void released(sf::Event::KeyEvent key);
    void draw();
    void drawMenu();
    void drawLost();
    void update();
    void drawGame();
    void drawUI();
    void doCollisions();
    bool collisionWithEnemies(sf::Vector2i p, int excludeIndex);
    bool collisionWithObstacle(sf::Vector2i p);
    //returns iterator to bullet
    decltype(auto) collisionWithShots(sf::Vector2i pos, bool player);
    void doShots();
    void spawnEnemies();
    void enemyAi();
};
