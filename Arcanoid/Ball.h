#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <SFML/Graphics.hpp>

class Ball
{
private:
	sf::Sprite sprite;
	int speed=0;
	float angle=M_PI_4;
	bool inert = 1;
public:
	Ball();
	Ball(sf::Texture& texture,float posX, float posY, float scaleX, float scaleY);
	void Throw(int speed);
	sf::Sprite getSprite();
	void setAngle(float angle);
	void addAngle(float angle);
	int getSpeed();
	sf::FloatRect getRect();
	bool isInert();
	void setPosition(float posX, float posY);
	void move();
	void moveBack();
	void bounce(int wall);//1-top/bottom 2-right/left
};

