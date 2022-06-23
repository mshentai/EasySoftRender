#pragma once
#include "Component.h"
#include "../Transfrom/Float4x4.h"
class Mesh;
class Material;
class Camera;
class Light;

class MeshRenderer :
	public Component
{
	typedef unsigned char BYTE;
private:
	const Mesh* m_Mesh;//Íø¸ñ
	const Material* m_Material;//²ÄÖÊ


private:
	static BYTE* m_bufferPtr;
	static int* m_Edge_XBuffer;
	static BYTE* m_Edge_ColorBuffer;
	static float* m_Edge_TexMapBuffer;
	static Vector3* m_Edge_ViewVecBuffer;
	static int m_Width;
	static int m_Height;

public:
	MeshRenderer(GameObject & go) : Component(go) {}
	MeshRenderer(GameObject * goPtr) : Component(goPtr) {}
	MeshRenderer(){}
	void SetMesh(const Mesh * mesh);
	const Mesh* GetMesh() const;
	void SetMaterial(const Material* material);
	const Material* GetMaterial() const;
	void Render(Camera* cameraPtr, Light* lightPtr);
	void Render1(Camera* cameraPtr, Light* lightPtr);


private:
	Float4x4 GetWVPMatrix(const Float4x4 obj_Tran, const Camera* cam) const;
	Float4x4 GetViewMatrix(const Camera* camera) const;
	Vector3 GetLightDir(const Transform* light, const Transform* obj) const;
	void UpdateBackground(BYTE r, BYTE g, BYTE b);
	bool IsBack(const Vector3& v0, const Vector3& v1, const Vector3& v2) const;

#pragma region Version0.1
	void DrawLine(int x0, int y0, BYTE rgb0[3], int x1, int y1, BYTE rgb1[3]);
	void DrawLine(int y, int x0, BYTE rgb0[3], int x1, BYTE rgb1[3]);
	void DrawTrangle(int x0, int y0, BYTE rgb0[3], int x1, int y1, BYTE rgb1[3], int x2, int y2, BYTE rgb2[3]);
	void ComputeEdgeBuffers(int x0, int y0, BYTE rgb0[3], int x1, int y1, BYTE rgb1[3], bool isBuffer1);
	bool ComputeEdgeBuffers(int x0, int y0, BYTE rgb0[3], int x1, int y1, BYTE rgb1[3], int x2, int y2, BYTE rgb2[3]);
	void ComputeEdgeBuffers(int x0, int y0, int x1, int y1, bool isBuffer1);
	bool ComputeEdgeBuffers(int x0, int y0, int x1, int y1, int x2, int y2);
	void DrawPixel(int x, int y, BYTE r, BYTE g, BYTE b)
	{
		int p = (y * m_Width + x + 1) * 3;
		m_bufferPtr[p - 3] = b;//b
		m_bufferPtr[p - 2] = g;//g
		m_bufferPtr[p - 1] = r;//r
	}
	void SaveEdge(int x, int y, BYTE r, BYTE g, BYTE b, bool num)
	{
		int p = ((y << 1) + num + 1) * 3;
		m_Edge_ColorBuffer[p - 3] = b;//b
		m_Edge_ColorBuffer[p - 2] = g;//g
		m_Edge_ColorBuffer[p - 1] = r;//r
		m_Edge_XBuffer[(y << 1) + num] = x;
	}
	void SaveEdge(int x, int y, bool num)
	{
		m_Edge_XBuffer[(y << 1) + num] = x;
	}
#pragma endregion

#pragma region Version0.2
	bool Compute_Edge_TexMap_Buffers(int vx0, int vy0, float x0, float y0, int vx1, int vy1, float x1, float y1, int vx2, int vy2, float x2, float y2);
	void Compute_Edge_TexMap_Buffers(int vx0, int vy0, float x0, float y0, int vx1, int vy1, float x1, float y1, bool isBuffer1);
	void SaveEdge(int x, int y, float tx, float ty, bool num)
	{
		m_Edge_XBuffer[(y << 1) + num] = x;
		m_Edge_TexMapBuffer[(y << 2) + (num << 1)] = tx;
		m_Edge_TexMapBuffer[(y << 2) + (num << 1) + 1] = ty;
	}
	void DrawTrangle(
		Vector3& vert0, float x0, float y0,
		Vector3& vert1, float x1, float y1,
		Vector3& vert2, float x2, float y2, Vector3& normal);
#pragma endregion

#pragma region Version0.3
	void DrawTrangle(
		Vector3& vert0, float x0, float y0, Vector3& view0,
		Vector3& vert1, float x1, float y1, Vector3& view1,
		Vector3& vert2, float x2, float y2, Vector3& view2, Vector3& normal, Vector3& lightDir);

	void SaveEdge(int x, int y, float tx, float ty, Vector3& view, bool num)
	{
		m_Edge_XBuffer[(y << 1) + num] = x;
		m_Edge_TexMapBuffer[(y << 2) + (num << 1)] = tx;
		m_Edge_TexMapBuffer[(y << 2) + (num << 1) + 1] = ty;
		m_Edge_ViewVecBuffer[(y << 1) + num] = view;
	}

	bool Compute_Edge_TexMap_View_Buffers(
		int vx0, int vy0, float x0, float y0, Vector3& view0, 
		int vx1, int vy1, float x1, float y1, Vector3& view1, 
		int vx2, int vy2, float x2, float y2, Vector3& view2);

	void Compute_Edge_TexMap_View_Buffers(
		int vx0, int vy0, float x0, float y0, Vector3& view0, 
		int vx1, int vy1, float x1, float y1, Vector3& view1, bool isBuffer1);
#pragma endregion


public:
	static void SetEdgeXBuffer(int* edge_XBuffer);
	static void SetColorBuffer(BYTE* edge_ColorBuffer);
	static void SetBufferPtr(BYTE* bufferPtr);
	static void SetWindowWidthAndHeight(int width, int height);
	static void SetTexMapBuffer(float* texMapBuffer);
	static void SetViewVecBuffer(Vector3* viewVecBuffer);

};



