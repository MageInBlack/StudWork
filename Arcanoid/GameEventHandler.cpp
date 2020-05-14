#include "GameEventHandler.h"
int ButtonPressCheck(int mouseX, int mouseY, sf::FloatRect rect)
{
	if (mouseX > rect.left && mouseX<rect.left + rect.width && mouseY>rect.top && mouseY < rect.top + rect.height) return 1;
	else return 0;
}