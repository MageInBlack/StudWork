#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
class Brick
{
private:
	int health = 0;
	
public:
	sf::Sprite sprite;
	Brick();
	Brick(sf::Texture& texture, int health, int posX, int posY, float scaleX, float scaleY);
	void damage(int amount);
	int getHealth();
	void color(sf::Color);
};

