#include "Transform.h"


inline const Float4x4 & Transform::ObjectToWorld() const
{
	return objectToWorldMatrix;
}

inline const Float4x4 & Transform::WorldToObject() const
{
	return worldToObjectMatrix;
}

void Transform::MoveTo(const Vector3 & pos)
{
	worldToObjectMatrix.SetValue(3, 0, pos[0]);
	worldToObjectMatrix.SetValue(3, 1, pos[1]);
	worldToObjectMatrix.SetValue(3, 2, pos[2]);
	objectToWorldMatrix.SetValue(3, 0, -pos[0]);
	objectToWorldMatrix.SetValue(3, 1, -pos[1]);
	objectToWorldMatrix.SetValue(3, 2, -pos[2]);
	position = pos;
}

void Transform::Move(const Vector3 & vec)
{
	worldToObjectMatrix.AddValue(3, 0, vec[0]);
	worldToObjectMatrix.AddValue(3, 1, vec[1]);
	worldToObjectMatrix.AddValue(3, 2, vec[2]);
	objectToWorldMatrix.AddValue(3, 0, -vec[0]);
	objectToWorldMatrix.AddValue(3, 1, -vec[1]);
	objectToWorldMatrix.AddValue(3, 2, -vec[2]);
	position += vec;
}

void Transform::RotateTo(const Vector3 & rot)
{
	Float4x4 mat=
	rotation = rot;
}

void Transform::Rotate(const Vector3 & degree)
{

}

Transform::Transform(Vector3 pos, Vector3 rot) : position(pos), rotation(rot)
{
	
}
