#include "Game.h"

Game::Game(sf::RenderWindow& window)
{
	this->window = &window;
	windowSize=window.getSize();
	scalingX = windowSize.x / GAME_BACKGROUND_WIDTH;
	scalingY = windowSize.y / GAME_BACKGROUND_HEIGHT;
}

int Game::Init(sf::String levelname)
{
	int checker;
	int Lkeycheck = 0, Rkeycheck = 0;
	int iterator = 1;
	int healthChange = 0;
	
	sf::String healthString;
	health = HEALTH;
	
	if (!font.loadFromFile(FONT_FILENAME)) return -1;
	if (!backgroundTexture.loadFromFile(GAME_BACKGROUND_FILENAME)) return -1;
	if (!brickTexture.loadFromFile(BRICK_TEXTURE_FILENAME)) return -1;
	if (!pongTexture.loadFromFile(PONG_TEXTURE_FILENAME)) return -1;
	if (!ballTexture.loadFromFile(BALL_TEXTURE_FILENAME)) return -1;
	if (!endScreenTexture.loadFromFile(GAME_END_SCREEN_FILENAME)) return -1;
	if (!buttonTexture.loadFromFile(BUTTON_TEXTURE_FILE)) return -1;
	if (!pressedButtonTexture.loadFromFile(PRESSED_BUTTON_TEXTURE_FILE)) return -1;

	for (int i = 0; i < SCORE_STRING_NUM; i++)
	{
		score[i].setFont(font);
		score[i].setFillColor(sf::Color::White);
		score[i].setCharacterSize(7 * scalingX);
		highscore[i].setFont(font);
		highscore[i].setFillColor(sf::Color::White);
		highscore[i].setCharacterSize(7 * scalingX);
		score[i].setPosition(1, 100+i*score->getCharacterSize()+1);
		highscore[i].setPosition(1, 200+ i * highscore->getCharacterSize() + 1);
	}
	healthText.setFont(font);
	healthText.setCharacterSize(7 * scalingX);
	healthText.setString("x");
	tempstring = std::to_string(health);
	healthString = healthText.getString();
	healthString.insert(1, tempstring);
	healthText.setString(healthString);
	healthText.setPosition(GAME_LEFT / 5 * 2, 300);
	for (int i = 0; i < END_TEXT_STRING; i++)
	{
		endText[i].setFont(font);
		endText[i].setFillColor(sf::Color::White);
		endText[i].setCharacterSize(7 * scalingX);
	}
	backButtonText.setFont(font);
	backButtonText.setFillColor(sf::Color::White);
	backButtonText.setCharacterSize(7 * scalingX);
	backButtonText.setString("Back");

	score[0].setString("Score:");
	highscore[0].setString("Highscore:");
	score[1].setString("0000000");
	highscore[1].setString("0000000");

	background.setTexture(backgroundTexture);
	background.setScale(scalingX, scalingY);

	endScreen.setTexture(endScreenTexture);
	endScreen.setScale(scalingX, scalingY);
	endScreen.setColor(sf::Color(0x000000f0));

	backButton.setTexture(buttonTexture);
	backButton.setScale(scalingX, scalingY);
	backButton.setPosition((windowSize.x-backButton.getGlobalBounds().width)/2,windowSize.y/4*3);
	backButtonText.setPosition((windowSize.x-backButtonText.getGlobalBounds().width)/2,backButton.getGlobalBounds().top);

	pong = Pong(pongTexture, GAME_LEFT + (GAME_WIDTH - PONG_WIDTH) / 2, GAME_TOP + GAME_HEIGHT / 6 * 5, scalingX, scalingY);

	healthBar.setTexture(ballTexture);
	healthBar.setScale(scalingX, scalingY);
	healthBar.setPosition(GAME_LEFT / 5, 300);

	ball = Ball(ballTexture, pong.getRect().left + (pong.getRect().width - BALL_SIZE*scalingX) / 2, pong.getRect().top - BALL_SIZE * scalingY,scalingX,scalingY);
	
	levelname.insert(0, "levels\\");
	levelname += ".txt";
	path += levelname.toAnsiString();
	level.open(path, std::ios::in);
	if (!level.is_open()) return -1;
	for (int i = 0; i < BRICKS_NUM; i++)
	{
		level >> reading;
		Bricks[i] = Brick(brickTexture,reading,GAME_LEFT+(i%BRICKS_PER_LINE)*BRICK_WIDTH*scalingX,GAME_TOP+i/BRICKS_PER_LINE*BRICK_HEIGHT*scalingY,scalingX,scalingY);
	}
	level.get();
	level >> scorestr;
	level.close();
	if (scorestr != "") highscore[1].setString(scorestr);
	else firstGame = 1;
	scorestr.clear();
	
	while (window->isOpen())
	{
		while (window->pollEvent(gameEvent))
		{
			if (gameEvent.type == sf::Event::Closed)
			{
				window->close();
				return -1;
			}
			if (gameEvent.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{

					Pause pause(*window);
					checker=pause.Init();
					if (checker == -1) return -1;
					if (checker == 0) return 0;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) Lkeycheck = 1;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) Rkeycheck = 1;
				if (ball.isInert() && (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||sf::Keyboard::isKeyPressed(sf::Keyboard::Space))) ball.Throw(BALL_SPEED);
			}
			if (gameEvent.type == sf::Event::KeyReleased)
			{
				if (gameEvent.key.code == sf::Keyboard::A || gameEvent.key.code == sf::Keyboard::Left) Lkeycheck = 0;
				if (gameEvent.key.code == sf::Keyboard::D || gameEvent.key.code == sf::Keyboard::Right) Rkeycheck = 0;
			}
		}
		if (health < 0)
		{
			gamestate = -1;
			writeHighscore();
			return lose();
		}

		if (healthChange)
		{
			int i;
			healthString=healthText.getString();
			iterator = tempstring.size();
			healthString.erase(1,iterator);
			tempstring = std::to_string(health);
			healthString.insert(1, tempstring);
			healthText.setString(healthString);
			healthChange = 0;
		}
		if (Lkeycheck)
		{
			if (pong.getRect().left - scalingX > GAME_LEFT) pong.move(-4);
			else (pong.setPosition(GAME_LEFT));
		}
		if (Rkeycheck)
		{
			if (pong.getRect().left + pong.getRect().width + scalingX < GAME_LEFT + GAME_WIDTH) pong.move(4);
			else pong.setPosition(GAME_LEFT + GAME_WIDTH - pong.getRect().width);
		}

		if (ball.isInert())
		{
			if (ball.getRect().left < pong.getRect().left) ball.setPosition(pong.getRect().left,ball.getRect().top);
			if (ball.getRect().left + ball.getRect().width > pong.getRect().left + pong.getRect().width) ball.setPosition(pong.getRect().left + pong.getRect().width-ball.getRect().width,ball.getRect().top);
		}
		else
		{
			ball.move();
		}

		if (ball.getRect().intersects(pong.getRect()))
		{
			ball.moveBack();
			ball.bounce(1);
			ball.move();
			if (!ball.getRect().intersects(pong.getRect()))
			{
				ball.moveBack();
				ball.setAngle(M_PI_2 * (1. - 1.5 * (ball.getRect().left + ball.getRect().width / 2 - pong.getRect().left - pong.getRect().width / 2) / pong.getRect().width));
				ball.move();
			}
			else
			{
				ball.moveBack();
				ball.bounce(2);
				ball.bounce(1);
				ball.move();
			}
		}
		if (ball.getRect().left < GAME_LEFT||ball.getRect().left+ball.getRect().width>GAME_LEFT+GAME_WIDTH)
		{
			ball.bounce(2);
			ball.move();
		}
		if (ball.getRect().top < GAME_TOP)
		{
			ball.bounce(1);
			ball.move();
		}

		if (ball.getRect().top + ball.getRect().height > GAME_TOP + GAME_HEIGHT)
		{
			health--;
			healthChange = 1;
			ball = Ball(ballTexture, pong.getRect().left+ (pong.getRect().width-BALL_SIZE*scalingX)/2, pong.getRect().top - BALL_SIZE * scalingY, scalingX, scalingY);
		}

		for (int i=0;i<BRICKS_NUM;i++)
			if (Bricks[i].getHealth() > 0 && ball.getRect().intersects(Bricks[i].sprite.getGlobalBounds()))
			{
				if (Bricks[i].getHealth() == 1) scoreint += 100;
				else scoreint += 10;
				Bricks[i].damage(1);
				
				ball.moveBack();
				ball.bounce(1);
				ball.move();
				if (ball.getRect().intersects(Bricks[i].sprite.getGlobalBounds()))
				{
					ball.moveBack();
					ball.bounce(2);
					ball.bounce(1);
					ball.move();
				}
				break;
			}
		scorestr = std::to_string(scoreint);
		if (scorestr.length() < 7) scorestr.insert(0, 7 - scorestr.length(), '0');
		score[1].setString(scorestr);
		if (draw())
		{
			gamestate = 1;
			writeHighscore();
			return win();
		}
	}
	return 0;
}

