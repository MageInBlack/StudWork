#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "Level_select.h"
#include "Help.h"
#define WINDOW_WIDTH 800 //ширина экрана
#define WINDOW_HEIGHT 600 //высота экрана

enum MenuChoice
{
	MAIN_MENU=0,
	LEVEL_SELECT=1,
	HELP = 2,
};

int main()
{
	MenuChoice choice;
	//создать окно window размерами WINDOW_WIDTHxWINDOW_HEIGHT с названием и кнопкой закрытия
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Arcanoid",sf::Style::Titlebar|sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	int menu_choice=0;
	/*sf::Texture GameMenuTexture;
	if (!GameMenuTexture.loadFromFile("GameMenu.jpg", sf::IntRect(0, 0, 800, 600)));
	sf::Sprite GameMenuSprite;
	GameMenuSprite.setTexture(GameMenuTexture);

	sf::Texture Button;
	if (!Button.loadFromFile("Button.jpg", sf::IntRect(0, 0, 200, 50)));
	sf::Sprite Button1;
	Button1.setTexture(Button);
	Button1.setPosition(200.f, 200.f);

	sf::Font font;
	if (!font.loadFromFile("18690.ttf"));

	sf::Text text;
	text.setFont(font);
	text.setString("Score:");
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::White);
	text.setPosition(16.f, 150.f);*/

	while (menu_choice >= 0)
	{
		switch (menu_choice)
		{
		case MAIN_MENU:
		{
			MainMenu mainMenu(window);
			menu_choice = mainMenu.Init();
			break;
		}
		case LEVEL_SELECT:
		{
			Level_select levelSelect(window);
			menu_choice = levelSelect.Init();
			break;
		}
		case HELP:
		{
			Help help(window);
			menu_choice = help.Init();
			break;
		}
		}
	}
	return 1;
}