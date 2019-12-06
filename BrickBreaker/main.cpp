#include "Brick_Breaker.h"
#include "Pong.h"

int main()
{
	BrickBreaker brick_game;
	FloatRect topEdge(0, 68, wWidth, 1), leftEdge(0, 68, 1, wHeight - 68), rightEdge(wWidth - 1, 68, 1, wHeight - 68), lowerEdge(0, wHeight - 1, wWidth, 1);
	Texture	texture;
	Sprite sprite;

	//brick_game.loadLevel(0);
	if (!texture.loadFromFile("BrickBreakerData/image/3.jpg"))
	{
		std::cout << "Load Textured failed";
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, wWidth, wHeight));


	while (brick_game.isOpen())
	{
		brick_game.startMenu();
		brick_game.handleKeyPress();
		brick_game.handleEdgeCollision(topEdge, leftEdge, rightEdge, lowerEdge);
		brick_game.handleBrickCollision();
		brick_game.Countdown_timer();
		if (brick_game.getRemainLives() == 0 || brick_game.getRemainBricks() == 0)
		{
			brick_game.gameOverHandle(sprite);
		}
		brick_game.draw_game(sprite);
	}
}