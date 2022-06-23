#include "RenderSystem.h"
#include "Camera.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "../Primitives/Mesh.h"
#include "ObjectManager.h"
#include "../Primitives/Material.h"
#include "Light.h"

//Background color of client Area = (bgR,bgG,bgB)
constexpr auto bgR = 128;
constexpr auto bgG = 128;
constexpr auto bgB = 128;

void RenderSystem::SetCamera(Camera * cameraPtr)
{
	m_CameraPtr = cameraPtr;
}

void RenderSystem::SetClientRect(int width, int height)
{
	m_Width = width;
	m_Height = height;
}

bool RenderSystem::OnInitialize()
{
	return OnInitialize1();
}

void RenderSystem::InitializeBuffer()
{
	m_bufferPtr = new BYTE[m_Width * m_Height * 3];
	m_CurrentBufferPtr = new BYTE[m_Width * m_Height * 3];
	m_Edge_ColorBuffer = new BYTE[m_Height * 6];
	ZeroMemory(m_Edge_ColorBuffer, m_Height * 6 * sizeof(BYTE));
	MeshRenderer::SetColorBuffer(m_Edge_ColorBuffer);
	m_Edge_XBuffer = new int[m_Height * 2];
	ZeroMemory(m_Edge_XBuffer, m_Height * 2 * sizeof(int));
	MeshRenderer::SetEdgeXBuffer(m_Edge_XBuffer);
	m_Edge_TexMapBuffer = new float[m_Height * 4];
	ZeroMemory(m_Edge_TexMapBuffer, m_Height * 4 * sizeof(float));
	MeshRenderer::SetTexMapBuffer(m_Edge_TexMapBuffer);
	m_Edge_ViewVecBuffer = new Vector3[m_Height * 2];
	ZeroMemory(m_Edge_ViewVecBuffer, m_Height * 2 * sizeof(Vector3));
	MeshRenderer::SetViewVecBuffer(m_Edge_ViewVecBuffer);
	m_Edge_DepthBuffer = new float[m_Height * 2];
	ZeroMemory(m_Edge_DepthBuffer, m_Height * sizeof(float));
	MeshRenderer::SetEdgeDepthBuffer(m_Edge_DepthBuffer);
	m_DepthBuffer = new float[m_Width * m_Height];
	ClearDepthBuffer();
	//ZeroMemory(m_DepthBuffer, m_Width * m_Height * sizeof(float));
	MeshRenderer::SetDepthBuffer(m_DepthBuffer);
	m_StencilBuffer = new BYTE[m_Width * m_Height];
	ZeroMemory(m_StencilBuffer, m_Width * m_Height * sizeof(BYTE));
	MeshRenderer::SetStencilBuffer(m_StencilBuffer);
}

void RenderSystem::ClearDepthBuffer()
{
	int len = m_Width * m_Height;
	for (int i = 0; i < len; ++i)
	{
		m_DepthBuffer[i] = 1.0f;
	}
}



bool RenderSystem::OnInitialize0()
{
	if (m_CameraPtr == nullptr)
	{
		InitializeCamera();
	}

	m_Light = new Light();
	Transform* tran_Light = new Transform();
	tran_Light->SetPosition(Vector3(100, 100, 100));
	m_Light->SetTransform(tran_Light);

	//建立场景
	CreateScence();

	//设置缓存
	InitializeBuffer();

	//如果是正交投影则缩小图形。还没实现裁剪，导致模型过大会奔溃。
	if (!m_CameraPtr->IsPerspective())
	{
		m_MeshRenderer->SetScale(0.3f);
	}

	return true;
}

bool RenderSystem::OnInitialize1()
{
	if (m_CameraPtr == nullptr)
	{
		InitializeCamera();
	}

	//建立场景
	CreateScence();

	//设置缓存
	InitializeBuffer();

	//如果是正交投影则缩小图形。还没实现裁剪，导致模型过大会奔溃。
	if (!m_CameraPtr->IsPerspective())
	{
		m_MeshRenderer->SetScale(0.2f);
	}

	return true;
}

