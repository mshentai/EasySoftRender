#pragma once
#include "GameTimer.h"
#include "../Gameobject/RenderSystem.h"

class WinApp
{
public:
	WinApp(HINSTANCE hInstance);

	HINSTANCE AppInst()const;
	HWND MainWnd()const;
	float GetDeltaTime() const;
	HDC hBuffDC;
	HBITMAP hBuffBitmap;
	BITMAPINFO bitmapinfo;

	bool Init();
	void UpdateScene(float deltaTime);
	void DrawScene();
	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	

	// ������������¼��ı�����غ���
	void OnMouseDown(WPARAM btnState, int x, int y) 
	{ 
		switch (btnState)
		{
		case MK_LBUTTON:
			//renderSys.LBtnDownEvent(x, y);
			renderSys.LBtnDownMoveEvent(x, y);
			break;
		case MK_RBUTTON:
			//renderSys.RBtnDownEvent(x, y);
			renderSys.RBtnDownMoveEvent(x, y);
			break;
		}
	}
	void OnMouseUp(WPARAM btnState, int x, int y) { }
	void OnMouseMove(WPARAM btnState, int x, int y) 
	{ 
		switch (btnState)
		{
		case MK_LBUTTON:
			renderSys.BtnMoveEvent(x, y);
			break;
		case MK_RBUTTON:
			break;
		}
	}
	void OnKeyDown(WPARAM keyCode) 
	{
		switch (keyCode)
		{
		case VK_NUMPAD0:
		case VK_NUMPAD1:
		case VK_NUMPAD2:
		case VK_NUMPAD3:
		case VK_NUMPAD4:
		case VK_NUMPAD5:
		case VK_NUMPAD6:
		case VK_NUMPAD7:
		case VK_NUMPAD8:
		case VK_NUMPAD9:
			renderSys.OnNumKeyDown(keyCode - VK_NUMPAD0);
			break;

		}
	}


protected:
	bool InitMainWindow();
	void SwapBuff(HDC hdc);
	void SetBitmapInfo();
	void AntiAliasing(BYTE* src, BYTE* dest, int width, int height);

protected:
	HINSTANCE mhAppInst;// Ӧ�ó���ʵ�����
	HWND mhMainWnd; // �����ھ��
	bool mAppPaused; // �����Ƿ�����ͣ״̬

	// ���ڼ�¼"delta-time"����Ϸʱ��(��4.3)
	GameTimer mTimer;

	//���ڱ��⡣D3DApp ��Ĭ�ϱ�����"D3D11 Application"��
	std::string mMainWndCaption;
	// ���ڵĳ�ʼ��С��D3DApp Ĭ��Ϊ 800x600��ע�⣬�����ڴ�С�����н׶θı�ʱ����ЩֵҲ����֮�ı䡣
	int mClientWidth;
	int mClientHeight;
	
	RenderSystem renderSys;
};

