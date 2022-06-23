#pragma once
#include "Float3x3.h"
class __declspec(dllexport) Quaternion
{
	friend __declspec(dllexport) Quaternion operator* (const Quaternion & lhs, const Quaternion & rhs);
private:
	float q[4];

public:
	Quaternion() : q{ 1,0,1,0 } {}
	Quaternion(const Quaternion & other)
	{
		q[0] = other.q[0];
		q[1] = other.q[1];
		q[2] = other.q[2];
		q[3] = other.q[3];
	}

	Quaternion(const float v[4]) :q{ v[0],v[1],v[2],v[3] } {}

	Quaternion(float x) : q{ 1,0,1,0 } {}

	Quaternion(const float arc, const Vector3 & axis)
	{
		float c = cos(arc / 2.0f);
		float s = sin(arc / 2.0f);
		float x = s * axis[0];
		float y = s * axis[1];
		float z = s * axis[2];
		q[0] = c;
		q[1] = x;
		q[2] = y;
		q[3] = z;
	}

	Quaternion(float r, float sw1, float sw2, float sw3) : q{ r,sw1,sw2,sw3 }
	{
	}

	static Quaternion EulerToQuaternion(const Vector3 & euler)
	{
		Quaternion x(euler[0], Vector3::RIGHT);
		Quaternion y(euler[1], Vector3::UP);
		Quaternion z(euler[2], Vector3::FORWARD);
		return x * y * z;
	}

	Float3x3 ToFloat3x3() const
	{
		float w = q[0];
		float x = q[1];
		float y = q[2];
		float z = q[3];
		float mat[3][3];
		mat[0][0] = 1 - 2 * (y * y + z * z);
		mat[0][1] = 2 * x * y + 2 * w * z;
		mat[0][2] = 2 * x * z - 2 * w * y;
		mat[1][0] = 2 * x * y - 2 * w * z;
		mat[1][1] = 1 - 2 * x * x - 2 * z * z;
		mat[1][2] = 2 * y * z + 2 * w * x;
		mat[2][0] = 2 * x * z + 2 * w * y;
		mat[2][1] = 2 * y * z - 2 * w * x;
		mat[2][2] = 1 - 2 * x * x - 2 * y * y;
		return Float3x3(mat);
	}

	float operator[] (int i) const
	{
		return q[i];
	}
};

