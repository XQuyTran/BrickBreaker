#include "Brick_Breaker.h"

void BrickBreaker::loadLevel(int level)
{
	// khai báo chuỗi lưu tên file của level
	string level_file = "BrickBreakerData/levels/";
	
	// khai báo vector lưu vị trí viên gạch trên màn hình, ký tự đặc biệt
	Vector2f pos = { 0,100 };
	char brick_kind;
	
	// ghép chuỗi tên file cho hoàn chỉnh
	level_file += to_string(level);
	level_file += ".txt";
	
	// Khai báo file stream để mở file
	ifstream f(level_file.c_str());
	
	while (true)
	{
		// đọc kí tự từ file
		f.get(brick_kind);
		
		// kiểm tra hết file
		// nếu đúng thì thoát
		if (f.eof())
		{
			break;
		}
		
		// kiểm tra ký tự đọc được khác ' ' và '\n'
		if (brick_kind != ' ' && brick_kind != '\n')
		{
			// khia báo đối tượng gạch vói vị trí pos
			Brick brick(pos);
			
			// Kiêm tra đọc được ký tự '~'
			if (brick_kind == '~')
			{
				// chọn ngẫu nhiên 1 tính năng đặc biệt cho viên gạch từ danh sách
				brick.setSpecial(specialList[rand() % specialList.length()]);
			}
			
			// thêm viên gạch vào danh sách
			brick_list.push_back(brick);
		}
		
		// cập nhật vị trí
		pos.x += 65;
		if (brick_kind == '\n')
		{
			pos.x = 0;
			pos.y += 30;
		}
	}
	
	// khởi gán điểm số, số mạng, và thời gian chơi
	lives = 3;
	score = 0;
	timer = milliseconds(270 * 1000);
	
	// tạo chuỗi ghi lại số mạng, số diểm và thời gian để vẽ ra màn hình
	String S_lives(to_string(lives)), S_score(to_string(score));
	String S_timer_min(to_string(int(timer.asSeconds() / 60))), S_timer_sec(to_string(int(timer.asSeconds()) % 60));

	txt_lives.setString(S_lives);
	txt_score.setString(S_score);
	txt_timer_min.setString(S_timer_min);
	txt_timer_sec.setString(S_timer_sec);
}

