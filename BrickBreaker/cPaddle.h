#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
class cPaddle
{
private:
	Vector2f Position;
	RectangleShape PaddleShape;
	float PaddleSpeed = 2;
public:
	cPaddle(float X,float Y);
	FloatRect getPosition();
	RectangleShape getShape();
	void moveUp();
	void moveDown();
	void Update();
	cPaddle();
	~cPaddle();
};

