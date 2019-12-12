#pragma once
#include "Ball.h"
#include "cPaddle.h"
#include <SFML\Graphics.hpp>
#include "Menu.h"
#include "Option.h"
#include "Brick.h"
#include <fstream>
#include <string>
#include <list>
#include <stdlib.h>
#include <algorithm>
#include <utility>
using namespace std;
using namespace sf;

const int wWidth = 1024;
const int wHeight = 768;

class BrickBreaker
{
public:
	BrickBreaker();
	~BrickBreaker();
	void handleKeyPress();
	void handleEdgeCollision(FloatRect, FloatRect, FloatRect, FloatRect);
	void draw_game(Sprite);
	bool isOpen();
	void loadLevel(int);
	void handleBrickCollision();
	void Countdown_timer();
	void gameOverHandle(Sprite sprite);
	void handleSpecialBrick(char);
	void clearWindow();
	RenderWindow& getWindow();
	void loadShieldBrick();
	void togglePause();
	void saveGame();
	void loadGame();
	void startMenu();
	void saveHighScore();
	void writeHighScore();
	void loadHighScore();
	void displayHighScore(Sprite sprite);
	int getRemainLives();
	int getRemainBricks();
private:
	int padLength, ball_speed, pad_speed, lives, score, combo;
	bool start, pause, shield, penetrate, play;
	string specialList = "mdspRrLlFS+";
	Vector2f InitializePadPos, InitializeBallPos;
	cPaddle pad;
	Ball ball;
	RenderWindow window;
	ContextSettings setting;
	list<Brick> brick_list, shield_brick;
	list<int> highScore;
	Text Lives, Score, txt_lives, txt_score, txt_timer_min, txt_timer_sec, continue_guide, start_guide, colon, txt_togglePause;
	Font font, numeric_font;
	list<Brick>::iterator pos, shieldPos;
	Time timer, _timer;
	void resetBallPad();
	
};

