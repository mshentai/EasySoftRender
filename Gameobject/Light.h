#pragma once
#include "Component.h"
#include "../Transfrom/Vector3.h"
class Light :
    public Component
{
    //成员属性
private:
    Vector3 m_AmbiColor;
    Vector3 m_DiffColor;
    Vector3 m_SpecColor;

    Vector3 m_LightDir;

    //成员函数
public:
    Light():m_AmbiColor(0.1f,0.1f,0.1f),m_DiffColor(1.0f,1.0f,1.0f),m_SpecColor(1.0f,1.0f,1.0f),m_LightDir(1.0f, -1.0f, 1.0f){}
    Vector3 GetLightDir() const;
};

