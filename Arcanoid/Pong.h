#pragma once
#include <SFML/Graphics.hpp>
class Pong
{
private:
	sf::Sprite sprite;
	
public:
	Pong();
	Pong(sf::Texture& texture, float posX, float posY, float scaleX, float scaleY);
	sf::Sprite getSprite();
	sf::FloatRect getRect();
	void setPosition(float posX);
	void move(float posX);
};

