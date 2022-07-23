#include "Vector3.h"
#include "Float4x4.h"

const Vector3 Vector3::UP = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::FORWARD = Vector3(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::RIGHT = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::ZERO;

inline Vector3::Vector3(float x, float y, float z) noexcept : v3{ x,y,z }
{
}

inline Vector3::Vector3() noexcept : v3{ 0,0,0 }
{
}

inline Vector3 & Vector3::operator+=(const Vector3 & rhs)
{
	this->v3[0] += rhs[0];
	this->v3[1] += rhs[1];
	this->v3[2] += rhs[2];
	this->v3[3] += rhs[3];
	return *this;
}

inline Vector3 & Vector3::operator=(const Vector3 & rhs)
{
	this->v3[0] = rhs[0];
	this->v3[1] = rhs[1];
	this->v3[2] = rhs[2];
	this->v3[3] = rhs[3];
	return *this;
}

Vector3 Vector3::Normalize() const
{
	float v0 = v3[0];
	float v1 = v3[1];
	float v2 = v3[2];
	float mod = 1 / sqrtf(v0 * v0 + v1 * v1 + v2 * v2);
	return Vector3(v0*mod, v1*mod, v2*mod);
}

float Vector3::Dot(const Vector3 & rhs) const
{
	return (*this) * rhs;
}

Vector3 Vector3::Cross(const Vector3 & rhs) const
{
	float x = (*this)[1] * rhs[2] - (*this)[2] * rhs[1];
	float y = (*this)[2] * rhs[0] - (*this)[0] * rhs[2];
	float z = (*this)[0] * rhs[1] - (*this)[1] * rhs[0];
	return Vector3(x, y, z);
}

float Vector3::Norm() const
{
	return sqrtf(v3[0] * v3[0] + v3[1] * v3[1] + v3[2] * v3[2]);
}


inline Vector3::Vector3(const Vector3 & rhs) noexcept : v3{ rhs[0],rhs[1],rhs[2],rhs[3] }
{
}

inline Vector3 operator+(const Vector3&lhs, const Vector3&rhs)
{
	return Vector3(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]);
}

inline Vector3 operator-(const Vector3&lhs, const Vector3&rhs)
{
	return Vector3(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]);
}

inline float operator*(const Vector3&lhs, const Vector3&rhs)
{
	return lhs[0]*rhs[0] + lhs[1] *rhs[1] + lhs[2] *rhs[2];
}

Vector3 operator*(const Vector3 & vec, const float n)
{
	return Vector3(vec[0] * n, vec[1] * n, vec[2] * n);
}

Vector3 operator/(const Vector3& vec, const float n)
{
	float r = 1.0f / n;
	return vec * r;
}

inline bool operator==(const Vector3&lhs, const Vector3&rhs)
{
	return (fabsf(lhs[0] - rhs[0]) < ACC) && (fabsf(lhs[1] - rhs[1]) < ACC) && (fabsf(lhs[2] - rhs[2]) < ACC);
}

Vector3 Vector3::OX(const Vector3 rhs) const
{
	return Vector3(v3[0] * rhs[0], v3[1] * rhs[1], v3[2] * rhs[2]);
}