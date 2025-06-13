#include "enemy.h"
#include <SFML/Graphics.hpp>

Enemy::Enemy() : health(100.0f), attackPower(10.0f), speed(100.0f) {
	// set the triangle shape of the enemy
    hitbox.setPointCount(3);
    hitbox.setPoint(0, sf::Vector2f(0, -15)); // Top point
    hitbox.setPoint(1, sf::Vector2f(-30, 10)); // Bottom left point
    hitbox.setPoint(2, sf::Vector2f(30, 10));  // Bottom right point
	hitbox.setOrigin(0, 0);                   // set origin to the centre of the triangle
    hitbox.setPosition(0, 0);
    hitbox.setFillColor(sf::Color::Red); // Set color to 
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

void Enemy::rotate(float angle) { sprite.rotate(angle); hitbox.rotate(angle); }

float Enemy::getRotation() const { return sprite.getRotation(); }

sf::Vector2f Enemy::getPosition() const { return hitbox.getPosition(); }

void Enemy::move(float offsetX, float offsetY) {
    hitbox.move(offsetX, offsetY);
    sprite.move(offsetX, offsetY);
}

void Enemy::setPosition(float x, float y) {
    hitbox.setPosition(x, y);
    sprite.setPosition(x, y);
}

void Enemy::setHealth(float newHealth) {
    health = newHealth;
    if (health < 0) {
        health = 0; // Ensure health doesn't go below zero
    }
}

void Enemy::setRotation(float angle) {
    sprite.setRotation(angle);
    hitbox.setRotation(angle);
}

sf::ConvexShape& Enemy::getHitbox()
{
    return hitbox;
}

