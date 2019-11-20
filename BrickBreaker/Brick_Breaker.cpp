#include "Brick_Breaker.h"

void BrickBreaker::loadLevel(int level)
{
	string level_file = "BrickBreakerData/levels/";
	Vector2f pos = { 0,70 };
	char brick_kind;
	level_file += to_string(level);
	level_file += ".txt";
	ifstream f;
	f.open(level_file.c_str());
	
	while (true)
	{
		f.get(brick_kind);
		if (f.eof())
		{
			break;
		}
		if (brick_kind == '\n')
		{
			continue;
		}
		if (brick_kind == '-')
		{
			Brick brick(pos);
			brick_list.push_back(brick);
			pos.x += 65;
			if (pos.x >= 1024)
			{
				pos.x = 0;
				pos.y += 30;
			}
		}
	}
}

BrickBreaker::BrickBreaker()
{
	padLength = 125;
	ball_speed = 3;
	pad_speed = 3;
	start = false;
	InitializePadPos = { float(wWidth / 2) - 50,float(wHeight - 100) };
	pad.setAttributes(InitializePadPos, padLength, pad_speed);
	InitializeBallPos = { (InitializePadPos.x + pad.getPosition().width / 2) - 8,InitializePadPos.y + 5 - pad.getHeight() };
	ball.setAttributes(InitializeBallPos);
	pad.setFillColor(Color::Green);
	ball.setFillColor(Color::White);
	setting.antialiasingLevel = 4;
	window.create(VideoMode(wWidth, wHeight), "Brick Breaker", Style::Default, setting);
	window.setFramerateLimit(60);
}

BrickBreaker::~BrickBreaker()
{
}

void BrickBreaker::handleKeyPress()
{
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		start = true;
		ball.SetSpeed(ball_speed);
	}
	if (Keyboard::isKeyPressed(Keyboard::Left) && pad.getPosition().left > 0)
	{
		pad.moveLeft();
		if (!start)
		{
			Vector2f new_pos = pad.GetPosition();
			ball.SetPosition((new_pos.x + pad.getPosition().width / 2) - 8, new_pos.y + 5 - pad.getHeight());
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Right) && pad.getPosition().width + pad.getPosition().left < wWidth)
	{
		pad.moveRight();
		if (!start)
		{
			Vector2f new_pos = pad.GetPosition();
			ball.SetPosition((new_pos.x + pad.getPosition().width / 2) - 8, new_pos.y + 5 - pad.getHeight());
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window.close();
	}
}

void BrickBreaker::handleEdgeCollision(FloatRect topEdge, FloatRect leftEdge, FloatRect rightEdge, FloatRect lowerEdge)
{
	if (ball.getGlobalBounds().intersects(topEdge))
	{
		ball.ReboundTopOrBot();
	}
	if (ball.getGlobalBounds().intersects(leftEdge) || ball.getGlobalBounds().intersects(rightEdge))
	{
		ball.ReboundEdge();
	}
	if (ball.getPosition().intersects(pad.getPosition()))
	{
		ball.Rebound_IncreaseSpeed();
	}
	if (ball.getPosition().intersects(lowerEdge))
	{
		resetBallPad();
	}
}

void BrickBreaker::resetBallPad()
{
	pad.setPosition(InitializePadPos);
	ball.SetPosition(InitializeBallPos.x,InitializeBallPos.y);
	start = false;
	ball.SetSpeed(0);
}

void BrickBreaker::draw(Sprite sprite)
{
	pad.Update();
	ball.update();
	window.clear();
	window.draw(sprite);
	window.draw(pad.getShape());
	window.draw(ball);
	list<Brick>::iterator pos;
	pos = brick_list.begin();
	while (pos != brick_list.end())
	{
		window.draw(pos->getShape());
		++pos;
	}
	window.display();
}

bool BrickBreaker::isOpen()
{
	return window.isOpen();
}

void BrickBreaker::handleBrickCollision()
{
	FloatRect ballBound = ball.getGlobalBounds();
	float ballRadius = ball.getRadius();
	int n = brick_list.size();
	char colide_type;
	list<Brick>::iterator pos;
	pos = brick_list.begin();

	while (pos != brick_list.end())
	{
		colide_type = pos->handleCollision(ballBound, ballRadius);

		if (colide_type != 'n')
		{
			if (colide_type == 'v')
			{
				ball.ReboundTopOrBot();
			}
			else
			{
				if (colide_type == 'h')
				{
					ball.ReboundEdge();
				}
				else
				{
					ball.ReboundTopOrBot();
					ball.ReboundEdge();
				}
			}
			pos = brick_list.erase(pos);
		}
		else
		{
			++pos;
		}
		
	}
}

void Brick_Breaker()
{
	BrickBreaker brick_game;
	brick_game.loadLevel(1);
	FloatRect topEdge(0, 68, wWidth, 1), leftEdge(0, 68, 1, wHeight - 68), rightEdge(wWidth - 1, 68, 1, wHeight - 68), lowerEdge(0, wHeight - 1, wWidth, 1);
	
	Texture	texture;
	Sprite sprite;
	if (!texture.loadFromFile("image/2.png"))
	{
		std::cout << "Load Textured failed";
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, wWidth, wHeight));
	
	
	while (brick_game.isOpen())
	{
		brick_game.handleKeyPress();
		brick_game.handleEdgeCollision(topEdge,leftEdge,rightEdge,lowerEdge);
		brick_game.handleBrickCollision();
		brick_game.draw(sprite);
		

		
	}
}