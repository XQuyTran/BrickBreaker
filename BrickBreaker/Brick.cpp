#include "Brick.h"

Brick::Brick(Vector2f pos, const char special_char)
{
	position.x = pos.x;
	position.y = pos.y;
	brickShape.setSize(Vector2f(64, 25));
	special = special_char;
	brickShape.setPosition(position);
	brickShape.setOutlineColor(Color::Black);
	brickShape.setFillColor(Color::Blue);
}

Brick::Brick() {}

Brick::~Brick() {}

void Brick::setSpecial(char kind)
{
	special = kind;
}

void Brick::setFillColor(Color color)
{
	brickShape.setFillColor(color);
}

RectangleShape Brick::getShape()
{
	return brickShape;
}

const char Brick::handleCollision(FloatRect& ballBound, float& ballRadius)
{
	FloatRect brickBound = brickShape.getGlobalBounds();
	Vector2f ballCenter(ballBound.left + ballBound.width / 2, ballBound.top + ballBound.height / 2);
	
	if (brickBound.intersects(ballBound))
	{
		if (brickBound.contains(ballCenter.x, ballBound.top) || brickBound.contains(ballCenter.x, ballBound.top + ballBound.height))
		{
			return 'v';
		}
		else
		{
			if (brickBound.contains(ballBound.left, ballCenter.y) || brickBound.contains(ballBound.left + ballBound.width, ballCenter.y))
			{
				return 'h';
			}
			else
			{
				return 'c';
			}
		}
	}

	return 'n';
}

void Brick::setPosition(Vector2f pos)
{
	position = pos;
}