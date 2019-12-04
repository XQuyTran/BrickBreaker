#include "Menu.h"
using namespace std;

Menu::Menu()
{

}

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("game_over.ttf"))
	{
	}
	menu[0].setFont(font);
	menu[0].setFillColor(Color::Cyan);
	menu[0].setString("Play");
	menu[0].setCharacterSize(75);
	menu[0].setPosition(Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEM + 7) * 3));

	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setString("Option");
	menu[1].setCharacterSize(75);
	menu[1].setPosition(Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEM + 7) * 5));

	menu[2].setFont(font);
	menu[2].setFillColor(Color::White);
	menu[2].setString("Exit");
	menu[2].setCharacterSize(75);
	menu[2].setPosition(Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEM + 7) * 7));
	selectecItem = 0;
}

Menu::~Menu()
{
	/*delete[]menu;*/
}

void Menu::draw(RenderWindow& window)
{
	SpriteDraw1(window);
	for (int i = 0; i < MAX_NUMBER_OF_ITEM; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::moveUp()
{
	if (selectecItem - 1 >= 0)
	{
		menu[selectecItem].setFillColor(Color::White);
		selectecItem--;
		menu[selectecItem].setFillColor(Color::Cyan);
	}
}

void Menu::moveDown()
{
	if (selectecItem + 1 < MAX_NUMBER_OF_ITEM)
	{
		menu[selectecItem].setFillColor(Color::White);
		selectecItem++;
		menu[selectecItem].setFillColor(Color::Cyan);
	}
}

int Menu::getPressedItem()
{
	return selectecItem;
}
void Menu::SpriteDraw1(sf::RenderWindow& window)
{
	sf::Texture texture;
	sf::Sprite sprite;
	if (!texture.loadFromFile("BrickBreakerData/image/1.jpg"))
	{
		std::cout << "Load Textured failed";
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 1024, 768));
	window.draw(sprite);
}
void Menu::SpriteDraw2(sf::RenderWindow& window)
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

Menu::Menu(string content[], float width, float height, Font font)
{
	menu[0].setFont(font);
	menu[0].setFillColor(Color::Cyan);
	menu[0].setString(content[0]);
	menu[0].setCharacterSize(75);
	menu[0].setPosition(Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEM + 7) * 3));
	
	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setString(content[1]);
	menu[1].setCharacterSize(75);
	menu[1].setPosition(Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEM + 7) * 5));

	menu[2].setFont(font);
	menu[2].setFillColor(Color::White);
	menu[2].setString(content[2]);
	menu[2].setCharacterSize(75);
	menu[2].setPosition(Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEM + 7) * 7));
	selectecItem = 0;
}