void RenderSystem::OnTerminate()
{

}

void RenderSystem::OnIdle()
{
	ClearBuffers();
	OnIdle1();
	SwapBuffer();
}
/// <summary>
/// 
/// </summary>
/// <returns></returns>
BYTE* RenderSystem::GetBuffer()
{
	return m_CurrentBufferPtr;
}



Float4x4 RenderSystem::GetWVPMatrix(const Transform* obj_Tran, const Camera* cam) const
{
	return (obj_Tran->ObjectToWorld()) * (cam->GetViewMatrix()) * (cam->GetProjectMatrix());
}

Float4x4 RenderSystem::GetViewMatrix(const Camera * camera)
{
	return camera->GetViewMatrix();
}

void RenderSystem::DrawLine(int x0, int y0, BYTE rgb0[3], int x1, int y1, BYTE rgb1[3])
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
	//	for (int decy = ay - dx; x += sx, decy += ay)
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
	//	for (int decx = ax - dy; y += sy, decx += ax)
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

void RenderSystem::DrawLine(int y, int x0, BYTE rgb0[3], int x1, BYTE rgb1[3])
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

void XYSwap(int& x0, int& y0, int& x1, int& y1)
{
	int tmp = x0;
	x0 = x1;
	x1 = tmp;
	tmp = y0;
	y0 = y1;
	y1 = tmp;
}
void XYSwap(int& x0, int& y0, BYTE*& rgb0, int& x1, int& y1, BYTE*& rgb1)
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

void XYOrder(int& x0, int& y0, int& x1, int& y1, int& x2, int& y2)
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

void XYOrder(int& x0, int& y0, BYTE*& rgb0, int& x1, int& y1, BYTE*& rgb1, int& x2, int& y2, BYTE*& rgb2)
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

void RenderSystem::DrawTrangle(int x0, int y0, BYTE rgb0[3], int x1, int y1, BYTE rgb1[3], int x2, int y2, BYTE rgb2[3])
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

void RenderSystem::ComputeEdgeBuffers(int x0, int y0, BYTE rgb0[3], int x1, int y1, BYTE rgb1[3], bool isBuffer1)
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

bool RenderSystem::ComputeEdgeBuffers(int x0, int y0, BYTE rgb0[3], int x1, int y1, BYTE rgb1[3], int x2, int y2, BYTE rgb2[3])
{
	if ((x0 == x1 && x1 == x2) || (y0 == y1 && y1 == y2)) return false;
	ComputeEdgeBuffers(x0, y0, rgb0, x1, y1, rgb1, false);
	ComputeEdgeBuffers(x1, y1, rgb1, x2, y2, rgb2, false);
	ComputeEdgeBuffers(x0, y0, rgb0, x2, y2, rgb2, true);
	return true;
}

void RenderSystem::ComputeEdgeBuffers(int x0, int y0, int x1, int y1, bool isBuffer1)
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

bool RenderSystem::ComputeEdgeBuffers(int x0, int y0, int x1, int y1, int x2, int y2)
{
	//if ((x0 == x1 && x1 == x2) || (y0 == y1 && y1 == y2)) return false;
	ComputeEdgeBuffers(x0, y0, x1, y1, false);
	ComputeEdgeBuffers(x1, y1, x2, y2, false);
	ComputeEdgeBuffers(x0, y0, x2, y2, true);
	return true;
}

void RenderSystem::OnIdle0()
{
	if (m_RenderFlag)
	{
		UpdateBackground(bgR, bgG, bgB);
		MeshRenderer::SetBufferPtr(m_bufferPtr);
		m_MeshRenderer->Render(m_CameraPtr, m_Light);
		//GouraudShader();
		//WireframeShader();
		m_RenderFlag = false;
	}
	//m_MeshRenderer->GetTransform()->Rotate(0.0f, PI / 180.0f);
}



void RenderSystem::UpdateBackground(BYTE r, BYTE g, BYTE b)
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

