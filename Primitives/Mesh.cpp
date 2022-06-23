#include "Mesh.h"
#include "Reference.h"

Mesh* Mesh::Cube = nullptr;
Mesh* Mesh::triangle = nullptr;

Mesh* Mesh::CubeStaticStructor()
{
	Cube = new Mesh();
	Cube->m_Vertexes = std::vector<Vector3>
	{
			Vector3(0.5f, 0.5f, 0.5f),//0
			Vector3(0.5f, 0.5f, -0.5f),//1
			Vector3(-0.5f, 0.5f, -0.5f),//2
			Vector3(-0.5f, 0.5f, 0.5f),//3
			Vector3(0.5f, -0.5f, 0.5f),//4
			Vector3(0.5f, -0.5f, -0.5f),//5
			Vector3(-0.5f, -0.5f, -0.5f),//6
			Vector3(-0.5f, -0.5f, 0.5f)//7
	};
	Cube->m_Normals = std::vector<Vector3>
	{
			Vector3(0, 1, 0),//0
			Vector3(0, 0, 1),//1
			Vector3(1, 0, 0),//2
			Vector3(0, -1, 0),//3
			Vector3(0, 0, -1),//4
			Vector3(-1, 0, 0),//5
	};
	std::vector<int> vexID{ 0,1,2,2,3,0,4,7,5,5,7,6,1,5,6,1,6,2,0,3,4,3,7,4,2,6,7,3,2,7,1,0,5,0,4,5 };
	std::vector<int> norID{ 0,0,0,0,0,0,3,3,3,3,3,3,4,4,4,4,4,4,1,1,1,1,1,1,5,5,5,5,5,5,2,2,2,2,2,2 };
	float texMaps[]{
		1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,
		0.0f,1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,0.0f,
		1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,0.0f,0.0f,0.0f,1.0f,
		0.0f,1.0f,1.0f,1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,
		1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,0.0f,0.0f,
		0.0f,1.0f,1.0f,1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,0.0f,0.0f,0.0f
	};
	Cube->CreateTriangle(vexID, norID, texMaps);
	return Cube;
}

Mesh* Mesh::TriangleStaticStructor()
{
	triangle = new Mesh();
	triangle->m_Vertexes = std::vector<Vector3>
	{
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 0.0f, 0.0f),
		Vector3(0.0f, 0.0f, 1.0f)
	};
	triangle->m_Normals = std::vector<Vector3>
	{
		Vector3(0, 1, 0)
	};
	std::vector<int> vexID{ 0,1,2 };
	std::vector<int> norID{ 0,0,0 };
	triangle->CreateTriangle(vexID, norID);
	return triangle;
}

void Mesh::CreateTriangle(int vex0ID, int vex1ID, int vex2ID)
{
	m_Triangles.emplace_back(
		&m_Vertexes[vex0ID],
		&m_Vertexes[vex1ID],
		&m_Vertexes[vex2ID],
		&m_Normals[vex0ID],
		&m_Normals[vex1ID],
		&m_Normals[vex2ID]
	);
}

void Mesh::CreateTriangle(int vex0ID, int vex1ID, int vex2ID, int nor0ID, int nor1ID, int nor2ID)
{
	m_Triangles.emplace_back(
		&m_Vertexes[vex0ID],
		&m_Vertexes[vex1ID],
		&m_Vertexes[vex2ID],
		&m_Normals[nor0ID],
		&m_Normals[nor1ID],
		&m_Normals[nor2ID]
	);
}

void Mesh::CreateTriangle(int vex0ID, int vex1ID, int vex2ID, int nor0ID, int nor1ID, int nor2ID, float* texMap)
{
	m_Triangles.emplace_back
	(
		&m_Vertexes[vex0ID],
		&m_Vertexes[vex1ID],
		&m_Vertexes[vex2ID],
		&m_Normals[nor0ID],
		&m_Normals[nor1ID],
		&m_Normals[nor2ID],
		texMap
	);
}

void Mesh::CreateTriangle(std::vector<int>& vexID)
{
	int len = vexID.size();
	for (int i = 0; i < len; i += 3)
	{
		CreateTriangle(vexID[i], vexID[i + 1], vexID[i + 2]);
	}
}

void Mesh::CreateTriangle(std::vector<int>& vexID, std::vector<int>& norID)
{
	int len = vexID.size();
	for (int i = 0; i < len; i += 3)
	{
		CreateTriangle(vexID[i], vexID[i + 1], vexID[i + 2], norID[i], norID[i + 1], norID[i + 2]);
	}
}

void Mesh::CreateTriangle(std::vector<int>& vexID, std::vector<int>& norID, float* texMap)
{
	int len = vexID.size();
	for (int i = 0; i < len; i += 3)
	{
		CreateTriangle(vexID[i], vexID[i + 1], vexID[i + 2], norID[i], norID[i + 1], norID[i + 2], (texMap + i * 2));
	}
}

Mesh * Mesh::GetCubeMesh()
{
	if (!Cube) Cube = CubeStaticStructor();
	return Cube;
}

Mesh * Mesh::GetTriangleMesh()
{
	if (!triangle) triangle = TriangleStaticStructor();
	return triangle;
}

const std::vector<Triangle> & Mesh::GetTriangles() const
{
	return m_Triangles;
}
