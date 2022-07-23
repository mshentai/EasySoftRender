#include "Vector3.h"

const Vector3 Vector3::UP = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::FORWARD = Vector3(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::RIGHT = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::ZERO;

Vector3::Vector3(float x, float y, float z) noexcept : v3{ x,y,z }
{
}

Vector3::Vector3() noexcept : v3{ 0,0,0 }
{
}

inline float Vector3::operator[](const int i) const
{
	return v3[i];
}

inline Vector3 & Vector3::operator+=(const Vector3 & rhs)
{
	this->v3[0] = rhs[0];
	this->v3[1] = rhs[1];
	this->v3[2] = rhs[2];
	return *this;
}

inline Vector3::Vector3(const Vector3 & rhs) noexcept : v3{ rhs[0],rhs[1],rhs[3] }
{
}

inline Vector3 operator+(Vector3 & lhs, Vector3 & rhs)
{
	return Vector3(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]);
}

inline Vector3 operator-(Vector3 & lhs, Vector3 & rhs)
{
	return Vector3(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]);
}

inline float operator*(Vector3 & lhs, Vector3 & rhs)
{
	return lhs[0]*rhs[0] + lhs[1] *rhs[1] + lhs[2] *rhs[2];
}

inline bool operator==(Vector3 & lhs, Vector3 & rhs)
{
	return (fabsf(lhs[0] - rhs[0]) < 1e-4) && (fabsf(lhs[1] - rhs[1]) < 1e-4) && (fabsf(lhs[2] - rhs[2]) < 1e-4);
}
