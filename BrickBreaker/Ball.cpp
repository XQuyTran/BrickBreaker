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
	dx = NewSpeed;
	dy = NewSpeed;
}