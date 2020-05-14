#pragma once
#include <SFML/Graphics.hpp>
#include "GameEventHandler.h"
#include "Brick.h"
#include "Pause.h"
#include <string>
#include "Ball.h"
#include "Pong.h"
#define BRICK_WIDTH 8
#define BRICK_HEIGHT 8
#define GAME_BACKGROUND_FILENAME "Textures\\Backgrounds\\GameMenu.jpg"
#define GAME_END_SCREEN_FILENAME "Textures\\Backgrounds\\EndScreen.jpg"
#define GAME_BACKGROUND_WIDTH 200
#define GAME_BACKGROUND_HEIGHT 150
#define SCORE_STRING_NUM 2
#define BALL_TEXTURE_FILENAME "Textures\\Objects\\Ball.jpg"
#define BRICK_TEXTURE_FILENAME "Textures\\Objects\\Brick.jpg"
#define PONG_TEXTURE_FILENAME "Textures\\Objects\\Pong.jpg"
#define BRICKS_NUM 200
#define GAME_LEFT 140
#define GAME_TOP 20
#define GAME_WIDTH 640
#define GAME_HEIGHT 560
#define BRICKS_PER_LINE 20
#define BALL_SPEED 6
#define PONG_WIDTH 24
#define PONG_HEIGHT 6
#define BALL_SIZE 4
#define HEALTH 2
#define END_TEXT_STRING 5
#define BRICK_BYTE_SIZE 2
class Game
{
private:
	Ball ball;
	Pong pong;
	int health = HEALTH;
	int gamestate = 0;
	int scoreint = 0;
	int firstGame = 0;
	sf::Text healthText;
	sf::Text endText[END_TEXT_STRING];
	int reading;
	std::fstream level;
	std::string path;
	std::string tempstring;
	std::string scorestr;
	sf::RenderWindow* window;
	Brick Bricks[BRICKS_NUM];
	sf::Vector2u windowSize;
	int scalingX, scalingY;
	sf::Event gameEvent;
	sf::Sprite background;
	sf::Texture backgroundTexture;
	sf::Font font;
	sf::Text score[2];
	sf::Text highscore[2];
	sf::Text backButtonText;
	sf::Texture endScreenTexture;
	sf::Texture brickTexture;
	sf::Texture pongTexture;
	sf::Texture ballTexture;
	sf::Texture buttonTexture;
	sf::Texture pressedButtonTexture;
	sf::Sprite backButton;
	sf::Sprite healthBar;
	sf::Sprite endScreen;
public:
	Game(sf::RenderWindow& window);
	int Init(sf::String levelName);
	int draw();
	int lose();
	int win();
	int endLoop();
	void writeHighscore();
};

