#pragma once
#include <memory>
class Sampler2D;

namespace Mgr
{
	std::shared_ptr<Sampler2D> CreateSampler2D(const char* bmpName);
}


