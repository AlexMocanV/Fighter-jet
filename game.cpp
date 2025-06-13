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
    // Check for collisions between bullets and enemies
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
        bool collision = false;
        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
            if (bulletIt->getShape().getGlobalBounds().intersects(enemyIt->getHitbox().getGlobalBounds())) {
                // Remove bullet and enemy take damage
                bulletIt = bullets.erase(bulletIt); // Remove bullet on collision
                enemyIt->setHealth(enemyIt->getHealth() - 30);
                if (enemyIt->getHealth() <= 0) {
                    enemyIt = enemies.erase(enemyIt); // Remove enemy on death
                }
                collision = true;
                break; // Exit inner loop since bullet is removed
            }
            else {
                ++enemyIt; // Move to next enemy
            }
        }
        if (!collision) {
            ++bulletIt; // Move to next bullet if no collision occurred
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
		
        Enemy enemy;
		enemy.setSprite(enemySprite);
        enemy.getHitbox().setPosition(enemyPosition);
		enemies.push_back(enemy);
        
	}
    for (int i = 0; i < bullets.size(); i++) {
        // Remove bullet if out of bounds
        if (bullets[i].getShape().getPosition().x < 0 || bullets[i].getShape().getPosition().x > window.getSize().x ||
            bullets[i].getShape().getPosition().y < 0 || bullets[i].getShape().getPosition().y > window.getSize().y) {
            bullets.erase(bullets.begin() + i);
        }
    }
}
void Game::addPlayerBullet() {
    sf::Vector2f playercenter = player.getPosition();
    float playerRotation = player.getRotation() * 3.14159f / 180; // Convert to radians
    sf::Vector2f aimDir(cos(playerRotation), sin(playerRotation));

    // Calculate bullet starting position
	sf::Vector2f bulletPosition = playercenter + aimDir * 110.f; // Offset from player position
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

void Game::addEnemyBullet(Enemy enemy) {
    sf::Vector2f enemycenter = enemy.getPosition();
    float enemyRotation = enemy.getRotation() * 3.14159f / 180; // Convert to radians
    sf::Vector2f aimDir(cos(enemyRotation), sin(enemyRotation));

    // Calculate bullet starting position
    sf::Vector2f bulletPosition = enemycenter + aimDir * 110.f; // Offset from player position
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
    }
}
void Game::handlePlayerMovement()
{
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
}
void Game::handleEnemyMovement()
{
	// Check if right mouse button is pressed to spawn enemies at the window position
    if (enemyClock.getElapsedTime().asMilliseconds() > 1000) {
		enemyClock.restart(); // Reset the clock for the next enemy spawn
        sf::Vector2f windowPosition = sf::Vector2f(window.getSize().x - 100, rand() % window.getSize().y);
        sf::Sprite enemySprite;
        enemySprite.setTexture(textures.get(Textures::Enemy));
        enemySprite.setOrigin(textures.get(Textures::Enemy).getSize().x / 2.f, textures.get(Textures::Enemy).getSize().y / 2.f);
        enemySprite.setPosition(windowPosition);
        Enemy enemy;
        enemy.setSprite(enemySprite);
        enemy.getHitbox().setPosition(windowPosition);
        enemies.push_back(enemy);
    }
	//point the enemy towards the player
    for (Enemy enemy : enemies)
    {
        sf::Vector2f enemyPosition = enemy.getPosition();
        sf::Vector2f playerPosition = player.getPosition();
        sf::Vector2f direction = playerPosition - enemyPosition;
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0.f) {
            // Avoid division by 
            direction /= length; // Normalize the direction vector
            float desiredRotation = atan2(direction.y, direction.x) * 180 / 3.14159f; // Convert to degrees
            std::cout << enemy.getRotation() << std::endl;
            std::cout << desiredRotation << std::endl;
            // get enemy current rotation
            float currentRotation = enemy.getRotation();
            float difference = desiredRotation - currentRotation;

            // Adjust difference to be within -180 to 180 degrees (shortest turn)
            while (difference > 180) difference -= 360;
            while (difference < -180) difference += 360;

            // Define maximum turn rate (degrees per frame)
            float maxTurnRate = 1.0f; // Adjust this to control turning speed

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
            enemy.rotate(rotationAmount);
            // Move the player forward based on its current rotation
            float moveSpeed = enemy.getSpeed();
            float currentAngle = enemy.getRotation() * 3.14159f / 180; // Convert degrees to radians
            sf::Vector2f moveDirection(cos(currentAngle), sin(currentAngle));
             // Only move if there’s a valid direction
            enemy.move(moveDirection.x * moveSpeed, moveDirection.y * moveSpeed);
        }
    }
}
void Game::handleBulletMovement() {
    // Check if left mouse button is held and enough time has passed
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (bulletClock.getElapsedTime().asMilliseconds() > 100) {
            addPlayerBullet();           // Add a bullet
            bulletClock.restart(); // Reset the clock for the next shot
        }
    }
    for (int i = 0; i < bullets.size(); i++) {
        sf::Vector2f velocity = bullets[i].getDirection() * bullets[i].getSpeed();
        bullets[i].move(velocity.x, velocity.y);
    }
}
// Check for collisions and update bullet positions

void Game::update() {
   	handlePlayerMovement(); // Handle player movement and rotation
    handleBulletMovement();
    handleEnemyMovement();
	isCollision();
}
void Game::render() {
    window.clear(sf::Color::Black);
    //window.draw(player.getShape());
    window.draw(player.getSprite());
    for (auto& bullet : bullets) {
        window.draw(bullet.getSprite()); // Draw sprite for visuals
    }
    for (auto& enemy : enemies) {
        window.draw(enemy.getSprite());
        //window.draw(enemy.getHitbox());// Draw sprite for visuals
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