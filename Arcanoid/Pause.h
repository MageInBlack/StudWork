#pragma once
#include <SFML/Graphics.hpp>
#include "GameEventHandler.h"
#define PAUSE_MENU_WIDTH 200
#define PAUSE_MENU_HEIGHT 150
#define PAUSE_MENU_FILE "Textures\\backgrounds\\PauseMenu.jpg"
#define PAUSE_BUTTONS 2
enum choice
{
	BACK_TO_GAME = 0,
	TO_MAIN_MENU = 1,
};
class Pause
{
private:
	int mouseClick = -1;
	int buttonPress = -1;
	float scalingX, scalingY;
	sf::Vector2u windowSize;
	sf::RenderWindow* window;
	sf::Text pauseText;
	sf::Font font;
	sf::Texture backgroundTexture;
	sf::Sprite background;
	sf::Texture buttonTexture;
	sf::Texture pressedButtonTexture;
	sf::Sprite buttons[2];
	sf::Text buttonText[2];
	sf::Event pauseEvent;
public:
	Pause(sf::RenderWindow& window);
	int Init();
};

