#pragma once
#include <vector>
#include <memory>
#include "Triangle.h"

class Vector3;
class Triangle;

class Mesh
{
private:
	std::vector<Vector3> m_Vertexes;
	std::vector<Vector3> m_Normals;
	std::vector<float> m_TextureMapping;
	std::vector<Triangle> m_Triangles;
	static Mesh * Cube;
	static Mesh * triangle;
	static Mesh * CubeStaticStructor();
	static Mesh * TriangleStaticStructor();
	void CreateTriangle(int vex0ID, int vex1ID, int vex2ID);
	void CreateTriangle(int vex0ID, int vex1ID, int vex2ID, int nor0ID, int nor1ID, int nor2ID);
	void CreateTriangle(int vex0ID, int vex1ID, int vex2ID, int nor0ID, int nor1ID, int nor2ID, float* texMap);
	void CreateTriangle(std::vector<int>& vexID);
	void CreateTriangle(std::vector<int>& vexID, std::vector<int>& norID);
	void CreateTriangle(std::vector<int>& vexID, std::vector<int>& norID, float* texMap);
public:
	static Mesh * GetCubeMesh();
	static Mesh * GetTriangleMesh();
	const std::vector<Triangle> & GetTriangles() const;
	
};




