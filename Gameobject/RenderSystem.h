#pragma once
#include "../Transfrom/Float4x4.h"
class Camera;
class Culler;
class MeshRenderer;
class Transform;
class Light;

class RenderSystem
{
	typedef unsigned char BYTE;
	//±‰¡ø
private:
	Camera * m_CameraPtr;
	Culler * m_Culler;
	MeshRenderer* m_MeshRenderer;
	Light* m_Light;
	int m_Height;
	int m_Width;
	BYTE* m_bufferPtr;
	BYTE* m_Edge_ColorBuffer;
	BYTE* m_CurrentBufferPtr;
	int* m_Edge_XBuffer;
	float* m_Edge_TexMapBuffer;
	Vector3* m_Edge_ViewVecBuffer;
	bool m_RenderFlag;
	
	
	
	//∫Ø ˝ 
public:
	RenderSystem() :
		m_CameraPtr(nullptr),
		m_Culler(nullptr),
		m_MeshRenderer(nullptr),
		m_Light(nullptr),
		m_Height(0),
		m_Width(0),
		m_bufferPtr(nullptr), 
		m_Edge_ColorBuffer(nullptr),
		m_CurrentBufferPtr(nullptr),
		m_Edge_XBuffer(nullptr),
		m_Edge_TexMapBuffer(nullptr),
		m_RenderFlag(true)
	{}
	/// <summary>
	/// Set the camera as main camera of the scene.
	/// </summary>
	/// <param name="cameraPtr">main Camera</param>
	void SetCamera(Camera * cameraPtr);
	/// <summary>
	/// using width and heigth set as width and height of client rect;
	/// </summary>
	/// <param name="width"></param>
	/// <param name="height"></param>
	void SetClientRect(int width, int height);
	/// <summary>
	/// 
	/// </summary>
	/// <returns>Initial result</returns>
	bool OnInitialize();
	void OnTerminate();
	void OnIdle();
	BYTE* GetBuffer();
	bool IsActive() { return m_bufferPtr != nullptr; }
	bool IsDirty() const { return m_RenderFlag; }
#pragma region ≤‚ ‘
	void LBtnDownEvent(float arcX, float arcY);
	void RBtnDownEvent(float arcX, float arcY);
	void BtnMoveEvent(float x, float y);
	void LBtnDownMoveEvent(float x, float y);
	void RBtnDownMoveEvent(float x, float y);
#pragma endregion


private:
	RenderSystem(const RenderSystem& other) = delete;
	void CreateScence();
	
	Float4x4 GetWVPMatrix(const Transform * obj_Tran, const Camera* cam) const;
	Float4x4 GetViewMatrix(const Camera* camera);
	
	void DrawLine(int x0, int y0, BYTE rgb0[3], int x1, int y1, BYTE rgb1[3]);
	void DrawLine(int y, int x0, BYTE rgb0[3], int x1, BYTE rgb1[3]);
	void DrawTrangle(int x0, int y0, BYTE rgb0[3], int x1, int y1, BYTE rgb1[3], int x2, int y2, BYTE rgb2[3]);
	void ComputeEdgeBuffers(int x0, int y0, BYTE rgb0[3], int x1, int y1, BYTE rgb1[3], bool isBuffer1);
	bool ComputeEdgeBuffers(int x0, int y0, BYTE rgb0[3], int x1, int y1, BYTE rgb1[3], int x2, int y2, BYTE rgb2[3]);
	void ComputeEdgeBuffers(int x0, int y0, int x1, int y1, bool isBuffer1);
	bool ComputeEdgeBuffers(int x0, int y0, int x1, int y1, int x2, int y2);
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

	void DrawPixel(int x, int y, BYTE r, BYTE g, BYTE b)
	{
		int p = (y * m_Width + x + 1) * 3;
		m_bufferPtr[p - 3] = b;//b
		m_bufferPtr[p - 2] = g;//g
		m_bufferPtr[p - 1] = r;//r
	}
	void UpdateBackground(BYTE r, BYTE g, BYTE b);

	bool IsBack(const Vector3& v0, const Vector3& v1, const Vector3& v2) const;

	void SwapBuffer();

#pragma region ≤‚ ‘
	void GouraudShader();
	void WireframeShader();
#pragma endregion


};



