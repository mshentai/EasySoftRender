#include "ObjectManager.h"
#include "../Primitives/Sampler2D.h"

namespace Mgr
{
    std::shared_ptr<Sampler2D> CreateSampler2D(const char* bmpName)
    {
        Sampler2D* p = new Sampler2D(bmpName);
        p->Init();
        return std::shared_ptr<Sampler2D>(p);
    }
}