BrickBreaker::BrickBreaker()
{
	// Khởi tạo:
	// độ dài thanh trượt
	// tốc độ của banh và thanh trượt
	// các lá cờ thể hiện trạng thái trò chơi
	// độ giảm thời gian
	padLength = 125;
	ball_speed = 3;
	pad_speed = 3;
	start = false;
	pause = false;
	shield = false;
	play = false;
	_timer = milliseconds(17.5);
	
	// khai báo vị trí ban đầu và đặt vị trí cho thanh trượt
	InitializePadPos = { float(wWidth / 2) - 50,float(wHeight - 100) };
	pad.setAttributes(InitializePadPos, padLength, pad_speed);
	pad.setFillColor(Color(140,125,112));
	
	// khai báo vị trí ban đầu và đặt vị trí cho banh
	InitializeBallPos = { (InitializePadPos.x + pad.getPosition().width / 2) - 8,InitializePadPos.y + 5 - pad.getHeight() };
	ball.setAttributes(InitializeBallPos);
	ball.setFillColor(Color::White);
	
	// đặt độ khử răng cưa, tên cửa sổ và giới hạn độ khung hình/giấy
	setting.antialiasingLevel = 4;
	window.create(VideoMode(wWidth, wHeight), "Brick Breaker", Style::Default, setting);
	window.setFramerateLimit(60);

	// tải font chữ lên từ file
	numeric_font.loadFromFile("BrickBreakerData/Fonts/Calculator.ttf");
	font.loadFromFile("BrickBreakerData/Fonts/game_over.ttf");

	// cài đặt các thuộc tính cho các chuỗi thể hiện:
	// số mạng, số điểm, thời gian, các dòng chữ hướng dẫn thao tác
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
	// kiểm tra cờ start đang là false
	if (!start)
	{
		// kiểm tra phím space có dược nhấn
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			// đặt cờ start là true - tức là bắt đầu chơi
			// đặt tốc độ di chuyển của banh
			start = true;
			ball.SetSpeed(ball_speed);
		}
	}
	else
	{
		// kiểm tra phím mũi tên trái được nhấn và vị trí thanh trượt chạm biên trái
		if (Keyboard::isKeyPressed(Keyboard::Left) && pad.getPosition().left > 0)
		{
			// di chuyển thanh trượt qua trái
			pad.moveLeft();
			if (!start)
			{
				Vector2f new_pos = pad.GetPosition();
				ball.SetPosition((new_pos.x + pad.getPosition().width / 2) - 8, new_pos.y + 5 - pad.getHeight());
			}
		}
		
		// kiểm tra phím mũi tên phải được nhấn và vị trí thanh trượt chạm biên phải
		if (Keyboard::isKeyPressed(Keyboard::Right) && pad.getPosition().width + pad.getPosition().left < wWidth)
		{
			// di chuyển thanh trượt qua phải
			pad.moveRight();
			if (!start)
			{
				Vector2f new_pos = pad.GetPosition();
				ball.SetPosition((new_pos.x + pad.getPosition().width / 2) - 8, new_pos.y + 5 - pad.getHeight());
			}
		}
		
		// kiểm tra phím 'P' được nhấn
		if (Keyboard::isKeyPressed(Keyboard::P))
		{
			// gọi phương thức hiện pause menu
			togglePause();
		}
	}
	
	// kiểm tra phím ESC được nhấn
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		// đóng cửa sổ trò chơi
		window.close();
	}
}

void BrickBreaker::handleEdgeCollision(FloatRect topEdge, FloatRect leftEdge, FloatRect rightEdge, FloatRect lowerEdge)
{
	// Lần lượt kiểm tra banh có chạm vào các biên trên, trái, phải, dưới và chạm vào thanh trượt
	// nếu có thực hiện xử lý tương ứng
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
		// đặt lại combo
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
	// đặt lại vị trí thanh trượt và banh, trạng thái chơi và tốc độ banh
	pad.setPosition(InitializePadPos);
	ball.SetPosition(InitializeBallPos.x,InitializeBallPos.y);
	start = false;
	ball.SetSpeed(0);
}

void BrickBreaker::draw_game(Sprite sprite)
{
	// cập nhật vị trí banh và thanh trượt
	pad.Update();
	ball.update();

	// xóa những gì đã vẽ trên cửa sổ
	// vẽ lại hình nền
	window.clear();
	window.draw(sprite);

	// vẽ lại thanh trượt và banh
	window.draw(pad.getShape());
	window.draw(ball);

	// vẽ chuỗi ghi các thông tin về mạng, điểm số và thời gian
	window.draw(Lives);
	window.draw(Score);
	window.draw(txt_lives);
	window.draw(txt_score);
	window.draw(txt_timer_min);
	window.draw(txt_timer_sec);
	window.draw(colon);

	// vẽ hàng gạch
	pos = brick_list.begin();
	while (pos != brick_list.end())
	{
		window.draw(pos->getShape());
		++pos;
	}

	// kiểm tra bắt đầu chơi
	if (!start)
	{
		// vẽ chuỗi ghi hướng dẫn bắt đầu
		window.draw(start_guide);
	}
	
	// kiểm tra lá chắn được bật
	if (shield)
	{
		// vẽ hàng gạch lá chắn dưới thanh trượt
		shieldPos = shield_brick.begin();
		while (shieldPos != shield_brick.end())
		{
			window.draw(shieldPos->getShape());
			++shieldPos;
		}
	}
	
	// hiển thị những gì đã vẽ
	window.display();
}

bool BrickBreaker::isOpen()
{
	return window.isOpen();
}

