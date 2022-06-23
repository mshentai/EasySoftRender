#include "Reference.h"
#include"WinApp.h"

#ifdef _DEBUG
#pragma comment(lib,"../Debug/Gameobject.lib")
#else
#pragma comment(lib,"../Release/Gameobject.lib")
#endif

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WinApp app(hInstance);
	if (app.Init())
	{
		MSG msg = {};
        float counter = 0.0f;
        while (true)
        {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                if (msg.message == WM_QUIT) break;
            }
            float t = app.GetDeltaTime();
            counter += t;
            app.UpdateScene(t);
            //if (counter > 0.028f)
            {
                counter = 0.0f;
                app.DrawScene();
            }
        }
	}
    return 0;
}