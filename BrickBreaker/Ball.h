#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Ball:public CircleShape
{
private:
	Vector2f position;
	float dx = 2;
	float dy = 2;
	int speed = 1.1;
public:
	FloatRect getPosition();
	
	Ball();
	~Ball();
	Ball(float, float);
	void ReboundTopOrBot();
	void ReboundPaddle();
	void update();
	void ReturnCenter(int);
	CircleShape getShape();
	void SetSpeed(int);
};

