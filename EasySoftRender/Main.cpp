#include "Reference.h"
#include"WinApp.h"
#pragma comment(lib,"../Debug/Gameobject.lib")
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WinApp app(hInstance);
	if (app.Init())
	{
		MSG msg = {};
        while (true)
        {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                if (msg.message == WM_QUIT) break;
            }
            app.UpdateScene(app.GetDeltaTime());
            app.DrawScene();
        }
	}
    return 0;
}