#pragma once
#include <SFML/Graphics.hpp>
#include "GameEventHandler.h"
#define MAIN_MENU_BUTTON_NUM 3

#define MAIN_MENU_BACKGROUND_TEXTURE_FILE "Textures\\Backgrounds\\MainMenu.jpg"

#define MAIN_MENU_BACKGROUND_WIDTH 200
#define MAIN_MENU_BACKGROUND_HEIGHT 150
class MainMenu
{
private:
	sf::RenderWindow* window;
	int mouseClick;
	int buttonPress;
	sf::Event MainMenuEvent;
	sf::FloatRect tempTextSize;
	sf::Vector2u windowSize;
	float scalingX;
	float scalingY;
	sf::Texture buttonTexture;
	sf::Texture PressedbuttonTexture;
	sf::Texture backgroundTexture;
	sf::Sprite background;
	sf::Sprite button[3];
	sf::Text buttonText[3];
	sf::Font font;
public:
	MainMenu(sf::RenderWindow& window);
	int Init();
};

