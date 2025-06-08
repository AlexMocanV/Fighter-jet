#include "bullet.h"

Bullet::Bullet() {}

float Bullet::getSpeed() { return speed; }
sf::Sprite Bullet::getSprite() { return sprite; }
sf::Vector2f Bullet::getDirection() { return direction; }
sf::CircleShape Bullet::getShape() { return shape; }
void Bullet::move(float offsetX, float offsetY) {
    shape.move(offsetX, offsetY);
    sprite.move(offsetX, offsetY);
}

void Bullet::setSpeed(float newSpeed) { speed = newSpeed; }
void Bullet::setSprite(sf::Sprite newSprite) { sprite = newSprite; }
void Bullet::setDirection(sf::Vector2f& newDirection) { direction = newDirection; }
void Bullet::setShape(sf::CircleShape newShape) { shape = newShape; }