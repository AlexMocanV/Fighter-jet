#include "game.h"
#include "bullet.h"
#include "resource_holder.hpp"
#include "resource_holder.h"
// Constructor: Initialize window and load bullet texture
Game::Game() : window(sf::VideoMode(1600, 900), "Fighter Jet Game") {
	textures.load(Textures::ID::Bullet, "textures/small_bullet.png");
	textures.load(Textures::ID::Player, "textures/player.png");
    textures.load(Textures::ID::Enemy, "textures/enemy.png");
	player.getSprite().setTexture(textures.get(Textures::Player));
	player.setTexture(textures.get(Textures::Player));
	player.getSprite().setOrigin(textures.get(Textures::Player).getSize().x / 2.f, textures.get(Textures::Player).getSize().y / 2.f);
}
void Game::isCollision()
{
    // Check for collisions between bullets and player
    for (auto it = bullets.begin(); it != bullets.end();) {
        if (it->getShape().getGlobalBounds().intersects(player.getShape().getGlobalBounds())) {
            // Handle collision (e.g., remove bullet, reduce player health, etc.)
            it = bullets.erase(it); // Remove bullet on collision
			player.setHealth(player.getHealth() - 10); // Example: reduce player health
        } else {
            ++it; // Move to the next bullet
        }
	}
    // Check if player health is below zero
    if (player.getHealth() <= 0) {
        // Handle player death (e.g., end game, reset player, etc.)
        window.close(); // Example: close the window on player death
	}
	//check if player is out of bounds
	sf::Vector2f playerPosition = player.getShape().getPosition();
	if (playerPosition.x < 0 || playerPosition.x > window.getSize().x ||
        playerPosition.y < 0 || playerPosition.y > window.getSize().y) {
		playerPosition.x = std::max(0.f, std::min(playerPosition.x, static_cast<float>(window.getSize().x)));
		playerPosition.y = std::max(0.f, std::min(playerPosition.y, static_cast<float>(window.getSize().y)));
		// Reset player position to within bounds
		player.getShape().setPosition(playerPosition); // Reset player position to within bounds
		player.getSprite().setPosition(playerPosition); // Reset sprite position to match

		//Spawn enemy at random position
		sf::Vector2f enemyPosition(rand() % window.getSize().x, rand() % window.getSize().y);
		sf::Sprite enemySprite;
		enemySprite.setTexture(textures.get(Textures::Enemy));
		enemySprite.setOrigin(textures.get(Textures::Enemy).getSize().x / 2.f, textures.get(Textures::Enemy).getSize().y / 2.f);
		enemySprite.setPosition(enemyPosition);
		// Create enemy object (assuming you have an Enemy class similar to Player)
        Enemy enemy;
		enemy.setSprite(enemySprite);
		enemy.setShape(enemySprite.getGlobalBounds()); // Set shape based on sprite bounds
		enemies.push_back(enemy); // Add enemy to the list
	}
    for (int i = 0; i < bullets.size(); i++) {
        // Remove bullet if out of bounds
        if (bullets[i].getShape().getPosition().x < 0 || bullets[i].getShape().getPosition().x > window.getSize().x ||
            bullets[i].getShape().getPosition().y < 0 || bullets[i].getShape().getPosition().y > window.getSize().y) {
            bullets.erase(bullets.begin() + i);
        }
    }
}
void Game::addBullet() {
    sf::Vector2f playercenter = player.getPosition();
    float playerRotation = player.getRotation() * 3.14159f / 180; // Convert to radians
    sf::Vector2f aimDir(cos(playerRotation), sin(playerRotation));

    // Calculate bullet starting position
	sf::Vector2f bulletPosition = playercenter + aimDir * 90.f; // Offset from player position
    // Create bullet shape
    sf::CircleShape bulletShape(5.0f);
    bulletShape.setFillColor(sf::Color::Red);
    bulletShape.setOrigin(5.f, 5.f);
    bulletShape.setPosition(bulletPosition);

    // Create bullet sprite
    sf::Sprite bulletSprite;
    bulletSprite.setTexture(textures.get(Textures::Bullet));
    bulletSprite.setOrigin(textures.get(Textures::Bullet).getSize().x / 2.f, textures.get(Textures::Bullet).getSize().y / 2.f);
    bulletSprite.setPosition(bulletPosition);

    // Configure bullet
    Bullet bullet;
    bullet.setDirection(aimDir);
    bullet.setShape(bulletShape);
    bullet.setSpeed(0.5f);
    bullet.setSprite(bulletSprite);

    bullets.push_back(bullet);
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        //Add a bullet while mouse button is pressed
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            addBullet();
		}
    }
}

void Game::update() {
    // Update bullet positions
    
	 // Check for collisions and update bullet positions
    for (int i = 0; i < bullets.size(); i++) {
        sf::Vector2f velocity = bullets[i].getDirection() * bullets[i].getSpeed();
        bullets[i].move(velocity.x, velocity.y);
    }
    // Get current rotation
    float currentRotation = player.getRotation();

    // Calculate desired rotation towards the mouse
    sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
    sf::Vector2f playerPosition = player.getPosition();
    sf::Vector2f direction = mousePosition - playerPosition;
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    float desiredRotation = atan2(direction.y, direction.x) * 180 / 3.14159f; // Convert radians to degrees

    // Calculate the difference between current and desired rotation
    float difference = desiredRotation - currentRotation;

    // Adjust difference to be within -180 to 180 degrees (shortest turn)
    while (difference > 180) difference -= 360;
    while (difference < -180) difference += 360;

    // Define maximum turn rate (degrees per frame)
    float maxTurnRate = 0.25f; // Adjust this to control turning speed

    // Determine rotation amount for this frame
    float rotationAmount;
    if (difference > maxTurnRate) {
        rotationAmount = maxTurnRate;      // Turn clockwise
    }
    else if (difference < -maxTurnRate) {
        rotationAmount = -maxTurnRate;     // Turn counterclockwise
    }
    else {
        rotationAmount = difference;       // Snap to exact angle if within turn rate
    }

    // Apply the rotation
    player.rotate(rotationAmount);

    // Move the player forward based on its current rotation
    float moveSpeed = player.getSpeed();
    float currentAngle = player.getRotation() * 3.14159f / 180; // Convert degrees to radians
    sf::Vector2f moveDirection(cos(currentAngle), sin(currentAngle));
    if (length > 0.f) { // Only move if there’s a valid direction
        player.move(moveDirection.x * moveSpeed, moveDirection.y * moveSpeed);
    }

    // Check for collisions and update bullet positions
	isCollision();
}

void Game::render() {
    window.clear(sf::Color::Black);
    //window.draw(player.getShape());
    window.draw(player.getSprite());
    for (auto& bullet : bullets) {
        window.draw(bullet.getSprite()); // Draw sprite for visuals
    }
    window.display();
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}