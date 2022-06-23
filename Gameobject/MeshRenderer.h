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
	typedef void (MeshRenderer::*RenderFun)(Camera* cameraPtr, Light* lightPtr);
	typedef unsigned char BYTE;
private:
	const Mesh* m_Mesh;//网格
	const Material* m_Material;//材质
	float m_Scale;
	bool m_RecvShadow;
	RenderFun m_RenderFunPtr;


private:
	static BYTE* m_bufferPtr;
	static int* m_Edge_XBuffer;
	static BYTE* m_Edge_ColorBuffer;
	static float* m_Edge_TexMapBuffer;
	static float* m_Edge_DepthBuffer;
	static float* m_DepthBuffer;
	static BYTE* m_StencilBuffer;
	static Vector3* m_Edge_ViewVecBuffer;
	static int m_Width;
	static int m_Height;

public:
	MeshRenderer(GameObject & go) : m_Scale(1.0f), Component(go) {}
	MeshRenderer(GameObject * goPtr) : m_Scale(1.0f),Component(goPtr) {}
	MeshRenderer() : m_Scale(1.0f), m_RenderFunPtr(&MeshRenderer::Render1){}
	/// <summary>
	/// 设置该网格渲染器的网格
	/// </summary>
	/// <param name="mesh"></param>
	void SetMesh(const Mesh * mesh);
	/// <summary>
	/// 获取该网格渲染器的网格
	/// </summary>
	/// <returns></returns>
	const Mesh* GetMesh() const;
	/// <summary>
	/// 获取该网格渲染器的材质
	/// </summary>
	/// <param name="material"></param>
	void SetMaterial(const Material* material);
	/// <summary>
	/// 设置该网格渲染器的材质
	/// </summary>
	/// <returns></returns>
	const Material* GetMaterial() const;
	/// <summary>
	/// 渲染函数接口
	/// </summary>
	/// <param name="cameraPtr"></param>
	/// <param name="lightPtr"></param>
	void Render(Camera* cameraPtr, Light* lightPtr);

	void SetScale(float scale);

	float GetScale() const;

	bool IsShadowRecv() const;

	void SetShadowRecv(bool isRecv);

	Float4x4 GetPlanarMatrix(const Vector3& lightDir, const Vector3& pos, const Vector3& nor) const;

	void DrawShadow(Camera* cameraPtr, Light* lightPtr);

	void SetRenderFunc(int num) 
	{ 
		m_RenderFunPtr = num ? &MeshRenderer::Render1 : &MeshRenderer::Render0;
	}

private:
	Float4x4 GetWVPMatrix(const Float4x4 obj_Tran, const Camera* cam) const;
	Float4x4 GetViewMatrix(const Camera* camera) const;
	Vector3 GetLightDir(const Transform* light, const Transform* obj) const;
	void UpdateBackground(BYTE r, BYTE g, BYTE b);
	bool IsBack(const Vector3& v0, const Vector3& v1, const Vector3& v2) const;
	bool IsBack1(const Vector3& v0, const Vector3& v1, const Vector3& v2) const;
	/// <summary>
	/// 渲染函数（纹理）
	/// </summary>
	/// <param name="cameraPtr"></param>
	/// <param name="lightPtr"></param>
	void Render0(Camera* cameraPtr, Light* lightPtr);
	/// <summary>
	/// 渲染函数（光照+纹理）
	/// </summary>
	/// <param name="cameraPtr"></param>
	/// <param name="lightPtr"></param>
	void Render1(Camera* cameraPtr, Light* lightPtr);
	

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

#pragma region Version0.4
	void DrawTrangleNew(Vector3& vert0, float x0, float y0, Vector3& view0,Vector3& vert1, float x1, float y1, Vector3& view1,Vector3& vert2, float x2, float y2, Vector3& view2, Vector3& normal, Vector3& lightDir);
	void SaveEdge(int x, int y, float z, float tx, float ty, Vector3& view, bool num)
	{
		m_Edge_XBuffer[(y << 1) + num] = x;
		m_Edge_TexMapBuffer[(y << 2) + (num << 1)] = tx;
		m_Edge_TexMapBuffer[(y << 2) + (num << 1) + 1] = ty;
		m_Edge_ViewVecBuffer[(y << 1) + num] = view;
		m_Edge_DepthBuffer[(y << 1) + num] = z;
	}
	void SaveEdge(int x, int y, float z, bool num)
	{
		m_Edge_XBuffer[(y << 1) + num] = x;
		m_Edge_DepthBuffer[(y << 1) + num] = z;
	}
	bool ComputeEdgeBuffers(Vector3& vert0, float x0, float y0, Vector3& view0, Vector3& vert1, float x1, float y1, Vector3& view1, Vector3& vert2, float x2, float y2, Vector3& view2);
	void ComputeEdgeBuffers(Vector3& vert0, float x0, float y0, Vector3& view0, Vector3& vert1, float x1, float y1, Vector3& view1, bool isBuffer1);
	bool ComputeEdgeBuffers(int vx0, int vy0, float vz0, float x0, float y0, Vector3& view0, int vx1, int vy1, float vz1, float x1, float y1, Vector3& view1, int vx2, int vy2, float vz2, float x2, float y2, Vector3& view2);
	void ComputeEdgeBuffers(int vx0, int vy0, float vz0, float x0, float y0, Vector3& view0, int vx1, int vy1, float vz1, float x1, float y1, Vector3& view1, bool isBuffer1);
#pragma endregion

	void DrawShadow(Vector3& vert0, Vector3& vert1, Vector3& vert2, const Vector3& shadowColor);
	bool ComputeShadowEdge(int x0, int y0, float z0, int x1, int y1, float z1, int x2, int y2, float z2);
	void ComputeShadowEdge(int x0, int y0, float z0, int x1, int y1, float z1, bool isBuffer1);

#pragma region 透视校正插值
	void DrawTrangleR(Vector3& vert0, float x0, float y0, Vector3& view0, Vector3& nor0, Vector3& vert1, float x1, float y1, Vector3& view1, Vector3& nor1, Vector3& vert2, float x2, float y2, Vector3& view2, Vector3& nor2, Vector3& lightDir);
	bool ComputeEdgeBuffer(int x0, int y0, int x1, int y1, int x2, int y2);
	void ComputeEdgeBuffer(int x0, int y0, int x1, int y1, bool isBuffer1);
	void SaveEdge(int x, int y, bool num)
	{
		m_Edge_XBuffer[(y << 1) + num] = x;
	}
#pragma endregion


public:
	static void SetEdgeXBuffer(int* edge_XBuffer);
	static void SetColorBuffer(BYTE* edge_ColorBuffer);
	static void SetBufferPtr(BYTE* bufferPtr);
	static void SetWindowWidthAndHeight(int width, int height);
	static void SetTexMapBuffer(float* texMapBuffer);
	static void SetEdgeDepthBuffer(float* edgeDepthBuffer);
	static void SetDepthBuffer(float* depthBuffer);
	static void SetStencilBuffer(BYTE* stencilBuffer);
	static void SetViewVecBuffer(Vector3* viewVecBuffer);

};



