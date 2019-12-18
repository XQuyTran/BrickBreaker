#include "Brick.h"

Brick::Brick(Vector2f pos, const char special_char)
{
	// đặt vị trí của viên gạch
	position.x = pos.x;
	position.y = pos.y;
	
	// đặt kích thước của viên gạch
	brickShape.setSize(Vector2f(64, 25));
	
	// đặt vật phẩm đặc biệt
	special = special_char;
	brickShape.setPosition(position);
	
	// đặt màu viền và màu tô cho viên gạch
	// viên gạch có màu mặc định là xanh, nếu là viên gạch đặc biệt sẽ được đổi màu
	brickShape.setOutlineColor(Color::Black);
	brickShape.setFillColor(Color::Blue);
}

Brick::Brick() {}

Brick::~Brick() {}

void Brick::setSpecial(char kind)
{
	special = kind;
	brickShape.setFillColor(Color::Red);
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
	// tạo đối tượng lưu kích thước và vị trí của viên gạch
	FloatRect brickBound = brickShape.getGlobalBounds();
	
	// tạo đối tượng lớp vector 2 chiều lưu tọa độ tâm trái banh
	Vector2f ballCenter(ballBound.left + ballBound.width / 2, ballBound.top + ballBound.height / 2);
	
	// kiểm tra trái banh có giao với viên gạch
	// nếu có kiểm tra loại va chạm
	// nếu không trả về ký tự 'n' ký hiệu không có va chạm
	if (brickBound.intersects(ballBound))
	{
		// kiểm tra trái banh chạm vào cạnh dọc của viện gạch
		// nếu có trả về ký tự 'v' ký hiệu va chạm cạnh dọc
		if (brickBound.contains(ballCenter.x, ballBound.top) || brickBound.contains(ballCenter.x, ballBound.top + ballBound.height))
		{
			return 'v';
		}
		else
		{
			// kiểm tra trái banh chạm vào cạnh ngang của viện gạch
			// nếu có trả về ký tự 'v' ký hiệu va chạm cạnh ngang
			if (brickBound.contains(ballBound.left, ballCenter.y) || brickBound.contains(ballBound.left + ballBound.width, ballCenter.y))
			{
				return 'h';
			}
			else
			{
				// nếu có trả về ký tự 'c' ký hiệu va chạm góc
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

char Brick::getSpecialchar()
{
	return special;
}

void Brick::setSize(float x, float y)
{
	brickShape.setSize(Vector2f(x, y));
}

Vector2f Brick::getPosition()
{
	return position;
}