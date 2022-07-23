#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "../Primitives/Triangle.h"
#include "../Primitives/Mesh.h"
#include "../Primitives/Material.h"
#include <utility>
#include "Light.h"


unsigned char* MeshRenderer::m_bufferPtr = nullptr;
unsigned char* MeshRenderer::m_Edge_ColorBuffer = nullptr;
int* MeshRenderer::m_Edge_XBuffer = nullptr;
int MeshRenderer::m_Width = 0;
int MeshRenderer::m_Height = 0;
float* MeshRenderer::m_Edge_TexMapBuffer = nullptr;
Vector3* MeshRenderer::m_Edge_ViewVecBuffer = nullptr;

void MeshRenderer::SetMesh(const Mesh * mesh)
{
	m_Mesh = mesh;
}
const Mesh * MeshRenderer::GetMesh() const
{
	return m_Mesh;
}
void MeshRenderer::SetMaterial(const Material* material)
{
	m_Material = material;
}
const Material* MeshRenderer::GetMaterial() const
{
	return m_Material;
}
void MeshRenderer::Render(Camera* cameraPtr, Light* lightPtr)
{
	float4x4 OTW = this->GetTransform()->ObjectToWorld();
	Float4x4 WVP = GetWVPMatrix(OTW, cameraPtr);
	Float4x4 Hscreen = cameraPtr->GetScreenMatrix(m_Width, m_Height);
	const Mesh* m = this->GetMesh();
	const std::vector<Triangle>& tris = m->GetTriangles();
	int len = tris.size();
	std::vector<Vector3> projPos;
	std::vector<Vector3> projNor;
	std::vector<const float*> texMaps;
	for (int i = 0; i < len; ++i)
	{
		auto v = tris[i].GetVertexes();
		auto n = tris[i].GetNormal();
		auto t = tris[i].GetTexMaps();
		texMaps.push_back(t);
		Vector3 pos;
		Vector3 nor = (*v[0]) * OTW;
		projNor.push_back(nor);
		m_Material->Vertex((*v[0]), WVP, pos);
		projPos.push_back(pos);
		m_Material->Vertex((*v[1]), WVP, pos);
		projPos.push_back(pos);
		m_Material->Vertex((*v[2]), WVP, pos);
		projPos.push_back(pos);
	}
	len = projPos.size();
	for (int i = 0; i < len; i += 3)
	{
		Vector3& v0 = projPos[i];
		Vector3& v1 = projPos[i + 1];
		Vector3& v2 = projPos[i + 2];
		if (!IsBack(v0, v1, v2) && true)
		{
			float x = v0[0];
			float y = v0[1];
			float z = v0[2];
			float w = 1.0f / v0[3];
			Vector3 ndcV0(x * w, y * w, z * w, 1.0f);
			Vector3 screenV0 = ndcV0 * Hscreen;
			x = v1[0];
			y = v1[1];
			z = v1[2];
			w = 1.0f / v1[3];
			Vector3 ndcV1 = Vector3(x * w, y * w, z * w, 1.0f);
			Vector3 screenV1 = ndcV1 * Hscreen;
			x = v2[0];
			y = v2[1];
			z = v2[2];
			w = 1.0f / v2[3];
			Vector3 ndcV2 = Vector3(x * w, y * w, z * w, 1.0f);
			Vector3 screenV2 = ndcV2 * Hscreen;
			const float* t = texMaps[i / 3];

			DrawTrangle(screenV0, t[0], t[1], screenV1, t[2], t[3], screenV2, t[4], t[5], projNor[i / 3]);
		}
	}
}