void RenderSystem::UpdateBackground0(BYTE r, BYTE g, BYTE b)
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
	int halfHei = hei / 2;
	for (int w = 0; w < wid; ++w)
	{
		DrawPixel(w, halfHei, 0, 0, 0);
	}
}

void RenderSystem::SwapBuffer()
{
	BYTE* tmp = m_bufferPtr;
	m_bufferPtr = m_CurrentBufferPtr;
	m_CurrentBufferPtr = tmp;
}

bool RenderSystem::IsBack(const Vector3& v0, const Vector3& v1, const Vector3& v2) const
{
	Vector3 e1 = v1 - v0;
	Vector3 e2 = v2 - v0;
	Vector3 N = e1.Cross(e2);
	float res = N.Dot(v0);
	return res <= 0.001f;
}

std::vector<MeshRenderer*> RenderSystem::GetMeshRenderers()
{
	return m_AllMeshRenderers;
}

void RenderSystem::GouraudShader()
{
	Float4x4 WTP = GetWVPMatrix(m_MeshRenderer->GetTransform(), m_CameraPtr);
	Float4x4 Hscreen = m_CameraPtr->GetScreenMatrix(m_Width, m_Height);
	const std::vector<Triangle>& tris = m_MeshRenderer->GetMesh()->GetTriangles();
	const Vector3& pos = m_MeshRenderer->GetTransform()->GetPosition();
	for (int i = 0; i < 12; ++i)
	{
		auto v = tris[i].GetVertexes();
		Vector3 v0 = Dot((*v[0]), WTP, true);
		Vector3 v1 = Dot((*v[1]), WTP, true);
		Vector3 v2 = Dot((*v[2]), WTP, true);
		if (!IsBack(v0, v1, v2) && true)
		{
			float x = v0[0];
			float y = v0[1];
			float z = v0[2];
			float w = 1.0f / v0[3];
			Vector3 ndcV0(x * w, y * w, z * w, 1.0f);
			Vector3 screenV0 = Dot(ndcV0, Hscreen, true);
			x = v1[0];
			y = v1[1];
			z = v1[2];
			w = 1.0f / v1[3];
			Vector3 ndcV1 = Vector3(x * w, y * w, z * w, 1.0f);
			Vector3 screenV1 = Dot(ndcV1, Hscreen, true);
			x = v2[0];
			y = v2[1];
			z = v2[2];
			w = 1.0f / v2[3];
			Vector3 ndcV2 = Vector3(x * w, y * w, z * w, 1.0f);
			Vector3 screenV2 = Dot(ndcV2, Hscreen, true);
			BYTE rgb0[3]{ 255,255,255 };
			BYTE rgb1[3]{ 255,255,255 };
			BYTE rgb2[3]{ 255,255,255 };
			DrawTrangle(screenV0[0], screenV0[1], rgb0, screenV1[0], screenV1[1], rgb1, screenV2[0], screenV2[1], rgb2);
		}
		//break;
	}
}

void RenderSystem::ComputeShadowEdge(int x0, int y0, int x1, int y1, bool isBuffer1)
{
	float x = x0;
	float dy = 1.0f / (y1 - y0);
	float dx = (x1 - x0) * dy;
	int vy0 = y0;
	int vy1 = y1;
	for (int y = vy0; y <= vy1; ++y, x += dx)
	{
		SaveEdge(x, y, isBuffer1);
	}
}

bool RenderSystem::ComputeShadowEdge(int x0, int y0, int x1, int y1, int x2, int y2)
{
	//if ((x0 == x1 && x1 == x2) || (y0 == y1 && y1 == y2)) return false;
	ComputeShadowEdge(x0, y0, x1, y1, false);
	ComputeShadowEdge(x1, y1, x2, y2, false);
	ComputeShadowEdge(x0, y0, x2, y2, true);
	return true;
}

static void SwapOrder(Vector3& v0, Vector3& v1)
{
	Vector3 vtmp = v0;
	v0 = v1;
	v1 = vtmp;
}

