#include "GameBoard.h"
#include "Player.h"
#include "Enemies.h"
GameBoard::GameBoard(sf::RenderWindow& window) : w(window) {
    if (!font.loadFromFile(
            "fonts/font.ttf")) {
        std::cerr << "ERROR NO FONT FOUND" << std::endl;
    }
}

void GameBoard::restart() {
    spawnNumber = 0;
    spawnCooldown = 180;
    for(auto it = enemies.begin(); it < enemies.end(); it++) {
        delete (*it);
        enemies.erase(it);
    }
    for(auto it = bullets.begin(); it < bullets.end(); it++) {
        bullets.erase(it);
    }
    kills = 0;
    player = MainCharacter();
}

void GameBoard::pressed(sf::Event::KeyEvent key) {
    if(gameState == State::lost) {
        gameState = State::menu;
        restart();
        return;
    }
    if(gameState == State::menu) {
        gameState = State::playing;
        return;
    }

    using Key = sf::Keyboard;
    sf::Vector2i v(0,0);
    sf::Vector2i bulletv(0,0);
    Bullet bToShoot;
    switch(key.code) {
        //moving
        case Key::W:
            v.y--;
            break;
        case Key::S:
            v.y++;
            break;
        case Key::A:
            v.x--;
            break;
        case Key::D:
            v.x++;
            break;
        case Key::Up:
            bulletv.y--;
            break;
        case Key::Down:
            bulletv.y++;
            break;
        case Key::Left:
            bulletv.x--;
            break;
        case Key::Right:
            bulletv.x++;
            break;
    }
    player.setVelocity(v);

    if(bulletv.x != 0 || bulletv.y != 0) {
        player.shoot();
        Bullet b(player.damage(), player.Position(), bulletv, 8, true);
        bullets.push_back(b);
    }
}

void GameBoard::released(sf::Event::KeyEvent key) {
    if(gameState != State::playing)
        return;

    using Key = sf::Keyboard;
    sf::Vector2i v(0,0);

    switch(key.code) {
        case Key::W:
            v.y--;
            break;
        case Key::S:
            v.y++;
            break;
        case Key::A:
            v.x--;
            break;
        case Key::D:
            v.x++;
            break;
    }
    player.unsetVelocity(v);
}

void GameBoard::draw() {
    switch(gameState) {
        case State::playing:
            drawGame();
            break;
        case State::lost:
            drawLost();
            break;
        case State::menu:
            drawMenu();
            break;
    }
}

void GameBoard::drawMenu() {
    sf::Text t("ZOMBIE ATTACK!", font, 80);
    t.setPosition(40,20);
    t.setFillColor(sf::Color::White);
    w.draw(t);

    t.setString("Press any key to begin...");
    t.setCharacterSize(50);
    t.setPosition(40, 500);
    w.draw(t);
}

void GameBoard::drawLost() {
    drawGame();
    sf::RectangleShape rect({500, 150});
    rect.setPosition(200,300);
    rect.setFillColor(sf::Color(40,40,40));
    w.draw(rect);

    sf::Text t("GAME OVER", font, 60);
    t.setFillColor(sf::Color::White);
    t.setPosition(250, 310);
    w.draw(t);

    t.setString("Press any key to return to menu...");
    t.setCharacterSize(20);
    t.setPosition(250, 410);
    w.draw(t);
}

void GameBoard::update() {
    if(gameState == State::playing) {
        spawnEnemies();
        enemyAi();
        doShots();
        doCollisions();
        if(player.getHP() <= 0) gameState = State::lost;
    }
}

void GameBoard::drawGame() {
    for(int x = 0; x < 20; x++)
        for(int y = 0; y < 20; y++)
        {
            sf::RectangleShape rect({38, 38});
            rect.setPosition(x * 40 + 1, y * 40 + 1);
            rect.setFillColor(sf::Color(20, 20, 20));
            w.draw(rect);
        }

    auto ppos = player.Position();
    sf::RectangleShape rect({20,20});
    rect.setPosition(ppos.x + 10, ppos.y + 19);
    rect.setFillColor(sf::Color::Blue);
    w.draw(rect);
    sf::CircleShape circ(10);
    circ.setPosition(ppos.x + 10, ppos.y + 2);
    circ.setFillColor(sf::Color::Yellow);
    w.draw(circ);

    for(auto b : bullets)
    {
        sf::CircleShape c(5);
        auto pos = b.Position();
        c.setPosition(pos.x+15, pos.y+15);
        if(b.isFriendly())
            c.setFillColor(sf::Color::White);
        else
            c.setFillColor(sf::Color::Red);
        w.draw(c);
    }

    for(auto e : enemies)
    {
        auto ppos = e->Position();
        sf::RectangleShape rect({20,20});
        rect.setPosition(ppos.x + 10, ppos.y + 19);
        rect.setFillColor(e->bodyColor());
        w.draw(rect);
        sf::CircleShape circ(10);
        circ.setPosition(ppos.x + 10, ppos.y + 2);
        circ.setFillColor(e->headColor());
        w.draw(circ);
    }

    drawUI();
}

