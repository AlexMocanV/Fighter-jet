#include "player.h"
#include "game.h"
Player::Player() {
    health = 100.0f;
    attackDamage = 10.0f;
    speed = 0.3f;
    bulletSpeed = 10.0f;

    // Set up triangle shape
    hitbox.setPointCount(3);
    // Top point
    hitbox.setPoint(0, sf::Vector2f(-35, -18)); // Top
	// Left point
    hitbox.setPoint(1, sf::Vector2f(-50, 18)); // Bottom left
	// Right point
    hitbox.setPoint(2, sf::Vector2f(72, 18)); // Bottom right
    
    hitbox.setFillColor(sf::Color::Green);
	// Origin at geometric center for the values used
	// Center of the triangle
    hitbox.setOrigin(0, 0); // No offset
	
    hitbox.setPosition(400, 300); // Center of the window
	sprite.setPosition(400, 300); // Center of the window
}
void Player::move(float offsetX, float offsetY) {
    hitbox.move(offsetX, offsetY);
    sprite.move(offsetX, offsetY);
}
float Player::getHealth() { return health; }
float Player::getAttackDamage() { return attackDamage; }
float Player::getSpeed() { return speed; }
float Player::getBulletSpeed() { return bulletSpeed; }
sf::Sprite& Player::getSprite() { return sprite; }
sf::Texture& Player::getTexture() { return texture; }
sf::ConvexShape& Player::getShape() { return hitbox; }

void Player::setHealth(float h) { health = h; }
void Player::setAttackDamage(float d) { attackDamage = d; }
void Player::setSpeed(float s) { speed = s; }
void Player::setBulletSpeed(float s) { bulletSpeed = s; }
void Player::setSprite(const sf::Sprite& s) { sprite = s; }
void Player::setTexture(const sf::Texture& t) { texture = t; }

void Player::rotate(float angle) { sprite.rotate(angle); hitbox.rotate(angle);}

float Player::getRotation() const { return sprite.getRotation(); }

sf::Vector2f Player::getPosition() const { return hitbox.getPosition();}