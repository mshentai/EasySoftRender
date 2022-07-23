#pragma once
class Vector3;
class __declspec(dllexport) Triangle
{
	const Vector3 * m_Vertexes[3];
	const Vector3 * m_Normals[3];
	float m_TexMap[6];

public:
	explicit Triangle
	(
		const Vector3 * vert0,
		const Vector3 * vert1,
		const Vector3 * vert2,
		const Vector3 * norm0,
		const Vector3 * norm1,
		const Vector3 * norm2,
		const float texMaps[6]
	):
		m_Vertexes{vert0,vert1,vert2},
		m_Normals{norm0,norm1,norm2},
		m_TexMap{texMaps[0],texMaps[1], texMaps[2], texMaps[3], texMaps[4], texMaps[5]}
	{}
	explicit Triangle
	(
		const Vector3* vert0,
		const Vector3* vert1,
		const Vector3* vert2,
		const Vector3* norm0,
		const Vector3* norm1,
		const Vector3* norm2
	) :
		m_Vertexes{ vert0,vert1,vert2 },
		m_Normals{ norm0,norm1,norm2 },
		m_TexMap{ 0.0f,0.0f, 0.0f, 0.0f, 0.0f, 0.0f }
	{}

	explicit Triangle(const Triangle & other):
		m_Vertexes{other.m_Vertexes[0],other.m_Vertexes[1],other.m_Vertexes[2]},
		m_Normals{other.m_Normals[0],other.m_Normals[1],other.m_Normals[2]},
		m_TexMap{other.m_TexMap[0],other.m_TexMap[1], other.m_TexMap[2], other.m_TexMap[3], other.m_TexMap[4], other.m_TexMap[5]}
	{}
	
	const Vector3 * const * const GetVertexes() const;
	const Vector3 * const * const GetNormal() const;
	const float* const GetTexMaps() const;

};

