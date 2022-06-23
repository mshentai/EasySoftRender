#pragma once
#include "GameTimer.h"

class WinApp
{
public:
	WinApp(HINSTANCE hInstance);

	HINSTANCE AppInst()const;
	HWND MainWnd()const;

	virtual bool Init();
	virtual void UpdateScene(float dt);
	virtual void DrawScene();
	virtual LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// 处理鼠标输入事件的便捷重载函数
	virtual void OnMouseDown(WPARAM btnState, int x, int y) { }
	virtual void OnMouseUp(WPARAM btnState, int x, int y) { }
	virtual void OnMouseMove(WPARAM btnState, int x, int y) { }

protected:
	bool InitMainWindow();

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
};

