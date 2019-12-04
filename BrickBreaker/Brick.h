#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"
using namespace sf;
class Brick
{
private:
	RectangleShape brickShape;
	Vector2f position;
	char special;
public:
	Brick();
	Brick(Vector2f pos, const char special_char = 0);
	~Brick();
	void setSpecial(char);
	void setFillColor(Color);
	void setPosition(Vector2f);
	RectangleShape getShape();
	const char handleCollision(FloatRect&, float&);
	char getSpecialchar();
	Vector2f getPosition();
	void setSize(float x, float y);
};