int Game::draw()
{
	int nobricks = 1;
	window->draw(background);
	for (int i = 0; i < SCORE_STRING_NUM; i++)
	{
		window->draw(score[i]);
		window->draw(highscore[i]);
	}
	for (int i = 0; i < BRICKS_NUM; i++)
	{
		if (Bricks[i].getHealth() == 0) continue;
		else
		{
			nobricks = 0;
			if (Bricks[i].getHealth() == 1) Bricks[i].color(sf::Color::Red);
			if (Bricks[i].getHealth() == 2) Bricks[i].color(sf::Color::Yellow);
			if (Bricks[i].getHealth() == 3) Bricks[i].color(sf::Color::Green);
		}
		window->draw(Bricks[i].sprite);
	}
	window->draw(pong.getSprite());
	window->draw(ball.getSprite());
	window->draw(healthBar);
	window->draw(healthText);
	if (gamestate)
	{
		window->draw(endScreen);
		window->draw(backButton);
		for (int i = 0; i < END_TEXT_STRING; i++)
			window->draw(endText[i]);
		window->draw(backButtonText);
	}
	window->display();
	return nobricks;
}

int Game::win()
{
	endText[0].setString("You've won");
	endText[1].setString(score[0].getString());
	endText[2].setString(score[1].getString());
	endText[3].setString(highscore[0].getString());
	endText[4].setString(highscore[1].getString());
	for (int i = 0; i < END_TEXT_STRING; i++)
		endText[i].setPosition((windowSize.x-endText[i].getGlobalBounds().width)/2,windowSize.y/7*2+i*endText[i].getCharacterSize());
	return endLoop();
	
}

