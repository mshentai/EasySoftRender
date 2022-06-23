#pragma once
#include "Reference.h"
extern int GetGameObjectID(const std::string& name);
class GameObject
{
	friend class GameObjectManager;
	//º¯Êý
public:
	//Constructor
	GameObject(const std::string& name) : m_Name(&name), m_IsActive(true){}
	GameObject(const GameObject& target) : m_Name(target.m_Name), m_IsActive(true) {}
	GameObject(const GameObject&& target) : m_Name(target.m_Name), m_IsActive(true) {}
	GameObject() :m_Name(&nullStr), m_IsActive(false) {}
	GameObject& operator= (GameObject & other) 
	{ 
		SetName(other.m_Name);
		m_IsActive = other.m_IsActive;
		other.SetName(&nullStr);
		other.SetActive(false);
		return *this;
	}

	//normal menber function
	int GetID() const { return GetGameObjectID(*m_Name); }
	const std::string & GetName() const { return *m_Name; }
	bool IsActive() const { return m_IsActive; }
	void SetActive(bool isActive){ m_IsActive = isActive; }
private:
	GameObject(std::string && name) = delete;
	void SetName(const std::string& name) { m_Name = &name; }
	void SetName(const std::string* namePtr) { m_Name = namePtr; }
	//±äÁ¿
private:
	const std::string* m_Name;
	bool m_IsActive;
	static std::string nullStr;
};


