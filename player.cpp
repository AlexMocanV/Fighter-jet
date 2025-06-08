#include "player.h"
#include "game.h"
Player::Player() {
    health = 100.0f;
    attackDamage = 10.0f;
    speed = 0.7f;
    bulletSpeed = 10.0f;

    // Set up triangle shape
    triangleShape.setPointCount(3);
    triangleShape.setPoint(0, sf::Vector2f(0, -20));  // Top point
    triangleShape.setPoint(1, sf::Vector2f(-15, 10)); // Bottom left
    triangleShape.setPoint(2, sf::Vector2f(15, 10));  // Bottom right
    triangleShape.setFillColor(sf::Color::Green);
    triangleShape.setOrigin(0, 0);  // Origin at geometric center
    triangleShape.setPosition(400, 300); // Center of the window

    if (!textureJet.loadFromFile("textures/first fighter jet.png")) {
        std::cerr << "Can't load jet image" << std::endl;
    }
	sprite.setTexture(textureJet);
	sprite.setPosition(400, 300); // Center of the window
}
void Player::move(float offsetX, float offsetY) {
    triangleShape.move(offsetX, offsetY);
    sprite.move(offsetX, offsetY);
}
float Player::getHealth() { return health; }
float Player::getAttackDamage() { return attackDamage; }
float Player::getSpeed() { return speed; }
float Player::getBulletSpeed() { return bulletSpeed; }
sf::Sprite Player::getSprite() { return sprite; }
sf::Texture Player::getTexture() { return texture; }
sf::ConvexShape& Player::getShape() { return triangleShape; }

void Player::setHealth(float h) { health = h; }
void Player::setAttackDamage(float d) { attackDamage = d; }
void Player::setSpeed(float s) { speed = s; }
void Player::setBulletSpeed(float s) { bulletSpeed = s; }
void Player::setSprite(const sf::Sprite& s) { sprite = s; }
void Player::setTexture(const sf::Texture& t) { texture = t; }