static void SwapOrder(Vector3& v0, Vector3& v1, Vector3& v2)
{
	if (v0[1] > v1[1])
	{
		SwapOrder(v0, v1);
	}
	if (v1[1] > v2[1])
	{
		SwapOrder(v1, v2);
	}
	if (v0[1] > v1[1])
	{
		SwapOrder(v0, v1);
	}
}

void RenderSystem::DrawPlanarShadow(std::vector<MeshRenderer*>& shadowProjectors, std::vector<MeshRenderer*>& planes, Camera* cam, const Vector3& lightDir)
{
	int planeNum = planes.size();
	Float4x4 VP = (cam->GetViewMatrix()) * (cam->GetProjectMatrix());
	Float4x4 Hscreen = cam->GetScreenMatrix(m_Width, m_Height);
	for (auto plane : planes)
	{
		const std::vector<Triangle>& triangles = plane->GetMesh()->GetTriangles();
		Vector3 planePos = plane->GetTransform()->GetPosition();
		Vector3 planeNor = Dot((*(triangles[0].GetNormal()[0])), plane->GetTransform()->ObjectToWorld(), false);
		Float4x4 PVP = plane->GetPlanarMatrix(lightDir, planePos, planeNor) * VP;
		std::vector<Vector3> projPos;
		for (auto projector : shadowProjectors)
		{
			Float4x4 WPVP = projector->GetTransform()->ObjectToWorld() * PVP;
			const std::vector<Triangle>& tris = projector->GetMesh()->GetTriangles();
			int len = tris.size();
			float scale = projector->GetScale();
			const Material* materal = projector->GetMaterial();
			for (int i = 0; i < len; ++i)
			{
				auto v = tris[i].GetVertexes();
				Vector3 v0 = (*v[0]) * scale;
				Vector3 v1 = (*v[1]) * scale;
				Vector3 v2 = (*v[2]) * scale;
				Vector3 pos;
				//Vector3 p =  Dot((*v[0]), projector->GetTransform()->ObjectToWorld(),true);
				//p = Dot(p, plane->GetPlanarMatrix(lightDir, planePos, planeNor), true);
				//p = Dot(p, VP, true);
				materal->Vertex(v0, WPVP, pos);
				projPos.push_back(pos);
				materal->Vertex(v1, WPVP, pos);
				projPos.push_back(pos);
				materal->Vertex(v2, WPVP, pos);
				projPos.push_back(pos);
			}
			len = projPos.size();
			for (int i = 0; i < len; i += 3)
			{
				Vector3& v0 = projPos[i];
				Vector3& v1 = projPos[i + 1];
				Vector3& v2 = projPos[i + 2];
				float x = v0[0];
				float y = v0[1];
				float z = v0[2];
				float w = 1.0f / v0[3];
				Vector3 ndcV0(x * w, y * w, z * w, 1.0f);
				Vector3 screenV0 = Dot(ndcV0, Hscreen, true);
				x = v1[0];
				y = v1[1];
				z = v1[2];
				w = 1.0f / v1[3];
				Vector3 ndcV1 = Vector3(x * w, y * w, z * w, 1.0f);
				Vector3 screenV1 = Dot(ndcV1, Hscreen, true);
				x = v2[0];
				y = v2[1];
				z = v2[2];
				w = 1.0f / v2[3];
				Vector3 ndcV2 = Vector3(x * w, y * w, z * w, 1.0f);
				Vector3 screenV2 = Dot(ndcV2, Hscreen, true);
				SwapOrder(screenV0, screenV1, screenV2);
				int vx0 = screenV0[0];
				int vy0 = screenV0[1];
				float rvz0 = 1.0f / screenV0[2];
				int vx1 = screenV1[0];
				int vy1 = screenV1[1];
				float rvz1 = 1.0f / screenV1[2];
				int vx2 = screenV2[0];
				int vy2 = screenV2[1];
				float rvz2 = 1.0f / screenV2[2];
				float diffA = ((vy0 - vy1) * (vx2 - vx1) - (vx0 - vx1) * (vy2 - vy1));
				float diffB = ((vy1 - vy2) * (vx0 - vx2) - (vx1 - vx2) * (vy0 - vy2));
				if (ComputeShadowEdge(vx0,vy0, vx1, vy1, vx2, vy2))
				{
					int h = m_Height;
					int low = vy0 * 2;
					int hei = vy2 * 2;
					for (int y = low; y <= hei; y += 2)
					{
						//DrawLine(y >> 1, m_Edge_XBuffer[y], (m_Edge_ColorBuffer + y * 3), m_Edge_XBuffer[y + 1], (m_Edge_ColorBuffer + (y + 1) * 3));
						int firstX = m_Edge_XBuffer[y];
						int lastX = m_Edge_XBuffer[y + 1];
						if (firstX > lastX)
						{
							int tmp = firstX;
							firstX = lastX;
							lastX = tmp;
						}
						float d = 1.0f / (lastX - firstX);
						int py = (y >> 1);
						int dd = 1;
						for (int px = firstX; px <= lastX; px += dd)
						{
							float A = ((py - vy1) * (vx2 - vx1) - (px - vx1) * (vy2 - vy1));
							float B = ((py - vy2) * (vx0 - vx2) - (px - vx2) * (vy0 - vy2));
							float a = A / diffA;
							float b = B / diffB;
							float c = 1.0f - a - b;
							float rz = a * rvz0 + b * rvz1 + c * rvz2;
							float z = 1.0f / rz;
							float zbuffer = m_DepthBuffer[py * m_Width + px];
							BYTE val = (rz > zbuffer - 0.001f) ? 1 : 0;
							m_StencilBuffer[py * m_Width + px] = 1;
							//m_StencilBuffer[py * m_Width + px] =  1;
						}
					}
				}
			}
		}
		plane->DrawShadow(cam, m_Light);
	}
}

