#pragma once
#include "Gameobject.h"
#include "Transform.h"
class ComponentManager
{
	//----±äÁ¿-----//
	
private:
	static ComponentManager* m_Instance;
	std::vector<int> m_Mapping;
	std::vector<Transform> m_Transforms;
	
	

	//----º¯Êý-----//
public:
	static ComponentManager& Instance() { return *m_Instance; }

private:
	explicit ComponentManager() : 
		m_Transforms(InitCount),
		m_Mapping(InitCount)
	{
		for (int i = 0; i < InitCount; ++i)
		{
			m_Mapping[i] = i;
		}
	}

};

