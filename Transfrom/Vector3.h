#pragma once
#include "Reference.h"
class __declspec(dllexport) Vector3
{
	//向量加法
	friend __declspec(dllexport) Vector3 operator+(Vector3&lhs, Vector3&rhs);
	//向量减法
	friend __declspec(dllexport) Vector3 operator-(Vector3&lhs, Vector3&rhs);
	//向量乘法
	friend __declspec(dllexport) float operator*(Vector3&lhs, Vector3&rhs);
	//判断向量是否相等
	friend __declspec(dllexport) bool operator==(Vector3&lhs, Vector3&rhs);
public:
	//----成员函数----//
	
	//三维向量构造函数，x,y,z分别对应坐标
	Vector3(float x, float y, float z) noexcept;
	//三维向量构造函数，默认为原点坐标
	Vector3() noexcept;
	//三维向量复制构造函数
	Vector3(const Vector3 & rhs) noexcept;
	//取向量的分量。
	float operator[](const int i) const;
	//复制运算符重载
	Vector3& operator+=(const Vector3 & rhs);
	

	//----成员变量-----//

	static const Vector3 UP;//向上向量
	static const Vector3 RIGHT;//向右向量
	static const Vector3 FORWARD;//向前向量
	static const Vector3 ZERO;//零向量
private:
	//----成员变量----//

	float v3[3];
	
	

};

