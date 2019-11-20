#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

const float BALL_MAX_SPEED = 10.0;

class Ball:public CircleShape
{
private:
	Vector2f position;
	float dx = 0;
	float dy = 0;
	int speed = 1.6;
public:
	FloatRect getPosition();
	
	Ball();
	~Ball();
	Ball(float, float);
	void ReboundTopOrBot();
	void ReboundPaddle();
	void ReboundEdge();
	void Rebound_IncreaseSpeed();
	void update();
	void ReturnCenter(int);
	CircleShape getShape();
	void SetPosition(float,float);
	void setAttributes(Vector2f);
	void SetSpeed(int);
};

