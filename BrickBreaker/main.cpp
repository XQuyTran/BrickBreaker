#include "Ball.h"
#include "cPaddle.h"
#include "Game.h"
#include <SFML\Graphics.hpp>
#include "Menu.h"
#include "Option.h"
#include <conio.h>
#include <sstream>
using namespace std;
using namespace sf;
int main()
{
	int select;
	int selectOption;
	int score1 = 0;
	int score2 = 0;
	int Speed = 2;
	int ScoreEnd = 10;
	int wWidth = 1024;
	int wHeight = 768;
	Option Option(wWidth, wHeight);
	Menu Menu(wWidth, wHeight);
	RenderWindow window1(VideoMode(wWidth, wHeight), "Pong");
	cPaddle paddle1(1, (wHeight / 2) - 20);
	cPaddle paddle2(wWidth - 25, (wHeight / 2) - 20);
	Ball Ball(wWidth / 2, 1);
	while (window1.isOpen())
	{
		Menu.draw(window1);
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			Menu.moveUp();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			Menu.moveDown();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			select = Menu.getPressedItem();
			window1.close();
		}
		window1.display();
	}
	if (select == 1)
	{
		RenderWindow window3(VideoMode(wWidth, wHeight), "Pong");
		while (window3.isOpen())
		{
			Option.drawSpeed(window3, Speed);
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				Option.moveRight();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				Option.moveLeft();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				selectOption = Option.getPressedItem();
				if (selectOption == 0)
				{
					Speed++;
				}
				else
				{
					Speed--;
					if (Speed <= 2)
						Speed = 2;
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				select = 0;
				window3.close();
			}
			window3.display();
		}
		RenderWindow windowScore(VideoMode(wWidth, wHeight), "Pong");
		while (windowScore.isOpen())
		{
			Option.drawScoreEnd(windowScore, ScoreEnd);
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				Option.moveRight();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				Option.moveLeft();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				selectOption = Option.getPressedItem();
				if (selectOption == 0)
				{
					ScoreEnd++;
				}
				else
				{
					ScoreEnd--;
					if (ScoreEnd <= 3)
						ScoreEnd = 3;
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				select = 0;
				windowScore.close();
			}
			windowScore.display();
		}
	}
	Ball.SetSpeed(Speed);
	if (select == 0)
	{
		RenderWindow window2(VideoMode(wWidth, wHeight), "Pong");
		while (window2.isOpen())
		{
			window2.setFramerateLimit(120);
			Event event;
			while (window2.pollEvent(event))
			{
				if (event.type == Event::Closed)
					// Someone closed the window- bye
					window2.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::W) && paddle1.getPosition().top > 1)
			{
				//paddle1 di chuyen len tren
				paddle1.moveUp();
			}
			else if (Keyboard::isKeyPressed(Keyboard::S) && paddle1.getPosition().top < wHeight - 100)
			{
				//paddle1 di chuyen xuong duoi
				paddle1.moveDown();
			}
			if (Keyboard::isKeyPressed(Keyboard::I) && paddle2.getPosition().top > 1)
			{
				//paddle 2 di chuyen len tren
				paddle2.moveUp();
			}
			else if (Keyboard::isKeyPressed(Keyboard::K) && paddle2.getPosition().top < wHeight - 100)
			{
				//paddle2 di chuyen xuong duoi
				paddle2.moveDown();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Escape)||(score1 == ScoreEnd) || (score2== ScoreEnd))
			{
				//Dong cua so tro choi
				window2.close();
			}
			paddle1.Update();
			paddle2.Update();
			if (Ball.getPosition().top > wHeight || Ball.getPosition().top < 0)
			{
				Ball.ReboundTopOrBot();
			}
			if (Ball.getPosition().left < 0)
			{
				score2++;
				Ball.ReturnCenter(Speed);
			}
			if (Ball.getPosition().left + 10 > wWidth)
			{
				score1++;
				Ball.ReturnCenter(Speed);
			}
			if (Ball.getPosition().intersects(paddle1.getPosition()))
			{
				Ball.ReboundPaddle();
			}
			if (Ball.getPosition().intersects(paddle2.getPosition()))
			{
				Ball.ReboundPaddle();
			}
			Ball.update();
			window2.clear(Color(26, 128, 182, 255));
			window2.draw(Ball);
			window2.draw(paddle1.getShape());
			window2.draw(paddle2.getShape());
			{
				Text hud;
				Font font;
				font.loadFromFile("Calculator.ttf");
				hud.setFont(font);
				hud.setCharacterSize(75);
				hud.setFillColor(sf::Color::White);
				stringstream ss;
				ss << score1 << "      " << score2;
				hud.setString(ss.str());
				hud.setPosition(Vector2f((1024/3)+70, 3));
				window2.draw(hud);
			}
			window2.display();

		}
		RenderWindow EndGame(VideoMode(wWidth, wHeight), "Pong");
		while(EndGame.isOpen())
		{
			sf::Texture texture;
			sf::Sprite sprite;
			if (!texture.loadFromFile("image/2.png"))
			{
				std::cout << "Load Textured failed";
			}
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(0, 0, 1024, 768));
			EndGame.draw(sprite);
			Text hud;
			Font font;
			font.loadFromFile("Calculator.ttf");
			hud.setFont(font);
			hud.setCharacterSize(80);
			hud.setFillColor(sf::Color::White);
			stringstream ss;
			if ((score1 == ScoreEnd) || (score1 > score2))
			{
				ss << "Nguoi choi 1 da chien thang";
			}
			else if ((score2 == ScoreEnd) || (score1 < score2))
				ss << "Nguoi choi 2 da chien thang";
			else if (score1 == score2)
				ss << "2 Nguoi choi hoa nhau";
			hud.setString(ss.str());
			hud.setPosition(Vector2f(100, 768 / 2));
			EndGame.draw(hud);
			EndGame.display();
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				EndGame.close();
			}
		}
	}
	return 0;
}