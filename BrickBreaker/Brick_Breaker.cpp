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

	play = true;
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
	pad_speed = 7;
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

	start_guide.setCharacterSize(60);
	start_guide.setFont(font);
	start_guide.setString("PRESS SPACE TO START\n\tPRESS P TO PAUSE\n\tPRESS ESC TO QUIT");
	start_guide.setPosition(wWidth / 2 - 125, wHeight / 2 - 40);

	colon.setCharacterSize(60);
	colon.setFont(numeric_font);
	colon.setString(":");
	colon.setPosition(wWidth / 2 + 20, 15);
	colon.setStyle(Text::Bold);
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
		// đặt lại combo và tăng tốc banh
		combo = 0;
		ball.Rebound_IncreaseSpeed();
	}
	if (ball.getPosition().intersects(lowerEdge))
	{
		// đặt lại vị trí banh và thanh trượt
		resetBallPad();

		// trừ 1 mạng
		--lives;

		// hủy hết hiệu ứng thưởng nếu có
		penetrate = false;
		ball.setFillColor(Color::White);
		ball.setRadius(10);
		pad_speed = 7;
		pad.setSpeed(pad_speed);
		padLength = 125;
		pad.setLength(padLength);

		// đặt lại combo
		combo = 0;
		
		// cập nhật chuỗi ghi số mạng còn lại
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
	if (!play)
	{
		return;
	}
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

			// kiểm tra combo là hệ số của 10
			if (combo % 5 == 0)
			{
				// điểm thêm vào được nhân với combo/2 (lấy phần nguyên)
				score += (2 * combo) * (combo / 2);
			}
			else
			{
				score += 2 * combo;
			}
			
			// đặt lại chuỗi ghi số diểm để in ra màn hình
			String S_score(to_string(score));
			txt_score.setString(S_score);

			// xóa viên gạch
			pos = brick_list.erase(pos);

			restoreBrick();
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
	if (!play)
	{
		return;
	}

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

	// Hiện menu với tùy chọn chơi lại hoặc thoát
	// tạo và cài đặt thuộc tính cho 2 chuỗi tượng trưng cho 2 tùy chọn
	Text playAgainTxt("PLAY AGAIN", font, 70), ExitTxt("EXIT", font, 70);
	Vector2f drawPos = InitializePadPos;
	drawPos.y -= 75;

	playAgainTxt.setPosition(drawPos);
	drawPos.y += 75;
	ExitTxt.setPosition(drawPos);

	// Lấy phạm vi của 2 chuỗi
	FloatRect playAgainTxtBound = playAgainTxt.getGlobalBounds(), ExitTxtBound = ExitTxt.getGlobalBounds();

	// Vẽ ra màn hình
	window.draw(playAgainTxt);
	window.draw(ExitTxt);
	window.display();

	// Tạm dừng vẽ để chờ người dùng click chuột vào tùy chọn mong muốn
	pause = true;
	while (pause)
	{
		// kiểm tra chuột trái được nhấn
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			// Tạo vector lưu vị trí của con trỏ chuột
			Vector2i int_mouse_pos = inGameMouse.getPosition(window);
			Vector2f mousePos(float(int_mouse_pos.x), float(int_mouse_pos.y));

			// kiểm tra trỏ chuột được nhấn trong phạm vi của tùy chọn chơi lại
			if (playAgainTxtBound.contains(mousePos))
			{
				// đặt lại trạng thái trò chơi từ đầu
				pause = false;
				start = false;
				play = false;
			}
			else
			{
				// kiểm tra trỏ chuột được nhấn trong phạm vi của tùy chọn chơi lại
				if (ExitTxtBound.contains(mousePos))
				{
					// đóng trò chơi
					pause = false;
					window.close();
				}
			}
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
	// tạo 2 chuỗi ứng với 3 tùy chọn tiếp tục, lưu game và thoát
	Text continueTxt("CONTINUE", font, 70), SaveTxt("SAVE GAME", font, 70), ExitTxt("Exit", font, 70);

	// đặt vị trí cho các tùy chọn
	Vector2f drawPos = start_guide.getPosition();
	drawPos.x += 100;

	continueTxt.setPosition(drawPos);
	drawPos.y += 100;

	SaveTxt.setPosition(drawPos);
	drawPos.y += 100;

	ExitTxt.setPosition(drawPos);

	// lấy phạm vi của các chuỗi
	FloatRect conTxtBound = continueTxt.getGlobalBounds(), SavTxtBound = SaveTxt.getGlobalBounds(), ExTxtBound = ExitTxt.getGlobalBounds();

	// đặt trạng thái tạm dừng game
	// in pause menu ra màn hình
	pause = true;
	window.draw(continueTxt);
	window.draw(SaveTxt);
	window.draw(ExitTxt);
	window.display();

	// vòng lặp đợi người dùng click chuột vào tùy chọn mong muốn
	while (pause)
	{
		// kiểm tra click chuột trái
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			// tạo vector lưu vị trí con trỏ chuột lúc click chuột trái
			Vector2i int_mouse_pos = inGameMouse.getPosition(window);
			Vector2f mousePos(float(int_mouse_pos.x), float(int_mouse_pos.y));

			// kiểm tra vị trí trỏ chuột trong phạm vi tùy chọn tiếp tục
			if (conTxtBound.contains(mousePos))
			{
				// tắt trạng thái tạm dừng game
				pause = false;
			}
			else
			{
				// kiểm tra vị trí trỏ chuột trong phạm vi tùy chọn lưu game
				if (SavTxtBound.contains(mousePos))
				{
					// gọi phương thức lưu game
					saveGame();

					// tạo đối tượng chữ in ra màn hình thông báo game đã lưu
					Text saved("GAME SAVED", font, 70);
					saved.setPosition(SaveTxt.getPosition());
					saved.setFillColor(Color::White);

					// ẩn pause menu và in thông báo đã lưu ra màn hình
					window.draw(saved);
					window.display();

					// tạm dừng trong 2 giây
					Time dur;
					dur = milliseconds(2000);
					sleep(dur);

					// ẩn thông báo và hiện lại pause menu
					saved.setFillColor(Color::Transparent);
					window.draw(saved);
					window.display();
				}
				else
				{
					// kiểm tra vị trí trỏ chuột trong phạm vi tùy chọn thoát game
					if (ExTxtBound.contains(mousePos))
					{
						// tắt trạng thái tạm dừng và đóng cửa sổ game
						pause = false;
						window.close();
					}
				}
			}
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

	if (!f.is_open())
	{
		return;
	}
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

	// đặt trạng thái bắt đầu chơi
	play = true;
}

void BrickBreaker::startMenu()
{
	// kiểm tra người dùng đã vào chơi
	if (!play)
	{
		// tải hình nền start menu vào game
		Texture background;
		background.loadFromFile("BrickBreakerData/image/1.jpg");
		Text newGame("NEW GAME", font, 70), LoadGame("LOAD GAME", font, 70), Exit("Exit", font, 70);
		
		// đặt vị trí, kiểu chữ in đậm cho hướng dẫn vào chơi trên màn hình
		Vector2f position = start_guide.getPosition();
		position.x += 100;
		position.y -= 200;
		newGame.setPosition(position);

		position.y += 100;
		LoadGame.setPosition(position);

		position.y += 100;
		Exit.setPosition(position);

		newGame.setStyle(Text::Bold);
		LoadGame.setStyle(Text::Bold);
		Exit.setStyle(Text::Bold);

		FloatRect newGamePos = newGame.getGlobalBounds(), LoadGamePos = LoadGame.getGlobalBounds(), ExitPos = Exit.getGlobalBounds();

		// vẽ hình nền và hướng dẫn ra màn hình
		window.draw(Sprite(background));
		window.draw(newGame);
		window.draw(LoadGame);
		window.draw(Exit);
		window.display();

		// đợi người dùng click chuột vào tùy chọn tương ứng
		while (true)
		{
			// kiểm tra click chuột trái
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				// tạo vector lưu vị trí con trỏ chuột
				Vector2i int_mouse_pos = inGameMouse.getPosition(window);
				Vector2f mousePos(float(int_mouse_pos.x), float(int_mouse_pos.y));

				// kiểm tra click vào tùy chọn chơi mới
				if (newGamePos.contains(mousePos))
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

					// thoát vòng lặp
					break;
				}
				else
				{
					// kiểm tra click vào tùy chọn chơi tiếp game đã lưu
					if (LoadGamePos.contains(mousePos))
					{

						// tải level đã lưu vào game
						loadGame();

						// thoát vòng lặp
						break;
					}

					// kiểm tra click vào tùy chọn thoát game
					if (ExitPos.contains(mousePos))
					{
						// thoát game
						exit(0);
					}
				}
				
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
			// ghi số điểm vào danh sách
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
		else
		{
			// số điểm được tô màu trắng và in thường
			scoreText.setFillColor(Color::White);
			scoreText.setStyle(Text::Regular);
		}

		// in số điểm ra màn hình
		// dời vị trí in, chuyển sang điểm số tiếp theo trong danh sách
		window.draw(scoreText);
		draw_pos.y += 100;
		++pos;
	}
}

int BrickBreaker::getRemainLives()
{
	return lives;
}

int BrickBreaker::getRemainBricks()
{
	return brick_list.size();
}

void BrickBreaker::restoreBrick()
{
	// kiểm tra combo khác bội số của 3
	// đúng thì trả về
	if (combo % 3 != 0)
	{
		return;
	}

	// tạo vector để dò vị trí trống trên màn chơi
	Vector2f brick_pos = { 0,100 };

	// đặt iterator về đầu danh sách viên gạch trên màn chơi
	pos = brick_list.begin();

	// kiểm tra chưa duyêt tới cuối danh sách
	while (pos != brick_list.end())
	{
		// so sánh vị trí viên gạch khác vị trí đang duyệt
		if (brick_pos != pos->getPosition())
		{
			// tạo viên gạch để phục hồi
			Brick restore_brick(brick_pos);

			// chọn ngẫu nhiên gạch đặc biệt hay gạch thường
			if (rand() % 2 == 1)
			{
				// chọn ngẫu nhiên vật phẩm đặc biệt
				restore_brick.setSpecial(specialList[rand() % specialList.length()]);
			}

			// thêm vào danh sách viên gạch
			brick_list.insert(pos, restore_brick);

			break;
		}
		
		// dời vị trí duyệt
		brick_pos.x += 65;
		if (brick_pos.x >= 1024)
		{
			brick_pos.x = 0;
			brick_pos.y += 30;
		}

		++pos;
	}
}