void GameBoard::drawUI() {
    sf::Text t("HP", font, 50);
    t.setPosition(820,10);
    t.setFillColor(sf::Color::White);
    w.draw(t);
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::Red);
    rect.setSize({50, 200});
    rect.setPosition(825,70);
    w.draw(rect);
    rect.setFillColor(sf::Color::Green);
    int hplen = 200 * greater(0,player.getHP()) / player.getMaxHP();
    rect.setSize({50, (float)hplen});
    rect.setPosition(825, 70 + 200 - hplen);
    w.draw(rect);

    t.setString(std::to_string(kills));
    t.setCharacterSize(32);
    t.setPosition(820,300);
    w.draw(t);

    t.setString("kills");
    t.setPosition(820,340);
    w.draw(t);
}

void GameBoard::doCollisions() {
    player.updatePos();
    bool movedBack = false;
    for(int i = 0; i < enemies.size(); i++)
    {
        auto e = enemies[i];
        e->updatePos();
        if(e->Position() == player.Position())
        {
            player.dealDamage(e->damage());
            e->unUpdatePos();
        }
        else if(collisionWithObstacle(e->Position()) ||
                collisionWithEnemies(e->Position(), i))
            e->unUpdatePos();
    }
    if(collisionWithObstacle(player.Position()) && !movedBack)
        player.unUpdatePos();
}

bool GameBoard::collisionWithEnemies(sf::Vector2i p, int excludeIndex = -1) {
    for(int i = 0; i < enemies.size(); i++)
    {
        if(i == excludeIndex)
            continue;
        if(enemies[i]->Position() == p)
            return true;
    }

    return false;
}

bool GameBoard::collisionWithObstacle(sf::Vector2i p) {
    for(auto o : obstaclesPosition)
    {
        if(o == p) return true;
    }
    return false;
}

decltype(auto) GameBoard::collisionWithShots(sf::Vector2i pos, bool player)
{
    for(auto it = bullets.begin(); it < bullets.end(); it++)
    {
        if((player != (*it).isFriendly()) && ((*it).Position() == pos))
        {
            return it;
        }
    }
    return bullets.end();
}

void GameBoard::doShots() {
    for(auto it = bullets.begin(); it < bullets.end(); it++)
    {
        (*it).updatePos();
        auto pos = (*it).Position();
        if(collisionWithObstacle(pos) ||
           pos.x >= 800 || pos.x < 0 ||
           pos.y >= 800 || pos.y < 0)

            bullets.erase(it);
    }

    auto bullet = collisionWithShots(player.Position(), true);
    if(bullet != bullets.end()) {
        player.dealDamage((*bullet).damage());
        bullets.erase(bullet);
    }

    for(auto it = enemies.begin(); it < enemies.end(); it++)
    {
        auto e = (*it);
        auto enemyBullet = e->shotBullet();
        if(enemyBullet.isBullet()) {
            bullets.push_back(enemyBullet);
            e->clearBullet();
        }

        bullet = collisionWithShots(e->Position(), false);
        if(bullet != bullets.end()) {
            e->takeDamage((*bullet).damage());
            bullets.erase(bullet);

            if(!e->isAlive()) {
                delete e;
                enemies.erase(it);
                kills++;
            }
            break;
        }
    }
}

void GameBoard::spawnEnemies() {
    if(spawnCooldown > 0) {
        spawnCooldown--;
        return;
    }

    srand(time(0));
    int r = rand() % smaller(7 + spawnNumber, 30);
    int x = 19, y = 19;
    int r2 = rand()%40;
    if(r2 >= 20)
        x = r2 - 20;
    else
        y = r2;

    x*=40, y*=40;

    int pluscooldown = 0;
    if(r < 15) {
        Enemy* z = new Zombie(x, y);
        enemies.push_back(z);
    }
    else if(r < 25) {
        Enemy* d = new Dres(x, y);
        enemies.push_back(d);
        pluscooldown = 180 - 2 * smaller(spawnNumber, 50);
    }
    else {
        Enemy* k = new Koxy(x, y);
        enemies.push_back(k);
        pluscooldown = 360 - 3 * smaller(spawnNumber, 80);
    }

    spawnNumber++;
    spawnCooldown = 5*60 - 10 * smaller(spawnNumber, 24) + pluscooldown;
}

void GameBoard::enemyAi() {
    for(auto e : enemies)
    {
        e->ai(player.Position());
        auto bullet = e->shotBullet();
        if(bullet.isBullet())
            bullets.push_back(bullet);
    }
}