#pragma once
typedef unsigned char byte;
class Color_RGBA
{
private:
	byte rgba[4];//颜色rgba各分量
public:
	Color_RGBA() : rgba{ 255u,255u,255u,255u }{}
	Color_RGBA(byte r, byte g, byte b, byte a) : rgba{ r,g,b,a } {}
	void SetRGB(byte r, byte g, byte b);
	void SetA(byte a);
	byte& operator[](int i);
	const byte * ToArray() const
	{
		return rgba;
	}
	
};

