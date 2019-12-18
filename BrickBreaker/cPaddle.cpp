#include "cPaddle.h"


cPaddle::cPaddle()
{
}


cPaddle::~cPaddle()
{
}

cPaddle::cPaddle(float X, float Y)
{
	// đặt vị trí thanh trượt
	Position.x = X;
	Position.y = Y;
	
	// đặt kích thước thanh trượt
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
	// PaddleSpeed: độ dời thanh trượt
	Position.y += PaddleSpeed;
}

void cPaddle::moveUp()
{
	// PaddleSpeed: độ dời thanh trượt
	Position.y -= PaddleSpeed;
}

void cPaddle::Update()
{
	PaddleShape.setPosition(Position);
}

void cPaddle::moveLeft()
{
	// PaddleSpeed: độ dời thanh trượt
	Position.x -= PaddleSpeed;
}

void cPaddle::moveRight()
{
	// PaddleSpeed: độ dời thanh trượt
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
	// đặt vị trí thanh trượt
	Position = pos;
	
	// đặt tốc độ thanh trượt
	PaddleSpeed = initialSpeed;
	
	// đặt độ dài thanh trượt
	PaddleShape.setSize(Vector2f(length, 25));
	PaddleShape.setPosition(Position);
}

void cPaddle::setLength(float length)
{
	PaddleShape.setSize(Vector2f(length, 25));
}

void cPaddle::setSpeed(float speed)
{
	PaddleSpeed = speed;
}