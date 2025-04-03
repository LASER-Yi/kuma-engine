#include <windows.h>

extern int GuardedMain(const char*);

int WINAPI WinMain(
    HINSTANCE hInInstance, HINSTANCE hPrevInstance, char* pCmdLine, int nCmdShow
)
{
    int Result = GuardedMain(nullptr);
    return Result;
}
