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
	

	// 处理鼠标输入事件的便捷重载函数
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
	HINSTANCE mhAppInst;// 应用程序实例句柄
	HWND mhMainWnd; // 主窗口句柄
	bool mAppPaused; // 程序是否处在暂停状态

	// 用于记录"delta-time"和游戏时间(§4.3)
	GameTimer mTimer;

	//窗口标题。D3DApp 的默认标题是"D3D11 Application"。
	std::string mMainWndCaption;
	// 窗口的初始大小。D3DApp 默认为 800x600。注意，当窗口大小在运行阶段改变时，这些值也会随之改变。
	int mClientWidth;
	int mClientHeight;
	
	RenderSystem renderSys;
};