void MeshRenderer::Render1(Camera* cameraPtr, Light* lightPtr)
{
	float4x4 OTW = this->GetTransform()->ObjectToWorld();
	Float4x4 WVP = GetWVPMatrix(OTW, cameraPtr);
	Float4x4 Hscreen = cameraPtr->GetScreenMatrix(m_Width, m_Height);
	const Mesh* m = this->GetMesh();
	const std::vector<Triangle>& tris = m->GetTriangles();
	int len = tris.size();
	std::vector<Vector3> projPos;
	std::vector<Vector3> worldNor;
	std::vector<Vector3> viewVec;
	std::vector<const float*> texMaps;
	Vector3 cameraPos = cameraPtr->GetTransform()->GetPosition();
	Vector3 lightDir = lightPtr->GetLightDir().Normalize();
	for (int i = 0; i < len; ++i)
	{
		auto v = tris[i].GetVertexes();
		auto n = tris[i].GetNormal();
		auto t = tris[i].GetTexMaps();
		viewVec.emplace_back(((*v[0]) * OTW - cameraPos).Normalize());
		viewVec.emplace_back(((*v[1]) * OTW - cameraPos).Normalize());
		viewVec.emplace_back(((*v[2]) * OTW - cameraPos).Normalize());
		texMaps.push_back(t);
		Vector3 pos;
		worldNor.push_back(Dot((*n[0]), OTW, false).Normalize());
		m_Material->Vertex((*v[0]), WVP, pos);
		projPos.push_back(pos);
		m_Material->Vertex((*v[1]), WVP, pos);
		projPos.push_back(pos);
		m_Material->Vertex((*v[2]), WVP, pos);
		projPos.push_back(pos);
	}
	len = projPos.size();
	for (int i = 0; i < len; i += 3)
	{
		Vector3& v0 = projPos[i];
		Vector3& v1 = projPos[i + 1];
		Vector3& v2 = projPos[i + 2];
		if (!IsBack(v0, v1, v2) && true)
		{
			float x = v0[0];
			float y = v0[1];
			float z = v0[2];
			float w = 1.0f / v0[3];
			Vector3 ndcV0(x * w, y * w, z * w, 1.0f);
			Vector3 screenV0 = ndcV0 * Hscreen;
			x = v1[0];
			y = v1[1];
			z = v1[2];
			w = 1.0f / v1[3];
			Vector3 ndcV1 = Vector3(x * w, y * w, z * w, 1.0f);
			Vector3 screenV1 = ndcV1 * Hscreen;
			x = v2[0];
			y = v2[1];
			z = v2[2];
			w = 1.0f / v2[3];
			Vector3 ndcV2 = Vector3(x * w, y * w, z * w, 1.0f);
			Vector3 screenV2 = ndcV2 * Hscreen;
			const float* t = texMaps[i / 3];

			DrawTrangle(screenV0, t[0], t[1], viewVec[i], screenV1, t[2], t[3], viewVec[i + 1], screenV2, t[4], t[5], viewVec[i + 2], worldNor[i / 3], lightDir);
		}
	}
}

void MeshRenderer::SetEdgeXBuffer(int* edge_XBuffer)
{
	m_Edge_XBuffer = edge_XBuffer;
}
void MeshRenderer::SetColorBuffer(BYTE* edge_ColorBuffer)
{
	m_Edge_ColorBuffer = edge_ColorBuffer;
}
void MeshRenderer::SetBufferPtr(BYTE* bufferPtr)
{
	m_bufferPtr = bufferPtr;
}
void MeshRenderer::SetWindowWidthAndHeight(int width, int height)
{
	m_Width = width;
	m_Height = height;
}
void MeshRenderer::SetTexMapBuffer(float* texMapBuffer)
{
	m_Edge_TexMapBuffer = texMapBuffer;
}
void MeshRenderer::SetViewVecBuffer(Vector3* viewVecBuffer)
{
	m_Edge_ViewVecBuffer = viewVecBuffer;
}
Float4x4 MeshRenderer::GetWVPMatrix(const Float4x4 otw, const Camera* cam) const
{
	return otw * (cam->GetViewMatrix()) * (cam->GetProjectMatrix());
}
Float4x4 MeshRenderer::GetViewMatrix(const Camera* camera) const
{
	return camera->GetViewMatrix();
}
Vector3 MeshRenderer::GetLightDir(const Transform* light, const Transform* obj) const
{
	return light->GetPosition() - obj->GetPosition();
}