void BrickBreaker::handleSpecialBrick(char special_char)
{
	// so sánh kí hiệu đặc biệt
	switch (special_char)
	{
	case 'm':
		// x2 số điểm
		score *= 2;
		break;
	case 'd':
		//chia đôi số điểm
		score /= 2;
		break;
	case 's':
		// tạo hàng gạch chắn dưới thanh trượt
		loadShieldBrick();
		break;
	case 'p':
		// cho banh xuyên phá gạch
		penetrate = true;
		ball.setFillColor(Color(105, 105, 105));
		break;
	case 'R':
		// tăng kích thước banh
		ball.setRadius(ball.getRadius() + 5);
		break;
	case 'r':
		// giảm kích thước banh
		ball.setRadius(ball.getRadius() - 3);
		break;
	case 'L':
		// tăng độ dài thanh trượt
		pad.setLength(padLength + 25);
		break;
	case 'l':
		// giảm độ dài thanh trượt
		pad.setLength(padLength - 25);
		break;
	case 'F':
		// tăng tốc độ thanh trượt
		pad.setSpeed(pad_speed * 2);
		break;
	case 'S':
		// giảm tốc độ thanh trượt
		pad.setSpeed(pad_speed / 2);
		break;
	case '+':
		// thêm 1 mạng
		lives += 1;
	default:
		break;
	}
}

void BrickBreaker::handleBrickCollision()
{
	// khai báo đối tượng lưu hình dạng, bán kính banh;
	// số lượng viên gạch; kiểu va chạm; kí hiệu đặc biệt
	FloatRect ballBound = ball.getGlobalBounds();
	float ballRadius = ball.getRadius();
	int n = brick_list.size();
	char colide_type, special_char;
	
	pos = brick_list.begin();

	while (pos != brick_list.end())
	{
		// xét va chạm với 1 viên gạch
		colide_type = pos->handleCollision(ballBound, ballRadius);
		
		// kiểm tra kiểu va chạm khác 'không có'
		if (colide_type != 'n')
		{
			// xử lý vật phẩm đặc biệt
			special_char = pos->getSpecialchar();
			if (special_char != 0)
			{
				handleSpecialBrick(special_char);
			}
			
			// kiểm tra banh xuyên phá
			if (!penetrate)
			{
				// kiểm tra kiểu va chạm và đổi hướng banh tương ứng
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
	
			// tính combo và cộng điểm
			combo++;
			score += 2 * combo;
			
			// đặt lại chuỗi ghi số diểm để in ra màn hình
			String S_score(to_string(score));
			txt_score.setString(S_score);

			// xóa viên gạch
			pos = brick_list.erase(pos);
		}
		else
		{
			++pos;
		}
	}
	
	// kiểm tra va chạm với hàng gạch chắn dưới thanh trượt
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
	// kiểm tra thời gian > 0 và người chơi đang chơi
	// nếu có thực hiện đếm giờ
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
	// xóa màn hình và vẽ lại hình nền
	window.clear();
	window.draw(sprite);
	
	// kiểm tra kiểu kết thức, in ra thông báo
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

	// tạm ngưng trò chơi trong 2s
	Time dur;
	dur = milliseconds(2000);
	sleep(dur);

	// thêm số điểm vào danh sách điểm cao và hiển thị ra màn hình
	loadHighScore();
	saveHighScore();
	displayHighScore(sprite);
	writeHighScore();

	pause = true;
	while (pause)
	{
		// kiểm tra phím Space được nhấn
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			// đặt lại trạng thái trò chơi như mới mở
			pause = false;
			start = false;
			play = false;
		}
		// kiểm tra phím ESC được nhấn
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			// đóng trò chơi
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
	// bật lớp gạch chắn
	// đặt vị trí dưới thanh trượt
	// khai báo đối tượng lưu màu gạch
	shield = true;
	Vector2f shield_pos;
	Color color;
	shield_pos.x = 0;
	shield_pos.y = pad.GetPosition().y + 50;
	
	// đặt màu xám cho gạch chắn
	color.r = 128;
	color.g = 128;
	color.b = 128;
	
	// thêm gạch vào danh sách để vẽ ra màn hình
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
	// đặt trạng thái tạm dừng game
	// in pause menu ra màn hình
	pause = true;
	window.draw(txt_togglePause);
	window.display();

	// vòng lặp đợi người dùng nhấn phím theo hướng dẫn
	while (pause)
	{
		// kiểm tra phím Space được nhấn
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			// tắt trạng thái tạm dừng game
			pause = false;
		}
		
		// kiểm tra phím 'S' được nhấn
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			// gọi phương thức lưu game
			saveGame();

			// tạo đối tượng chữ in ra màn hình thông báo game đã lưu
			Text saved("GAME SAVED", font, 60);
			saved.setPosition(txt_togglePause.getPosition());
			saved.setFillColor(Color::White);

			// ẩn pause menu và in thông báo đã lưu ra màn hình
			txt_togglePause.setFillColor(Color::Transparent);
			window.draw(txt_togglePause);
			window.draw(saved);
			window.display();
			
			// tạm dừng trong 2 giây
			Time dur;
			dur = milliseconds(2000);
			sleep(dur);

			// ẩn thông báo và hiện lại pause menu
			saved.setFillColor(Color::Transparent);
			txt_togglePause.setFillColor(Color::White);
			window.draw(txt_togglePause);
			window.draw(saved);
			window.display();
		}
		
		// kiểm tra phím ESC được nhấn
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			// tắt trạng thái tạm dừng và đóng cửa sổ game
			pause = false;
			window.close();
		}
	}
}