void RenderSystem::WireframeShader()
{
	Float4x4 WTP = GetWVPMatrix(m_MeshRenderer->GetTransform(), m_CameraPtr);
	Float4x4 Hscreen = m_CameraPtr->GetScreenMatrix(static_cast<float>(m_Width), static_cast<float>(m_Height));
	const std::vector<Triangle>& tris = m_MeshRenderer->GetMesh()->GetTriangles();
	for (int i = 0; i < tris.size(); ++i)
	{
		auto v = tris[i].GetVertexes();
		Vector3 v0 = Dot((*v[0]), WTP, true);
		Vector3 v1 = Dot((*v[1]), WTP, true);
		Vector3 v2 = Dot((*v[2]), WTP, true);
		if (!IsBack(v0, v1, v2) && true)
		{
			float x = v0[0];
			float y = v0[1];
			float z = v0[2];
			float w = 1.0f / v0[3];
			Vector3 ndcV0(x * w, y * w, z * w, 1.0f);
			Vector3 screenV0 = Dot(ndcV0, Hscreen, true);
			x = v1[0];
			y = v1[1];
			z = v1[2];
			w = 1.0f / v1[3];
			Vector3 ndcV1 = Vector3(x * w, y * w, z * w, 1.0f);
			Vector3 screenV1 = Dot(ndcV1, Hscreen, true);
			x = v2[0];
			y = v2[1];
			z = v2[2];
			w = 1.0f / v2[3];
			Vector3 ndcV2 = Vector3(x * w, y * w, z * w, 1.0f);
			Vector3 screenV2 = Dot(ndcV2, Hscreen, true);
			BYTE rgb0[3]{ 0,0,0 };
			DrawLine(screenV0[0], screenV0[1], rgb0, screenV1[0], screenV1[1], rgb0);
			DrawLine(screenV1[0], screenV1[1], rgb0, screenV2[0], screenV2[1], rgb0);
			DrawLine(screenV0[0], screenV0[1], rgb0, screenV2[0], screenV2[1], rgb0);
		}
	}
}

void RenderSystem::LBtnDownEvent(float arcX, float arcY)
{
	m_MeshRenderer->GetTransform()->Rotate(0, 0.008f);
	m_RenderFlag = true;
}