#pragma region Version0.1
void MeshRenderer::DrawLine(int x0, int y0, BYTE rgb0[3], int x1, int y1, BYTE rgb1[3])
{

#pragma region 书上的
	//int x = x0, y = y0;
	//int dx = x1 - x0, dy = y1 - y0;
	//int sx, sy;
	//float r = rgb0[0];
	//float g = rgb0[1];
	//float b = rgb0[2];
	//if (dx > 0)
	//{
	//	sx = 1;
	//}
	//else if (dx < 0)
	//{
	//	sx = -1;
	//	dx = -dx;
	//}
	//else
	//{
	//	sx = 0;
	//}
	//if (dy > 0)
	//{
	//	sy = 1;
	//}
	//else if (dy < 0)
	//{
	//	sy = -1;
	//	dy = -dy;
	//}
	//else
	//{
	//	sy = 0;
	//}
	//int ax = 2 * dx, ay = 2 * dy;
	//if (dx <= dx)
	//{
	//	for (int decy = ay - dx;; x += sx, decy += ay)
	//	{
	//		DrawPixel(x, y, r, g, b);
	//		if (x == x1)
	//		{
	//			break;
	//		}
	//		if (decy >= 0)
	//		{
	//			decy -= ax;
	//			y += sy;
	//		}
	//	}
	//}
	//else
	//{
	//	for (int decx = ax - dy;; y += sy, decx += ax)
	//	{
	//		DrawPixel(x, y, r, g, b);
	//		if (y == y1)
	//		{
	//			break;
	//		}
	//		if (decx >= 0)
	//		{
	//			decx -= ay;
	//			x += sx;
	//		}
	//	}
	//}
#pragma endregion

#pragma region 自己的
	if (y0 > y1)
	{
		int tmp = x0;
		x0 = x1;
		x1 = tmp;
		tmp = y0;
		y0 = y1;
		y1 = tmp;
		BYTE* rgb = rgb0;
		rgb0 = rgb1;
		rgb1 = rgb;
	}
	else if (y0 == y1)
	{
		DrawLine(y0, x0, rgb0, x1, rgb0);
		return;
	}
	float x = x0;
	float dx = x1 - x0;
	float dy = 1.0f / (y1 - y0);
	float d = dx * dy;
	float dr = (float)(rgb1[0] - rgb0[0]) * dy;
	float dg = (float)(rgb1[1] - rgb0[1]) * dy;
	float db = (float)(rgb1[2] - rgb0[2]) * dy;
	float r = rgb0[0];
	float g = rgb0[1];
	float b = rgb0[2];
	for (int y = y0; y <= y1; ++y, r += dr, g += dg, b += db)
	{
		DrawPixel(x, y, r, g, b);
		x += d;
	}
#pragma endregion

}

void MeshRenderer::DrawLine(int y, int x0, BYTE rgb0[3], int x1, BYTE rgb1[3])
{
	if (x0 > x1)
	{
		int tmp = x0;
		x0 = x1;
		x1 = tmp;
		BYTE* rgb = rgb0;
		rgb0 = rgb1;
		rgb1 = rgb;
	}
	int dx = x1 - x0;
	float r = rgb0[0];
	float g = rgb0[1];
	float b = rgb0[2];
	float dr = (float)(rgb1[0] - rgb0[0]) / dx;
	float dg = (float)(rgb1[1] - rgb0[1]) / dx;
	float db = (float)(rgb1[2] - rgb0[2]) / dx;

	for (int i = 0; i <= dx; r += dr, g += dg, b += db, ++i)
	{
		DrawPixel(x0 + i, y, r, g, b);
	}
}