void BrickBreaker::saveGame()
{
	// mở file lưu game
	// khai báo vector 2 chiều số thực lưu vị trí viên gạch
	ofstream f;
	Vector2f brickPos = { 0,100 }, savePos;
	f.open("BrickBreakerData/save.txt");

	// ghi số mạng còn lại, thời gian còn lại và điểm hiện tại
	f << lives << "," << timer.asSeconds() << "," << score << endl;
	pos = brick_list.begin();
	
	// ghi lại những viên gạch còn trên màn chơi
	while (pos != brick_list.end())
	{
		// lấy vị trí của viên gạch
		savePos = pos->getPosition();

		// kiểm tra vị trí hiện tại lớn hơn vị trí ghi vào file
		if (savePos.y > brickPos.y)
		{
			// vị trí ghi xuống 1 dòng
			f << endl;
			brickPos.y = savePos.y;
			brickPos.x = 0;
		}
		else
		{
			// kiểm tra 2 viên gạch liên tiếp nhau trong danh sách cách 1 hay nhiều khoảng trắng	
			while (savePos.x > brickPos.x + 65)
			{
				// ghi khoảng trắng và dời vị trí ghi
				f << " ";
				brickPos.x += 65;
			}
			brickPos.x += 65;
		}
		
		// kiểm tra viên gạch không có vật phẩm thưởng/đặc biệt
		if (pos->getSpecialchar() == 0)
		{
			// ghi ký hiệu gạch thường
			f << "-";
		}
		else
		{
			// ghi ký hiệu vật phẩm thưởng/đặc biệt
			f << pos->getSpecialchar();
		}

		// trỏ tới viên gạch tiếp theo
		++pos;
	}

	// đóng file
	f.close();
}

