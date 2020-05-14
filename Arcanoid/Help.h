#pragma once
#include <SFML/Graphics.hpp>
#include "GameEventHandler.h"

#define HELP_STRINGS 10
#define HELP_MENU_BACKGROUND_WIDTH 200
#define HELP_MENU_BACKGROUND_HEIGHT 150
#define HELP_MENU_BACKGROUND_TEXTURE_FILE "Textures\\Backgrounds\\HelpMenu.jpg"
class Help
{
private:
	sf::RenderWindow* window;
	sf::Sprite background;
	sf::Text help_text[HELP_STRINGS];
	sf::Font font;
	sf::Sprite backButton;
	sf::Text backButtonText;
	sf::Texture backgroundTexture;
	sf::Texture buttonTexture;
	sf::Texture PressedButtonTexture;
	sf::Event helpEvent;
public:
	Help(sf::RenderWindow& window);
	
	int Init();
};

