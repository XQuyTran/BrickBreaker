#pragma once
#include<SFML\Graphics.hpp>
#include<iostream>
#define MAX_NUMBER_OF_ITEM 3
using namespace sf;
class Menu
{
private:
	int selectecItem;
	Font font;
	Text menu[MAX_NUMBER_OF_ITEM];
public:
	Menu(float width,float height);
	void draw(RenderWindow &window);
	void moveUp();
	void moveDown();
	int getPressedItem();
	~Menu();
	void SpriteDraw1(RenderWindow& window);
	void SpriteDraw2(RenderWindow& window);
};

