#include <iostream>
#include <SFML/Graphics.hpp>
#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
    float health;
    float attackDamage;
    float speed;
    float bulletSpeed;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::ConvexShape triangleShape; 
public:
    Player();
    void rotate(float angle);            
    float getRotation() const;           
    sf::Vector2f getPosition() const;    
    float getHealth();
    float getAttackDamage();
    float getSpeed();
    float getBulletSpeed();
    sf::Sprite& getSprite();
    sf::Texture getTexture();
    sf::ConvexShape& getShape();
    void move(float offsetX, float offsetY);

    void setHealth(float health);
    void setAttackDamage(float attackDamage);
    void setSpeed(float speed);
    void setBulletSpeed(float bulletSpeed);
    void setSprite(const sf::Sprite& sprite);
    void setTexture(const sf::Texture& texture);
};

#endif