static void XYSwap(int& x0, int& y0, int& x1, int& y1)
{
	int tmp = x0;
	x0 = x1;
	x1 = tmp;
	tmp = y0;
	y0 = y1;
	y1 = tmp;
}
static void XYSwap(int& x0, int& y0, BYTE*& rgb0, int& x1, int& y1, BYTE*& rgb1)
{
	int tmp = x0;
	x0 = x1;
	x1 = tmp;
	tmp = y0;
	y0 = y1;
	y1 = tmp;
	BYTE* t = rgb0;
	rgb0 = rgb1;
	rgb1 = t;
}
static void XYOrder(int& x0, int& y0, int& x1, int& y1, int& x2, int& y2)
{
	if (y0 > y1)
	{
		XYSwap(x0, y0, x1, y1);
	}
	if (y1 > y2)
	{
		XYSwap(x1, y1, x2, y2);
	}
	if (y0 > y1)
	{
		XYSwap(x0, y0, x1, y1);
	}
}
static void XYOrder(int& x0, int& y0, BYTE*& rgb0, int& x1, int& y1, BYTE*& rgb1, int& x2, int& y2, BYTE*& rgb2)
{
	if (y0 > y1)
	{
		XYSwap(x0, y0, rgb0, x1, y1, rgb1);
	}
	if (y1 > y2)
	{
		XYSwap(x1, y1, rgb1, x2, y2, rgb2);
	}
	if (y0 > y1)
	{
		XYSwap(x0, y0, rgb0, x1, y1, rgb1);
	}
}
void MeshRenderer::DrawTrangle(int x0, int y0, BYTE rgb0[3], int x1, int y1, BYTE rgb1[3], int x2, int y2, BYTE rgb2[3])
{
	XYOrder(x0, y0, rgb0, x1, y1, rgb1, x2, y2, rgb2);
	//XYOrder(x0, y0, x1, y1, x2, y2);
	if (ComputeEdgeBuffers(x0, y0, rgb0, x1, y1, rgb1, x2, y2, rgb2))
	{
		int h = m_Height;
		int low = y0 * 2;
		int hei = y2 * 2;
		for (int y = low; y <= hei; y += 2)
		{
			DrawLine(y >> 1, m_Edge_XBuffer[y], (m_Edge_ColorBuffer + y * 3), m_Edge_XBuffer[y + 1], (m_Edge_ColorBuffer + (y + 1) * 3));
		}
	}
}
void MeshRenderer::ComputeEdgeBuffers(int x0, int y0, BYTE rgb0[3], int x1, int y1, BYTE rgb1[3], bool isBuffer1)
{
	if (y0 > y1)
	{
		XYSwap(x0, y0, rgb0, x1, y1, rgb1);
	}
	float x = x0;
	float dx = x1 - x0;
	float dy = 1.0f / (y1 - y0);
	float d = dx * dy;
	float dr = (float)(rgb1[0] - rgb0[0]) * dy;
	float dg = (float)(rgb1[1] - rgb0[1]) * dy;
	float db = (float)(rgb1[2] - rgb0[2]) * dy;
	float r = rgb0[0];
	float g = rgb0[1];
	float b = rgb0[2];
	for (int y = y0; y <= y1; ++y, x += d, r += dr, g += dg, b += db)
	{
		SaveEdge(x, y, r, g, b, isBuffer1);
	}
}
bool MeshRenderer::ComputeEdgeBuffers(int x0, int y0, BYTE rgb0[3], int x1, int y1, BYTE rgb1[3], int x2, int y2, BYTE rgb2[3])
{
	if ((x0 == x1 && x1 == x2) || (y0 == y1 && y1 == y2)) return false;
	ComputeEdgeBuffers(x0, y0, rgb0, x1, y1, rgb1, false);
	ComputeEdgeBuffers(x1, y1, rgb1, x2, y2, rgb2, false);
	ComputeEdgeBuffers(x0, y0, rgb0, x2, y2, rgb2, true);
	return true;
}
void MeshRenderer::ComputeEdgeBuffers(int x0, int y0, int x1, int y1, bool isBuffer1)
{
	if (y0 > y1)
	{
		XYSwap(x0, y0, x1, y1);
	}
	float x = x0;
	float dx = x1 - x0;
	float dy = 1.0f / (y1 - y0);
	float d = dx * dy;
	for (int y = y0; y <= y1; ++y, x += d)
	{
		SaveEdge(x, y, isBuffer1);
	}
}
bool MeshRenderer::ComputeEdgeBuffers(int x0, int y0, int x1, int y1, int x2, int y2)
{
	if ((x0 == x1 && x1 == x2) || (y0 == y1 && y1 == y2)) return false;
	ComputeEdgeBuffers(x0, y0, x1, y1, false);
	ComputeEdgeBuffers(x1, y1, x2, y2, false);
	ComputeEdgeBuffers(x0, y0, x2, y2, true);
	return true;
}
#pragma endregion

