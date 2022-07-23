#include "WinApp.h"

WinApp *gApp = nullptr;

LRESULT CALLBACK MainWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return gApp->MsgProc(hWnd, msg, wParam, lParam);
}

WinApp::WinApp(HINSTANCE hInstance) : 
	mhAppInst(hInstance),
	mMainWndCaption("Easy Appliation"),
	mClientWidth(800),
	mClientHeight(600),
	mhMainWnd(NULL),
	mAppPaused(false)
{
	gApp = this;
}

HINSTANCE WinApp::AppInst() const
{
	return this->mhAppInst;
}

HWND WinApp::MainWnd() const
{
	return this->mhMainWnd;
}

bool WinApp::Init()
{
	return this->InitMainWindow();
}

void WinApp::UpdateScene(float dt)
{
}

void WinApp::DrawScene()
{
}

LRESULT WinApp::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			mAppPaused = true;
			mTimer.Stop();
		}
		else
		{
			mAppPaused = false;
			mTimer.Start();
		}
		return 0;
		// 窗口被销毁时发送 WM_DESTROY 消息
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		OnMouseDown(wParam, LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		OnMouseUp(wParam, LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_MOUSEMOVE:
		OnMouseMove(wParam, LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool WinApp::InitMainWindow()
{
	//注册窗口
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(GetStockObject(NULL_BRUSH));
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = mhAppInst;
	wc.lpfnWndProc = MainWinProc;
	wc.lpszClassName = "D3DWndClassName";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	if (!RegisterClass(&wc))
	{
		MessageBox(0, "Register Class Failed", 0, 0);
		return false;
	}
	//创建窗口
	RECT rect{ 0,0,mClientWidth,mClientHeight };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	int width = rect.right - rect.left;
	int heigth = rect.bottom - rect.top;

	mhMainWnd = CreateWindow("D3DWndClassName", mMainWndCaption.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, heigth, 0, 0, mhAppInst, 0);

	if (mhMainWnd == NULL)
	{
		MessageBox(0, "Create Window Failed", 0, 0);
		return false;
	}
	//显示窗口
	ShowWindow(mhMainWnd, SW_SHOW);
	//更新窗口
	UpdateWindow(mhMainWnd);
	return true;
}
