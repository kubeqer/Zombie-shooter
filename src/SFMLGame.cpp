#include "SFMLGame.h"

void SFMLGame::play(){
    sf::RenderWindow window(sf::VideoMode(900, 800), "Zombie Attack");
    window.setFramerateLimit(60);

    GameBoard board(window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
                board.pressed(event.key);
            else if (event.type == sf::Event::KeyReleased)
                board.released(event.key);
        }

        board.update();
        window.clear();
        board.draw();
        window.display();
    }
}