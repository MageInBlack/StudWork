#include "Brick.h"
Brick::Brick()
{

}

Brick::Brick(sf::Texture& texture, int health, int posX, int posY, float scaleX, float scaleY)
{
	this->health = health;
	sprite.setTexture(texture);
	sprite.setScale(scaleX, scaleY);
	sprite.setPosition(posX, posY);
}

void Brick::damage(int amount)
{
	this->health -= amount;
	if (health < 0) health = 0;
}

int Brick::getHealth()
{
	return this->health;
}

void Brick::color(sf::Color col)
{
	this->sprite.setColor(col);
}