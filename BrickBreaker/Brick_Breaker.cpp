#include "Brick_Breaker.h"

void BrickBreaker::loadLevel(int level)
{
	string level_file = "BrickBreakerData/levels/";
	Vector2f pos = { 0,100 };
	char brick_kind;
	level_file += to_string(level);
	level_file += ".txt";
	ifstream f(level_file.c_str());
	
	while (true)
	{
		f.get(brick_kind);
		if (f.eof())
		{
			break;
		}
		if (brick_kind != ' ' && brick_kind != '\n')
		{
			Brick brick(pos);
			if (brick_kind == '~')
			{
				brick.setSpecial(specialList[rand() % specialList.length()]);
			}

			brick_list.push_back(brick);
		}
		
		pos.x += 65;
		if (brick_kind == '\n')
		{
			pos.x = 0;
			pos.y += 30;
		}
	}

	lives = 3;
	score = 0;

	timer = milliseconds(270 * 1000);
	String S_lives(to_string(lives)), S_score(to_string(score));
	String S_timer_min(to_string(int(timer.asSeconds() / 60))), S_timer_sec(to_string(int(timer.asSeconds()) % 60));

	txt_lives.setString(S_lives);
	txt_score.setString(S_score);
	txt_timer_min.setString(S_timer_min);
	txt_timer_sec.setString(S_timer_sec);
}

BrickBreaker::BrickBreaker()
{
	padLength = 125;
	ball_speed = 3;
	pad_speed = 4;
	start = false;
	pause = false;
	shield = false;
	play = false;
	_timer = milliseconds(17.5);

	InitializePadPos = { float(wWidth / 2) - 50,float(wHeight - 100) };
	pad.setAttributes(InitializePadPos, padLength, pad_speed);
	pad.setFillColor(Color(140,125,112));

	InitializeBallPos = { (InitializePadPos.x + pad.getPosition().width / 2) - 8,InitializePadPos.y + 5 - pad.getHeight() };
	ball.setAttributes(InitializeBallPos);
	ball.setFillColor(Color::White);
	
	setting.antialiasingLevel = 4;
	window.create(VideoMode(wWidth, wHeight), "Brick Breaker", Style::Default, setting);
	window.setFramerateLimit(60);

	numeric_font.loadFromFile("BrickBreakerData/Fonts/Calculator.ttf");
	font.loadFromFile("BrickBreakerData/Fonts/game_over.ttf");

	Lives.setString("Lives:");
	Lives.setCharacterSize(60);
	Lives.setFont(font);
	Lives.setPosition(5, 5);

	Score.setString("Score:");
	Score.setCharacterSize(60);
	Score.setFont(font);
	Score.setPosition(850, 5);

	txt_score.setCharacterSize(36);
	txt_score.setFont(numeric_font);
	txt_score.setPosition(935, 30);
	txt_score.setStyle(Text::Bold);
	
	txt_lives.setCharacterSize(36);
	txt_lives.setFont(numeric_font);
	txt_lives.setPosition(85, 30);
	txt_lives.setStyle(Text::Bold);

	txt_timer_min.setCharacterSize(40);
	txt_timer_min.setFont(numeric_font);
	txt_timer_min.setPosition(wWidth / 2, 30);
	txt_timer_min.setStyle(Text::Bold);

	txt_timer_sec.setCharacterSize(40);
	txt_timer_sec.setFont(numeric_font);
	txt_timer_sec.setPosition(wWidth / 2 + 30, 30);
	txt_timer_sec.setStyle(Text::Bold);

	continue_guide.setCharacterSize(60);
	continue_guide.setFont(font);
	continue_guide.setString("PRESS SPACE TO CONTINUE\n   OR PRESS ESC TO QUIT");

	start_guide.setCharacterSize(60);
	start_guide.setFont(font);
	start_guide.setString("PRESS SPACE TO START\n\tPRESS P TO PAUSE\n\tPRESS ESC TO QUIT");
	start_guide.setPosition(wWidth / 2 - 125, wHeight / 2 - 40);

	colon.setCharacterSize(60);
	colon.setFont(numeric_font);
	colon.setString(":");
	colon.setPosition(wWidth / 2 + 20, 15);
	colon.setStyle(Text::Bold);

	txt_togglePause.setCharacterSize(60);
	txt_togglePause.setFont(font);
	txt_togglePause.setString("PRESS SPACE TO CONTINUE\n\t\tPRESS S TO SAVE\n\t\tPRESS ESC TO QUIT");
	txt_togglePause.setPosition(wWidth / 2 - 125, wHeight / 2 -45);
}

