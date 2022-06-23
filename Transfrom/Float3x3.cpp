#include "Float3x3.h"


Vector3 operator*(const Vector3 & vec, const Float3x3 & f3x3)
{
	float x = vec[0] * f3x3[0][0] + vec[1] * f3x3[1][0] + vec[2] * f3x3[2][0];
	float y = vec[0] * f3x3[0][1] + vec[1] * f3x3[1][1] + vec[2] * f3x3[2][1];
	float z = vec[0] * f3x3[0][2] + vec[1] * f3x3[1][2] + vec[2] * f3x3[2][2];
	return Vector3(x, y, z);
}

Float3x3 Float3x3::operator*(const Float3x3& rhs) const
{
	const Float3x3& lhs = (*this);
	float mat[3][3];
	mat[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0];
	mat[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1];
	mat[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2];
	mat[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0];
	mat[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1];
	mat[1][2] = lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2] + lhs[1][2] * rhs[2][2];
	mat[2][0] = lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0] + lhs[2][2] * rhs[2][0];
	mat[2][1] = lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1] + lhs[2][2] * rhs[2][1];
	mat[2][2] = lhs[2][0] * rhs[0][2] + lhs[2][1] * rhs[1][2] + lhs[2][2] * rhs[2][2];
	return Float3x3(mat);
}



Float3x3 Float3x3::GetXMatrix(float arc)
{
	arc = -arc;
	float mat[3][3];
	mat[0][0] = 1;
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[1][0] = 0;
	mat[1][1] = cosf(arc);
	mat[1][2] = sinf(arc);
	mat[2][0] = 0;
	mat[2][1] = -sinf(arc);
	mat[2][2] = cosf(arc);
	return Float3x3(mat);
}
Float3x3 Float3x3::GetYMatrix(float arc)
{
	arc = -arc;
	float mat[3][3];
	mat[0][0] = cosf(arc);
	mat[0][1] = 0;
	mat[0][2] = -sinf(arc);
	mat[1][0] = 0;
	mat[1][1] = 1;
	mat[1][2] = 0;
	mat[2][0] = sinf(arc);
	mat[2][1] = 0;
	mat[2][2] = cosf(arc);
	return Float3x3(mat);
}
Float3x3 Float3x3::GetZMatrix(float arc)
{
	arc = -arc;
	float mat[3][3];
	mat[0][0] = cosf(arc);
	mat[0][1] = sinf(arc);
	mat[0][2] = 0;
	mat[1][0] = -sinf(arc);
	mat[1][1] = cosf(arc);
	mat[1][2] = 0;
	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = 1;
	return Float3x3(mat);
}