void RenderSystem::RBtnDownEvent(float arcX, float arcY)
{
	m_MeshRenderer->GetTransform()->Rotate(0.008f, 0);
	m_RenderFlag = true;
}

void RenderSystem::BtnMoveEvent(float x, float y)
{
	//Vector3 pos = m_MeshRenderer->GetTransform()->GetPosition();
	//pos = Vector3(pos[0] + (x - (m_Width >> 1)) / m_Width, pos[1] - (y - (m_Height >> 1)) / m_Height, pos[2]);
	//m_MeshRenderer->GetTransform()->MoveTo(pos);

}

void RenderSystem::LBtnDownMoveEvent(float x, float y)
{
	bool right = (x / m_Width) > 0.7f;
	bool left = (x / m_Width) < 0.3f;
	bool top = (y / m_Height) < 0.3f;
	bool button =  (y / m_Height) > 0.7f;
	if (left)
	{
		m_MeshRenderer->GetTransform()->Move(Vector3(-0.1f, 0.0f, 0.0f));
	}
	if (right)
	{
		m_MeshRenderer->GetTransform()->Move(Vector3(0.1f, 0.0f, 0.0f));
	}
	if (top)
	{
		m_MeshRenderer->GetTransform()->Move(Vector3(0.0f, 0.01f, 0.0f));
	}
	if (button)
	{
		m_MeshRenderer->GetTransform()->Move(Vector3(0.0f, -0.01f, 0.0f));
	}
	const Vector3& pos = m_MeshRenderer->GetTransform()->GetPosition();
	char s[256];
	sprintf_s(s, "(%f,%f,%f)\n", pos[0], pos[1], pos[2]);
	OutputDebugString(s);
	m_RenderFlag = true;
}

void RenderSystem::RBtnDownMoveEvent(float x, float y)
{
	bool top = (y / m_Height) < 0.3f;
	bool button = (y / m_Height) > 0.7f;
	if (top)
	{
		m_MeshRenderer->GetTransform()->Move(Vector3(0.0f, 0.0f, 0.1f));
	}
	if (button)
	{
		m_MeshRenderer->GetTransform()->Move(Vector3(0.0f, 0.0f, -0.1f));
	}
	const Vector3& pos = m_MeshRenderer->GetTransform()->GetPosition();
	char s[256];
	sprintf_s(s, "(%f,%f,%f)\n", pos[0], pos[1], pos[2]);
	OutputDebugString(s);
	m_RenderFlag = true;
}

void RenderSystem::ClearBuffers()
{
	ZeroMemory(m_DepthBuffer, m_Width * m_Height * sizeof(float));
	//ClearDepthBuffer();
	ZeroMemory(m_StencilBuffer, m_Width * m_Height * sizeof(BYTE));
}

void RenderSystem::OnNumKeyDown(int num)
{
	for (auto r : m_AllMeshRenderers)
	{
		r->SetRenderFunc(num);
		
	}
	m_RenderFlag = true;
}

