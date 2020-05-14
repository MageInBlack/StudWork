#include "Ball.h"
Ball::Ball()
{

}

Ball::Ball(sf::Texture& texture, float posX, float posY, float scaleX, float scaleY)
{
	this->sprite.setTexture(texture);
	this->sprite.setPosition(posX, posY);
	this->sprite.setScale(scaleX, scaleY);
	this->inert = 1;
	this->angle = -M_PI_2;
	this->speed = 0;
}

void Ball::Throw(int speed)
{
	inert = 0;
	this->speed = speed;
}

sf::Sprite Ball::getSprite()
{
	return this->sprite;
}

void Ball::setAngle(float angle)
{
	this->angle = angle;
}

void Ball::addAngle(float angle)
{
	this->angle += angle;
	if (this->angle > M_PI) this->angle -= 2 * M_PI;
	if (this->angle < -M_PI) this->angle += 2 * M_PI;
}

int Ball::getSpeed()
{
	return this->speed;
}

sf::FloatRect Ball::getRect()
{
	return this->sprite.getGlobalBounds();
}

bool Ball::isInert()
{
	return inert;
}

void Ball::setPosition(float posX, float posY)
{
	sprite.setPosition(posX, posY);
}

void Ball::move()
{
	sprite.move(speed * cosf(angle), -speed * sinf(angle));
}

void Ball::moveBack()
{
	sprite.move(-speed * cosf(angle), speed * sinf(angle));
}

void Ball::bounce(int wall)
{
	switch (wall)
	{
	case 1:
	{
		this->addAngle(M_PI);
		angle *= -1;
		this->addAngle(M_PI);
	} break;
	case 2:
	{
		this->addAngle(M_PI);
		angle *= -1;
		this->addAngle(0);
	}break;
	}
}