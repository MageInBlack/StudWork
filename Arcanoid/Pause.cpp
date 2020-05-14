#include "Pause.h"
Pause::Pause(sf::RenderWindow& window)
{
	this->window = &window;
	windowSize=window.getSize();
	scalingX = windowSize.x / PAUSE_MENU_WIDTH;
	scalingY = windowSize.y / PAUSE_MENU_HEIGHT;
}

int Pause::Init()
{
	if (!font.loadFromFile(FONT_FILENAME)) return -1;
	if (!buttonTexture.loadFromFile(BUTTON_TEXTURE_FILE)) return -1;
	if (!pressedButtonTexture.loadFromFile(PRESSED_BUTTON_TEXTURE_FILE)) return -1;
	if (!backgroundTexture.loadFromFile(PAUSE_MENU_FILE)) return -1;
	background.setTexture(backgroundTexture);
	background.setScale(scalingX, scalingY);
	pauseText.setFont(font);
	pauseText.setCharacterSize(15 * scalingX);
	pauseText.setFillColor(sf::Color::White);
	pauseText.setString("Pause");
	pauseText.setPosition((windowSize.x-pauseText.getGlobalBounds().width)/2,windowSize.y/3);
	buttonText[0].setString("Return");
	buttonText[1].setString("To Menu");
	for (int i = 0; i < PAUSE_BUTTONS; i++)
	{
		buttonText[i].setFont(font);
		buttonText[i].setFillColor(sf::Color::White);
		buttonText[i].setCharacterSize(7 * scalingX);
		buttons[i].setTexture(buttonTexture);
		buttons[i].setScale(scalingX, scalingY);
		buttons[i].setPosition((windowSize.x - buttons[i].getGlobalBounds().width) / 2, windowSize.y / 7 * (4 + i));
		buttonText[i].setPosition(buttons[i].getGlobalBounds().left + (buttons[i].getGlobalBounds().width - buttonText[i].getGlobalBounds().width) / 2, buttons[i].getGlobalBounds().top);
	}

	while (window->isOpen())
	{
		while (window->pollEvent(pauseEvent))
		{
			if (pauseEvent.type == sf::Event::Closed) window->close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) return 1;
			if (pauseEvent.type == sf::Event::MouseButtonPressed)
			{
				if (pauseEvent.mouseButton.button == sf::Mouse::Left)
				{
					for (int i = 0; i < PAUSE_BUTTONS; i++)
					{
						if (ButtonPressCheck(pauseEvent.mouseButton.x, pauseEvent.mouseButton.y, buttons[i].getGlobalBounds()))
						{
							mouseClick = i;
							buttons[i].setTexture(pressedButtonTexture);
							buttonText[i].setFillColor(sf::Color(0x808080ff));
							buttonText[i].move(0, scalingY);
							break;
						}
					}
				}
			}
			if (pauseEvent.type == sf::Event::MouseButtonReleased)
			{
				if (pauseEvent.mouseButton.button == sf::Mouse::Left)
				{
					if (mouseClick > -1 && mouseClick < 4)
					{
						buttonPress = -1;
						for (int i = 0; i < PAUSE_BUTTONS; i++)
						{
							if (ButtonPressCheck(pauseEvent.mouseButton.x, pauseEvent.mouseButton.y, this->buttons[i].getGlobalBounds()))
								buttonPress = i;
						}
						if (buttonPress == mouseClick)
						{
							switch (mouseClick)
							{
							case TO_MAIN_MENU:
								return 0;
								break;
							case BACK_TO_GAME:
								return 1;
								break;
							}
						}
						if (mouseClick > -1 && mouseClick < 2)
						{
							this->buttons[mouseClick].setTexture(buttonTexture);
							this->buttonText[mouseClick].setFillColor(sf::Color::White);
							this->buttonText[mouseClick].move(0, -scalingY);
						}
						mouseClick = -1;
					}
				}
			}
		}


		window->draw(background);
		for (int i = 0; i < PAUSE_BUTTONS; i++)
		{
			window->draw(buttons[i]);
			window->draw(buttonText[i]);
		}
		window->draw(pauseText);
		window->display();
	}
	return -1;
}