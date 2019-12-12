#include "Brick_Breaker.h"
#include "Pong.h"

int main()
{
	// Khởi tạo:
	// trò chơi, các đường biên trên, dưới, trái và phải
	// hình nền cho màn hình chơi
	BrickBreaker brick_game;
	FloatRect topEdge(0, 68, wWidth, 1), leftEdge(0, 68, 1, wHeight - 68), rightEdge(wWidth - 1, 68, 1, wHeight - 68), lowerEdge(0, wHeight - 1, wWidth, 1);
	Texture	texture;
	Sprite sprite;

	// Tải hình nền màn hình chơi từ file hình
	// nếu thất bại xuất ra thông báo trên console
	if (!texture.loadFromFile("BrickBreakerData/image/3.jpg"))
	{
		std::cout << "Load Textured failed";
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, wWidth, wHeight));

	while (brick_game.isOpen())
	{
		// Gọi phương thứ vẽ ra menu khỏi đầu (nếu người dùng chưa vào chơi)
		brick_game.startMenu();
		
		// Gọi phương thức kiểm tra nhấn phím và thực hiện xử lý tương ứng với từng phím
		brick_game.handleKeyPress();
		
		// Gọi phương thức kiểm tra và xử lý trái banh va vào các biên của màn hình chơi
		brick_game.handleEdgeCollision(topEdge, leftEdge, rightEdge, lowerEdge);
		
		// Gọi phương thức kiểm tra và xử lý trái banh va vào viên gạch, áp dụng vật phẩm đặc biệt nếu có
		brick_game.handleBrickCollision();
		
		// Gọi phương thức thực hiện đếm giờ
		brick_game.Countdown_timer();
		
		// Kiểm tra điều kiện kết thúc game: hết mạng hay đã phá hết gạch
		// nếu đạt được thì gọi phương thức xử lý kết thúc game
		if (brick_game.getRemainLives() == 0 || brick_game.getRemainBricks() == 0)
		{
			brick_game.gameOverHandle(sprite);
		}
		
		// Gọi phương thức vẽ các thành phần của game ra màn hình
		brick_game.draw_game(sprite);
	}
}