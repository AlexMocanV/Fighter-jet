#include "enemies.h"
Enemy::Enemy ()
{
	// Initialize enemy attributes
	health = 100;
	attackPower = 10;
}
void Enemy::takeDamage(float damage)
{
	health -= damage;
	if (health < 0) {
		health = 0; // Ensure health doesn't go below zero
	}
}
float Enemy::getHealth() const
{
	return health;
}
float Enemy::getAttackPower() const
{
	return attackPower;
}
float Enemy::getSpeed() const
{
	return speed;
}


