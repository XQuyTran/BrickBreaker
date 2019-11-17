#ifndef __Game_H_
#define __Game_H_
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Ball.h"
class Game
{
private:
	Ball ball;
	int wWidth = 1024;
	int wHeight = 768;
public:
	void GameManage(Ball);
	int getWidth();
	int getHeight();
};
#endif