int Game::lose()
{
	endText[0].setString("You've lost");
	endText[1].setString(score[0].getString());
	endText[2].setString(score[1].getString());
	endText[3].setString(highscore[0].getString());
	endText[4].setString(highscore[1].getString());
	for (int i = 0; i < END_TEXT_STRING; i++)
		endText[i].setPosition((windowSize.x - endText[i].getGlobalBounds().width) / 2, windowSize.y / 7 * 2 + i * endText[i].getCharacterSize());
	return endLoop();
}

int Game::endLoop()
{
	int mouseClick = -1;
	int buttonPress = -1;
	while (window->isOpen())
	{
		while (window->pollEvent(gameEvent))
		{
			if (gameEvent.type == sf::Event::Closed) 
			{
				window->close();
				return -1;
			}
			if (gameEvent.type == sf::Event::MouseButtonPressed)
			{
				if (gameEvent.mouseButton.button == sf::Mouse::Left)
				{
					if (ButtonPressCheck(gameEvent.mouseButton.x, gameEvent.mouseButton.y, backButton.getGlobalBounds()))
					{
						mouseClick = 0;
						backButton.setTexture(pressedButtonTexture);
						backButtonText.setFillColor(sf::Color(0x808080ff));
						backButtonText.move(0, scalingY);
						break;
					}
				}
			}
			if (gameEvent.type == sf::Event::MouseButtonReleased)
			{
				if (gameEvent.mouseButton.button == sf::Mouse::Left)
				{
					if (mouseClick > -1 && mouseClick < 4)
					{
						buttonPress = -1;

						if (ButtonPressCheck(gameEvent.mouseButton.x, gameEvent.mouseButton.y, this->backButton.getGlobalBounds()))
							buttonPress = 0;
						
						if (buttonPress == mouseClick)
						{
							return 0;
						}
						if (mouseClick > -1 && mouseClick < 2)
						{
							backButton.setTexture(buttonTexture);
							backButtonText.setFillColor(sf::Color::White);
							backButtonText.move(0, -scalingY);
						}
						mouseClick = -1;
					}
				}
			}
		}
		draw();
	}
}

void Game::writeHighscore()
{
	if (std::stoi(scorestr) > std::stoi(highscore[1].getString().toAnsiString()))
	{
		highscore[1].setString(scorestr);
		level.open(path);
		if (firstGame)level.seekp(1, std::ios::end);
		else level.seekp(-7, std::ios::end);
		level.write(scorestr.data(), 7);
		level.close();
	}
	
}