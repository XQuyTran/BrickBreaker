#include "cPaddle.h"


cPaddle::cPaddle()
{
}


cPaddle::~cPaddle()
{
}

cPaddle::cPaddle(float X, float Y)// tao paddle voi toa do X,Y
{
	Position.x = X;
	Position.y = Y;
	PaddleShape.setSize(Vector2f(25, 100));
	PaddleShape.setPosition(Position);
}

FloatRect cPaddle::getPosition()
{
	return PaddleShape.getGlobalBounds();
}

RectangleShape cPaddle::getShape()
{
	return PaddleShape;
}

void cPaddle::moveDown()
{
	Position.y += PaddleSpeed;
}

void cPaddle::moveUp()
{
	Position.y -= PaddleSpeed;
}

void cPaddle::Update()
{
	PaddleShape.setPosition(Position);
}

void cPaddle::moveLeft()
{
	Position.x -= PaddleSpeed;
}

void cPaddle::moveRight()
{
	Position.x += PaddleSpeed;
}

void cPaddle::setFillColor(const Color& color)
{
	PaddleShape.setFillColor(color);
}

float cPaddle::getHeight()
{
	FloatRect shape = getPosition();
	return shape.height;
}

cPaddle::cPaddle(float X, float Y, int length, int initial_speed)
{
	Position.x = X;
	Position.y = Y;
	PaddleSpeed = initial_speed;
	PaddleShape.setSize(Vector2f(length, 25));
	PaddleShape.setPosition(Position);
}

Vector2f cPaddle::GetPosition()
{
	return Position;
}

void cPaddle::setPosition(Vector2f pos)
{
	Position = pos;
}

void cPaddle::setAttributes(Vector2f pos, int length, int initialSpeed)
{
	Position = pos;
	PaddleSpeed = initialSpeed;
	PaddleShape.setSize(Vector2f(length, 25));
	PaddleShape.setPosition(Position);
}