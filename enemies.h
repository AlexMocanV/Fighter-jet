#pragma once
#include <SFML/Graphics.hpp>
#ifndef ENEMIES_H
#define ENEMIES_H

class Enemy {
private:
    float health;
    float attackPower;
    float speed;
    sf::Sprite sprite;  // Changed from sf::Sprite& to sf::Sprite
    sf::Texture texture;
public:
    Enemy();
    void takeDamage(float damage);
    float getHealth() const;
    float getSpeed() const;
    float getAttackPower() const;
    void setSprite(const sf::Sprite&);
    sf::Sprite getSprite() const;
};
#endif