#include "Help.h"
Help::Help(sf::RenderWindow& window)
{
	this->window = &window;
}

int Help::Init()
{
	int mouseClick = -1;
	int buttonPress = -1;
	sf::Vector2u windowSize = window->getSize();
	float scalingX = 1.f * windowSize.x / HELP_MENU_BACKGROUND_WIDTH;
	float scalingY = 1.f * windowSize.y / HELP_MENU_BACKGROUND_HEIGHT;
	if (!this->font.loadFromFile(FONT_FILENAME)) return -1;
	this->backButtonText.setFont(this->font);
	this->backButtonText.setFillColor(sf::Color::White);
	this->backButtonText.setCharacterSize(7 * scalingX);
	this->backButtonText.setString("Back");

	for (int i = 0; i < HELP_STRINGS;i++)
	{
		this->help_text[i].setFont(this->font);
		this->help_text[i].setFillColor(sf::Color::White);
		this->help_text[i].setCharacterSize(7 * scalingX);
		this->help_text[i].setString("");
	}
	this->help_text[0].setString("Use A, D or arrows to move your pong.");
	this->help_text[2].setString("W, Up or Space to launch a ball.");
	this->help_text[3].setString("The pong reflects the ball");
	this->help_text[4].setString("according to the hit part of pong.");
	this->help_text[6].setString("The goal is to break all bricks.");
	this->help_text[7].setString("When you run out of available balls, you loose.");
	this->help_text[8].setString("P or Esc to pause game and Enter to continue.");

	if (!this->backgroundTexture.loadFromFile(HELP_MENU_BACKGROUND_TEXTURE_FILE,sf::IntRect(0,0,HELP_MENU_BACKGROUND_WIDTH,HELP_MENU_BACKGROUND_HEIGHT))) return -1;
	if (!this->buttonTexture.loadFromFile(BUTTON_TEXTURE_FILE, sf::IntRect(0, 0, BUTTON_WIDTH, BUTTON_HEIGHT))) return -1;
	if (!this->PressedButtonTexture.loadFromFile(PRESSED_BUTTON_TEXTURE_FILE, sf::IntRect(0, 0, BUTTON_WIDTH, BUTTON_HEIGHT))) return -1;
	this->background.setTexture(backgroundTexture);
	this->backButton.setTexture(buttonTexture);
	this->background.setScale(scalingX, scalingY);
	this->backButton.setScale(scalingX,scalingY);

	this->backButton.setPosition((windowSize.x - BUTTON_WIDTH*scalingX) / 2, windowSize.y / 5 * 4);
	this->backButtonText.setPosition(this->backButton.getGlobalBounds().left+(this->backButton.getGlobalBounds().width-this->backButtonText.getLocalBounds().width)/2,this->backButton.getGlobalBounds().top);
	
	for (int i = 0; i < HELP_STRINGS; i++)
	{
		this->help_text[i].setPosition((windowSize.x-this->help_text[i].getLocalBounds().width)/2, 50+i*7*scalingX);
	}
	

	while (window->isOpen())
	{
		while (window->pollEvent(helpEvent))
		{
			if (helpEvent.type == sf::Event::Closed) window->close();
			if (helpEvent.type == sf::Event::MouseButtonPressed)
			{
				if (helpEvent.mouseButton.button == sf::Mouse::Left)
				{
					if (ButtonPressCheck(helpEvent.mouseButton.x, helpEvent.mouseButton.y, this->backButton.getGlobalBounds()))
					{
						mouseClick = 0;
						this->backButton.setTexture(PressedButtonTexture);
						this->backButtonText.setFillColor(sf::Color(0x808080ff));
						this->backButtonText.move(0, scalingY);
					}
				}
			}
			if (helpEvent.type == sf::Event::MouseButtonReleased)
			{
				if (helpEvent.mouseButton.button == sf::Mouse::Left)
				{
					if (mouseClick > -1)
					{
						buttonPress = -1;
						if (ButtonPressCheck(helpEvent.mouseButton.x, helpEvent.mouseButton.y, this->backButton.getGlobalBounds()))
							buttonPress = 0;
						
						if (buttonPress == mouseClick) return 0;

						this->backButton.setTexture(this->buttonTexture);
						this->backButtonText.setFillColor(sf::Color::White);
						this->backButtonText.move(0, -scalingY);
						mouseClick = -1;
					}
				}
			}
		}
		window->clear();
		window->draw(background);
		window->draw(backButton);
		window->draw(backButtonText);
		for(int i=0;i<HELP_STRINGS;i++)
			window->draw(help_text[i]);
		window->display();
	}
	return -1;
}