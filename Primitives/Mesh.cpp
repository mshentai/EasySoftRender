#include "Mesh.h"
#include "Reference.h"
#include <fstream>

Mesh* Mesh::Cube = nullptr;
Mesh* Mesh::triangle = nullptr;
Mesh* Mesh::square = nullptr;

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
	float texMaps[]{
		0.0f,0.0f,1.0f,0.0f,0.0f,1.0f
	};
	triangle->CreateTriangle(vexID, norID,texMaps);
	return triangle;
}

Mesh* Mesh::SquareStaticStructor()
{
	square = new Mesh();
	square->m_Vertexes = std::vector<Vector3>
	{
			//Vector3(1.6f, 0.0f, 20.0f),//0
			//Vector3(1.6f, 0.0f, -1.0f),//1
			//Vector3(-1.6f, 0.0f, -1.0f),//2
			//Vector3(-1.6f, 0.0f, 20.0f),//3

			Vector3(1.5f, 0.0f, 1.5f),//0
			Vector3(1.5f, 0.0f, -1.5f),//1
			Vector3(-1.5f, 0.0f, -1.5f),//2
			Vector3(-1.5f, 0.0f, 1.5f),//3
	};
	square->m_Normals = std::vector<Vector3>
	{
			Vector3(0, 1, 0),//0
	};
	std::vector<int> vexID{ 0,1,2,2,3,0};
	std::vector<int> norID{ 0,0,0,0,0,0};
	float texMaps[]{
		1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f
	};
	square->CreateTriangle(vexID, norID, texMaps);
	return square;
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

Mesh* Mesh::GetSquareMesh()
{
	if (!square) square = SquareStaticStructor();
	return square;
}

const std::vector<Triangle> & Mesh::GetTriangles() const
{
	return m_Triangles;
}

#include<iostream>
#include<string>
#include<sstream>
Mesh* Mesh::LoadObjFile(const char* objPath)
{
	using namespace std;
	Mesh* mesh = new Mesh();
	ifstream in;
	in.open(objPath, ifstream::in);
	if (in.fail())
	{
		throw in;
	}
	string line;
	Vector3 minPoint = Vector3(1e9f, 1e9f, 1e9f);
	Vector3 maxPoint = Vector3(-1e9f, -1e9f, -1e9f);
	vector<float> texs;
	vector<int> vexIDs;
	vector<int> norIDs;
	vector<int> texIDs;
	while (!in.eof())
	{
		getline(in, line);
		istringstream iss(line.c_str());
		char trash;
		//vertex
		if (!line.compare(0, 2, "v "))
		{
			iss >> trash;
			Vector3 vertex;
			iss >> vertex[0];
			iss >> vertex[1];
			iss >> vertex[2];
			mesh->m_Vertexes.push_back(vertex);
			if (minPoint[0] > vertex[0])minPoint[0] = vertex[0];
			if (minPoint[1] > vertex[1])minPoint[1] = vertex[1];
			if (minPoint[2] > vertex[2])minPoint[2] = vertex[2];
			if (maxPoint[0] < vertex[0])maxPoint[0] = vertex[0];
			if (maxPoint[1] < vertex[1])maxPoint[1] = vertex[1];
			if (maxPoint[2] < vertex[2])maxPoint[2] = vertex[2];
		}
		// normal
		else if (!line.compare(0, 3, "vn "))
		{
			iss >> trash >> trash;
			Vector3 normal;
			iss >> normal[0];
			iss >> normal[1];
			iss >> normal[2];
			normal.Normalize();
			mesh->m_Normals.push_back(normal);
		}
		// texcoord
		else if (!line.compare(0, 3, "vt "))
		{
			iss >> trash >> trash;
			float x;
			float y;
			iss >> x;
			iss >> y;
			texs.push_back(x);
			texs.push_back(y);
		}
		// face
		else if (!line.compare(0, 2, "f "))
		{
			iss >> trash;
			int index[3];
			while (iss >> index[0] >> trash >> index[1] >> trash >> index[2])
			{
				vexIDs.push_back(index[0] - 1);
				texIDs.push_back(index[1] - 1);
				norIDs.push_back(index[2] - 1);
			}
		}
	}
	int size = vexIDs.size();
	int texsi = texs.size();
	float* texMap = new float[size * 2];
	for (int i = 0; i < size; ++i)
	{
		texMap[i * 2] = texs[texIDs[i] * 2];
		texMap[i * 2 + 1] = texs[texIDs[i] * 2 + 1];
	}
	mesh->CreateTriangle(vexIDs, norIDs, texMap);
	delete[] texMap;
	in.close();
	return mesh;
}




