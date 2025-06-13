#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "resource_holder.hpp"
#include "resource_holder.h"
#ifndef GAME_H
#define GAME_H

class Game {
public:
    Game();
    void run();
    void addPlayerBullet();
    void addEnemyBullet(Enemy);
	void isCollision();
    void handlePlayerMovement();
	void handleEnemyMovement();
	void handleBulletMovement();
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
    sf::Clock bulletClock;
    sf::Clock enemyClock;
};

#endif