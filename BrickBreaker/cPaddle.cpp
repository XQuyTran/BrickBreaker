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