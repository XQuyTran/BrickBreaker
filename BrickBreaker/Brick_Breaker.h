#pragma once
#include "Ball.h"
#include "cPaddle.h"
#include <SFML\Graphics.hpp>
#include "Menu.h"
#include "Option.h"
#include "Brick.h"
#include <conio.h>
#include <sstream>
#include <fstream>
#include <string>
#include <list>
using namespace std;
using namespace sf;

void Brick_Breaker();
const int wWidth = 1024;
const int wHeight = 768;

class BrickBreaker
{
public:
	BrickBreaker();
	~BrickBreaker();
	void handleKeyPress();
	void handleEdgeCollision(FloatRect, FloatRect, FloatRect, FloatRect);
	void draw(Sprite);
	bool isOpen();
	void loadLevel(int);
	void handleBrickCollision();

private:
	int padLength, ball_speed, pad_speed;
	bool start;
	Vector2f InitializePadPos, InitializeBallPos;
	cPaddle pad;
	Ball ball;
	RenderWindow window;
	ContextSettings setting;
	list<Brick> brick_list;
	void resetBallPad();
};

