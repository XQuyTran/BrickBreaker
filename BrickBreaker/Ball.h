#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

const float BALL_MAX_SPEED = 7.0f;

class Ball:public CircleShape
{
private:
	Vector2f position;
	float dx = 0;
	float dy = 0;
	float speed = 1.1f;
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