void BrickBreaker::loadGame()
{
	// mở file lưu game
	// khai báo:
	// vector 2 chiều số thực lưu vị trí viên gạch
	// ký hiệu vật phẩm đặc biệt
	// chuỗi để đọc số mạng, thời gian và điểm
	ifstream f("BrickBreakerData/save.txt");
	Vector2f pos = { 0,100 };
	char brick_kind;
	string str_read;

	// đọc dòng đầu tiên chứa số mạng, thời gian và điểm
	// chuyển đổi kiểu dữ liệu và lưu vào thành phần tương ứng
	getline(f, str_read, ',');
	lives = stoi(str_read);
	getline(f, str_read, ',');
	timer = seconds(stof(str_read));
	getline(f, str_read, '\n');
	score = stoi(str_read);
	timer.asMilliseconds();

	// đọc các viên gạch và nạp vào game
	while (true)
	{
		// đọc 1 ký tự và kiểm tra hết file
		f.get(brick_kind);
		if (f.eof())
		{
			break;
		}

		// kiểm tra đọc được ký tự khác khoảng trắng
		if (brick_kind != ' ')
		{
			// tạo viên gạch
			Brick brick(pos);
			
			// kiểm tra viên gạch chứa vật phẩm thưởng/đặc biệt
			if (brick_kind != '-')
			{
				// đặt ký hiệu vật phẩm
				brick.setSpecial(brick_kind);
			}

			// thêm viên gạch vào danh sách
			brick_list.push_back(brick);
		}

		// dời vị trí
		// kiểm tra đọc được ký tự xuống dòng
		pos.x += 65;
		if (brick_kind == '\n')
		{
			// dời vị trí đọc viên gạch xuống dòng
			pos.x = 0;
			pos.y += 30;
		}
	}
	
	// tạo chuỗi ghi lại số mạng, thời gian và điểm
	String S_lives(to_string(lives)), S_score(to_string(score));
	String S_timer_min(to_string(int(timer.asSeconds() / 60))), S_timer_sec(to_string(int(timer.asSeconds()) % 60));

	// gán các chuỗi vào đối tượng chữ in ra màn hình tương ứng
	txt_lives.setString(S_lives);
	txt_score.setString(S_score);
	txt_timer_min.setString(S_timer_min);
	txt_timer_sec.setString(S_timer_sec);
	
	// đóng file
	f.close();
}

void BrickBreaker::startMenu()
{
	// kiểm tra người dùng đã vào chơi
	if (!play)
	{
		// tải hình nền start menu vào game
		Texture background;
		background.loadFromFile("BrickBreakerData/image/1.jpg");
		
		// đặt vị trí, kiểu chữ in đậm cho hướng dẫn vào chơi trên màn hình
		Vector2f position = start_guide.getPosition();
		position.x -= 75;
		Text begin_guide("PRESS ENTER TO START A NEW GAME\nPRESS L TO LOAD LAST SAVE GAME\nPRESS ESC TO QUIT", font, 70);
		begin_guide.setPosition(position);
		begin_guide.setStyle(Text::Bold);

		// vẽ hình nền và hướng dẫn ra màn hình
		window.draw(Sprite(background));
		window.draw(begin_guide);
		window.display();

		// đợi người dùng nhấn phím theo hướng dẫn
		while (true)
		{
			// kiểm tra phím Enter được nhấn
			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				// khai báo biến lưu level của trò chơi
				int level;
				
				// chọn ngẫu nhiên 1 trong 6 level mẫu
				for (int i = 0; i < rand() % 6 + 1; i++)
				{
					level = rand() % 6 + 1;
				}

				// nạp level đó vào game
				loadLevel(level);
				
				// đặt trạng thái bắt đầu chơi
				play = true;

				// thoát vòng lặp
				break;
			}
			
			// kiểm tra phím 'L' được nhấn
			if (Keyboard::isKeyPressed(Keyboard::L))
			{
				// đặt trạng thái bắt đầu chơi
				play = true;
				
				// tải level đã lưu vào game
				loadGame();
				
				// thoát vòng lặp
				break;
			}
			
			// kiểm tra phím Escape được nhấn
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				// thoát game
				exit(0);
			}
		}
	}

}

void BrickBreaker::saveHighScore()
{
	// thêm số điểm mới vào danh sách
	highScore.push_back(score);
	
	// sắp xếp lại danh sách theo thứ tự giảm dần
	highScore.sort(greater<int>());

	// loại bỏ những số điểm nằm ngoài top 5
	while (highScore.size() > 5)
	{
		highScore.pop_back();
	}
}

