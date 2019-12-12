#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
class cPaddle
{
private:
	Vector2f Position;
	RectangleShape PaddleShape;
	float PaddleSpeed = 2;
public:
	// Game Pong
	// Phương thức khởi tạo thanh trượt truyền vào 2 biến kiểu float
	// X: hoành độ của thanh trượt
	// Y: tung độ của thanh trượt
	cPaddle(float X, float Y);
	
	// Game Brick Breaker
	// Phương thức tạo lập thanh trượt
	// tham số đầu vào:
	// X: hoành độ của thanh trượt
	// Y: tung độ của thanh trượt
	// length: độ dài thanh trượt
	// initial_speed: tốc độ ban đầu của thanh trượt
	cPaddle(float, float, int, int);
	
	// Game Pong
	// Phương thức trả về vị trí thanh trượt
	FloatRect getPosition();
	
	// Game Brick Breaker
	// Phương thức trả về vị trí thanh trượt
	Vector2f GetPosition();
	void setPosition(Vector2f);
	
	// Game Brick Breaker
	// Phương thức trả về chiều cao của thanh trượt
	float getHeight();
	
	// Game Pong & BrickBreaker
	// Phương thức trả về hình dạng thanh trượt
	RectangleShape getShape();
	
	// Game Pong
	// Phương thức di chuyển thanh trượt hướng lên
	void moveUp();
	
	// Game Pong
	// Phương thức di chuyển thanh trượt hướng xuống
	void moveDown();
	
	// Game Brick Breaker
	// Phương thức di chuyển thanh trượt sang trái
	void moveLeft();
	
	// Game Brick Breaker
	// Phương thức di chuyển thanh trượt sang phải
	void moveRight();
	
	// Game Pong & BrickBreaker
	// Phương thức cập nhật vị trí thanh trượt
	void Update();
	
	// Game Brick Breaker
	// Phương thức đặt màu tô cho thanh trượt, truyền vào màu muốn tô
	// color: đối tượng thuộc lớp Color thể hiện màu xuất ra màn hình
	void setFillColor(const Color&);
	
	// Game Brick Breaker
	// Phương thức đặt thuộc tính của thanh trượt
	// đầu vào:
	// pos: vị trí thanh trượt
	// length: độ dài thanh trượt
	// speed: tốc độ mới của thanh trượt
	void setAttributes(Vector2f pos, int length, int initial_speed);
	
	// Game Brick Breaker
	// Phương thức đặt độ dài của thanh trượt
	// length: độ dài thanh trượt
	void setLength(float length);
	
	// Game Brick Breaker
	// Phương thức đặt tốc độ của thanh trượt
	// speed: tốc độ mới của thanh trượt
	void setSpeed(float speed);
	
	// Phương thức khởi tạo mặc định
	cPaddle();
	
	// Phương thức hủy mặc định
	~cPaddle();
};