BrickBreaker::~BrickBreaker()
{
}

void BrickBreaker::handleKeyPress()
{
	if (!start)
	{
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			start = true;
			ball.SetSpeed(ball_speed);
		}
	}
	else
	{
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
		if (Keyboard::isKeyPressed(Keyboard::P))
		{
			togglePause();
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
		combo = 0;
		ball.Rebound_IncreaseSpeed();
	}
	if (ball.getPosition().intersects(lowerEdge))
	{
		resetBallPad();
		--lives;
		penetrate = false;
		ball.setFillColor(Color::White);
		ball.setRadius(10);
		pad_speed = 3;
		pad.setSpeed(pad_speed);
		padLength = 125;
		pad.setLength(padLength);
		
		String S_lives(to_string(lives));
		txt_lives.setString(S_lives);
	}
}

void BrickBreaker::resetBallPad()
{
	pad.setPosition(InitializePadPos);
	ball.SetPosition(InitializeBallPos.x,InitializeBallPos.y);
	start = false;
	ball.SetSpeed(0);
}

void BrickBreaker::draw_game(Sprite sprite)
{
	pad.Update();
	ball.update();

	window.clear();
	window.draw(sprite);

	window.draw(pad.getShape());
	window.draw(ball);

	window.draw(Lives);
	window.draw(Score);

	window.draw(txt_lives);
	window.draw(txt_score);
	
	window.draw(txt_timer_min);
	window.draw(txt_timer_sec);
	window.draw(colon);

	pos = brick_list.begin();
	while (pos != brick_list.end())
	{
		window.draw(pos->getShape());
		++pos;
	}

	if (!start)
	{
		window.draw(start_guide);
	}
	if (shield)
	{
		shieldPos = shield_brick.begin();
		while (shieldPos != shield_brick.end())
		{
			window.draw(shieldPos->getShape());
			++shieldPos;
		}
	}
	window.display();
}

bool BrickBreaker::isOpen()
{
	return window.isOpen();
}

void BrickBreaker::handleSpecialBrick(char special_char)
{
	switch (special_char)
	{
	case 'm':
		score *= 2;
		break;
	case 'd':
		score /= 2;
		break;
	case 's':
		loadShieldBrick();
		break;
	case 'p':
		penetrate = true;
		ball.setFillColor(Color(105, 105, 105));
		break;
	case 'R':
		ball.setRadius(ball.getRadius() + 5);
		break;
	case 'r':
		ball.setRadius(ball.getRadius() - 3);
		break;
	case 'L':
		pad.setLength(padLength + 25);
		break;
	case 'l':
		pad.setLength(padLength - 25);
		break;
	case 'F':
		pad.setSpeed(pad_speed * 2);
		break;
	case 'S':
		pad.setSpeed(pad_speed / 2);
		break;
	case '+':
		lives += 1;
	default:
		break;
	}
}

void BrickBreaker::handleBrickCollision()
{
	FloatRect ballBound = ball.getGlobalBounds();
	float ballRadius = ball.getRadius();
	int n = brick_list.size();
	char colide_type, special_char;
	
	pos = brick_list.begin();

	while (pos != brick_list.end())
	{
		colide_type = pos->handleCollision(ballBound, ballRadius);

		if (colide_type != 'n')
		{
			special_char = pos->getSpecialchar();
			if (special_char != 0)
			{
				handleSpecialBrick(special_char);
			}
			if (!penetrate)
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
			}

			combo++;
			score += 2 * combo;

			String S_score(to_string(score));
			txt_score.setString(S_score);

			pos = brick_list.erase(pos);
		}
		else
		{
			++pos;
		}
	}

	shieldPos = shield_brick.begin();

	while (shieldPos != shield_brick.end())
	{
		colide_type = shieldPos->handleCollision(ballBound, ballRadius);

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

			shieldPos = shield_brick.erase(shieldPos);
		}
		else
		{
			++shieldPos;
		}
	}
}

