#pragma once
#include<SFML\Graphics.hpp>
#include<iostream>
#include <sstream>
#define MAX_NUMBER_OF_ITEM 2
using namespace sf;
class Option
{
private:
	int selectecItem;
	Font font;
	Text menu[MAX_NUMBER_OF_ITEM];
public:
	Option(float width, float height);
	void drawSpeed(RenderWindow& window,int Speed);
	void drawScoreEnd(RenderWindow& window, int ScoreEnd);
	void moveRight();
	void moveLeft();
	int getPressedItem();
	void SpriteDraw2(RenderWindow& window);
	void TocDo(int,RenderWindow& window);
	void DiemKetThuc(int, RenderWindow& window);
};


