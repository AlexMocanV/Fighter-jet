#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "enemies.h"
#include "bullet.h"
#include "resource_holder.hpp"
#include "resource_holder.h"
#ifndef GAME_H
#define GAME_H

class Game {
public:
    Game();
    void run();
    void addBullet();
	void isCollision();
private:
    void update();
    void processEvents();
    void render();
private:
    sf::RenderWindow window;
    Player player;
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;
    ResourceHolder<sf::Texture, Textures::ID> textures;
};

#endif