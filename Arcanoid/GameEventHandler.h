#pragma once
#include <SFML/Graphics.hpp>
#define FONT_FILENAME "18690.ttf"
#define BUTTON_WIDTH 50
#define BUTTON_HEIGHT 13
#define BUTTON_TEXTURE_FILE "Textures\\Objects\\Button.jpg"
#define PRESSED_BUTTON_TEXTURE_FILE "Textures\\Objects\\Button_pressed.jpg"
#define MAIN_MENU_BACKGROUND_WIDTH 200
#define MAIN_MENU_BACKGROUND_HEIGHT 150
int ButtonPressCheck(int mouseX, int mouseY, sf::FloatRect rect);