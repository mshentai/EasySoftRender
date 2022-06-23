#include "ObjectManager.h"
#include "../Primitives/Sampler2D.h"
#include "../Primitives/Mesh.h"
#include "../Transfrom/Vector3.h"

namespace Mgr
{
    std::shared_ptr<Sampler2D> CreateSampler2D(const char* bmpName)
    {
        Sampler2D* p = new Sampler2D(bmpName);
        p->Init();
        return std::shared_ptr<Sampler2D>(p);
    }

    std::shared_ptr<Sampler2D> CreateWhiteSampler2D()
    {
        Sampler2D* p = Sampler2D::GetWhite();
        return std::shared_ptr<Sampler2D>(p);
    }

    std::shared_ptr<Mesh> CreateMesh(const char* objPath)
    {
        Mesh* mesh = Mesh::LoadObjFile(objPath);
        return std::shared_ptr<Mesh>(mesh);
    }
}