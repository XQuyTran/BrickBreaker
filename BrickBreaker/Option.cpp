#include "Option.h"
using namespace std;

Option::Option(float width, float height)
{
	if (!font.loadFromFile("game_over.ttf"))
	{
	}
	menu[0].setFont(font);
	menu[0].setFillColor(Color::Cyan);
	menu[0].setString("<<");
	menu[0].setCharacterSize(75);
	menu[0].setPosition(Vector2f(width / (MAX_NUMBER_OF_ITEM + 7) * 6, height / 2));

	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setString(">>");
	menu[1].setCharacterSize(75);
	menu[1].setPosition(Vector2f(width / (MAX_NUMBER_OF_ITEM + 7) * 4, height / 2));
	selectecItem = 0;
}



void Option::drawSpeed(RenderWindow& window,int Speed)
{
	SpriteDraw2(window);
	TocDo(Speed-1, window);
	for (int i = 0; i < MAX_NUMBER_OF_ITEM; i++)
	{
		window.draw(menu[i]);
	}
}

void Option::moveRight()
{
	if (selectecItem - 1 >= 0)
	{
		menu[selectecItem].setFillColor(Color::White);
		selectecItem--;
		menu[selectecItem].setFillColor(Color::Cyan);
	}
}

void Option::moveLeft()
{
	if (selectecItem + 1 < MAX_NUMBER_OF_ITEM)
	{
		menu[selectecItem].setFillColor(Color::White);
		selectecItem++;
		menu[selectecItem].setFillColor(Color::Cyan);
	}
}

int Option::getPressedItem()
{
	return selectecItem;
}
void Option::SpriteDraw2(sf::RenderWindow& window)
{
	sf::Texture texture;
	sf::Sprite sprite;
	if (!texture.loadFromFile("image/3.jpg"))
	{
		std::cout << "Load Textured failed";
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 1024, 768));
	window.draw(sprite);
}
void Option::TocDo(int Speed, sf::RenderWindow& window)
{
	Text hud1;
	Font font;
	font.loadFromFile("Calculator.ttf");
	hud1.setFont(font);
	hud1.setCharacterSize(100);
	hud1.setFillColor(sf::Color::White);
	stringstream ss;
	ss << Speed;
	hud1.setString(ss.str());
	hud1.setPosition(Vector2f(1024 / (MAX_NUMBER_OF_ITEM + 7) * 5, 768 / 2));
	window.draw(hud1);
	Text hud2;
	hud2.setFont(font);
	hud2.setCharacterSize(100);
	hud2.setFillColor(sf::Color::White);
	stringstream title;
	title << "Select Speed";
	hud2.setString(title.str());
	hud2.setPosition(Vector2f((1024/2)- 100, 768 /4));
	window.draw(hud2);
}
void Option::drawScoreEnd(RenderWindow& window, int ScoreEnd)
{
	SpriteDraw2(window);
	DiemKetThuc(ScoreEnd, window);
	for (int i = 0; i < MAX_NUMBER_OF_ITEM; i++)
	{
		window.draw(menu[i]);
	}
}
void Option::DiemKetThuc(int Speed, sf::RenderWindow& window)
{
	Text hud1;
	Font font;
	font.loadFromFile("Calculator.ttf");
	hud1.setFont(font);
	hud1.setCharacterSize(100);
	hud1.setFillColor(sf::Color::White);
	stringstream ss;
	ss << Speed;
	hud1.setString(ss.str());
	hud1.setPosition(Vector2f(1024 / (MAX_NUMBER_OF_ITEM + 7) * 5, 768 / 2));
	window.draw(hud1);
	Text hud2;
	hud2.setFont(font);
	hud2.setCharacterSize(100);
	hud2.setFillColor(sf::Color::White);
	stringstream title;
	title << "Max Scored";
	hud2.setString(title.str());
	hud2.setPosition(Vector2f((1024 / 2) - 100, 768 / 4));
	window.draw(hud2);
}