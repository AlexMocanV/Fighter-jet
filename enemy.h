#pragma once
#include <SFML/Graphics.hpp>
#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
private:
    float health;
    float attackPower;
    float speed;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::ConvexShape hitbox;
public:
    Enemy();
    void takeDamage(float damage);
    float getHealth() const;
    float getSpeed() const;
    float getAttackPower() const;
    void setSprite(const sf::Sprite&);
    sf::Sprite getSprite() const;
	void rotate(float angle);
	float getRotation() const;
    sf::Vector2f getPosition() const;
	void move(float, float);
	void setHealth(float);
    void setPosition(float, float);
	void setRotation(float angle);
    sf::ConvexShape& getHitbox();
};
#endif