void BrickBreaker::Countdown_timer()
{
	if (timer >= Time::Zero && start)
	{
		timer -= _timer;
		
		String S_timer_min(to_string(int(timer.asSeconds() / 60))), S_timer_sec(to_string(int(timer.asSeconds()) % 60));

		txt_timer_min.setString(S_timer_min);
		txt_timer_sec.setString(S_timer_sec);
	}
}

void BrickBreaker::gameOverHandle(Sprite sprite)
{
	window.clear();
	window.draw(sprite);

	if (lives == 0)
	{
		Text game_over;

		game_over.setCharacterSize(60);
		game_over.setFont(font);
		game_over.setString("GAME OVER");
		game_over.setPosition(wWidth / 2 - 45, wHeight / 2);

		window.draw(game_over);
	}
	else
	{
		if (brick_list.size() == 0)
		{
			score += int(timer.asSeconds());

			Text won;

			won.setCharacterSize(60);
			won.setString("YOU WON");
			won.setFont(font);
			won.setPosition(wWidth / 2 - 45, wHeight / 2);

			window.draw(won);
			
		}
	}

	window.display();

	Time dur;
	dur = milliseconds(2000);
	sleep(dur);

	loadHighScore();
	saveHighScore();
	displayHighScore(sprite);
	writeHighScore();

	pause = true;
	while (pause)
	{
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			pause = false;
			start = false;
			play = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			pause = false;
			window.close();
		}
	}
	
}

void BrickBreaker::clearWindow()
{
	window.clear();
}

RenderWindow& BrickBreaker::getWindow()
{
	return window;
}

void BrickBreaker::loadShieldBrick()
{
	shield = true;
	Vector2f shield_pos;
	Color color;
	shield_pos.x = 0;
	shield_pos.y = pad.GetPosition().y + 50;
	
	color.r = 128;
	color.g = 128;
	color.b = 128;
	do
	{
		Brick shield(shield_pos);

		shield.setSize(120, 15);
		shield.setFillColor(color);

		shield_brick.push_back(shield);
		shield_pos.x += 128;
	} while (shield_pos.x <= 1024);
}

void BrickBreaker::togglePause()
{
	pause = true;
	window.draw(txt_togglePause);
	window.display();

	while (pause)
	{
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			pause = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			saveGame();

			Text saved("GAME SAVED", font, 60);
			saved.setPosition(txt_togglePause.getPosition());
			saved.setFillColor(Color::White);

			txt_togglePause.setFillColor(Color::Transparent);
			window.draw(txt_togglePause);
			window.draw(saved);
			window.display();
			
			Time dur;
			dur = milliseconds(2000);
			sleep(dur);

			saved.setFillColor(Color::Transparent);
			txt_togglePause.setFillColor(Color::White);
			window.draw(txt_togglePause);
			window.draw(saved);
			window.display();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			pause = false;
			window.close();
		}
	}
}

void BrickBreaker::saveGame()
{
	ofstream f;
	Vector2f brickPos = { 0,100 }, savePos;
	f.open("BrickBreakerData/save.txt");

	f << lives << "," << timer.asSeconds() << "," << score << endl;
	pos = brick_list.begin();
	while (pos != brick_list.end())
	{
		savePos = pos->getPosition();

		if (savePos.y > brickPos.y)
		{
			f << endl;
			brickPos.y = savePos.y;
			brickPos.x = 0;
		}
		else
		{
			while (savePos.x > brickPos.x + 65)
			{
				f << " ";
				brickPos.x += 65;
			}
			brickPos.x += 65;
		}
		if (pos->getSpecialchar() == 0)
		{
			f << "-";
		}
		else
		{
			f << pos->getSpecialchar();
		}

		++pos;
	}

	f.close();
}

