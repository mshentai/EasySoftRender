#pragma once
#include "Gameobject.h"

class GameObjectManager
{
	//---------±äÁ¿----------//
private:
	static GameObjectManager * m_Instance;
	std::unordered_map<std::string, size_t> m_Mapping;
	std::vector<std::string> m_Names;
	std::vector<GameObject> m_GameObjects;
	int m_MaxID;
	int m_Capacity;
	
	//----------º¯Êý---------//
public:
	static GameObjectManager & Instance()
	{
		if (m_Instance == nullptr) m_Instance = new GameObjectManager();
		return *m_Instance;
	}

	GameObject& CreateInstance(const std::string& name)
	{
		if (m_Mapping.count(name)) return m_GameObjects[m_Mapping[name]];
		if (m_MaxID < m_Capacity)
		{
			m_Names[m_MaxID] = name;
			new(&(m_GameObjects[m_MaxID])) GameObject(m_Names[m_MaxID]);
		}
		else
		{
			m_Names.push_back(name);
			m_GameObjects.emplace_back(m_Names[m_MaxID]);
			++m_Capacity;
		}
		m_Mapping[name] = m_MaxID;
		return m_GameObjects[m_MaxID++];
	}

	void RemoveInstance(const std::string& name)
	{
		int id = m_Mapping[name];
		if (id < 0) return;
		m_GameObjects[id] = m_GameObjects[--m_MaxID];
		m_Names[id] = m_Names[m_MaxID];
		m_Mapping[m_Names[id]] = id;
		m_Mapping.erase(name);
	}

	int GetGameObjectID(const std::string& name) const
	{
		if (m_Mapping.count(name) > 0)
		{
			return m_Mapping.at(name);
		}
		return -1;
	}
	
	GameObject* Find(size_t id)
	{
		return id < m_MaxID ? &m_GameObjects[id] : nullptr;
	}

	GameObject* Find(const std::string& name)
	{
		return m_Mapping.count(name) ? &m_GameObjects[m_Mapping[name]]: nullptr;
	}
private:
	GameObjectManager() : 
		m_Mapping(), 
		m_GameObjects(InitCount),
		m_MaxID(0),
		m_Capacity(InitCount),
		m_Names(InitCount)
	{}
};

inline int GetGameObjectID(const std::string& name)
{
	return GameObjectManager::Instance().GetGameObjectID(name);
}
inline int GetGameObjectID(const GameObject& go)
{
	return GetGameObjectID(go.GetName());
}