#pragma once
#include "Reference.h"
class Float4x4;
class __declspec(dllexport) Vector3
{
	//向量加法
	friend __declspec(dllexport) Vector3 operator+(const Vector3&lhs, const Vector3&rhs);
	//向量减法
	friend __declspec(dllexport) Vector3 operator-(const Vector3&lhs, const Vector3&rhs);
	//向量乘法
	friend __declspec(dllexport) float operator*(const Vector3&lhs, const Vector3&rhs);
	//向量整数乘法
	friend __declspec(dllexport) Vector3 operator*(const Vector3&vec, const float n);
	//向量整数除法
	friend __declspec(dllexport) Vector3 operator/(const Vector3& vec, const float n);
	//判断向量是否相等
	friend __declspec(dllexport) bool operator==(const Vector3&lhs, const Vector3&rhs);
public:
	//----成员函数----//
	
	//三维向量构造函数，x,y,z分别对应坐标
	Vector3(float x, float y, float z) noexcept;
	//三维向量构造函数，默认为原点坐标
	Vector3() noexcept;
	//三维向量复制构造函数
	Vector3(const Vector3 & rhs) noexcept;
	//四维向量构造函数
	Vector3(float x, float y, float z, float w) noexcept : v3{x,y,z,w}{}
	
	//取向量的分量。
	float operator[](const int i) const { return v3[i]; }
	float& operator[](const int i) { return v3[i]; }
	//+=运算符重载
	Vector3& operator+=(const Vector3 & rhs);
	//复制运算符重载
	Vector3& operator=(const Vector3 & rhs);
	//归一化
	Vector3 Normalize() const;
	//点乘
	float Dot(const Vector3 & rhs) const;
	//叉乘
	Vector3 Cross(const Vector3 & rhs) const;

	//Vector3 Dot(const Float4x4& mat, bool isPositon);
	
	Vector3 operator-() const { return Vector3(-v3[0], -v3[1], -v3[2]); }

	Vector3 OX(const Vector3 rhs) const;

	float Norm() const;

	void Init()
	{
		v3[0] = 0;
		v3[1] = 0;
		v3[2] = 0;
		v3[3] = 0;
	}

	//----成员变量-----//

	static const Vector3 UP;//向上向量
	static const Vector3 RIGHT;//向右向量
	static const Vector3 FORWARD;//向前向量
	static const Vector3 ZERO;//零向量
private:
	//----成员变量----//

	float v3[4];

};


