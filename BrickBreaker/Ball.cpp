#include "Ball.h"

Ball::Ball()
{
}


Ball::~Ball()
{
}
Ball::Ball(float x, float y)
{
	this->setFillColor(sf::Color::Green);
	position.x = x;
	position.y = y;
	this->setRadius(10);
	this->setPosition(position);
}
void Ball::ReboundTopOrBot()
{
	dy = -dy;
}
void Ball::ReboundPaddle()
{
	dx = -dx*speed;
	dy *= speed;
}
void Ball::update()
{
	position.x += dx;
	position.y += dy;
	this->setPosition(position);
}
FloatRect Ball::getPosition()
{
	return this->getGlobalBounds();
}
CircleShape Ball::getShape()
{
	this->setFillColor(sf::Color::Blue);
	return CircleShape::CircleShape();
}
void Ball::ReturnCenter(int Speed)
{
	position.x = 512;
	position.y = 768 / 2;
	dx = Speed;
	dy = Speed;
}
void Ball::SetSpeed(int NewSpeed)
{
	int direction = rand() % 2;
	dx = NewSpeed;
	if (direction == 0)
	{
		dx = -dx;
	}
	direction = rand() % 2;

	dy = -NewSpeed;
}

void Ball::ReboundEdge()
{
	dx = -dx;
}

void Ball::SetPosition(float X, float Y)
{
	position.x = X;
	position.y = Y;
}

void Ball::Rebound_IncreaseSpeed()
{
	dy = -dy * speed;
	dx *= speed;
	if (dy > BALL_MAX_SPEED)
	{
		dy = BALL_MAX_SPEED;
	}
	if (dy < -BALL_MAX_SPEED)
	{
		dy = -BALL_MAX_SPEED;
	}

	if (dx > BALL_MAX_SPEED)
	{
		dx = BALL_MAX_SPEED;
	}
	if (dx < -BALL_MAX_SPEED)
	{
		dx = -BALL_MAX_SPEED;
	}
}

void Ball::setAttributes(Vector2f pos)
{
	position.x = pos.x;
	position.y = pos.y;
	setRadius(10);
	setPosition(position);
}