void BrickBreaker::writeHighScore()
{
	// mở file lưu danh sách điểm cao
	ofstream scoreFile("BrickBreakerData/score.txt");
	
	// tạo iterator tới từng phần tử của danh sách
	list<int>::iterator pos = highScore.begin();

	// ghi số điểm trong danh sách vào file
	while (pos != highScore.end())
	{
		scoreFile << *pos;

		++pos;

		if (pos != highScore.end())
		{
			scoreFile << ",";
		}
	}
	
	// đóng file
	scoreFile.close();
}

void BrickBreaker::loadHighScore()
{
	// xóa danh sách điểm cao cũ
	highScore.clear();

	// mở file lưu danh sách điểm cao, nếu không mở được thì thoát
	ifstream scoreFile("BrickBreakerData/score.txt");
	if (!scoreFile.is_open())
	{
		return;
	}
	
	// tạo chuỗi lưu ký tự đọc từ file
	string s;

	if (!scoreFile.is_open())
	{
		return;
	}

	// kiểm tra chưa đọc tới cuối file
	while (!scoreFile.eof())
	{
		// đọc chuỗi ghi số điểm ngăn cách bởi dấu ','
		getline(scoreFile, s, ',');
		
		// kiểm tra đọc được chuỗi khác rỗng
		if (!s.empty())
		{
			// ghio số điểm vào danh sách
			highScore.push_back(stoi(s));
		}
		
	}
	
	// đóng file
	scoreFile.close();
}

void BrickBreaker::displayHighScore(Sprite sprite)
{
	// tạo tiêu đề danh sách điểm cao và đặt vị trí
	Text highScoreTxt("HIGH SCORE", font, 80), scoreText;
	Vector2f draw_pos = txt_timer_min.getPosition();
	
	// khai báo:
	// mảng chứa số điểm mới thêm để tìm kiếm
	// chuỗi ghi lại số điểm
	// iterator tới phần tử trong danh sách điểm cao
	int added[] = { score };
	String strScore;
	list<int>::iterator pos = highScore.begin(), new_added;
	
	// chỉnh lại vị trí vẽ
	draw_pos.x -= 50;

	// đặt cỡ chữ và font chữ cho điểm số
	scoreText.setCharacterSize(60);
	scoreText.setFont(numeric_font);
	
	// đặt vị trí, kiểu in đậm và màu xanh cho tiêu đề danh sách điểm cao
	highScoreTxt.setPosition(draw_pos);
	highScoreTxt.setStyle(Text::Bold);
	highScoreTxt.setFillColor(Color::Blue);

	// chỉnh lại vị trí vẽ
	draw_pos.x += 50;
	draw_pos.y += 100;
	
	// xóa màn hình
	// vẽ hình nền và tiêu đề danh sách điểm cao
	window.clear();
	window.draw(sprite);
	window.draw(highScoreTxt);

	// tìm vị trí số điểm mới được thêm vào
	new_added = find_end(highScore.begin(), highScore.end(), added, added + 1);
	
	// kiểm tra đã chưa tới cuối danh sách điểm cao
	while (pos != highScore.end())
	{
		// ghi số điểm trong danh sách vào chuỗi in ra màn hình
		strScore = to_string(*pos);

		scoreText.setString(strScore);
		scoreText.setPosition(draw_pos);
		
		// kiễm tra số điểm trùng với điểm mới thêm vào
		if (pos == new_added)
		{
			// đặt màu xanh lơ và in đậm số điểm
			scoreText.setFillColor(Color::Cyan);
			scoreText.setStyle(Text::Bold);
		}

		// in số điểm ra màn hình
		// dời vị trí in, chuyển sang điểm số tiếp theo trong danh sách
		window.draw(scoreText);
		draw_pos.y += 100;
		++pos;
	}

	// dời vị trí xuống góc dưới bảng điểm cao
	// in hướng dẫn nhấn phím
	draw_pos.x -= 100;
	continue_guide.setPosition(draw_pos);
	window.draw(continue_guide);

	// hiển thị ra màn hình
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