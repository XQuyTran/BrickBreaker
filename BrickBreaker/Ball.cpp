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
	// khai báo biến kiểm tra vận tốc đã được thay đổi, khởi gán là true
	bool change_x = true, change_y = true;

	// kiểm tra vận tốc theo phương dọc có lớn hơn vận tốc tối đa
	// nếu đúng thì gán lại vận tốc thành vận tốc tối đa
	// đánh dấu vận tốc chưa được thay đổi nếu ngược lại
	if (dy > BALL_MAX_SPEED)
	{
		dy = BALL_MAX_SPEED;
	}
	else
	{
		if (dy < -BALL_MAX_SPEED)
		{
			dy = -BALL_MAX_SPEED;
		}
		else
		{
			change_y = false;
		}
	}
	
	if (dx > BALL_MAX_SPEED)
	{
		dx = BALL_MAX_SPEED;
	}
	else
	{
		if (dx < -BALL_MAX_SPEED)
		{
			dx = -BALL_MAX_SPEED;
		}
		else
		{
			change_x = false;
		}
	}

	// kiểm tra vận tốc được thay đổi
	if (!change_y && !change_x)
	{
		// tăng tốc và đổi hướng di chuyển
		dy *= -speed;
		dx *= speed;
	}
}

void Ball::setAttributes(Vector2f pos)
{
	// Gán vị trí của trái banh về lại ban đầu
	position.x = pos.x;
	position.y = pos.y;
	
	// Gán bán kính của trái banh về lại ban đầu
	setRadius(10);
	
	// Gọi phương thức đặt vị trí trên cửa sổ màn hình
	setPosition(position);
}