void RenderSystem::CreateScence()
{
	m_Light = new Light();
	Transform* tran_Light = new Transform();
	tran_Light->SetPosition(Vector3(100, 100, 100));
	m_Light->SetTransform(tran_Light);

	//设置物体
	Transform* tran_Object = new Transform();
	//tran_Object->Rotate(0.0f, -PI / 2.0f);
	//tran_Object->SetRotation(0.0f, 0.0f, PI / 2.0f);
	tran_Object->SetPosition(Vector3(-0.800000f, -0.70000f, 4.00000f));
	m_MeshRenderer = new MeshRenderer();
	m_MeshRenderer->SetMesh(Mesh::GetCubeMesh());
	m_MeshRenderer->SetTransform(tran_Object);
	auto sp = Mgr::CreateSampler2D("0.bmp");
	Material* m = new Material();
	m->SetSampler2D(sp);
	MeshRenderer::SetWindowWidthAndHeight(m_Width, m_Height);
	m_MeshRenderer->SetMaterial(m);

	//设置物体2
	Transform* tran_Object1 = new Transform();
	//tran_Object->Rotate(0.0f, -PI / 2.0f);
	tran_Object1->Rotate(0.0f, PI);
	tran_Object1->SetPosition(Vector3(-0.00000f, -1.500000f, 3.50000f));
	MeshRenderer* m_MeshRenderer1 = new MeshRenderer();
	Mesh * ms = Mesh::LoadObjFile("0.obj");
	m_MeshRenderer1->SetMesh(ms);
	m_MeshRenderer1->SetTransform(tran_Object1);
	auto sp2 = Mgr::CreateSampler2D("3.bmp");
	Material* m2 = new Material();
	m2->SetSampler2D(sp2);

	//添加法线纹理
	auto norsp = Mgr::CreateSampler2D("4.bmp");
	m2->SetSamplerNor(norsp);

	m_MeshRenderer1->SetMaterial(m2);
	m_MeshRenderer1->SetScale(0.01f);


	//设置底座
	MeshRenderer* plane = new MeshRenderer();
	plane->SetMesh(Mesh::GetSquareMesh());
	Transform* plane_tran = new Transform();
	plane_tran->SetPosition(Vector3(0.0f, -1.5f, 4.5f));

	//plane_tran->SetRotation(PI / 6.0f, PI / 4.0f, 0.0f);
	plane->SetTransform(plane_tran);
	//plane->SetScale(1.0f);
	auto sp1 = Mgr::CreateSampler2D("1.bmp");
	//auto sp1 = Mgr::CreateWhiteSampler2D();
	Material* m1 = new Material();
	m1->SetSampler2D(sp1);
	plane->SetMaterial(m1);


	//建立场景
	m_AllMeshRenderers.push_back(plane);
	//m_AllMeshRenderers.push_back(m_MeshRenderer);
	m_AllMeshRenderers.push_back(m_MeshRenderer1);


	m_Planes.push_back(plane);
	//m_ShadowProjectors.push_back(m_MeshRenderer);
	m_ShadowProjectors.push_back(m_MeshRenderer1);
}

void RenderSystem::OnIdle1()
{
	if (m_RenderFlag)
	{
		UpdateBackground(bgR, bgG, bgB);
		MeshRenderer::SetBufferPtr(m_bufferPtr);
		std::vector<MeshRenderer*> needRender = GetMeshRenderers();
		//m_MeshRenderer->GetTransform()->Rotate(0.0f, 0.01f);
		for (auto mr : needRender)
		{
			mr->Render(m_CameraPtr, m_Light);
		}
		m_ShadowProjectors[0]->GetTransform()->Rotate(0.0f, 0.01f);
		//m_MeshRenderer->GetTransform()->MoveTo(Vector3(-0.000000f, -1.000000f, 3.000000f));
		//m_MeshRenderer->Render(m_CameraPtr, m_Light);
		DrawPlanarShadow(m_ShadowProjectors, m_Planes, m_CameraPtr, m_Light->GetLightDir());
		//m_RenderFlag = false;
	}
}

void RenderSystem::InitializeCamera()
{
	m_CameraPtr = new Camera();
	Transform* tran_Camera = new Transform();
	//tran_Camera->SetPosition(Vector3(5.0f / 2.0f, 3.0f, 7.0f / 2.0f));
	//tran_Camera->SetRotation(Vector3(1, 0, 0), Vector3(0, 1, 0));
	//tran_Camera->SetPosition(Vector3(5.0/2, 3.0f, 7.0/2));
	//tran_Camera->SetRotation(Vector3(-1.0f, 1.0f, 0.0f), Vector3(-1, -1, 2));
	//tran_Camera->Rotate(0.1f, 0.0f);
	m_CameraPtr->SetTransform(tran_Camera);
	m_CameraPtr->SetFrustum(PI / 3.0f, (float)m_Width / (float)m_Height, 0.95f, 10.0f);
	m_CameraPtr->SetProjectMode(true);
	m_CameraPtr->SetViewPort(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
}