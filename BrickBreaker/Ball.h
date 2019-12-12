#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

const float BALL_MAX_SPEED = 7.0f;

class Ball:public CircleShape
{
private:
	Vector2f position;
	float dx = 0;
	float dy = 0;
	float speed = 1.1f;
public:
	// Game Pong & BrickBreaker
	// Phương thức lấy vị trí trái banh
	FloatRect getPosition();
	
	// Phương thức khởi tạo mặc định
	Ball();
	
	// Phương thức hủy mặc định
	~Ball();
	
	// Game Pong
	// Phương thức khởi tạo truyền vào tham số
	// đầu vào lần lượt là tọa độ x và y của trái banh
	Ball(float, float);
	
	// Game Pong & Brick Breaker
	// Phương thức đổi hướng đi theo phương dọc của trái banh
	// Kết quả là hướng đi theo phương dọc của trái banh được thay đổi
	void ReboundTopOrBot();
	
	// Game Pong
	// Phương thức đổi hướng đi của trái banh khi chạm thanh trượt
	void ReboundPaddle();
	
	// Game Brick Breaker
	// Phương thức đổi hướng đi theo phương ngang của trái banh
	// Kết quả là hướng đi theo phương ngang của trái banh được thay đổi
	void ReboundEdge();
	
	// Game Brick Breaker
	// Phương thức đổi hướng đi và tăng tốc trái banh
	// Kết quả là vận tốc trái banh được thay đổi, nhưng vẫn có tốc độ trong giới hạn
	void Rebound_IncreaseSpeed();
	
	// Game Pong & Brick Breaker
	// Phương thức cập nhật vị trí mới của trái banh
	// Kết quả là vị trí của trái banh được thay đổi
	void update();
	
	// Game Pong
	// Phương thức đưa trái banh về lại vị trí trung tâm màn hình
	void ReturnCenter(int);
	
	// Game Pong & Brick Breaker
	// Phương thức lấy hình dạng trái banh
	CircleShape getShape();
	
	// Game Brick Breaker
	// Phương thức đặt vị trí trái banh
	// đầu vào:
	// X: hoành độ của trái banh
	// Y: tung độ của trái banh
	void SetPosition(float X,float Y);
	
	// Game Brick Breaker
	// Phương thức đặt lại vị trí và bán kính của trái banh
	// đầu vào là vector 2 chiều lưu vị trí ban đầu của trái banh
	// Kết quả là các thuộc tính vị trí, bán kính được đặt lại như mới bắt đầu
	void setAttributes(Vector2f);
	
	// Game Pong
	// Phương thức đặt tốc độ cho trái banh
	// NewSpeed: tốc độ mới của trái banh
	void SetSpeed(int NewSpeed);
};

