#include "Triangle.h"

const Vector3 * const * const Triangle::GetVertexes() const
{
	return m_Vertexes;
}

const Vector3 * const * const Triangle::GetNormal() const
{
	return m_Normals;
}

const float* const Triangle::GetTexMaps() const
{
	return m_TexMap;
}


