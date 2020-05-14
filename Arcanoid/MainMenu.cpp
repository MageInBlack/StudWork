#include "MainMenu.h"

enum buttons
{
	LEVEL_SELECT = 0,
	HELP = 1,
	EXIT=2,
};

MainMenu::MainMenu(sf::RenderWindow& window)
{
	this->window = &window;
}

int MainMenu::Init()
{
	mouseClick=-1;
	buttonPress=-1;
	windowSize = window->getSize();
	scalingX= 1.f * windowSize.x / MAIN_MENU_BACKGROUND_WIDTH;
	scalingY = 1.f * windowSize.y / MAIN_MENU_BACKGROUND_HEIGHT;
	if (!this->font.loadFromFile(FONT_FILENAME)) return -1;
	for (int i = 0; i < MAIN_MENU_BUTTON_NUM; i++)
	{
		this->buttonText[i].setFont(this->font);
		this->buttonText[i].setCharacterSize(7 * scalingX);
		this->buttonText[i].setFillColor(sf::Color::White);
	}
	this->buttonText[0].setString("Level Select");
	this->buttonText[1].setString("Help");
	this->buttonText[2].setString("Quit");

	if (!this->buttonTexture.loadFromFile(BUTTON_TEXTURE_FILE, sf::IntRect(0, 0, BUTTON_WIDTH, BUTTON_HEIGHT))) return -1;
	if (!this->PressedbuttonTexture.loadFromFile(PRESSED_BUTTON_TEXTURE_FILE, sf::IntRect(0, 0, BUTTON_WIDTH, BUTTON_HEIGHT))) return -1;
	if (!this->backgroundTexture.loadFromFile(MAIN_MENU_BACKGROUND_TEXTURE_FILE,sf::IntRect(0,0,MAIN_MENU_BACKGROUND_WIDTH,MAIN_MENU_BACKGROUND_HEIGHT))) return -1;
	this->background.setTexture(backgroundTexture);
	this->background.setScale(scalingX,scalingY);
	for (int i = 0; i < MAIN_MENU_BUTTON_NUM; i++)
	{
		this->button[i].setTexture(buttonTexture);
		this->button[i].setScale(scalingX, scalingY);
		this->button[i].setPosition((windowSize.x - BUTTON_WIDTH*scalingX) / 2, windowSize.y / 4 * (i + 1));
		tempTextSize = this->buttonText[i].getLocalBounds();
		this->buttonText[i].setPosition(this->button[i].getGlobalBounds().left+(this->button[i].getGlobalBounds().width-this->buttonText[i].getLocalBounds().width)/2,this->button[i].getGlobalBounds().top);
	}
	while (window->isOpen())
	{
		while (window->pollEvent(MainMenuEvent))
		{
			if (MainMenuEvent.type == sf::Event::Closed) window->close();
			if (MainMenuEvent.type == sf::Event::MouseButtonPressed)
			{
				if (MainMenuEvent.mouseButton.button == sf::Mouse::Left)
				{
					for (int i = 0; i < MAIN_MENU_BUTTON_NUM; i++)
					{
						if (ButtonPressCheck(MainMenuEvent.mouseButton.x, MainMenuEvent.mouseButton.y, this->button[i].getGlobalBounds()))
						{
							mouseClick = i;
							this->button[i].setTexture(PressedbuttonTexture);
							this->buttonText[i].setFillColor(sf::Color(0x808080ff));
							this->buttonText[i].move(0, scalingY);
							break;
						}
					}
				}
			}
			if (MainMenuEvent.type == sf::Event::MouseButtonReleased)
			{
				if (MainMenuEvent.mouseButton.button == sf::Mouse::Left)
				{
					if (mouseClick > -1 && mouseClick < MAIN_MENU_BUTTON_NUM)
					{
						buttonPress = -1;
						for (int i = 0; i < MAIN_MENU_BUTTON_NUM; i++)
						{
							if (ButtonPressCheck(MainMenuEvent.mouseButton.x, MainMenuEvent.mouseButton.y, this->button[i].getGlobalBounds()))
								buttonPress = i;
						}
						if (buttonPress == mouseClick)
						{
							switch (mouseClick)
							{

							case LEVEL_SELECT:
								return 1;
								break;
							case HELP:
								return 2;
								break;
							case EXIT:
								return -1;
							}
						}
						this->button[mouseClick].setTexture(buttonTexture);
						this->buttonText[mouseClick].setFillColor(sf::Color::White);
						this->buttonText[mouseClick].move(0, -scalingY);
						mouseClick = -1;
					}
				}
			}
		}
		window->clear();
		window->draw(background);
		for (int i = 0; i < MAIN_MENU_BUTTON_NUM; i++)
		{
			window->draw(this->button[i]);
			window->draw(this->buttonText[i]);
		}
		window->display();
	}
	return -1;
}