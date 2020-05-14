#include "Pong.h"
Pong::Pong()
{

}
Pong::Pong(sf::Texture& texture, float posX, float posY, float scaleX, float scaleY)
{
	sprite.setTexture(texture);
	sprite.setScale(scaleX, scaleY);
	sprite.setPosition(posX, posY);
}

sf::Sprite Pong::getSprite()
{
	return this->sprite;
}

sf::FloatRect Pong::getRect()
{
	return this->sprite.getGlobalBounds();
}

void Pong::setPosition(float posX)
{
	this->sprite.setPosition(posX, sprite.getGlobalBounds().top);
}

void Pong::move(float posX)
{
	this->sprite.move(posX,0);
}