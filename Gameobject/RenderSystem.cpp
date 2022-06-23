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
	if (m_CameraPtr == nullptr)
	{
		m_CameraPtr = new Camera();
		Transform* tran_Camera = new Transform();
		//tran_Camera->SetPosition(Vector3(5.0f / 2.0f, 3.0f, 7.0f / 2.0f));
		//tran_Camera->SetRotation(Vector3(-1, 1, 0), Vector3(-1, -1, 2));
		tran_Camera->SetPosition(Vector3(0, 0, 0));
		m_CameraPtr->SetTransform(tran_Camera);
		m_CameraPtr->SetFrustum(PI / 3.0f, (float)m_Width/ (float)m_Height, 1.0f, 10.0f);
		m_CameraPtr->SetProjectMode(true);
		m_CameraPtr->SetViewPort(0.0f, 1.0f, 1.0f, 0.0f);
	}

	m_Light = new Light();
	Transform* tran_Light = new Transform();
	tran_Light->SetPosition(Vector3(100, 100, 100));
	m_Light->SetTransform(tran_Light);


	Transform* tran_Object = new Transform();
	tran_Object->SetPosition(Vector3(0.0f, 0.0f, 4.0f));
	//tran_Object->SetRotation(Vector3(-1, 1, 0), Vector3(-1, -1, 2));
	//tran_Object->SetRotation(Vector3(1, 0, 0), Vector3(0, 1, 1));
	tran_Object->SetRotation(Quaternion::EulerToQuaternion(Vector3(PI / 4, PI / 3, PI / 4)));
	//tran_Object->SetRotation(Quaternion::EulerToQuaternion(Vector3(PI/4, 0, 0)));
	//tran_Object->SetRotation(Vector3(1, -1, -1), Vector3(1, 1, 1));
	m_MeshRenderer = new MeshRenderer();
	m_MeshRenderer->SetMesh(Mesh::GetCubeMesh());
	m_MeshRenderer->SetTransform(tran_Object);

	auto sp = Mgr::CreateSampler2D("E:\\TheoChou\\1.MyProjects\\Win32_Draw_Test\\Debug\\0.bmp");
	Material* m = new Material();
	m->SetSampler2D(sp);
	MeshRenderer::SetWindowWidthAndHeight(m_Width, m_Height);
	m_MeshRenderer->SetMaterial(m);

	m_bufferPtr = new BYTE[m_Width * m_Height * 3];
	m_CurrentBufferPtr = new BYTE[m_Width * m_Height * 3];
	m_Edge_ColorBuffer = new BYTE[m_Height * 6];
	ZeroMemory(m_Edge_ColorBuffer, m_Height * 6 * sizeof(BYTE));
	MeshRenderer::SetColorBuffer(m_Edge_ColorBuffer);
	m_Edge_XBuffer = new int[m_Height * 2];
	ZeroMemory(m_Edge_XBuffer, m_Height * 2 * sizeof(int));
	MeshRenderer::SetEdgeXBuffer(m_Edge_XBuffer);
	m_Edge_TexMapBuffer = new float[m_Height * 4 * sizeof(float)];
	ZeroMemory(m_Edge_TexMapBuffer, m_Height * 4 * sizeof(float));
	MeshRenderer::SetTexMapBuffer(m_Edge_TexMapBuffer);
	m_Edge_ViewVecBuffer = new Vector3[m_Height * 2 * sizeof(Vector3)];
	ZeroMemory(m_Edge_ViewVecBuffer, m_Height * 2 * sizeof(Vector3));
	MeshRenderer::SetViewVecBuffer(m_Edge_ViewVecBuffer);
	return true;
}

void RenderSystem::OnTerminate()
{

}

void RenderSystem::OnIdle()
{
	if (m_RenderFlag)
	{
		UpdateBackground(bgR, bgG, bgB);
		MeshRenderer::SetBufferPtr(m_bufferPtr);
		m_MeshRenderer->Render1(m_CameraPtr, m_Light);
		//GouraudShader();
		//WireframeShader();
		SwapBuffer();
		m_RenderFlag = false;
	}
	//m_MeshRenderer->GetTransform()->Rotate(0.0f, PI / 180.0f);
}

BYTE* RenderSystem::GetBuffer()
{
	return m_CurrentBufferPtr;
}

void RenderSystem::CreateScence()
{

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
	if ((x0 == x1 && x1 == x2) || (y0 == y1 && y1 == y2)) return false;
	ComputeEdgeBuffers(x0, y0, x1, y1, false);
	ComputeEdgeBuffers(x1, y1, x2, y2, false);
	ComputeEdgeBuffers(x0, y0, x2, y2, true);
	return true;
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
	return res >= -0.001f;
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
		Vector3 v0 = (*v[0]) * WTP;
		Vector3 v1 = (*v[1]) * WTP;
		Vector3 v2 = (*v[2]) * WTP;
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
			BYTE rgb0[3]{ 255,255,255 };
			BYTE rgb1[3]{ 255,255,255 };
			BYTE rgb2[3]{ 255,255,255 };
			DrawTrangle(screenV0[0], screenV0[1], rgb0, screenV1[0], screenV1[1], rgb1, screenV2[0], screenV2[1], rgb2);
		}
		//break;
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
		Vector3 v0 = (*v[0]) * WTP;
		Vector3 v1 = (*v[1]) * WTP;
		Vector3 v2 = (*v[2]) * WTP;
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
			BYTE rgb0[3]{ 0,0,0 };
			DrawLine(screenV0[0], screenV0[1], rgb0, screenV1[0], screenV1[1], rgb0);
			DrawLine(screenV1[0], screenV1[1], rgb0, screenV2[0], screenV2[1], rgb0);
			DrawLine(screenV0[0], screenV0[1], rgb0, screenV2[0], screenV2[1], rgb0);
		}

	}
}

void RenderSystem::LBtnDownEvent(float arcX, float arcY)
{
	m_MeshRenderer->GetTransform()->Rotate(0, PI / 18.0f);
	m_RenderFlag = true;
}

void RenderSystem::RBtnDownEvent(float arcX, float arcY)
{
	m_MeshRenderer->GetTransform()->Rotate(PI / 18.0f, 0);
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
		m_MeshRenderer->GetTransform()->Move(Vector3(0.0f, 0.1f, 0.0f));
	}
	if (button)
	{
		m_MeshRenderer->GetTransform()->Move(Vector3(0.0f, -0.1f, 0.0f));
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