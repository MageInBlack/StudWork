#include "Level_select.h"
Level_select::Level_select(sf::RenderWindow& window)
{
	this->window = &window;
	levelSelect = 0;
	mouseClick = -1;
	buttonPress = -1;
	windowSize = this->window->getSize();
}
int Level_select::Init()
{
	scalingX = 1.f * windowSize.x/LEVEL_SELECT_BACKGROUND_WIDTH;
	scalingY = 1.f * windowSize.y/LEVEL_SELECT_BACKGROUND_HEIGHT;
	if (!font.loadFromFile(FONT_FILENAME)) return -1;
	for (int i = 0; i < LEVEL_SELECT_BUTTON_NUM; i++)
	{
		buttonText[i].setFont(font);
		buttonText[i].setCharacterSize(7 * scalingX);
		buttonText[i].setFillColor(sf::Color::White);
	}
	buttonText[0].setString("Play");
	buttonText[1].setString("Back");
	levelSelectName.setFont(font);
	levelSelectName.setCharacterSize(7 * scalingX);
	levelSelectName.setFillColor(sf::Color::White);

	if (!AUpButtonTexture.loadFromFile(AUP_BUTTON_TEXTURE, sf::IntRect(0, 0, ABUTTON_WIDTH, ABUTTON_HEIGHT)));
	if (!AUpButtonPressedTexture.loadFromFile(AUP_BUTTON_PRESSED_TEXTURE, sf::IntRect(0, 0, ABUTTON_WIDTH, ABUTTON_HEIGHT)));
	if (!ADownButtonTexture.loadFromFile(ADOWN_BUTTON_TEXTURE, sf::IntRect(0, 0, ABUTTON_WIDTH, ABUTTON_HEIGHT)));
	if (!ADownButtonPressedTexture.loadFromFile(ADOWN_BUTTON_PRESSED_TEXTURE, sf::IntRect(0, 0, ABUTTON_WIDTH, ABUTTON_HEIGHT)));
	AUpButton.setTexture(AUpButtonTexture);
	AUpButton.setScale(scalingX, scalingY);
	ADownButton.setTexture(ADownButtonTexture);
	ADownButton.setScale(scalingX, scalingY);

	if (!buttonTexture.loadFromFile(BUTTON_TEXTURE_FILE, sf::IntRect(0, 0, BUTTON_WIDTH, BUTTON_HEIGHT))) return -1;
	if (!pressedButtonTexture.loadFromFile(PRESSED_BUTTON_TEXTURE_FILE, sf::IntRect(0, 0, BUTTON_WIDTH, BUTTON_HEIGHT))) return -1;
	if (!backgroundTexture.loadFromFile(LEVEL_SELECT_BACKGROUND_TEXTURE_FILE, sf::IntRect(0, 0, LEVEL_SELECT_BACKGROUND_WIDTH, LEVEL_SELECT_BACKGROUND_HEIGHT))) return -1;
	background.setTexture(backgroundTexture);
	background.setScale(scalingX, scalingY);
	for (int i = 0; i < LEVEL_SELECT_BUTTON_NUM; i++)
	{
		button[i].setTexture(buttonTexture);
		button[i].setScale(scalingX, scalingY);
		button[i].setPosition((windowSize.x - BUTTON_WIDTH * scalingX) / 2, windowSize.y / 5 * (i + 3));
		tempTextSize = buttonText[i].getLocalBounds();
		buttonText[i].setPosition(button[i].getGlobalBounds().left + (button[i].getGlobalBounds().width - buttonText[i].getLocalBounds().width) / 2, button[i].getGlobalBounds().top);
	}
	AUpButton.setPosition(windowSize.x/2-AUpButton.getGlobalBounds().width,windowSize.y/5*2);
	ADownButton.setPosition(windowSize.x / 2, windowSize.y / 5*2);
	while (window->isOpen())
	{
		
		while (window->pollEvent(selectEvent))
		{
			if (selectEvent.type == sf::Event::Closed) window->close();
			if (selectEvent.type == sf::Event::TextEntered)
			{
				if (levelSelect != -1)
				{
					levelSelect = -1;
					levelName.clear();
				}
				if (selectEvent.text.unicode != 0x08) { if (levelName.getSize() < 33) levelName += selectEvent.text.unicode;}
				else if (!levelName.isEmpty()) levelName.erase(levelName.getSize()-1);
			}
			if (selectEvent.type == sf::Event::MouseButtonPressed)
			{
				if (selectEvent.mouseButton.button == sf::Mouse::Left)
				{
					for (int i = 0; i < LEVEL_SELECT_BUTTON_NUM; i++)
					{
						if (ButtonPressCheck(selectEvent.mouseButton.x, selectEvent.mouseButton.y, button[i].getGlobalBounds()))
						{
							mouseClick = i;
							button[i].setTexture(pressedButtonTexture);
							buttonText[i].setFillColor(sf::Color(0x808080ff));
							buttonText[i].move(0, scalingY);
							break;
						}
					}
					if (ButtonPressCheck(selectEvent.mouseButton.x, selectEvent.mouseButton.y, AUpButton.getGlobalBounds()))
					{
						mouseClick = NEXT;
						AUpButton.setTexture(AUpButtonPressedTexture);
					}
					if (ButtonPressCheck(selectEvent.mouseButton.x, selectEvent.mouseButton.y, ADownButton.getGlobalBounds()))
					{
						mouseClick = PREVIOUS;
						ADownButton.setTexture(ADownButtonPressedTexture);
					}
				}
			}
			if (selectEvent.type == sf::Event::MouseButtonReleased)
			{
				if (selectEvent.mouseButton.button == sf::Mouse::Left)
				{
					if (mouseClick > -1 && mouseClick < 4)
					{
						buttonPress = -1;
						for (int i = 0; i < LEVEL_SELECT_BUTTON_NUM; i++)
						{
							if (ButtonPressCheck(selectEvent.mouseButton.x, selectEvent.mouseButton.y, this->button[i].getGlobalBounds()))
								buttonPress = i;
						}
						if (ButtonPressCheck(selectEvent.mouseButton.x, selectEvent.mouseButton.y, AUpButton.getGlobalBounds()))
							buttonPress = NEXT;
						if (ButtonPressCheck(selectEvent.mouseButton.x, selectEvent.mouseButton.y, ADownButton.getGlobalBounds()))
							buttonPress = PREVIOUS;
						if (buttonPress == mouseClick)
						{
							switch (mouseClick)
							{
							case PLAY:
							{
								Game game(*window);
								return game.Init(levelName);
							}
							case BACK:
								return 0;
							case NEXT:
							{
								levelSelect = (levelSelect + 1) % STANDART_LEVEL_NUM;
								break;
							}
							case PREVIOUS:
							{
								levelSelect = (levelSelect + STANDART_LEVEL_NUM - 1) % STANDART_LEVEL_NUM;
								break;
							}
							}
						}
						if (mouseClick > -1 && mouseClick < 2)
						{
							this->button[mouseClick].setTexture(buttonTexture);
							this->buttonText[mouseClick].setFillColor(sf::Color::White);
							this->buttonText[mouseClick].move(0, -scalingY);
						}
						if (mouseClick == NEXT)
							AUpButton.setTexture(AUpButtonTexture);
						if (mouseClick == PREVIOUS)
							ADownButton.setTexture(ADownButtonTexture);
						mouseClick = -1;
					}
				}
			}
		}
		switch (levelSelect)
		{
		case FIRST_LVL:
		{
			levelName = sf::String(FIRST_LVL_NAME);
			break;
		}
		case SECOND_LVL:
		{
			levelName = sf::String(SECOND_LVL_NAME);
			break;
		}
		case THIRD_LVL:
		{
			levelName = sf::String(THIRD_LVL_NAME);
			break;
		}
		}
		
		levelSelectName.setString(levelName);
		levelSelectName.setPosition((windowSize.x-levelSelectName.getGlobalBounds().width)/2,windowSize.y/4);
		window->clear();
		window->draw(background);
		window->draw(AUpButton);
		window->draw(ADownButton);
		window->draw(levelSelectName);
		for (int i = 0; i < LEVEL_SELECT_BUTTON_NUM; i++)
		{
			window->draw(button[i]);
			window->draw(buttonText[i]);
		}
		window->display();
	}
	return -1;
}