#pragma once

#include <SFML/Graphics.hpp>
#include "GameEventHandler.h"
#include <string>
#include "Game.h"
#define FIRST_LVL_NAME L"Getting started"
#define SECOND_LVL_NAME L"Something new"
#define THIRD_LVL_NAME L"Testing done"
#define STANDART_LEVEL_NUM 3
#define LEVEL_SELECT_BACKGROUND_TEXTURE_FILE "Textures\\Backgrounds\\LevelSelect.jpg"
#define LEVEL_SELECT_BACKGROUND_WIDTH 200
#define LEVEL_SELECT_BACKGROUND_HEIGHT 150
#define LEVEL_SELECT_BUTTON_NUM 2
#define AUP_BUTTON_TEXTURE "Textures\\Objects\\AUpButton.jpg"
#define AUP_BUTTON_PRESSED_TEXTURE "Textures\\Objects\\AUpButtonPressed.jpg"
#define ADOWN_BUTTON_TEXTURE "Textures\\Objects\\ADownButton.jpg"
#define ADOWN_BUTTON_PRESSED_TEXTURE "Textures\\Objects\\ADownButtonPressed.jpg"
#define ABUTTON_WIDTH 15
#define ABUTTON_HEIGHT 15
enum buttons
{
	PLAY = 0,
	BACK = 1,
	NEXT = 2,
	PREVIOUS = 3,
};

enum levels
{
	CUSTOM_LVL=-1,
	FIRST_LVL = 0,
	SECOND_LVL=1,
	THIRD_LVL=2,
};
class Level_select
{
private:
	sf::String levelName;
	int levelSelect;
	sf::RenderWindow* window;
	int mouseClick;
	int buttonPress;
	sf::Event selectEvent;
	sf::FloatRect tempTextSize;
	sf::Vector2u windowSize;
	float scalingX;
	float scalingY;
	sf::Texture buttonTexture;
	sf::Texture pressedButtonTexture;
	sf::Texture backgroundTexture;
	sf::Texture AUpButtonTexture;
	sf::Texture ADownButtonTexture;
	sf::Texture AUpButtonPressedTexture;
	sf::Texture ADownButtonPressedTexture;
	sf::Sprite background;
	sf::Sprite button[2];
	sf::Sprite AUpButton;
	sf::Sprite ADownButton;
	sf::Text buttonText[2];
	sf::Text levelSelectName;
	sf::Font font;
public:
	Level_select(sf::RenderWindow& window);
	int Init();
};

