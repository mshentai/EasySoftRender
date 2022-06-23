#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <utility>
#include <assert.h>
#include <memory>
#ifdef _DEBUG
#pragma comment(lib,"../Debug/Transfrom.lib")
#pragma comment(lib,"../Debug/RenderSystem.lib")
#else
#pragma comment(lib,"../Release/Transfrom.lib")
#pragma comment(lib,"../Release/RenderSystem.lib")
#endif


constexpr auto InitCount = 10;