#pragma region Version0.2
static void XYSwap(int& vx0, int& vy0, float& x0, float& y0, int& vx1, int& vy1, float& x1, float& y1)
{
	int tmp0 = vx0;
	vx0 = vx1;
	vx1 = tmp0;
	int tmp1 = vy0;
	vy0 = vy1;
	vy1 = tmp1;
	float fTmpx = x0;
	x0 = x1;
	x1 = fTmpx;
	float fTmpy = y0;
	y0 = y1;
	y1 = fTmpy;
}
static void XYOrder(int& vx0, int& vy0, float& x0, float& y0, int& vx1, int& vy1, float& x1, float& y1, int& vx2, int& vy2, float& x2, float& y2)
{
	if (vy0 > vy1)
	{
		XYSwap(vx0, vy0, x0, y0, vx1, vy1, x1, y1);
	}
	if (vy1 > vy2)
	{
		XYSwap(vx1, vy1, x1, y1, vx2, vy2, x2, y2);
	}
	if (vy0 > vy1)
	{
		XYSwap(vx0, vy0, x0, y0, vx1, vy1, x1, y1);
	}
}
bool MeshRenderer::Compute_Edge_TexMap_Buffers(int vx0, int vy0, float x0, float y0, int vx1, int vy1, float x1, float y1, int vx2, int vy2, float x2, float y2)
{
	if ((vx0 == vx1 && vx1 == vx2) || (vy0 == vy1 && vy1 == vy2)) return false;
	Compute_Edge_TexMap_Buffers(vx0, vy0, x0, y0, vx1, vy1, x1, y1, false);
	Compute_Edge_TexMap_Buffers(vx1, vy1, x1, y1, vx2, vy2, x2, y2, false);
	Compute_Edge_TexMap_Buffers(vx0, vy0, x0, y0, vx2, vy2, x2, y2, true);
	return true;
}
void MeshRenderer::Compute_Edge_TexMap_Buffers(int vx0, int vy0, float x0, float y0, int vx1, int vy1, float x1, float y1, bool isBuffer1)
{
	//if (vy0 > vy1)
	//{
	//	XYSwap(vx0, vy0, x0, y0, vx1, vy1, x1, y1);
	//}
	float x = vx0;
	float dy = 1.0f / (vy1 - vy0);
	float dx = (vx1 - vx0) * dy;
	float dtx = (x1 - x0) * dy;
	float dty = (y1 - y0) * dy;
	float tx = x0;
	float ty = y0;
	for (int y = vy0; y <= vy1; ++y, x += dx, tx += dtx, ty += dty)
	{
		SaveEdge(x, y, tx, ty, isBuffer1);
	}
}
void MeshRenderer::DrawTrangle(
	Vector3& vert0, float x0, float y0,
	Vector3& vert1, float x1, float y1,
	Vector3& vert2, float x2, float y2, Vector3& normal)
{
	int vx0 = vert0[0];
	int vy0 = vert0[1];
	int vx1 = vert1[0];
	int vy1 = vert1[1];
	int vx2 = vert2[0];
	int vy2 = vert2[1];

	XYOrder(vx0, vy0, x0, y0, vx1, vy1, x1, y1, vx2, vy2, x2, y2);

	if (Compute_Edge_TexMap_Buffers(vx0, vy0, x0, y0, vx1, vy1, x1, y1, vx2, vy2, x2, y2))
	{
		int h = m_Height;
		int low = vy0 * 2;
		int hei = vy2 * 2;
		for (int y = low; y <= hei; y += 2)
		{
			//DrawLine(y >> 1, m_Edge_XBuffer[y], (m_Edge_ColorBuffer + y * 3), m_Edge_XBuffer[y + 1], (m_Edge_ColorBuffer + (y + 1) * 3));
			int firstX = m_Edge_XBuffer[y];
			int lastX = m_Edge_XBuffer[y + 1];
			float firstTx = m_Edge_TexMapBuffer[(y << 1)];
			float firstTy = m_Edge_TexMapBuffer[(y << 1) + 1];
			float lastTx = m_Edge_TexMapBuffer[(y << 1) + 2];
			float lastTy = m_Edge_TexMapBuffer[(y << 1) + 3];
			float d = 1.0f / (lastX - firstX);
			float dx = (lastTx - firstTx) * d;
			float dy = (lastTy - firstTy) * d;
			int py = (y >> 1);
			int dd = 1;
			if (firstX > lastX)
			{
				int tmp = firstX;
				firstX = lastX;
				lastX = tmp;
				float ftmp = firstTx;
				firstTx = lastTx;
				lastTx = ftmp;
				//dx = -dx;
				ftmp = firstTy;
				firstTy = lastTy;
				lastTy = ftmp;
				//dy = -dy;
			}
			for (int px = firstX; px <= lastX; px += dd, firstTx += dx, firstTy += dy)
			{
				m_Material->Fragment(px, py, firstTx, firstTy, (m_bufferPtr + (py * m_Width + px) * 3));
			}
		}
	}
}
#pragma endregion

