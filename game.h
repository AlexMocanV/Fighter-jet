#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "bullet.h"
#ifndef GAME_H
#define GAME_H

class Game {
public:
    Game();
    void run();
    void addBullet();
private:
    void update();
    void processEvents();
    void render();
private:
    sf::RenderWindow window;
    Player player;
    std::vector<Bullet> bullets;
    sf::Texture bulletTexture;// Store bullet texture for efficiency
    
};

#endif