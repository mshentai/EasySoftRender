#include "Transform.h"
#include "../Transfrom/Float4x4.h"

void Transform::SetRotation(const Quaternion & newRot)
{
	Float3x3 mat = newRot.ToFloat3x3();
	m_RVec = Vector3(mat[0][0], mat[1][0], mat[2][0]).Normalize();
	m_UVec = Vector3(mat[0][1], mat[1][1], mat[2][1]).Normalize();
	m_Fvec = Vector3(mat[0][2], mat[1][2], mat[2][2]).Normalize();
}

Float4x4 Transform::ObjectToWorld() const
{
	return WorldToObject().Inverse();
}

Float4x4 Transform::WorldToObject() const
{
	float mat[4][4];
	const Vector3 & pos = GetPosition();
	const Vector3 & rve = GetRVector();
	const Vector3 & uve = GetUVector();
	const Vector3 & fve = GetFVector();

	mat[0][0] = rve[0];
	mat[0][1] = uve[0];
	mat[0][2] = fve[0];
	mat[0][3] = 0.0f;
	mat[1][0] = rve[1];
	mat[1][1] = uve[1];
	mat[1][2] = fve[1];
	mat[1][3] = 0.0f;
	mat[2][0] = rve[2];
	mat[2][1] = uve[2];
	mat[2][2] = fve[2];
	mat[2][3] = 0.0f;
	mat[3][0] = -rve.Dot(pos);
	mat[3][1] = -uve.Dot(pos);
	mat[3][2] = -fve.Dot(pos);
	mat[3][3] = 1.0f;
	return Float4x4(mat);
}

void Transform::SetRotation(const Vector3 & rVec, const Vector3 & uVec)
{
	m_RVec = Vector3(rVec).Normalize();
	m_UVec = Vector3(uVec).Normalize();
	m_Fvec = m_RVec.Cross(m_UVec).Normalize();
}

void Transform::SetRotation(float arcX, float arcY, float arcZ)
{
	Float3x3 matX = Float3x3::GetXMatrix(arcX);
	Float3x3 matY = Float3x3::GetYMatrix(arcY);
	Float3x3 matZ = Float3x3::GetZMatrix(arcZ);
	Float3x3 mat = matX * matY * matZ;
	m_RVec = Vector3(mat[0][0], mat[1][0], mat[2][0]).Normalize();
	m_UVec = Vector3(mat[0][1], mat[1][1], mat[2][1]).Normalize();
	m_Fvec = Vector3(mat[0][2], mat[1][2], mat[2][2]).Normalize();
}

void Transform::Rotate(float arcX, float arcY)
{
	const Vector3& rve = GetRVector();
	const Vector3& uve = GetUVector();
	const Vector3& fve = GetFVector();
	float m[3][3];
	m[0][0] = rve[0];
	m[1][0] = rve[1];
	m[2][0] = rve[2];
	m[0][1] = uve[0];
	m[1][1] = uve[1];
	m[2][1] = uve[2];
	m[0][2] = fve[0];
	m[1][2] = fve[1];
	m[2][2] = fve[2];
	Float3x3 mat(m);
	if (arcX > 0.001f) mat = mat * Float3x3::GetXMatrix(arcX);
	if (arcY > 0.001f) mat = mat * Float3x3::GetYMatrix(arcY);
	m_RVec = Vector3(mat[0][0], mat[1][0], mat[2][0]).Normalize();
	m_UVec = Vector3(mat[0][1], mat[1][1], mat[2][1]).Normalize();
	m_Fvec = Vector3(mat[0][2], mat[1][2], mat[2][2]).Normalize();
}

void Transform::MoveTo(const Vector3& pos)
{
	m_Position = pos;
}

void Transform::MoveTo(float x, float y, float z)
{
	MoveTo(Vector3(x, y, z));
}

void Transform::Move(const Vector3& dir)
{
	m_Position += dir;
}

