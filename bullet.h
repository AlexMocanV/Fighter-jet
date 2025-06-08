#pragma once
#include <SFML/Graphics.hpp>
#ifndef BULLET_H
#define BULLET_H

class Bullet {
private:
    float speed;
    sf::CircleShape shape;
    sf::Sprite sprite;
    sf::Vector2f direction;
public:
    Bullet();
    float getSpeed();
    sf::Sprite getSprite();
    sf::CircleShape getShape();
    sf::Vector2f getDirection();
    void move(float offsetX, float offsetY);

    void setSpeed(float);
    void setSprite(sf::Sprite);
    void setDirection(sf::Vector2f& dir);
    void setShape(sf::CircleShape);
};

#endif