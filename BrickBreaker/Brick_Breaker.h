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

void Brick_Breaker();
const int wWidth = 1024;
const int wHeight = 768;

class BrickBreaker
{
public:
	// Phương thức khởi tạo mặc định
	BrickBreaker();
	
	// Phương thức hủy mặc định
	~BrickBreaker();
	
	// Phương thức xử lý phím được nhập
	void handleKeyPress();
	
	// Phương thức xử lý banh va chạm vào biên
	// đầu vào:
	// topEdge: hình dạng biên trên của màn hình chơi
	// leftEdge: hình dạng biên trái của màn hình chơi
	// rightEdge: hình dạng biên phải của màn hình chơi
	// lowerEdge: hình dạng biên dưới của màn hình chơi
	void handleEdgeCollision(FloatRect topEdge, FloatRect leftEdge, FloatRect rightEdge, FloatRect lowerEdge);
	
	// Phương thức vẽ các thành phần của trò chơi ra màn hình
	// sprite: đối tượng thể hiện hình ảnh từ nguồn tải lên để vẽ ra màn hình
	void draw_game(Sprite sprite);
	
	// Phương thức kiểm tra cửa sổ trò chơi có mở
	// trả về true nếu đang mở, ngươc lại thì false
	bool isOpen();
	
	// Phương thức tải màn chơi
	// level: màn chơi mẫu muốn tải lên
	void loadLevel(int level);
	
	// Phương thức xử lý va chạm giữa banh và viên gạch
	void handleBrickCollision();
	
	// Phương thức đếm giờ
	// chạy đồng hồ đếm giờ trong trò chơi
	void Countdown_timer();
	
	// Phương thức xử lý kết thức game
	// sprite: đối tượng thể hiện hình ảnh từ nguồn tải lên để vẽ ra màn hình
	void gameOverHandle(Sprite sprite);
	
	// Phương thức xử lý vật phẩm đặc biệt khi người chơi phá được viên gạch đặc biệt
	// special_char: ký tự ký hiệu vật phẩm đặc biệt cua viên gạch
	void handleSpecialBrick(char special_char);
	
	// Phương thức tạo của sổ màn chơi
	void clearWindow();
	
	// Phương thức trả về của sổ màn chơi
	RenderWindow& getWindow();
	
	// Phương thức vẽ hàng gạch chắn dưới thanh trượt
	void loadShieldBrick();
	
	// Phương thức mở menu Pause
	void togglePause();
	
	// Phương thức lưu lại màn chơi
	void saveGame();
	
	// Phương thức tải màn chơi đã lưu
	void loadGame();
	
	// Phương thức mở menu bắt đầu
	void startMenu();
	
	// Phương thức lưu danh sách điểm cao
	void saveHighScore();
	
	// Phương thức ghi danh sách điểm cao vào file
	void writeHighScore();
	
	// Phương thức tải danh sách điểm cao từ file
	void loadHighScore();
	
	// Phương thức hiện danh sách điểm cao trên màn hình
	void displayHighScore(Sprite sprite);
	
	// Phương thức lấy số mạng còn lại của người chơi
	int getRemainLives();
	
	// Phương thức lấy số lượng viên gạch còn lại
	int getRemainBricks();

	// Phương thức tạo lại 1 viên gạch khi đat được combo nhất định
	void restoreBrick();
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
	Text Lives, Score, txt_lives, txt_score, txt_timer_min, txt_timer_sec, start_guide, colon;
	Font font, numeric_font;
	list<Brick>::iterator pos, shieldPos;
	Time timer, _timer;
	Mouse inGameMouse;
	void resetBallPad();
	
};

