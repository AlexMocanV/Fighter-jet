#pragma once
#include <SFML/Graphics.hpp>
#ifndef ENEMIES_H
#define ENEMIES_H

class Enemy {
private:
	float health;
	float attackPower;
	float speed;
	sf::Sprite sprite;
	sf::Texture texture;
public:
	Enemy();
	void takeDamage(float damage);
	float getHealth() const;
	float getSpeed() const;
	float getAttackPower() const;
	
	void setSprite(sf::Sprite sprite);
};
#endif