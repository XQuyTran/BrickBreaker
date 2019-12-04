#pragma once
#include<SFML\Graphics.hpp>
#include<iostream>
#include <string>
#define MAX_NUMBER_OF_ITEM 3
using namespace sf;
using namespace std;
class Menu
{
private:
	int selectecItem;
	Font font;
	Text menu[MAX_NUMBER_OF_ITEM];
public:
	Menu();
	Menu(float width,float height);
	Menu(string content[], float width, float height, Font font);
	void draw(RenderWindow &window);
	void moveUp();
	void moveDown();
	int getPressedItem();
	~Menu();
	void SpriteDraw1(RenderWindow& window);
	void SpriteDraw2(RenderWindow& window);
};

