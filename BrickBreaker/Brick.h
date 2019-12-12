#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"
using namespace sf;
class Brick
{
private:
	RectangleShape brickShape;
	Vector2f position;
	char special;
public:
	Brick();
	
	// Phương thức khởi tạo viên gạch
	// Đầu vào:
	// pos: là tọa độ viên gạch trên màn hình 
	// special_char: ký tự đánh dấu vật phẩm đặc biệt
	Brick(Vector2f pos, const char special_char = 0);
	~Brick();
	
	// Phương thức đặt vật phẩm đặc biệt cho viên gạch
	// viên gạch có chứa vật phẩm đặc biệt được tô màu đỏ
	void setSpecial(char);
	
	// Phương thức đặt màu tô cho viên gạch
	// color: đối tượng của lớp Color lưu màu để xuất ra màn hình
	void setFillColor(Color);
	
	// Phương thức đặt vị trí viên gạch
	// pos: đối tượng lớp vector 2 chiều lưu vị trí muốn đặt
	void setPosition(Vector2f);
	
	// phương thức lấy hình dạng viên gạch
	// trả về đối tượng lớp RectangleShape lưu thông tin viên gạch
	// RectangleShape: lớp đối tượng lưu thông tin của 1 hình chữ nhật trên màn hình
	RectangleShape getShape();
	
	// Phương thức xử lý trái banh va chạm viên gạch
	// ballBound: đối tượng lưu mô tả kích thước và vị trí trái banh
	// ballRadius: biến kiểu float lưu bán kính trái banh
	// trả về kí tự đánh dấu viên gạch đặc biệt
	const char handleCollision(FloatRect&, float&);
	
	// Phương thức lấy ký hiệu đặc biệt của viên gạch
	char getSpecialchar();
	
	// Phương thức trả về vi trí của viên gạch
	Vector2f getPosition();
	
	// Phương thức đặt kích thước viên gạch
	// x: chiều rộng viên gạch
	// y: chiều cao viên gạch
	void setSize(float x, float y);
};

