#pragma once
#include "Reference.h"
#include "Gameobject.h"
class Transform;
class Component
{
	friend class ComponentManager;
	//±äÁ¿
private:
	GameObject * m_GameObject;
	Transform * m_Transform;
	bool m_IsActive;

	//º¯Êý
public:
	Component(GameObject & go, bool isActive = true) : m_GameObject(&go),m_IsActive(isActive) {}
	Component(GameObject * const goPtr, bool isActive = true) : m_GameObject(goPtr), m_IsActive(isActive) {}
	Component() : m_GameObject(nullptr), m_IsActive(false) {}
	const GameObject & GetGameObjet() const { return *m_GameObject; }
	const std::string & GetName() const { return m_GameObject->GetName(); }
	bool IsActive() const { return m_IsActive; }
	void SetActive(bool isActive) { m_IsActive = isActive; }
	void SetTransform(Transform * t);
	const Transform * GetTransform() const;
	Transform* GetTransform();
private:
	
};


