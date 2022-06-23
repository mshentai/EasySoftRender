#include "WinApp.h"
constexpr auto AAStrength = 1;


WinApp *gApp = nullptr;

LRESULT CALLBACK MainWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return gApp->MsgProc(hWnd, msg, wParam, lParam);
}

WinApp::WinApp(HINSTANCE hInstance) : 
	mhAppInst(hInstance),
	mMainWndCaption("Easy Appliation"),
	mClientWidth(1000),
	mClientHeight(1000),
	mhMainWnd(NULL),
	mAppPaused(false)
{
	gApp = this;
	mTimer.Reset();
}

HINSTANCE WinApp::AppInst() const
{
	return this->mhAppInst;
}

HWND WinApp::MainWnd() const
{
	return this->mhMainWnd;
}

float WinApp::GetDeltaTime() const
{
	return mTimer.GetDeltaTime();
}

bool WinApp::Init()
{
	ZeroMemory(&bitmapinfo, sizeof(BITMAPINFO));
	SetBitmapInfo();
	HDC screen_hdc = GetDC(mhMainWnd);
	hBuffDC = CreateCompatibleDC(screen_hdc);
	hBuffBitmap = CreateCompatibleBitmap(screen_hdc, mClientWidth * AAStrength, mClientHeight * AAStrength);
	HBITMAP o = static_cast<HBITMAP>(SelectObject(hBuffDC, hBuffBitmap));
	DeleteObject(o);
	renderSys.SetClientRect(mClientWidth * AAStrength, mClientHeight * AAStrength);
	bool res = renderSys.OnInitialize() && this->InitMainWindow();
	mTimer.Start();
	return res;
}

void WinApp::UpdateScene(float dt)
{
	mTimer.Tick();
	//char s[20];
	//sprintf_s(s, "%f\n", dt);
	//OutputDebugString(s);

}

void WinApp::DrawScene()
{
	if (renderSys.IsDirty())
	{
		renderSys.OnIdle();
		BYTE* bufferPtr = renderSys.GetBuffer();
		SetDIBits(hBuffDC, hBuffBitmap, 0, mClientHeight * AAStrength, bufferPtr, &bitmapinfo, DIB_RGB_COLORS);
		RECT rect;
		GetClientRect(mhMainWnd, &rect);
		InvalidateRect(mhMainWnd, &rect, true);
		UpdateWindow(mhMainWnd);
	}
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
		//OnMouseMove(wParam, LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		if (renderSys.IsActive())
		{
			SwapBuff(hdc);
		}
		EndPaint(hWnd, &ps);
		return 0;
	}
	case WM_ERASEBKGND:
		return 0;
	case WM_KEYDOWN:
		OnKeyDown(wParam);
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

void WinApp::SwapBuff(HDC hdc)
{
	//BitBlt(hdc, 0, 0, mClientWidth, mClientHeight, hBuffDC, 0, 0, SRCCOPY);
	StretchBlt(hdc, 0, 0, mClientWidth, mClientHeight, hBuffDC, 0, 0, mClientWidth * AAStrength, mClientHeight * AAStrength, SRCCOPY);
}

void WinApp::SetBitmapInfo()
{
	bitmapinfo.bmiHeader.biBitCount = 24;      //每个像素多少位，也可直接写24(RGB)或者32(RGBA)
	bitmapinfo.bmiHeader.biCompression = BI_RGB;
	bitmapinfo.bmiHeader.biHeight = mClientHeight * AAStrength;
	bitmapinfo.bmiHeader.biPlanes = 1;
	bitmapinfo.bmiHeader.biSizeImage = 0;
	bitmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapinfo.bmiHeader.biWidth = mClientWidth * AAStrength;
}

void WinApp::AntiAliasing(BYTE* src, BYTE* dest, int width, int height)
{
	int halfWidth = width;
	int halfHeight = height;
	for (int r = 0; r < height; r += 2)
	{
		for (int c = 0; c < width; c += 2)
		{
		}
	}
}