void BrickBreaker::loadGame()
{
	ifstream f("BrickBreakerData/save.txt");
	Vector2f pos = { 0,100 };
	char brick_kind;
	string str_read;

	getline(f, str_read, ',');
	lives = stoi(str_read);
	getline(f, str_read, ',');
	timer = seconds(stof(str_read));
	getline(f, str_read, '\n');
	score = stoi(str_read);
	timer.asMilliseconds();

	while (true)
	{
		f.get(brick_kind);
		if (f.eof())
		{
			break;
		}

		if (brick_kind != ' ')
		{
			Brick brick(pos);
			if (brick_kind != '-')
			{
				brick.setSpecial(brick_kind);
			}

			brick_list.push_back(brick);
		}

		pos.x += 65;
		if (brick_kind == '\n')
		{
			pos.x = 0;
			pos.y += 30;
		}
	}
	String S_lives(to_string(lives)), S_score(to_string(score));
	String S_timer_min(to_string(int(timer.asSeconds() / 60))), S_timer_sec(to_string(int(timer.asSeconds()) % 60));

	txt_lives.setString(S_lives);
	txt_score.setString(S_score);
	txt_timer_min.setString(S_timer_min);
	txt_timer_sec.setString(S_timer_sec);
	f.close();
}

void BrickBreaker::startMenu()
{
	if (!play)
	{
		Texture background;
		background.loadFromFile("BrickBreakerData/image/1.jpg");
		Vector2f position = start_guide.getPosition();

		position.x -= 75;
		Text begin_guide("PRESS ENTER TO START A NEW GAME\nPRESS L TO LOAD LAST SAVE GAME\nPRESS ESC TO QUIT", font, 70);
		begin_guide.setPosition(position);
		begin_guide.setStyle(Text::Bold);

		window.draw(Sprite(background));
		window.draw(begin_guide);
		window.display();

		while (true)
		{
			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				int level;
				for (int i = 0; i < rand() % 6 + 1; i++)
				{
					level = rand() % 6 + 1;
				}

				loadLevel(level);
				play = true;

				break;
			}
			if (Keyboard::isKeyPressed(Keyboard::L))
			{
				play = true;
				loadGame();
				break;
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				exit(0);
			}
		}
	}

}

void BrickBreaker::saveHighScore()
{
	highScore.push_back(score);
	highScore.sort(greater<int>());

	while (highScore.size() > 5)
	{
		highScore.pop_back();
	}
}

void BrickBreaker::writeHighScore()
{
	ofstream scoreFile("BrickBreakerData/score.txt");

	list<int>::iterator pos = highScore.begin();

	while (pos != highScore.end())
	{
		scoreFile << *pos;

		++pos;

		if (pos != highScore.end())
		{
			scoreFile << ",";
		}
	}

	scoreFile.close();
}

void BrickBreaker::loadHighScore()
{
	highScore.clear();

	ifstream scoreFile("BrickBreakerData/score.txt");
	if (!scoreFile.is_open())
	{
		return;
	}

	string s;

	if (!scoreFile.is_open())
	{
		return;
	}

	while (!scoreFile.eof())
	{
		getline(scoreFile, s, ',');
		if (!s.empty())
		{
			highScore.push_back(stoi(s));
		}
		
	}

	scoreFile.close();
}

void BrickBreaker::displayHighScore(Sprite sprite)
{
	Text highScoreTxt("HIGH SCORE", font, 80), scoreText;
	Vector2f draw_pos = txt_timer_min.getPosition();
	
	int added[] = { score };
	String strScore;
	list<int>::iterator pos = highScore.begin(), new_added;
	
	draw_pos.x -= 50;

	scoreText.setCharacterSize(60);
	scoreText.setFont(numeric_font);
	highScoreTxt.setPosition(draw_pos);
	highScoreTxt.setStyle(Text::Bold);
	highScoreTxt.setFillColor(Color::Blue);

	draw_pos.x += 50;
	draw_pos.y += 100;

	window.clear();
	window.draw(sprite);
	window.draw(highScoreTxt);

	new_added = find_end(highScore.begin(), highScore.end(), added, added + 1);
	while (pos != highScore.end())
	{
		strScore = to_string(*pos);

		scoreText.setString(strScore);
		scoreText.setPosition(draw_pos);

		if (pos == new_added)
		{
			scoreText.setFillColor(Color::Cyan);
			scoreText.setStyle(Text::Bold);
		}

		window.draw(scoreText);
		draw_pos.y += 100;
		++pos;
	}

	draw_pos.x -= 100;
	continue_guide.setPosition(draw_pos);
	window.draw(continue_guide);

	window.display();
}

int BrickBreaker::getRemainLives()
{
	return lives;
}

int BrickBreaker::getRemainBricks()
{
	return brick_list.size();
}