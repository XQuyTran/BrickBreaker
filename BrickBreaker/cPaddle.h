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
	cPaddle(float X, float Y);
	cPaddle(float, float, int, int);
	FloatRect getPosition();
	Vector2f GetPosition();
	void setPosition(Vector2f);
	float getHeight();
	RectangleShape getShape();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void Update();
	void setFillColor(const Color&);
	void setAttributes(Vector2f, int, int);
	void setLength(float length);
	void setSpeed(float speed);
	cPaddle();
	~cPaddle();
};

