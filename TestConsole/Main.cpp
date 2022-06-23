#include <iostream>
#include <math.h>
#include <string>
#include "../Gameobject/Transform.h"
#include "../Transfrom/Float4x4.h"
#include "../Gameobject/Camera.h"
#include "../Primitives/Mesh.h"
#include "../Gameobject/MeshRenderer.h"
#pragma comment(lib,"../Debug/Gameobject.lib")
#pragma comment(lib,"../Debug/RenderSystem.lib")

void PrintMat(const Float4x4 & mat)
{
	for (int i = 0; i < 4; ++i)
	{
		printf("%5.4f,%5.4f,%5.4f,%5.4f\n", mat[i][0], mat[i][1], mat[i][2], mat[i][3]);
	}
}

void PrintVec(const Vector3 & vec)
{
	printf("%5.4f,%5.4f,%5.4f,%5.4f\n", vec[0], vec[1], vec[2], vec[3]);
}

int main()
{
	//int * ptr = nullptr;
	//assert("指针不能为零"&&ptr != nullptr);
	Transform tran_Camera;
	tran_Camera.SetPosition(Vector3(5.0f/2.0f, 3.0f, 7.0f/2.0f));
	tran_Camera.SetRotation(Vector3(-1,1,0),Vector3(-1,-1,2));
	Camera camera;
	camera.SetTransform(&tran_Camera);
	Transform tran_Object;
	tran_Object.SetPosition(Vector3(1, 1, 1));
	tran_Object.SetRotation(Quaternion::EulerToQuaternion(Vector3(0, 0, PI / 2)));
	Mesh* mesh = Mesh::GetTriangleMesh();
	const std::vector<Triangle>& tris = mesh->GetTriangles();
	MeshRenderer render;
	render.SetMesh(mesh);
	render.SetTransform(&tran_Object);

	camera.SetFrustum(PI / 3.0f, 4.0f / 3.0f, 1.0f, 10.0f);
	camera.SetProjectMode(true);

	camera.SetViewPort(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);

	Float4x4 Hworld = render.GetTransform()->ObjectToWorld();
	Float4x4 Hview = camera.GetViewMatrix();
	Float4x4 Hproj = camera.GetProjectMatrix();
	Float4x4 Hscreen = camera.GetScreenMatrix(640.0f, 480.0f);

	std::cout << "Hworld:\n";
	PrintMat(Hworld);
	std::cout << "Hview:\n";
	PrintMat(Hview);
	std::cout << "Hproj:\n";
	PrintMat(Hproj);
	std::cout << "Hscreen:\n";
	PrintMat(Hscreen);
	std::cout << '\n';
	

	for (int i = 0; i < tris.size(); ++i)
	{
		auto v = tris[i].GetVertexes();
		//auto n = tris[i].GetNormal();
		std::cout << "Triange : " << i << '\n';
		for (int j = 0; j < 3; ++j)
		{
			std::cout << "顶点序号 : " << j << '\n';
			printf("ModelVertex :");
			Vector3 modelV = *v[j];
			PrintVec(modelV);
			std::cout << '\n';
			printf("WorldVertex : ");
			Vector3 worldV = modelV * Hworld;
			PrintVec(worldV);
			std::cout << '\n';
			Vector3 viewV = worldV * Hview;
			printf("ViewVertex : ");
			PrintVec(viewV);
			std::cout << '\n';
			Vector3 projV = viewV * Hproj;
			printf("ProjVertex : ");
			PrintVec(projV);
			std::cout << '\n';
			float x = projV[0];
			float y = projV[1];
			float z = projV[2];
			float w = 1.0f / projV[3];
			Vector3 ndcV(x * w, y * w, z * w, 1.0f);
			printf("NDCVertex : ");
			PrintVec(ndcV);
			std::cout << '\n';
			Vector3 screenV = ndcV * Hscreen;
			printf("ScreenVertex : ");
			PrintVec(screenV);
			std::cout << '\n';
		}
		std::cout << '\n';
	}
	return 0;
}

