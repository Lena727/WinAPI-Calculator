#include "MainWindow.h"

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
) {
    if (!MainWindow_RegisterClass(hInstance)) {
        MessageBoxW(NULL, L"Failed to register window class", L"Error", MB_ICONERROR);
        return 0;
    }

    HWND hWnd = MainWindow_Create(hInstance);
    if (!hWnd) {
        MessageBoxW(NULL, L"Failed to create main window", L"Error", MB_ICONERROR);
        return 0;
    }

    ShowWindow(hWnd, nShowCmd);

    return MainWindow_Run();
}
