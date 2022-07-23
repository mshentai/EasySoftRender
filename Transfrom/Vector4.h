#pragma once
#include "Float4x4.h"
class __declspec(dllexport) Vector4
{
	//成员变量
private:
	float v[4];

	//成员函数
public:
	Vector4(float x, float y, float z, float w) : v{x,y,z,w}{}
	Vector4(const Vector4& other) : v{other[0],other[1],other[2],other[3]}{}
	Vector4(const Vector3& v3) : v{v3[0],v3[1],v[2],1.0f} {}
	Vector4():v{0,0,0,0}{}

	float operator[](int i) const { return v[i]; }
	float& operator[](int i) { return v[i]; }

	Vector4& operator=(const Vector4& other)
	{
		v[0] = other[0];
		v[1] = other[1];
		v[2] = other[2];
		v[3] = other[3];
		return *this;
	}

	float Dot(const Vector4& rhs)
	{
		return v[0] * rhs[0] + v[1] * rhs[1] + v[2] * rhs[2] + v[3] * rhs[3];
	}

	Vector4 Dot(const Float4x4& mat)
	{
		int x = v[0] * mat[0][0] + v[1] * mat[1][0] + v[2] * mat[2][0] + v[3] * mat[3][0];
		int y = v[0] * mat[0][1] + v[1] * mat[1][1] + v[2] * mat[2][1] + v[3] * mat[3][1];
		int z = v[0] * mat[0][2] + v[1] * mat[1][2] + v[2] * mat[2][2] + v[3] * mat[3][2];
		int w = v[0] * mat[0][3] + v[1] * mat[1][3] + v[2] * mat[2][3] + v[3] * mat[3][3];
		return Vector4(x, y, z, w);
	}

	float Cross(const Vector4& rhs)
	{
		throw;
	}

	void Init()
	{
		v[0] = 0;
		v[1] = 0;
		v[2] = 0;
		v[3] = 0;
	}
	

};


