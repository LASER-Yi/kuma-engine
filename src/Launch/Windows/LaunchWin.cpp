#include <windows.h>

extern void RequestEngineExit();
extern bool IsEngineExitRequested();
extern void EngineSetWindow(void* Handle);
extern void EngineInitialize(const char* CmdLine);
extern bool EngineLoop();
extern int EngineShutdown();

LRESULT CALLBACK WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch (Message)
    {
    case WM_CREATE:
    {
        EngineSetWindow(hWnd);
        EngineInitialize(nullptr);
        return 0;
    }
    case WM_PAINT:
    {
        EngineLoop();
        return 0;
    }
    case WM_DESTROY:
    {
        RequestEngineExit();
        return 0;
    }
    default:
    {
        return DefWindowProc(hWnd, Message, wParam, lParam);
    }
    }
}

int WINAPI WinMain(
    HINSTANCE hInInstance, HINSTANCE hPrevInstance, char* pCmdLine, int nCmdShow
)
{
    int Argc;
    LPWSTR* Argv = CommandLineToArgvW(GetCommandLineW(), &Argc);
    // TODO: Handle arguments
    LocalFree(Argv);

    WNDCLASSEX WindowClass = {0};
    WindowClass.cbSize = sizeof(WNDCLASSEX);
    WindowClass.style = CS_HREDRAW | CS_VREDRAW;
    WindowClass.lpfnWndProc = WndProc;
    WindowClass.hInstance = hInInstance;
    WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WindowClass.lpszClassName = "Kuma Engine";
    RegisterClassEx(&WindowClass);

    RECT WindowRect = {0, 0, 800, 600};
    AdjustWindowRect(&WindowRect, WS_OVERLAPPEDWINDOW, FALSE);

    HWND hWnd = CreateWindow(
        WindowClass.lpszClassName, "Kuma Engine", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, WindowRect.right - WindowRect.left,
        WindowRect.bottom - WindowRect.top, nullptr, nullptr, hInInstance,
        nullptr
    );

    ShowWindow(hWnd, nCmdShow);

    MSG Msg = {};
    while (Msg.message != WM_QUIT && IsEngineExitRequested() == false)
    {
        if (PeekMessage(&Msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&Msg);
            DispatchMessage(&Msg);
        }
    }

    const int Result = EngineShutdown();
    return Result;
}
