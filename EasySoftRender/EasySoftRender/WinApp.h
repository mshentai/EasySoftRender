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

	// ������������¼��ı�����غ���
	virtual void OnMouseDown(WPARAM btnState, int x, int y) { }
	virtual void OnMouseUp(WPARAM btnState, int x, int y) { }
	virtual void OnMouseMove(WPARAM btnState, int x, int y) { }

protected:
	bool InitMainWindow();

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
};

