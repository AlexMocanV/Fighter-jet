#include "game.h"
#include "bullet.h"

// Constructor: Initialize window and load bullet texture
Game::Game() : window(sf::VideoMode(1600, 900), "Fighter Jet Game") {
    if (!bulletTexture.loadFromFile("textures/bullet.png")) {
        std::cerr << "Can't load bullet image" << std::endl;
    }
}

void Game::addBullet() {
    // Calculate player center
    sf::Vector2f playercenter = player.getShape().getPosition();

    // Get mouse position relative to window
    sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));

    // Calculate direction from player to mouse
    sf::Vector2f aimDir = mousePosition - playercenter;

    // Normalize the direction vector
    float length = sqrt(aimDir.x * aimDir.x + aimDir.y * aimDir.y);
    if (length > 0.f) {
        aimDir = aimDir / length;
    }
    else {
        aimDir = sf::Vector2f(1.f, 0.f); // Default to right if mouse is at player position
    }
    //aimDir = sf::Vector2f(aimDir.x, 0.f);
    // Calculate bullet starting position (offset from player center)
    sf::Vector2f bulletOffset = aimDir * 20.f;  // Offset to avoid spawning inside player
    sf::Vector2f bulletPosition = playercenter + bulletOffset;

    // Create bullet shape for collision
    sf::CircleShape bulletShape(5.0f);
    bulletShape.setFillColor(sf::Color::Red);
    bulletShape.setOrigin(5.f, 5.f); // Center the shape
    bulletShape.setPosition(bulletPosition);

    // Create bullet sprite for rendering
    sf::Sprite bulletSprite;
    bulletSprite.setTexture(bulletTexture);
    bulletSprite.setOrigin(bulletTexture.getSize().x / 2.f, bulletTexture.getSize().y / 2.f);
    bulletSprite.setPosition(bulletPosition);

    // Create and configure bullet object
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
    for (int i = 0; i < bullets.size(); i++) {
        sf::Vector2f velocity = bullets[i].getDirection() * bullets[i].getSpeed();
        bullets[i].move(velocity.x, velocity.y);
		// if bullet is out of bound remove it
        if (bullets[i].getShape().getPosition().x < 0 || bullets[i].getShape().getPosition().x > window.getSize().x ||
            bullets[i].getShape().getPosition().y < 0 || bullets[i].getShape().getPosition().y > window.getSize().y) {
			bullets.erase(bullets.begin() + i);
        }
    }

    // Update player position based on keyboard input
    float moveSpeed = player.getSpeed();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        player.move(-moveSpeed, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        player.move(moveSpeed, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        player.move(0.f, -moveSpeed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        player.move(0.f, moveSpeed);
}

void Game::render() {
    window.clear(sf::Color::Black);
    window.draw(player.getShape());
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