#pragma region Version0.3
static void XYSwap(int& vx0, int& vy0, float& x0, float& y0, Vector3& view0, int& vx1, int& vy1, float& x1, float& y1, Vector3& view1)
{
	int tmp0 = vx0;
	vx0 = vx1;
	vx1 = tmp0;
	int tmp1 = vy0;
	vy0 = vy1;
	vy1 = tmp1;
	float fTmpx = x0;
	x0 = x1;
	x1 = fTmpx;
	float fTmpy = y0;
	y0 = y1;
	y1 = fTmpy;
	Vector3 temp = view0;
	view0 = view1;
	view1 = temp;
}
static void XYOrder(
	int& vx0, int& vy0, float& x0, float& y0, Vector3& view0, 
	int& vx1, int& vy1, float& x1, float& y1, Vector3& view1,
	int& vx2, int& vy2, float& x2, float& y2, Vector3& view2)
{
	if (vy0 > vy1)
	{
		XYSwap(vx0, vy0, x0, y0, view0, vx1, vy1, x1, y1, view1);
	}
	if (vy1 > vy2)
	{
		XYSwap(vx1, vy1, x1, y1, view1, vx2, vy2, x2, y2, view2);
	}
	if (vy0 > vy1)
	{
		XYSwap(vx0, vy0, x0, y0, view0, vx1, vy1, x1, y1, view1);
	}
}


