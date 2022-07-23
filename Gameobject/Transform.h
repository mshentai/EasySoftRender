#pragma once
#include "Component.h"
#include "../Transfrom/Vector3.h"
#include "../Transfrom/Quaternion.h"
class Float4x4;
class Transform :
	public Component
{
	//member variables
private:
	Vector3 m_Position;
	Vector3 m_RVec;
	Vector3 m_UVec;
	Vector3 m_Fvec;


	//member functions
public:
	explicit Transform(GameObject&go) : Component(go), m_Position(), m_RVec(Vector3::RIGHT), m_UVec(Vector3::UP), m_Fvec(Vector3::FORWARD) {}
	explicit Transform(GameObject*goPtr) : Component(goPtr), m_Position(), m_RVec(Vector3::RIGHT), m_UVec(Vector3::UP), m_Fvec(Vector3::FORWARD) {}
	explicit Transform() : m_Position(), m_RVec(Vector3::RIGHT), m_UVec(Vector3::UP), m_Fvec(Vector3::FORWARD){}

	const Vector3& GetPosition() const { return m_Position; }
	//const Quaternion & GetQuaternion() const { return m_Rotation; }
	void SetPosition(const Vector3 & newPos) { m_Position = newPos; }
	void SetRotation(const Quaternion & newRot);

	Float4x4 ObjectToWorld() const;
	Float4x4 WorldToObject() const;

	const Vector3& GetRVector() const { return m_RVec; }
	const Vector3& GetUVector() const { return m_UVec; }
	const Vector3& GetFVector() const { return m_Fvec; }

	void SetRotation(const Vector3 & rVec, const Vector3 & uVec);
	void SetRotation(float arcX, float arcY, float arcZ);

	void Rotate(float arcX, float arcY);

	void MoveTo(const Vector3& pos);
	void MoveTo(float x, float y, float z);
	void Move(const Vector3& dir);
};

