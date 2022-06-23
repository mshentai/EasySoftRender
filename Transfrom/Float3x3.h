#pragma once
#include "Vector3.h"
class __declspec(dllexport) Float3x3
{
private:
	float mat[3][3];
public:
	Float3x3() : mat{ {1,0,0},{0,1,0},{0,0,1} } {}
	Float3x3(const float m[3][3]) :
		mat{{m[0][0],m[0][1],m[0][2]},
			{m[1][0],m[1][1],m[1][2]},
			{m[2][0],m[2][1],m[2][2]} } { }
	const float * operator[](int i) const
	{
		return mat[i];
	}
	Float3x3 operator*(const Float3x3& rhs) const;

public:
	static Float3x3 GetXMatrix(float arc);
	static Float3x3 GetYMatrix(float arc);
	static Float3x3 GetZMatrix(float arc);
};

__declspec(dllexport) Vector3 operator*(const Vector3 &vec, const Float3x3 & f3x3);