void MeshRenderer::DrawTrangle(
	Vector3& vert0, float x0, float y0, Vector3& view0, 
	Vector3& vert1, float x1, float y1, Vector3& view1, 
	Vector3& vert2, float x2, float y2, Vector3& view2, Vector3& normal, Vector3& lightDir)
{
	int vx0 = vert0[0];
	int vy0 = vert0[1];
	int vx1 = vert1[0];
	int vy1 = vert1[1];
	int vx2 = vert2[0];
	int vy2 = vert2[1];

	char s[100];
	sprintf_s(s, "Triangle : (%d,%d),(%d,%d),(%d,%d)\n", vx0, vy0, vx1, vy1, vx2, vy2);
	OutputDebugString(s);

	XYOrder(vx0, vy0, x0, y0, view0, vx1, vy1, x1, y1, view1, vx2, vy2, x2, y2, view2);

	if (Compute_Edge_TexMap_View_Buffers(vx0, vy0, x0, y0, view0, vx1, vy1, x1, y1, view1, vx2, vy2, x2, y2, view2))
	{
		int h = m_Height;
		int low = vy0 * 2;
		int hei = vy2 * 2;
		for (int y = low; y <= hei; y += 2)
		{
			//DrawLine(y >> 1, m_Edge_XBuffer[y], (m_Edge_ColorBuffer + y * 3), m_Edge_XBuffer[y + 1], (m_Edge_ColorBuffer + (y + 1) * 3));
			int firstX = m_Edge_XBuffer[y];
			int lastX = m_Edge_XBuffer[y + 1];
			float firstTx = m_Edge_TexMapBuffer[(y << 1)];
			float firstTy = m_Edge_TexMapBuffer[(y << 1) + 1];
			float lastTx = m_Edge_TexMapBuffer[(y << 1) + 2];
			float lastTy = m_Edge_TexMapBuffer[(y << 1) + 3];
			Vector3 firstView = m_Edge_ViewVecBuffer[y];
			Vector3 lastView = m_Edge_ViewVecBuffer[y + 1];
			if (firstX > lastX)
			{
				int tmp = firstX;
				firstX = lastX;
				lastX = tmp;
				float ftmp = firstTx;
				firstTx = lastTx;
				lastTx = ftmp;
				ftmp = firstTy;
				firstTy = lastTy;
				lastTy = ftmp;
				Vector3 vtmp = firstView;
				firstView = lastView;
				lastView = vtmp;
			}
			float d = 1.0f / (lastX - firstX);
			float dx = (lastTx - firstTx) * d;
			float dy = (lastTy - firstTy) * d;
			Vector3 dv = ((lastView - firstView) * d);
			int py = (y >> 1);
			int dd = 1;
			Vector3 view = firstView;
			for (int px = firstX; px <= lastX; px += dd, firstTx += dx, firstTy += dy, view += dv)
			{
				m_Material->Fragment(px, py, firstTx, firstTy, lightDir, view, normal, (m_bufferPtr + (py * m_Width + px) * 3));
			}
		}
	}
}

bool MeshRenderer::Compute_Edge_TexMap_View_Buffers(
	int vx0, int vy0, float x0, float y0, Vector3& view0,
	int vx1, int vy1, float x1, float y1, Vector3& view1,
	int vx2, int vy2, float x2, float y2, Vector3& view2)
{
	if ((vx0 == vx1 && vx1 == vx2) || (vy0 == vy1 && vy1 == vy2)) return false;
	Compute_Edge_TexMap_View_Buffers(vx0, vy0, x0, y0, view0, vx1, vy1, x1, y1, view1, false);
	Compute_Edge_TexMap_View_Buffers(vx1, vy1, x1, y1, view1, vx2, vy2, x2, y2, view2, false);
	Compute_Edge_TexMap_View_Buffers(vx0, vy0, x0, y0, view0, vx2, vy2, x2, y2, view2, true);
	return true;
}

void MeshRenderer::Compute_Edge_TexMap_View_Buffers(int vx0, int vy0, float x0, float y0, Vector3& view0, int vx1, int vy1, float x1, float y1, Vector3& view1, bool isBuffer1)
{
	float x = vx0;
	float dy = 1.0f / (vy1 - vy0);
	float dx = (vx1 - vx0) * dy;
	float dtx = (x1 - x0) * dy;
	float dty = (y1 - y0) * dy;
	float tx = x0;
	float ty = y0;
	Vector3 dv = (view1 - view0) * dy;
	Vector3 view = view0;
	for (int y = vy0; y <= vy1; ++y, x += dx, tx += dtx, ty += dty, view += dv)
	{
		SaveEdge(x, y, tx, ty, view, isBuffer1);
	}
}
#pragma endregion


void MeshRenderer::UpdateBackground(BYTE r, BYTE g, BYTE b)
{
	int hei = m_Height;
	int wid = m_Width;
	for (int h = 0; h < hei; ++h)
	{
		for (int w = 0; w < wid; ++w)
		{
			DrawPixel(w, h, r, g, b);
		}
	}
}
bool MeshRenderer::IsBack(const Vector3& v0, const Vector3& v1, const Vector3& v2) const
{
	Vector3 e1 = v1 - v0;
	Vector3 e2 = v2 - v0;
	Vector3 N = e1.Cross(e2);
	float res = N.Dot(v0);
	//return res >= -0.001f;
	return res <= 0.001f;
}



