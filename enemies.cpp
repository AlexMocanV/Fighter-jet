#include "enemies.h"
#include <SFML/Graphics.hpp>

Enemy::Enemy() : health(100.0f), attackPower(10.0f), speed(1.0f) {
    // sprite and texture are default-constructed automatically
}

void Enemy::takeDamage(float damage)
{
    health -= damage;
    if (health < 0) {
        health = 0; // Ensure health doesn't go below zero
    }
}

float Enemy::getHealth() const
{
    return health;
}

float Enemy::getAttackPower() const
{
    return attackPower;
}

float Enemy::getSpeed() const
{
    return speed;
}

void Enemy::setSprite(const sf::Sprite& spritePath)
{
    sprite = spritePath;
}

sf::Sprite Enemy::getSprite() const
{
    return sprite;
}