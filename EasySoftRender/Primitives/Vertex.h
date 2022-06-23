#pragma once
#include "../Transfrom/Float4x4.h"
#include "../Transfrom/Vector3.h"
#include "Color_RGBA.h"
#pragma comment(lib,"../Debug/Transfrom.lib")
__declspec(dllexport) class Vertex
{
public:
	Vector3 position;
	Vector3 normal;
	Color_RGBA color_rgba;
};

